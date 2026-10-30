/*
 * 0098. Validate Binary Search Tree  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/validate-binary-search-tree/
 *
 * Problem: Is the tree a BST (left subtree strictly less, right strictly
 *          greater, at every node)?
 *
 * Examples (level order, null = missing):
 *   [2,1,3]                   -> true
 *   [5,1,4,null,null,3,6]     -> false
 *   [5,4,6,null,null,3,7]     -> false  (3 violates the grandparent 5)
 *   [2,2,2]                   -> false  (duplicates)
 *   [2147483647]              -> true   (no INT_MAX sentinels)
 *
 * Approaches:
 *   1. Inorder strictly increasing   O(n) time, O(h) space
 *   2. DFS with bounds  ⭐            O(n) time, O(h) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

// ---------- Approach 1: Inorder Strictly Increasing ----------
bool inorder(TreeNode* n, long long& prev) {
    if (!n) return true;
    if (!inorder(n->left, prev)) return false;
    if (n->val <= prev) return false;      // must strictly increase
    prev = n->val;
    return inorder(n->right, prev);
}

bool isValidBSTInorder(TreeNode* root) {
    long long prev = LLONG_MIN;            // 64-bit: below every int value
    return inorder(root, prev);
}

// ---------- Approach 2: DFS With Bounds ⭐ ----------
bool valid(TreeNode* n, long long lo, long long hi) {   // open interval (lo, hi)
    if (!n) return true;
    if (n->val <= lo || n->val >= hi) return false;
    return valid(n->left, lo, n->val) && valid(n->right, n->val, hi);
}

bool isValidBST(TreeNode* root) { return valid(root, LLONG_MIN, LLONG_MAX); }

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
    vector<vector<int>> tests = {
        {2, 1, 3}, {5, 1, 4, null, null, 3, 6}, {5, 4, 6, null, null, 3, 7}, {2, 2, 2}, {2147483647}
    };
    cout << boolalpha;
    for (auto& v : tests) {
        TreeNode* root = build(v);
        cout << "inorder: " << isValidBSTInorder(root) << "\n";
        cout << "bounds : " << isValidBST(root) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - long long bounds (LLONG_MIN/LLONG_MAX) sit outside the int range, so a
 *   node equal to INT_MAX/INT_MIN is still allowed.
 * - Passing prev by reference shares it across the whole inorder walk.
 */
