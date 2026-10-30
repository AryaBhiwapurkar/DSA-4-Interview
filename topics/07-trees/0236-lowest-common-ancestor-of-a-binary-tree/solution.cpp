/*
 * 0236. Lowest Common Ancestor of a Binary Tree  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
 *
 * Problem: LCA of two distinct nodes p, q in a general binary tree.
 *
 * Examples (level order, null = missing; answer printed as a value):
 *   [3,5,1,6,2,0,8,null,null,7,4], p 5, q 1  -> 3
 *   [3,5,1,6,2,0,8,null,null,7,4], p 5, q 4  -> 5
 *   [1,2],                         p 1, q 2  -> 1
 *   [3,5,1,6,2,0,8,null,null,7,4], p 7, q 8  -> 3
 *
 * Approaches:
 *   1. Parent pointers + ancestor set   O(n) time, O(n) space
 *   2. Recursive postorder  ⭐           O(n) time, O(h) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

// ---------- Approach 1: Parent Pointers + Ancestor Set ----------
TreeNode* lcaParents(TreeNode* root, TreeNode* p, TreeNode* q) {
    unordered_map<TreeNode*, TreeNode*> parent = {{root, nullptr}};
    vector<TreeNode*> st = {root};
    while (!parent.count(p) || !parent.count(q)) {   // stop once both are mapped
        TreeNode* n = st.back();
        st.pop_back();
        for (TreeNode* c : {n->left, n->right})
            if (c) { parent[c] = n; st.push_back(c); }
    }
    unordered_set<TreeNode*> anc;
    for (TreeNode* a = p; a; a = parent[a]) anc.insert(a);
    for (TreeNode* b = q;; b = parent[b])
        if (anc.count(b)) return b;
}

// ---------- Approach 2: Recursive Postorder ⭐ ----------
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;   // found one (or nothing)
    TreeNode* L = lowestCommonAncestor(root->left, p, q);
    TreeNode* R = lowestCommonAncestor(root->right, p, q);
    if (L && R) return root;               // p and q on different sides
    return L ? L : R;                      // pass up whichever side found something
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

TreeNode* findVal(TreeNode* n, int v) {    // locate the node LeetCode would pass
    if (!n || n->val == v) return n;
    TreeNode* l = findVal(n->left, v);
    return l ? l : findVal(n->right, v);
}

int main() {
    vector<int> big = {3, 5, 1, 6, 2, 0, 8, null, null, 7, 4};
    vector<tuple<vector<int>, int, int>> tests = {{big, 5, 1}, {big, 5, 4}, {{1, 2}, 1, 2}, {big, 7, 8}};
    for (auto& [v, a, b] : tests) {
        TreeNode* root = build(v);
        TreeNode *p = findVal(root, a), *q = findVal(root, b);
        cout << "parents  : " << lcaParents(root, p, q)->val << "\n";
        cout << "postorder: " << lowestCommonAncestor(root, p, q)->val << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Compare node pointers (root == p), not values: identity is what matters.
 * - `for (TreeNode* c : {n->left, n->right})` iterates both children.
 * - An endless for(;;) loop that always returns satisfies the compiler.
 */
