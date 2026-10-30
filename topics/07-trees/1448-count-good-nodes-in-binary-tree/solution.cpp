/*
 * 1448. Count Good Nodes in Binary Tree  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/count-good-nodes-in-binary-tree/
 *
 * Problem: A node is good if no node on its root path is greater. Count them.
 *
 * Examples (level order, null = missing):
 *   [3,1,4,3,null,1,5]  -> 4
 *   [3,3,null,4,2]      -> 3
 *   [1]                 -> 1
 *   [-1,-2,-3]          -> 1   (negatives: don't start max at 0)
 *
 * Approaches:
 *   1. DFS with path max  ⭐     O(n) time, O(h) space   <- go-to
 *   2. BFS with (node, max)     O(n) time, O(w) space
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

// ---------- Approach 1: DFS With Path Max ⭐ ----------
int dfs(TreeNode* n, int mx) {
    if (!n) return 0;
    int good = n->val >= mx;               // >= : equal values are good
    mx = max(mx, n->val);
    return good + dfs(n->left, mx) + dfs(n->right, mx);
}

int goodNodes(TreeNode* root) { return dfs(root, INT_MIN); }

// ---------- Approach 2: BFS With (node, max) ----------
int goodNodesBFS(TreeNode* root) {
    int count = 0;
    queue<pair<TreeNode*, int>> q;
    if (root) q.push({root, INT_MIN});
    while (!q.empty()) {
        auto [n, mx] = q.front();
        q.pop();
        if (n->val >= mx) count++;
        int nm = max(mx, n->val);
        if (n->left) q.push({n->left, nm});
        if (n->right) q.push({n->right, nm});
    }
    return count;
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
    vector<vector<int>> tests = {{3, 1, 4, 3, null, 1, 5}, {3, 3, null, 4, 2}, {1}, {-1, -2, -3}};
    for (auto& v : tests) {
        TreeNode* root = build(v);
        cout << "dfs: " << goodNodes(root) << "\n";
        cout << "bfs: " << goodNodesBFS(root) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `int good = a >= b;` converts the bool to 0/1.
 * - Pass state down by value (int mx): each branch gets its own copy.
 */
