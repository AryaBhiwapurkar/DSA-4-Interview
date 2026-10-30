/*
 * 0572. Subtree of Another Tree  |  Easy  |  Trees
 * Link: https://leetcode.com/problems/subtree-of-another-tree/
 *
 * Problem: Does subRoot appear in root as a complete subtree?
 *
 * Examples (level order, null = missing):
 *   [3,4,5,1,2],                         [4,1,2]  -> true
 *   [3,4,5,1,2,null,null,null,null,0],   [4,1,2]  -> false
 *   [12],                                [2]      -> false  (delimiter check)
 *   [1,1],                               [1]      -> true
 *
 * Approaches:
 *   1. DFS + same tree  ⭐          O(m*n) time, O(h) space   <- go-to
 *   2. Serialize + substring        O(m+n) with KMP, O(m+n) space
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

// ---------- Approach 1: DFS + Same Tree ⭐ ----------
bool same(TreeNode* a, TreeNode* b) {
    if (!a || !b) return a == b;
    return a->val == b->val && same(a->left, b->left) && same(a->right, b->right);
}

bool isSubtree(TreeNode* root, TreeNode* subRoot) {
    if (!root) return false;
    return same(root, subRoot) || isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}

// ---------- Approach 2: Serialize + Substring ----------
void pre(TreeNode* n, string& s) {
    if (!n) { s += ",#"; return; }         // null marker keeps shapes distinct
    s += "," + to_string(n->val);          // leading comma: "2" can't match inside "12"
    pre(n->left, s);
    pre(n->right, s);
}

bool isSubtreeSerialize(TreeNode* root, TreeNode* subRoot) {
    string a, b;
    pre(root, a);
    pre(subRoot, b);
    return a.find(b) != string::npos;      // string::find is fine here; KMP for guaranteed O(m+n)
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
        {{3, 4, 5, 1, 2}, {4, 1, 2}}, {{3, 4, 5, 1, 2, null, null, null, null, 0}, {4, 1, 2}}, {{12}, {2}}, {{1, 1}, {1}}
    };
    cout << boolalpha;
    for (auto& [a, b] : tests) {
        TreeNode *r = build(a), *s = build(b);
        cout << "dfs      : " << isSubtree(r, s) << "\n";
        cout << "serialize: " << isSubtreeSerialize(r, s) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `if (!a || !b) return a == b;` covers all three null cases in one line.
 * - string::find returns npos when the pattern is absent.
 * - Building into a string& avoids repeated concatenation copies.
 */
