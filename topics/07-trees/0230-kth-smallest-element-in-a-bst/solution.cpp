/*
 * 0230. Kth Smallest Element in a BST  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/kth-smallest-element-in-a-bst/
 *
 * Problem: Return the k-th smallest value (1-indexed) in a BST.
 *
 * Examples (level order, null = missing):
 *   [3,1,4,null,2],            k 1  -> 1
 *   [5,3,6,2,4,null,null,1],   k 3  -> 3
 *   [5,3,6,2,4,null,null,1],   k 6  -> 6
 *   [1],                       k 1  -> 1
 *
 * Approaches:
 *   1. Full inorder into a list       O(n) time, O(n) space
 *   2. Iterative inorder, stop at k ⭐ O(h + k) time, O(h) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

// ---------- Approach 1: Full Inorder Into a List ----------
void inorder(TreeNode* n, vector<int>& out) {
    if (!n) return;
    inorder(n->left, out);
    out.push_back(n->val);
    inorder(n->right, out);
}

int kthSmallestList(TreeNode* root, int k) {
    vector<int> vals;
    inorder(root, vals);
    return vals[k - 1];
}

// ---------- Approach 2: Iterative Inorder, Stop at k ⭐ ----------
int kthSmallest(TreeNode* root, int k) {
    vector<TreeNode*> st;
    TreeNode* cur = root;
    while (cur || !st.empty()) {
        while (cur) {                      // go as far left as possible
            st.push_back(cur);
            cur = cur->left;
        }
        cur = st.back();
        st.pop_back();
        if (--k == 0) return cur->val;     // k-th node in sorted order
        cur = cur->right;
    }
    return -1;                             // unreachable for valid k
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
    vector<int> t2 = {5, 3, 6, 2, 4, null, null, 1};
    vector<pair<vector<int>, int>> tests = {{{3, 1, 4, null, 2}, 1}, {t2, 3}, {t2, 6}, {{1}, 1}};
    for (auto& [v, k] : tests) {
        TreeNode* root = build(v);
        cout << "list : " << kthSmallestList(root, k) << "\n";
        cout << "stack: " << kthSmallest(root, k) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `if (--k == 0)` decrements first, then compares.
 * - Iterative inorder: inner loop pushes the left spine, then pop + go right.
 */
