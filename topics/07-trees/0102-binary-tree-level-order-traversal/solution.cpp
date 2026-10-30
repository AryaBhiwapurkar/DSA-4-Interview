/*
 * 0102. Binary Tree Level Order Traversal  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/binary-tree-level-order-traversal/
 *
 * Problem: Return node values level by level, left to right.
 *
 * Examples (level order, null = missing):
 *   [3,9,20,null,null,15,7]  -> [[3],[9,20],[15,7]]
 *   [1]                      -> [[1]]
 *   []                       -> []
 *   [1,2,null,3]             -> [[1],[2],[3]]
 *
 * Approaches:
 *   1. BFS with level size  ⭐   O(n) time, O(w) space   <- go-to
 *   2. DFS with depth           O(n) time, O(h) space
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

// ---------- Approach 1: BFS With Level Size ⭐ ----------
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;
    queue<TreeNode*> q;
    if (root) q.push(root);
    while (!q.empty()) {
        vector<int> level;
        for (int sz = q.size(); sz > 0; sz--) {   // snapshot: exactly this level
            TreeNode* n = q.front();
            q.pop();
            level.push_back(n->val);
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
        res.push_back(level);
    }
    return res;
}

// ---------- Approach 2: DFS With Depth ----------
void dfs(TreeNode* n, int depth, vector<vector<int>>& res) {
    if (!n) return;
    if (depth == (int)res.size()) res.push_back({});   // first visit to this depth
    res[depth].push_back(n->val);
    dfs(n->left, depth + 1, res);          // left first keeps left-to-right order
    dfs(n->right, depth + 1, res);
}

vector<vector<int>> levelOrderDFS(TreeNode* root) {
    vector<vector<int>> res;
    dfs(root, 0, res);
    return res;
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

void print(const string& label, const vector<vector<int>>& v) {
    cout << label << ": [";
    for (size_t i = 0; i < v.size(); i++) {
        cout << (i ? "," : "") << "[";
        for (size_t j = 0; j < v[i].size(); j++) cout << (j ? "," : "") << v[i][j];
        cout << "]";
    }
    cout << "]\n";
}

int main() {
    vector<vector<int>> tests = {{3, 9, 20, null, null, 15, 7}, {1}, {}, {1, 2, null, 3}};
    for (auto& v : tests) {
        TreeNode* root = build(v);
        print("bfs", levelOrder(root));
        print("dfs", levelOrderDFS(root));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `for (int sz = q.size(); sz > 0; sz--)` freezes the level size.
 * - res.push_back({}) appends an empty inner vector.
 * - Nested vectors print with a small helper; there's no built-in operator<<.
 */
