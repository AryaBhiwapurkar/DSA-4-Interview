/*
 * 0235. Lowest Common Ancestor of a Binary Search Tree  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
 *
 * Problem: In a BST, return the deepest node that has both p and q as
 *          descendants (a node is its own descendant).
 *
 * Examples (level order, null = missing; answer printed as a value):
 *   [6,2,8,0,4,7,9,null,null,3,5], p 2, q 8  -> 6
 *   [6,2,8,0,4,7,9,null,null,3,5], p 2, q 4  -> 2
 *   [2,1],                         p 2, q 1  -> 2
 *   [6,2,8,0,4,7,9,null,null,3,5], p 3, q 5  -> 4
 *
 * Approaches:
 *   1. Recursive descent        O(h) time, O(h) stack
 *   2. Iterative descent  ⭐     O(h) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

// ---------- Approach 1: Recursive Descent ----------
TreeNode* lcaRecursive(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (p->val < root->val && q->val < root->val) return lcaRecursive(root->left, p, q);
    if (p->val > root->val && q->val > root->val) return lcaRecursive(root->right, p, q);
    return root;                           // split point (or root is p or q)
}

// ---------- Approach 2: Iterative Descent ⭐ ----------
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    while (root) {
        if (p->val < root->val && q->val < root->val) root = root->left;        // strict: stop on equality
        else if (p->val > root->val && q->val > root->val) root = root->right;
        else return root;
    }
    return nullptr;                        // unreachable when p and q exist
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

TreeNode* find(TreeNode* root, int v) {    // BST lookup to get the actual node
    while (root && root->val != v) root = v < root->val ? root->left : root->right;
    return root;
}

int main() {
    vector<int> big = {6, 2, 8, 0, 4, 7, 9, null, null, 3, 5};
    vector<tuple<vector<int>, int, int>> tests = {{big, 2, 8}, {big, 2, 4}, {{2, 1}, 2, 1}, {big, 3, 5}};
    for (auto& [v, a, b] : tests) {
        TreeNode* root = build(v);
        TreeNode *p = find(root, a), *q = find(root, b);
        cout << "recursive: " << lcaRecursive(root, p, q)->val << "\n";
        cout << "iterative: " << lowestCommonAncestor(root, p, q)->val << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Chained ternary for the BST step: root = v < root->val ? left : right.
 * - The driver's find() turns test values into the node pointers LeetCode passes.
 */
