/*
 * 0530. Minimum Absolute Difference in BST  |  Easy  |  Trees
 * Link: https://leetcode.com/problems/minimum-absolute-difference-in-bst/
 *
 * Problem: Minimum absolute difference between values of any two nodes.
 *
 * Examples (level order, null = missing):
 *   [4,2,6,1,3]               -> 1
 *   [1,0,48,null,null,12,49]  -> 1
 *   [236,104,701,null,227,null,911]  -> 9   (closest pair 227, 236 isn't parent-child)
 *
 * Approaches:
 *   1. Inorder list + adjacent gaps   O(n) time, O(n) space
 *   2. Inorder with prev  ⭐           O(n) time, O(h) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

// ---------- Approach 1: Inorder List + Adjacent Gaps ----------
void collect(TreeNode* n, vector<int>& out) {
    if (!n) return;
    collect(n->left, out);
    out.push_back(n->val);
    collect(n->right, out);
}

int getMinimumDifferenceList(TreeNode* root) {
    vector<int> v;
    collect(root, v);
    int best = INT_MAX;
    for (size_t i = 1; i < v.size(); i++) best = min(best, v[i] - v[i - 1]);
    return best;
}

// ---------- Approach 2: Inorder With prev ⭐ ----------
void inorder(TreeNode* n, int& prev, int& best) {
    if (!n) return;
    inorder(n->left, prev, best);
    if (prev != -1) best = min(best, n->val - prev);   // -1 = none yet (values are >= 0)
    prev = n->val;
    inorder(n->right, prev, best);
}

int getMinimumDifference(TreeNode* root) {
    int prev = -1, best = INT_MAX;
    inorder(root, prev, best);
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
    vector<vector<int>> tests = {{4, 2, 6, 1, 3}, {1, 0, 48, null, null, 12, 49}, {236, 104, 701, null, 227, null, 911}};
    for (auto& v : tests) {
        TreeNode* root = build(v);
        cout << "list: " << getMinimumDifferenceList(root) << "\n";
        cout << "prev: " << getMinimumDifference(root) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Two by-reference accumulators (prev, best) thread state through recursion.
 * - -1 works as "no previous" only because values are non-negative here.
 */
