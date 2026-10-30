/*
 * 0100. Same Tree  |  Easy  |  Trees
 * Link: https://leetcode.com/problems/same-tree/
 *
 * Problem: Are two binary trees identical in structure and values?
 *
 * Examples (level order, null = missing):
 *   [1,2,3], [1,2,3]        -> true
 *   [1,2],   [1,null,2]     -> false
 *   [1,2,1], [1,1,2]        -> false
 *   [],      []             -> true
 *   [1],     []             -> false
 *
 * Approaches:
 *   1. Recursive parallel DFS  ⭐   O(n) time, O(h) space   <- go-to
 *   2. Queue of pairs              O(n) time, O(w) space
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

// ---------- Approach 1: Recursive Parallel DFS ⭐ ----------
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;
    if (!p || !q) return false;            // exactly one is null
    return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

// ---------- Approach 2: Queue of Pairs ----------
bool isSameTreeBFS(TreeNode* p, TreeNode* q) {
    queue<pair<TreeNode*, TreeNode*>> qu;
    qu.push({p, q});
    while (!qu.empty()) {
        auto [a, b] = qu.front();
        qu.pop();
        if (!a && !b) continue;
        if (!a || !b || a->val != b->val) return false;
        qu.push({a->left, b->left});
        qu.push({a->right, b->right});
    }
    return true;
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
        {{1, 2, 3}, {1, 2, 3}}, {{1, 2}, {1, null, 2}}, {{1, 2, 1}, {1, 1, 2}}, {{}, {}}, {{1}, {}}
    };
    cout << boolalpha;
    for (auto& [a, b] : tests) {
        TreeNode *p = build(a), *q = build(b);
        cout << "dfs: " << isSameTree(p, q) << "\n";
        cout << "bfs: " << isSameTreeBFS(p, q) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `!p || !q` after `!p && !q` means "exactly one is null".
 * - queue<pair<TreeNode*, TreeNode*>> + structured bindings for paired BFS.
 */
