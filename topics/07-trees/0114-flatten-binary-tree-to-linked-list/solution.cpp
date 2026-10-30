/*
 * 0114. Flatten Binary Tree to Linked List  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/flatten-binary-tree-to-linked-list/
 *
 * Problem: Flatten in place into a right-pointer chain in preorder;
 *          every left pointer becomes null.
 *
 * Examples (level order, null = missing):
 *   [1,2,5,3,4,null,6]  -> [1,null,2,null,3,null,4,null,5,null,6]
 *   []                  -> []
 *   [0]                 -> [0]
 *   [1,2,null,3]        -> [1,null,2,null,3]   (left chain)
 *
 * Approaches:
 *   1. Preorder list, relink         O(n) time, O(n) space
 *   2. Reverse preorder with prev    O(n) time, O(h) stack
 *   3. In-place splicing  ⭐          O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

// ---------- Approach 1: Preorder List, Relink ----------
void pre(TreeNode* n, vector<TreeNode*>& out) {
    if (!n) return;
    out.push_back(n);
    pre(n->left, out);
    pre(n->right, out);
}

void flattenList(TreeNode* root) {
    vector<TreeNode*> nodes;
    pre(root, nodes);
    for (size_t i = 0; i < nodes.size(); i++) {
        nodes[i]->left = nullptr;
        nodes[i]->right = i + 1 < nodes.size() ? nodes[i + 1] : nullptr;
    }
}

// ---------- Approach 2: Reverse Preorder With prev ----------
void rev(TreeNode* n, TreeNode*& prev) {
    if (!n) return;
    rev(n->right, prev);                   // right, left, node = reverse preorder
    rev(n->left, prev);
    n->right = prev;
    n->left = nullptr;
    prev = n;
}

void flattenReverse(TreeNode* root) {
    TreeNode* prev = nullptr;
    rev(root, prev);
}

// ---------- Approach 3: In-Place Splicing ⭐ ----------
void flatten(TreeNode* root) {
    for (TreeNode* cur = root; cur; cur = cur->right) {
        if (!cur->left) continue;
        TreeNode* pred = cur->left;        // rightmost of the left subtree precedes cur->right
        while (pred->right) pred = pred->right;
        pred->right = cur->right;
        cur->right = cur->left;
        cur->left = nullptr;
    }
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
    vector<vector<int>> tests = {{1, 2, 5, 3, 4, null, 6}, {}, {0}, {1, 2, null, 3}};
    for (auto& v : tests) {                // fresh tree per approach: flattening mutates
        TreeNode *a = build(v), *b = build(v), *c = build(v);
        flattenList(a);
        flattenReverse(b);
        flatten(c);
        cout << "list   : " << serialize(a) << "\n";
        cout << "reverse: " << serialize(b) << "\n";
        cout << "splice : " << serialize(c) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - TreeNode*& prev passes a pointer by reference so recursion can update it.
 * - The splice loop advances with cur = cur->right, which now holds the old left.
 */
