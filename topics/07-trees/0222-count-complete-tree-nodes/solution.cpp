/*
 * 0222. Count Complete Tree Nodes  |  Easy  |  Trees
 * Link: https://leetcode.com/problems/count-complete-tree-nodes/
 *
 * Problem: Count the nodes of a complete binary tree in less than O(n).
 *
 * Examples (level order, null = missing):
 *   [1,2,3,4,5,6]    -> 6
 *   []               -> 0
 *   [1]              -> 1
 *   [1,2,3,4,5,6,7]  -> 7   (perfect: answered at the root)
 *   [1,2,3,4]        -> 4
 *
 * Approaches:
 *   1. Plain DFS count               O(n) time, O(h) space
 *   2. Spine heights + recursion  ⭐  O(log^2 n) time, O(log n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

// ---------- Approach 1: Plain DFS Count ----------
int countNodesDFS(TreeNode* root) {
    return root ? 1 + countNodesDFS(root->left) + countNodesDFS(root->right) : 0;
}

// ---------- Approach 2: Spine Heights + Recursion ⭐ ----------
int countNodes(TreeNode* root) {
    if (!root) return 0;
    int lh = 0, rh = 0;
    for (TreeNode* n = root; n; n = n->left) lh++;     // walk spines only: O(log n)
    for (TreeNode* n = root; n; n = n->right) rh++;
    if (lh == rh) return (1 << lh) - 1;    // perfect tree
    return 1 + countNodes(root->left) + countNodes(root->right);   // one side is perfect
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
    vector<vector<int>> tests = {{1, 2, 3, 4, 5, 6}, {}, {1}, {1, 2, 3, 4, 5, 6, 7}, {1, 2, 3, 4}};
    for (auto& v : tests) {
        TreeNode* root = build(v);
        cout << "dfs   : " << countNodesDFS(root) << "\n";
        cout << "spines: " << countNodes(root) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - (1 << h) - 1 is 2^h - 1, the size of a perfect tree with h levels.
 * - Spine walks use for loops with the node as the loop variable.
 */
