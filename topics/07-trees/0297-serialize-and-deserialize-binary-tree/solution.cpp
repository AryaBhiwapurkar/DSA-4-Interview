/*
 * 0297. Serialize and Deserialize Binary Tree  |  Hard  |  Trees
 * Link: https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
 *
 * Problem: Encode a binary tree to a string and decode it back exactly.
 *
 * Examples (round trip shown in level order, plus each codec's encoding):
 *   [1,2,3,null,null,4,5]  -> [1,2,3,null,null,4,5]
 *   []                     -> []
 *   [1]                    -> [1]
 *   [1,-2,3,null,40]       -> [1,-2,3,null,40]   (negative, multi-digit)
 *
 * Approaches:
 *   1. Preorder with null markers  ⭐   O(n) time, O(n) space   <- go-to
 *   2. BFS level order with markers    O(n) time, O(n) space
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

vector<string> split(const string& s) {
    vector<string> out;
    stringstream ss(s);
    string tok;
    while (getline(ss, tok, ',')) out.push_back(tok);
    return out;
}

// ---------- Approach 1: Preorder With Null Markers ⭐ ----------
class Codec {
    void enc(TreeNode* n, string& s) {
        if (!s.empty()) s += ',';          // delimiter: "12" vs "1","2"
        if (!n) { s += '#'; return; }      // null marker fixes the shape
        s += to_string(n->val);
        enc(n->left, s);
        enc(n->right, s);
    }
    TreeNode* dec(const vector<string>& t, size_t& i) {
        const string& tok = t[i++];
        if (tok == "#") return nullptr;
        TreeNode* n = new TreeNode(stoi(tok));
        n->left = dec(t, i);               // same order as encoding: left, then right
        n->right = dec(t, i);
        return n;
    }
public:
    string serialize(TreeNode* root) {
        string s;
        enc(root, s);
        return s;
    }
    TreeNode* deserialize(const string& data) {
        vector<string> t = split(data);
        size_t i = 0;                      // local index: codec stays stateless
        return dec(t, i);
    }
};

// ---------- Approach 2: BFS Level Order With Markers ----------
class CodecBFS {
public:
    string serialize(TreeNode* root) {
        string s;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* n = q.front();
            q.pop();
            if (!s.empty()) s += ',';
            if (!n) { s += '#'; continue; }
            s += to_string(n->val);
            q.push(n->left);
            q.push(n->right);
        }
        return s;
    }
    TreeNode* deserialize(const string& data) {
        vector<string> t = split(data);
        if (t[0] == "#") return nullptr;
        TreeNode* root = new TreeNode(stoi(t[0]));
        queue<TreeNode*> q;
        q.push(root);
        for (size_t i = 1; i < t.size(); i += 2) {   // each queued node owns the next two tokens
            TreeNode* n = q.front();
            q.pop();
            if (t[i] != "#") q.push(n->left = new TreeNode(stoi(t[i])));
            if (t[i + 1] != "#") q.push(n->right = new TreeNode(stoi(t[i + 1])));
        }
        return root;
    }
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

int main() {
    vector<vector<int>> tests = {{1, 2, 3, null, null, 4, 5}, {}, {1}, {1, -2, 3, null, 40}};
    for (auto& v : tests) {
        TreeNode* root = build(v);
        Codec a;
        CodecBFS b;
        string ea = a.serialize(root), eb = b.serialize(root);
        cout << "preorder: " << ea << " -> " << serialize(a.deserialize(ea)) << "\n";
        cout << "bfs     : " << eb << " -> " << serialize(b.deserialize(eb)) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - getline(ss, tok, ',') splits on a delimiter; stoi parses "-2".
 * - A size_t& index threads through the recursive decoder.
 * - Member serialize() shadows the free serialize() inside the class only.
 */
