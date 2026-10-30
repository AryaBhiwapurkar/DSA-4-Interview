/*
 * 0108. Convert Sorted Array to Binary Search Tree  |  Easy  |  Trees
 * Link: https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
 *
 * Problem: Build a height-balanced BST from a sorted array of distinct ints.
 *          Any balanced BST is accepted.
 *
 * Examples (output in level order; left-middle choice, so it differs from
 * LeetCode's printed answer but is equally valid):
 *   [-10,-3,0,5,9]  -> [0,-10,5,null,-3,null,9]   (LC shows [0,-3,9,-10,null,5])
 *   [1,3]           -> [1,null,3]                 (LC shows [3,1])
 *   [1]             -> [1]
 *
 * Approaches:
 *   1. Recursive middle split  ⭐        O(n) time, O(log n) stack   <- go-to
 *   2. Iterative stack of (node, lo, hi) O(n) time, O(log n) space
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

// ---------- Approach 1: Recursive Middle Split ⭐ ----------
TreeNode* go(const vector<int>& a, int lo, int hi) {
    if (lo > hi) return nullptr;
    int mid = lo + (hi - lo) / 2;          // middle -> halves differ by at most 1
    return new TreeNode(a[mid], go(a, lo, mid - 1), go(a, mid + 1, hi));
}

TreeNode* sortedArrayToBST(const vector<int>& nums) { return go(nums, 0, nums.size() - 1); }

// ---------- Approach 2: Iterative Stack of (node, lo, hi) ----------
TreeNode* sortedArrayToBSTIter(const vector<int>& a) {
    if (a.empty()) return nullptr;
    auto mid = [](int lo, int hi) { return lo + (hi - lo) / 2; };
    int n = a.size();
    TreeNode* root = new TreeNode(a[mid(0, n - 1)]);
    vector<tuple<TreeNode*, int, int>> st = {{root, 0, n - 1}};
    while (!st.empty()) {
        auto [node, lo, hi] = st.back();
        st.pop_back();
        int m = mid(lo, hi);
        if (lo <= m - 1) {                 // left range non-empty
            node->left = new TreeNode(a[mid(lo, m - 1)]);
            st.push_back({node->left, lo, m - 1});
        }
        if (m + 1 <= hi) {
            node->right = new TreeNode(a[mid(m + 1, hi)]);
            st.push_back({node->right, m + 1, hi});
        }
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
    vector<vector<int>> tests = {{-10, -3, 0, 5, 9}, {1, 3}, {1}};
    for (auto& v : tests) {
        cout << "recursive: " << serialize(sortedArrayToBST(v)) << "\n";
        cout << "iterative: " << serialize(sortedArrayToBSTIter(v)) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - The TreeNode(val, left, right) constructor builds a subtree in one expression.
 * - A small lambda (mid) keeps the midpoint formula identical in both places.
 * - tuple + structured bindings for (node, lo, hi) stack entries.
 */
