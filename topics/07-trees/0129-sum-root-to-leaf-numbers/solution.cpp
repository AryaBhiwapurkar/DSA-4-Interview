/*
 * 0129. Sum Root to Leaf Numbers  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/sum-root-to-leaf-numbers/
 *
 * Problem: Each root-to-leaf path of digits spells a number; sum them all.
 *
 * Examples (level order, null = missing):
 *   [1,2,3]        -> 25
 *   [4,9,0,5,1]    -> 1026
 *   [0]            -> 0
 *   [1,0]          -> 10   (one-child node: null side adds nothing)
 *
 * Approaches:
 *   1. Recursive DFS  ⭐        O(n) time, O(h) space   <- go-to
 *   2. BFS (node, number)      O(n) time, O(w) space
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

// ---------- Approach 1: Recursive DFS ⭐ ----------
int dfs(TreeNode* n, int cur) {
    if (!n) return 0;                      // null contributes nothing
    cur = cur * 10 + n->val;               // append this digit
    if (!n->left && !n->right) return cur;
    return dfs(n->left, cur) + dfs(n->right, cur);
}

int sumNumbers(TreeNode* root) { return dfs(root, 0); }

// ---------- Approach 2: BFS (node, number) ----------
int sumNumbersBFS(TreeNode* root) {
    int total = 0;
    queue<pair<TreeNode*, int>> q;
    if (root) q.push({root, root->val});
    while (!q.empty()) {
        auto [n, cur] = q.front();
        q.pop();
        if (!n->left && !n->right) total += cur;
        if (n->left) q.push({n->left, cur * 10 + n->left->val});
        if (n->right) q.push({n->right, cur * 10 + n->right->val});
    }
    return total;
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
    vector<vector<int>> tests = {{1, 2, 3}, {4, 9, 0, 5, 1}, {0}, {1, 0}};
    for (auto& v : tests) {
        TreeNode* root = build(v);
        cout << "dfs: " << sumNumbers(root) << "\n";
        cout << "bfs: " << sumNumbersBFS(root) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - cur * 10 + digit builds a number left to right.
 * - Passing cur by value gives each branch its own prefix.
 */
