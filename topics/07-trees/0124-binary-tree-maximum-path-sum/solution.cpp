/*
 * 0124. Binary Tree Maximum Path Sum  |  Hard  |  Trees
 * Link: https://leetcode.com/problems/binary-tree-maximum-path-sum/
 *
 * Problem: Maximum sum of any non-empty path (connected nodes, each used
 *          once, not necessarily through the root).
 *
 * Examples (level order, null = missing):
 *   [1,2,3]                    -> 6
 *   [-10,9,20,null,null,15,7]  -> 42
 *   [-3]                       -> -3   (all negative)
 *   [2,-1]                     -> 2
 *
 * Approaches:
 *   1. Every node as top, recomputing gains   O(n^2) time, O(h) space
 *   2. Single DFS, global max  ⭐              O(n) time, O(h) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

// ---------- Approach 1: Every Node as Top ----------
int down(TreeNode* n) {                    // best path starting at n going down
    if (!n) return 0;
    return n->val + max({0, down(n->left), down(n->right)});
}

int maxPathSumBrute(TreeNode* root) {
    if (!root) return INT_MIN;
    int here = root->val + max(0, down(root->left)) + max(0, down(root->right));
    return max({here, maxPathSumBrute(root->left), maxPathSumBrute(root->right)});
}

// ---------- Approach 2: Single DFS, Global Max ⭐ ----------
int gain(TreeNode* n, int& best) {
    if (!n) return 0;
    int L = max(0, gain(n->left, best));   // a negative branch is never worth taking
    int R = max(0, gain(n->right, best));
    best = max(best, n->val + L + R);      // path bending at n
    return n->val + max(L, R);             // parent can extend only one side
}

int maxPathSum(TreeNode* root) {
    int best = INT_MIN;                    // not 0: all-negative trees
    gain(root, best);
    return best;
}

// ---------- Driver ----------
const int null = INT_MIN;                  // marks a missing node in level-order input

TreeNode* build(const vector<int>& v) {    // LeetCode level order
    if (v.empty() || v[0] == null) return nullptr;
    TreeNode* root = new TreeNode(v[0]);
    queue<TreeNode*> q;
    q.push(root);
    for (size_t i = 1; i < v.size(); i += 2) {
        TreeNode* n = q.front();
        q.pop();
        if (v[i] != null) q.push(n->left = new TreeNode(v[i]));
        if (i + 1 < v.size() && v[i + 1] != null) q.push(n->right = new TreeNode(v[i + 1]));
    }
    return root;
}

string serialize(TreeNode* root) {         // level order, trailing nulls trimmed
    vector<string> out;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* n = q.front();
        q.pop();
        out.push_back(n ? to_string(n->val) : "null");
        if (n) { q.push(n->left); q.push(n->right); }
    }
    while (!out.empty() && out.back() == "null") out.pop_back();
    string s = "[";
    for (size_t i = 0; i < out.size(); i++) s += (i ? "," : "") + out[i];
    return s + "]";
}

int main() {
    vector<vector<int>> tests = {{1, 2, 3}, {-10, 9, 20, null, null, 15, 7}, {-3}, {2, -1}};
    for (auto& v : tests) {
        TreeNode* root = build(v);
        cout << "brute : " << maxPathSumBrute(root) << "\n";
        cout << "global: " << maxPathSum(root) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - max({0, a, b}) picks the largest of three in one call.
 * - INT_MIN as the starting best; sums stay within int (3e4 * 1000).
 */
