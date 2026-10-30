/*
 * 0199. Binary Tree Right Side View  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/binary-tree-right-side-view/
 *
 * Problem: Values visible from the right side, top to bottom.
 *
 * Examples (level order, null = missing):
 *   [1,2,3,null,5,null,4]        -> [1,3,4]
 *   [1,2,3,4,null,null,null,5]   -> [1,3,4,5]
 *   [1,null,3]                   -> [1,3]
 *   []                           -> []
 *
 * Approaches:
 *   1. BFS, last per level  ⭐   O(n) time, O(w) space   <- go-to
 *   2. DFS right-first          O(n) time, O(h) space
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

// ---------- Approach 1: BFS, Last per Level ⭐ ----------
vector<int> rightSideView(TreeNode* root) {
    vector<int> res;
    queue<TreeNode*> q;
    if (root) q.push(root);
    while (!q.empty()) {
        int sz = q.size();
        for (int i = 0; i < sz; i++) {
            TreeNode* n = q.front();
            q.pop();
            if (i == sz - 1) res.push_back(n->val);   // rightmost of this level
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
    }
    return res;
}

// ---------- Approach 2: DFS Right-First ----------
void dfs(TreeNode* n, int depth, vector<int>& res) {
    if (!n) return;
    if (depth == (int)res.size()) res.push_back(n->val);   // first node seen at this depth
    dfs(n->right, depth + 1, res);         // right first
    dfs(n->left, depth + 1, res);
}

vector<int> rightSideViewDFS(TreeNode* root) {
    vector<int> res;
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

void print(const string& label, const vector<int>& v) {
    cout << label << ": [";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << v[i];
    cout << "]\n";
}

int main() {
    vector<vector<int>> tests = {{1, 2, 3, null, 5, null, 4}, {1, 2, 3, 4, null, null, null, 5}, {1, null, 3}, {}};
    for (auto& v : tests) {
        TreeNode* root = build(v);
        print("bfs", rightSideView(root));
        print("dfs", rightSideViewDFS(root));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Store sz in a variable when the loop body also needs it (i == sz - 1).
 * - depth == res.size() marks the first visit to a new depth.
 */
