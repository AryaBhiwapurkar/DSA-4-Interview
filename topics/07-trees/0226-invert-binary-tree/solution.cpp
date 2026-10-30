/*
 * 0226. Invert Binary Tree  |  Easy  |  Trees
 * Link: https://leetcode.com/problems/invert-binary-tree/
 *
 * Problem: Mirror a binary tree (swap left/right at every node).
 *
 * Examples (level order, null = missing):
 *   [4,2,7,1,3,6,9]  -> [4,7,2,9,6,3,1]
 *   [2,1,3]          -> [2,3,1]
 *   []               -> []
 *   [1,2]            -> [1,null,2]
 *
 * Approaches:
 *   1. Recursive DFS  ⭐   O(n) time, O(h) space   <- go-to
 *   2. Iterative BFS      O(n) time, O(w) space
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

// ---------- Approach 1: Recursive DFS ⭐ ----------
TreeNode* invertTree(TreeNode* root) {
    if (!root) return nullptr;
    swap(root->left, root->right);         // swap first, then recurse: no overwrite bug
    invertTree(root->left);
    invertTree(root->right);
    return root;
}

// ---------- Approach 2: Iterative BFS ----------
TreeNode* invertTreeBFS(TreeNode* root) {
    queue<TreeNode*> q;
    if (root) q.push(root);
    while (!q.empty()) {
        TreeNode* n = q.front();
        q.pop();
        swap(n->left, n->right);
        if (n->left) q.push(n->left);
        if (n->right) q.push(n->right);
    }
    return root;
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
    vector<vector<int>> tests = {{4, 2, 7, 1, 3, 6, 9}, {2, 1, 3}, {}, {1, 2}};
    for (auto& v : tests) {                // fresh tree per approach: inversion mutates
        cout << "dfs: " << serialize(invertTree(build(v))) << "\n";
        cout << "bfs: " << serialize(invertTreeBFS(build(v))) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - std::swap(a, b) swaps two pointers in place.
 * - `q.push(n->left = new TreeNode(x))` assigns, then pushes the new pointer.
 * - INT_MIN as a "null" marker keeps test input a plain vector<int>.
 */
