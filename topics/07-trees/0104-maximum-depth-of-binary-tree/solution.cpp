/*
 * 0104. Maximum Depth of Binary Tree  |  Easy  |  Trees
 * Link: https://leetcode.com/problems/maximum-depth-of-binary-tree/
 *
 * Problem: Number of nodes on the longest root-to-leaf path.
 *
 * Examples (level order, null = missing):
 *   [3,9,20,null,null,15,7]  -> 3
 *   [1,null,2]               -> 2
 *   []                       -> 0
 *   [1]                      -> 1
 *
 * Approaches:
 *   1. Recursive DFS  ⭐   O(n) time, O(h) space   <- go-to
 *   2. BFS level count    O(n) time, O(w) space
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

// ---------- Approach 1: Recursive DFS ⭐ ----------
int maxDepth(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

// ---------- Approach 2: BFS Level Count ----------
int maxDepthBFS(TreeNode* root) {
    if (!root) return 0;
    queue<TreeNode*> q;
    q.push(root);
    int depth = 0;
    while (!q.empty()) {
        depth++;
        for (int sz = q.size(); sz > 0; sz--) {   // exactly one level per iteration
            TreeNode* n = q.front();
            q.pop();
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
    }
    return depth;
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
    vector<vector<int>> tests = {{3, 9, 20, null, null, 15, 7}, {1, null, 2}, {}, {1}};
    for (auto& v : tests) {
        TreeNode* root = build(v);
        cout << "dfs: " << maxDepth(root) << "\n";
        cout << "bfs: " << maxDepthBFS(root) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `for (int sz = q.size(); sz > 0; sz--)` freezes the level size before
 *   children are pushed.
 * - max(a, b) needs both arguments of the same type.
 */
