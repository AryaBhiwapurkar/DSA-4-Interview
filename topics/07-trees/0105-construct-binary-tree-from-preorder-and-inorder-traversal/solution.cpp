/*
 * 0105. Construct Binary Tree from Preorder and Inorder Traversal  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
 *
 * Problem: Rebuild a tree (unique values) from its preorder and inorder.
 *
 * Examples (output in level order):
 *   pre [3,9,20,15,7], in [9,3,15,20,7]  -> [3,9,20,null,null,15,7]
 *   pre [-1],          in [-1]           -> [-1]
 *   pre [1,2,3],       in [3,2,1]        -> [1,2,null,3]   (left-skewed)
 *
 * Approaches:
 *   1. Slice + linear search         O(n^2) time, O(n^2) space
 *   2. Index ranges + hashmap  ⭐     O(n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

// ---------- Approach 1: Slice + Linear Search ----------
TreeNode* buildTreeSlice(vector<int> pre, vector<int> in) {
    if (pre.empty()) return nullptr;
    int mid = find(in.begin(), in.end(), pre[0]) - in.begin();   // O(n) search
    TreeNode* root = new TreeNode(pre[0]);
    root->left = buildTreeSlice(vector<int>(pre.begin() + 1, pre.begin() + 1 + mid),
                                vector<int>(in.begin(), in.begin() + mid));
    root->right = buildTreeSlice(vector<int>(pre.begin() + 1 + mid, pre.end()),
                                 vector<int>(in.begin() + mid + 1, in.end()));
    return root;
}

// ---------- Approach 2: Index Ranges + Hashmap ⭐ ----------
TreeNode* build(const vector<int>& pre, int& idx, int lo, int hi, unordered_map<int, int>& pos) {
    if (lo > hi) return nullptr;
    int val = pre[idx++];                  // next preorder value is this subtree's root
    TreeNode* root = new TreeNode(val);
    int mid = pos[val];
    root->left = build(pre, idx, lo, mid - 1, pos);    // LEFT first: preorder order
    root->right = build(pre, idx, mid + 1, hi, pos);
    return root;
}

TreeNode* buildTree(const vector<int>& preorder, const vector<int>& inorder) {
    unordered_map<int, int> pos;           // value -> inorder index
    for (int i = 0; i < (int)inorder.size(); i++) pos[inorder[i]] = i;
    int idx = 0;
    return build(preorder, idx, 0, inorder.size() - 1, pos);
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
    vector<pair<vector<int>, vector<int>>> tests = {
        {{3, 9, 20, 15, 7}, {9, 3, 15, 20, 7}}, {{-1}, {-1}}, {{1, 2, 3}, {3, 2, 1}}
    };
    for (auto& [pre, in] : tests) {
        cout << "slice: " << serialize(buildTreeSlice(pre, in)) << "\n";
        cout << "map  : " << serialize(buildTree(pre, in)) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - vector<int>(b, e) copies a sub-range (that copying is why approach 1 is O(n^2)).
 * - A shared index passed by reference (int& idx) consumes preorder in order.
 * - The level-order build() helper overloads by signature with the recursive build().
 */
