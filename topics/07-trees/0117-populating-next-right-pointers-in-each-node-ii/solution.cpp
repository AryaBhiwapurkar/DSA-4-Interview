/*
 * 0117. Populating Next Right Pointers in Each Node II  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/
 *
 * Problem: Point each node's next to its right neighbour on the same level
 *          (null at the end). Any binary tree.
 *
 * Examples (output: each level via next pointers, # ends a level):
 *   [1,2,3,4,5,null,7]     -> [1,#,2,3,#,4,5,7,#]
 *   []                     -> []
 *   [1,2,3,4,null,null,5]  -> [1,#,2,3,#,4,5,#]
 *
 * Approaches:
 *   1. BFS queue                  O(n) time, O(w) space
 *   2. Dummy-node level linking ⭐ O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node *left = nullptr, *right = nullptr, *next = nullptr;
    Node(int x, Node* l = nullptr, Node* r = nullptr) : val(x), left(l), right(r) {}
};
using TreeNode = Node;                     // lets the shared level-order builder create Nodes

// ---------- Approach 1: BFS Queue ----------
Node* connectBFS(Node* root) {
    queue<Node*> q;
    if (root) q.push(root);
    while (!q.empty()) {
        int sz = q.size();
        for (int i = 0; i < sz; i++) {
            Node* n = q.front();
            q.pop();
            if (i < sz - 1) n->next = q.front();   // not across levels
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
    }
    return root;
}

// ---------- Approach 2: Dummy-Node Level Linking ⭐ ----------
Node* connect(Node* root) {
    Node* cur = root;                      // walks the current (already linked) level
    while (cur) {
        Node dummy(0);
        Node* tail = &dummy;               // builds the next level's chain
        for (; cur; cur = cur->next) {
            if (cur->left) tail = tail->next = cur->left;
            if (cur->right) tail = tail->next = cur->right;
        }
        cur = dummy.next;                  // first node of the next level
    }
    return root;
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

string levels(Node* root) {                // follow next pointers level by level
    string s = "[";
    for (Node* start = root; start;) {
        Node* nextStart = nullptr;
        for (Node* p = start; p; p = p->next) {
            s += to_string(p->val) + ",";
            if (!nextStart) nextStart = p->left ? p->left : p->right;
        }
        s += "#,";
        start = nextStart;
    }
    if (s.size() > 1) s.pop_back();        // drop the trailing comma
    return s + "]";
}

int main() {
    vector<vector<int>> tests = {{1, 2, 3, 4, 5, null, 7}, {}, {1, 2, 3, 4, null, null, 5}};
    for (auto& v : tests) {
        cout << "bfs  : " << levels(connectBFS(build(v))) << "\n";
        cout << "dummy: " << levels(connect(build(v))) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `using TreeNode = Node;` is a type alias, so helper code written for
 *   TreeNode works unchanged.
 * - A stack dummy node per level (Node dummy(0)) needs no cleanup.
 */
