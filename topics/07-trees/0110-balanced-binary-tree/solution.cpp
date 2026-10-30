/*
 * 0110. Balanced Binary Tree  |  Easy  |  Trees
 * Link: https://leetcode.com/problems/balanced-binary-tree/
 *
 * Problem: Is every node's left/right subtree height difference <= 1?
 *
 * Examples (level order, null = missing):
 *   [3,9,20,null,null,15,7]                -> true
 *   [1,2,2,3,3,null,null,4,4]              -> false
 *   []                                     -> true
 *   [1,2,2,3,null,null,3,4,null,null,4]    -> false  (root looks balanced, subtrees aren't)
 *
 * Approaches:
 *   1. Top-down heights              O(n^2) time, O(h) space
 *   2. Bottom-up with -1 sentinel ⭐  O(n) time, O(h) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

// ---------- Approach 1: Top-Down Heights ----------
int height(TreeNode* n) { return n ? 1 + max(height(n->left), height(n->right)) : 0; }

bool isBalancedTopDown(TreeNode* root) {
    if (!root) return true;
    return abs(height(root->left) - height(root->right)) <= 1 &&
           isBalancedTopDown(root->left) && isBalancedTopDown(root->right);
}

// ---------- Approach 2: Bottom-Up With -1 Sentinel ⭐ ----------
int check(TreeNode* n) {                   // height, or -1 if unbalanced
    if (!n) return 0;
    int L = check(n->left);
    if (L == -1) return -1;                // propagate failure immediately
    int R = check(n->right);
    if (R == -1 || abs(L - R) > 1) return -1;
    return 1 + max(L, R);
}

bool isBalanced(TreeNode* root) { return check(root) != -1; }

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
    vector<vector<int>> tests = {
        {3, 9, 20, null, null, 15, 7}, {1, 2, 2, 3, 3, null, null, 4, 4}, {}, {1, 2, 2, 3, null, null, 3, 4, null, null, 4}
    };
    cout << boolalpha;
    for (auto& v : tests) {
        TreeNode* root = build(v);
        cout << "topDown : " << isBalancedTopDown(root) << "\n";
        cout << "bottomUp: " << isBalanced(root) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - abs(int) from <cstdlib> (included by bits/stdc++.h).
 * - A sentinel return value (-1) avoids returning a pair.
 */
