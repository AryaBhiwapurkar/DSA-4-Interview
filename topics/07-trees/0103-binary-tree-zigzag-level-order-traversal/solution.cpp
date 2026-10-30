/*
 * 0103. Binary Tree Zigzag Level Order Traversal  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
 *
 * Problem: Level order, alternating left-to-right and right-to-left.
 *
 * Examples (level order, null = missing):
 *   [3,9,20,null,null,15,7]  -> [[3],[20,9],[15,7]]
 *   [1]                      -> [[1]]
 *   []                       -> []
 *   [1,2,3,4,null,null,5]    -> [[1],[3,2],[4,5]]
 *
 * Approaches:
 *   1. BFS + index by direction  ⭐   O(n) time, O(w) space   <- go-to
 *   2. BFS + reverse odd levels       O(n) time, O(w) space
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

// ---------- Approach 1: BFS + Index by Direction ⭐ ----------
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> res;
    queue<TreeNode*> q;
    if (root) q.push(root);
    bool leftToRight = true;
    while (!q.empty()) {
        int sz = q.size();
        vector<int> level(sz);
        for (int i = 0; i < sz; i++) {
            TreeNode* n = q.front();
            q.pop();
            level[leftToRight ? i : sz - 1 - i] = n->val;   // BFS order stays normal
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
        res.push_back(level);
        leftToRight = !leftToRight;
    }
    return res;
}

// ---------- Approach 2: BFS + Reverse Odd Levels ----------
vector<vector<int>> zigzagLevelOrderReverse(TreeNode* root) {
    vector<vector<int>> res;
    queue<TreeNode*> q;
    if (root) q.push(root);
    while (!q.empty()) {
        vector<int> level;
        for (int sz = q.size(); sz > 0; sz--) {
            TreeNode* n = q.front();
            q.pop();
            level.push_back(n->val);
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
        if (res.size() % 2 == 1) reverse(level.begin(), level.end());
        res.push_back(level);
    }
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
    vector<vector<int>> tests = {{3, 9, 20, null, null, 15, 7}, {1}, {}, {1, 2, 3, 4, null, null, 5}};
    for (auto& v : tests) {
        TreeNode* root = build(v);
        print("index  ", zigzagLevelOrder(root));
        print("reverse", zigzagLevelOrderReverse(root));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - vector<int> level(sz) pre-sizes so you can write by index.
 * - reverse(b, e) flips a vector in place.
 */
