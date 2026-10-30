/*
 * 0101. Symmetric Tree  |  Easy  |  Trees
 * Link: https://leetcode.com/problems/symmetric-tree/
 *
 * Problem: Is the tree a mirror image of itself?
 *
 * Examples (level order, null = missing):
 *   [1,2,2,3,4,4,3]          -> true
 *   [1,2,2,null,3,null,3]    -> false
 *   [1]                      -> true
 *   [1,2,3]                  -> false
 *
 * Approaches:
 *   1. Recursive mirror check  ⭐   O(n) time, O(h) space   <- go-to
 *   2. Queue of pairs              O(n) time, O(w) space
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

// ---------- Approach 1: Recursive Mirror Check ⭐ ----------
bool mirror(TreeNode* a, TreeNode* b) {
    if (!a && !b) return true;
    if (!a || !b) return false;
    return a->val == b->val && mirror(a->left, b->right) && mirror(a->right, b->left);   // crossed
}

bool isSymmetric(TreeNode* root) {
    return !root || mirror(root->left, root->right);
}

// ---------- Approach 2: Queue of Pairs ----------
bool isSymmetricBFS(TreeNode* root) {
    if (!root) return true;
    queue<pair<TreeNode*, TreeNode*>> q;
    q.push({root->left, root->right});
    while (!q.empty()) {
        auto [a, b] = q.front();
        q.pop();
        if (!a && !b) continue;
        if (!a || !b || a->val != b->val) return false;
        q.push({a->left, b->right});       // outer pair
        q.push({a->right, b->left});       // inner pair
    }
    return true;
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
    vector<vector<int>> tests = {{1, 2, 2, 3, 4, 4, 3}, {1, 2, 2, null, 3, null, 3}, {1}, {1, 2, 3}};
    cout << boolalpha;
    for (auto& v : tests) {
        TreeNode* root = build(v);
        cout << "dfs: " << isSymmetric(root) << "\n";
        cout << "bfs: " << isSymmetricBFS(root) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `!root || mirror(...)` handles the empty tree in one expression.
 * - The only change from Same Tree is the crossed recursive arguments.
 */
