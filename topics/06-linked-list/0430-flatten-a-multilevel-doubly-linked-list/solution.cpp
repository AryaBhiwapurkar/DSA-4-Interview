/*
 * 0430. Flatten a Multilevel Doubly Linked List  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/
 *
 * Problem: Nodes have prev/next/child. Flatten so each child list sits between
 *          its parent and the parent's old next; clear all child pointers.
 *          (Input uses LeetCode's level format; N = null.)
 *
 * Examples:
 *   [1,2,3,4,5,6,N,N,N,7,8,9,10,N,N,11,12]   -> [1,2,3,7,8,11,12,9,10,4,5,6]
 *   [1,2,N,3]                                -> [1,3,2]
 *   []                                       -> []
 *   [1,N,2,N,3]                              -> [1,2,3]      (child chain)
 *   [1,2,3,N,N,N,4]                          -> [1,2,3,4]    (child on the last node)
 *
 * Approaches:
 *   1. Collect in pre-order, then relink   O(n) time, O(n) space
 *   2. Recursive DFS returning the tail    O(n) time, O(depth) stack
 *   3. Iterative splice  ⭐                 O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node *prev = nullptr, *next = nullptr, *child = nullptr;
    explicit Node(int v) : val(v) {}
};

// ---------- Approach 1: Collect in Pre-order, then Relink ----------
Node* flattenCollect(Node* head) {
    vector<Node*> order;
    vector<Node*> st;
    if (head) st.push_back(head);
    while (!st.empty()) {
        Node* n = st.back(); st.pop_back();
        order.push_back(n);
        if (n->next) st.push_back(n->next);    // next is visited after the child
        if (n->child) st.push_back(n->child);
    }
    for (size_t i = 0; i < order.size(); i++) {
        order[i]->prev = i ? order[i - 1] : nullptr;
        order[i]->next = i + 1 < order.size() ? order[i + 1] : nullptr;
        order[i]->child = nullptr;
    }
    return head;
}

// ---------- Approach 2: Recursive DFS Returning the Tail ----------
Node* flattenTail(Node* node) {               // flattens from node; returns the last node
    Node* last = node;
    while (node) {
        Node* nxt = node->next;
        if (node->child) {
            Node* childTail = flattenTail(node->child);
            node->next = node->child;
            node->child->prev = node;
            node->child = nullptr;
            childTail->next = nxt;
            if (nxt) nxt->prev = childTail;
            last = childTail;
        } else {
            last = node;
        }
        node = nxt;
    }
    return last;
}

Node* flattenRecursive(Node* head) {
    flattenTail(head);
    return head;
}

// ---------- Approach 3: Iterative Splice ⭐ ----------
Node* flatten(Node* head) {
    for (Node* cur = head; cur; cur = cur->next) {
        if (!cur->child) continue;
        Node* tail = cur->child;
        while (tail->next) tail = tail->next;  // each level's tail is searched once
        tail->next = cur->next;
        if (cur->next) cur->next->prev = tail;
        cur->next = cur->child;
        cur->child->prev = cur;
        cur->child = nullptr;
    }
    return head;
}

// ---------- Driver ----------
const int N = INT_MIN;                          // stands for null in the level format

Node* build(const vector<int>& tok) {
    Node* head = nullptr;
    vector<Node*> prevLevel;
    size_t i = 0;
    while (i < tok.size()) {
        int skip = 0;
        while (i < tok.size() && tok[i] == N) { skip++; i++; }
        vector<Node*> level;
        while (i < tok.size() && tok[i] != N) {
            Node* n = new Node(tok[i++]);
            if (!level.empty()) { level.back()->next = n; n->prev = level.back(); }
            level.push_back(n);
        }
        if (prevLevel.empty()) head = level[0];
        else prevLevel[skip - 1]->child = level[0];   // first null closes the previous level
        prevLevel = level;
    }
    return head;
}

string str(Node* head) {                       // also checks prev links and cleared children
    string s = "[";
    bool ok = true;
    for (Node* p = head; p; p = p->next) {
        s += to_string(p->val) + (p->next ? "," : "");
        if (p->child || (p->next && p->next->prev != p)) ok = false;
    }
    if (head && head->prev) ok = false;
    return s + "]" + (ok ? " links ok" : " LINKS BROKEN");
}

int main() {
    vector<vector<int>> tests = {
        {1, 2, 3, 4, 5, 6, N, N, N, 7, 8, 9, 10, N, N, 11, 12}, {1, 2, N, 3}, {}, {1, N, 2, N, 3}, {1, 2, 3, N, N, N, 4}};
    for (auto& t : tests) {
        cout << "collect  : " << str(flattenCollect(build(t))) << "\n";
        cout << "recursive: " << str(flattenRecursive(build(t))) << "\n";
        cout << "splice   : " << str(flatten(build(t))) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Default member initialisers (Node *prev = nullptr, ...) keep the constructor short.
 * - A vector used as a stack: push_back / back / pop_back.
 * - continue skips nodes without a child, keeping the splice un-nested.
 */
