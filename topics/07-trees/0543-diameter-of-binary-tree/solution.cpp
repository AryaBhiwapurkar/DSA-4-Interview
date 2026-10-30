/*
 * 0543. Diameter of Binary Tree  |  Easy  |  Trees
 * Link: https://leetcode.com/problems/diameter-of-binary-tree/
 *
 * Problem: Number of edges on the longest path between any two nodes.
 *
 * Examples (level order, null = missing):
 *   [1,2,3,4,5]                     -> 3
 *   [1,2]                           -> 1
 *   [1]                             -> 0
 *   [1,2,null,3,4,5,null,null,6]    -> 4   (longest path avoids the root)
 *
 * Approaches:
 *   1. Height per node                O(n^2) time, O(h) space
 *   2. Single DFS, global max  ⭐      O(n) time, O(h) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

// ---------- Approach 1: Height Per Node ----------
int height(TreeNode* n) { return n ? 1 + max(height(n->left), height(n->right)) : 0; }

int diameterOfBinaryTreeBrute(TreeNode* root) {
    if (!root) return 0;
    int through = height(root->left) + height(root->right);
    return max({through, diameterOfBinaryTreeBrute(root->left), diameterOfBinaryTreeBrute(root->right)});
}

// ---------- Approach 2: Single DFS, Global Max ⭐ ----------
int dfs(TreeNode* n, int& best) {          // returns height in nodes
    if (!n) return 0;
    int L = dfs(n->left, best), R = dfs(n->right, best);
    best = max(best, L + R);               // path bending here, in edges
    return 1 + max(L, R);                  // parent can only use one branch
}

int diameterOfBinaryTree(TreeNode* root) {
    int best = 0;
    dfs(root, best);
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
    vector<vector<int>> tests = {{1, 2, 3, 4, 5}, {1, 2}, {1}, {1, 2, null, 3, 4, 5, null, null, 6}};
    for (auto& v : tests) {
        TreeNode* root = build(v);
        cout << "brute : " << diameterOfBinaryTreeBrute(root) << "\n";
        cout << "global: " << diameterOfBinaryTree(root) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Pass the running answer by reference (int& best) instead of a global.
 * - max({a, b, c}) takes an initializer list for 3+ values.
 */
