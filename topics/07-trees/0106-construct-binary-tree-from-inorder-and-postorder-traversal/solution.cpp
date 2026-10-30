/*
 * 0106. Construct Binary Tree from Inorder and Postorder Traversal  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
 *
 * Problem: Rebuild a tree (unique values) from its inorder and postorder.
 *
 * Examples (output in level order):
 *   in [9,3,15,20,7], post [9,15,7,20,3]  -> [3,9,20,null,null,15,7]
 *   in [-1],          post [-1]           -> [-1]
 *   in [1,2,3],       post [3,2,1]        -> [1,null,2,null,3]   (right-skewed)
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
TreeNode* buildTreeSlice(vector<int> in, vector<int> post) {
    if (post.empty()) return nullptr;
    int rootVal = post.back();
    int mid = find(in.begin(), in.end(), rootVal) - in.begin();   // O(n) search
    TreeNode* root = new TreeNode(rootVal);
    root->left = buildTreeSlice(vector<int>(in.begin(), in.begin() + mid),
                                vector<int>(post.begin(), post.begin() + mid));
    root->right = buildTreeSlice(vector<int>(in.begin() + mid + 1, in.end()),
                                 vector<int>(post.begin() + mid, post.end() - 1));
    return root;
}

// ---------- Approach 2: Index Ranges + Hashmap ⭐ ----------
TreeNode* build(const vector<int>& post, int& idx, int lo, int hi, unordered_map<int, int>& pos) {
    if (lo > hi) return nullptr;
    int val = post[idx--];                 // postorder read backwards: root, right..., left...
    TreeNode* root = new TreeNode(val);
    int mid = pos[val];
    root->right = build(post, idx, mid + 1, hi, pos);   // RIGHT first
    root->left = build(post, idx, lo, mid - 1, pos);
    return root;
}

TreeNode* buildTree(const vector<int>& inorder, const vector<int>& postorder) {
    unordered_map<int, int> pos;
    for (int i = 0; i < (int)inorder.size(); i++) pos[inorder[i]] = i;
    int idx = postorder.size() - 1;
    return build(postorder, idx, 0, inorder.size() - 1, pos);
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
        {{9, 3, 15, 20, 7}, {9, 15, 7, 20, 3}}, {{-1}, {-1}}, {{1, 2, 3}, {3, 2, 1}}
    };
    for (auto& [in, post] : tests) {
        cout << "slice: " << serialize(buildTreeSlice(in, post)) << "\n";
        cout << "map  : " << serialize(buildTree(in, post)) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - post[idx--] reads then decrements: walking postorder from the end.
 * - post.end() - 1 drops the root (last element) from the right slice.
 */
