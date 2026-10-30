/*
 * 0173. Binary Search Tree Iterator  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/binary-search-tree-iterator/
 *
 * Problem: Iterator over a BST in ascending order: next() and hasNext(),
 *          O(1) average time and O(h) memory.
 *
 * Examples:
 *   [7,3,15,null,null,9,20]: next, next, hasNext, next, hasNext, next, hasNext, next, hasNext
 *     -> [null,3,7,true,9,true,15,true,20,false]
 *   [1]: hasNext, next, hasNext
 *     -> [null,true,1,false]
 *
 * Approaches:
 *   1. Flatten to an array      O(n) init, O(1) next, O(n) space
 *   2. Controlled stack  ⭐      O(1) amortized next, O(h) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

// ---------- Approach 1: Flatten to an Array ----------
class BSTIteratorArray {
    vector<int> vals;
    size_t i = 0;
    void inorder(TreeNode* n) {
        if (!n) return;
        inorder(n->left);
        vals.push_back(n->val);
        inorder(n->right);
    }
public:
    BSTIteratorArray(TreeNode* root) { inorder(root); }
    int next() { return vals[i++]; }
    bool hasNext() { return i < vals.size(); }
};

// ---------- Approach 2: Controlled Stack ⭐ ----------
class BSTIterator {
    vector<TreeNode*> st;                  // pending left spine: at most h nodes
    void pushLeft(TreeNode* n) {
        for (; n; n = n->left) st.push_back(n);
    }
public:
    BSTIterator(TreeNode* root) { pushLeft(root); }
    int next() {
        TreeNode* n = st.back();
        st.pop_back();
        pushLeft(n->right);                // successor lives in the right subtree's left spine
        return n->val;
    }
    bool hasNext() { return !st.empty(); }
};

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

template <class It>
void run(const string& label, const vector<int>& tree, const vector<string>& ops) {
    It it(build(tree));
    cout << label << ": [null" << boolalpha;
    for (size_t i = 1; i < ops.size(); i++) {
        if (ops[i] == "next") cout << "," << it.next();
        else cout << "," << it.hasNext();
    }
    cout << "]\n";
}

int main() {
    vector<pair<vector<int>, vector<string>>> tests = {
        {{7, 3, 15, null, null, 9, 20},
         {"BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"}},
        {{1}, {"BSTIterator", "hasNext", "next", "hasNext"}},
    };
    for (auto& [tree, ops] : tests) {
        run<BSTIteratorArray>("array", tree, ops);
        run<BSTIterator>("stack", tree, ops);
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `for (; n; n = n->left)` walks a spine with no init clause.
 * - Default member initializer `size_t i = 0;` avoids a constructor init list.
 * - A function template run<It>() drives both iterator classes.
 */
