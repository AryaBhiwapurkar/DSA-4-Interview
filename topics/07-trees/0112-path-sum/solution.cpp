/*
 * 0112. Path Sum  |  Easy  |  Trees
 * Link: https://leetcode.com/problems/path-sum/
 *
 * Problem: Is there a root-to-leaf path whose values sum to targetSum?
 *
 * Examples (level order, null = missing):
 *   [5,4,8,11,null,13,4,7,2,null,null,null,1], 22  -> true
 *   [1,2,3], 5                                     -> false
 *   [], 0                                          -> false
 *   [1,2], 1                                       -> false  (root isn't a leaf)
 *   [-2,null,-3], -5                               -> true
 *
 * Approaches:
 *   1. Recursive DFS  ⭐                 O(n) time, O(h) space   <- go-to
 *   2. Iterative stack (node, remaining) O(n) time, O(h) space
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

// ---------- Approach 1: Recursive DFS ⭐ ----------
bool hasPathSum(TreeNode* root, int target) {
    if (!root) return false;
    if (!root->left && !root->right) return target == root->val;   // only leaves end paths
    return hasPathSum(root->left, target - root->val) || hasPathSum(root->right, target - root->val);
}

// ---------- Approach 2: Iterative Stack ----------
bool hasPathSumIter(TreeNode* root, int target) {
    vector<pair<TreeNode*, int>> st;
    if (root) st.push_back({root, target});
    while (!st.empty()) {
        auto [n, rem] = st.back();
        st.pop_back();
        if (!n->left && !n->right && rem == n->val) return true;
        if (n->left) st.push_back({n->left, rem - n->val});
        if (n->right) st.push_back({n->right, rem - n->val});
    }
    return false;
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
    vector<pair<vector<int>, int>> tests = {
        {{5, 4, 8, 11, null, 13, 4, 7, 2, null, null, null, 1}, 22}, {{1, 2, 3}, 5}, {{}, 0}, {{1, 2}, 1}, {{-2, null, -3}, -5}
    };
    cout << boolalpha;
    for (auto& [v, t] : tests) {
        TreeNode* root = build(v);
        cout << "dfs  : " << hasPathSum(root, t) << "\n";
        cout << "stack: " << hasPathSumIter(root, t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Leaf test: !n->left && !n->right.
 * - `||` short-circuits: the right subtree is skipped once the left succeeds.
 */
