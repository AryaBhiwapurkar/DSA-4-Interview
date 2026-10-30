/*
 * 0138. Copy List with Random Pointer  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/copy-list-with-random-pointer/
 *
 * Problem: Deep-copy a list whose nodes have next and random pointers.
 *          Shown as [val, index of random or null].
 *
 * Examples (printed as the copy, then whether it shares no nodes with the input):
 *   [[7,null],[13,0],[11,4],[10,2],[1,0]]  -> same, deep
 *   [[1,1],[2,1]]                          -> same, deep
 *   [[3,null],[3,0],[3,null]]              -> same, deep
 *   []                                     -> [], deep
 *
 * Approaches:
 *   1. Two-pass hashmap  ⭐     O(n) time, O(n) space   <- go-to
 *   2. Interleave copies       O(n) time, O(1) extra space
 */

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node *next = nullptr, *random = nullptr;
    Node(int x) : val(x) {}
};

// ---------- Approach 1: Two-Pass Hashmap ⭐ ----------
Node* copyRandomList(Node* head) {
    unordered_map<Node*, Node*> copy = {{nullptr, nullptr}};   // null maps to null
    for (Node* p = head; p; p = p->next) copy[p] = new Node(p->val);
    for (Node* p = head; p; p = p->next) {     // all copies exist: forward randoms are safe
        copy[p]->next = copy[p->next];
        copy[p]->random = copy[p->random];
    }
    return copy[head];
}

// ---------- Approach 2: Interleave Copies ----------
Node* copyRandomListInterleave(Node* head) {
    for (Node* p = head; p; p = p->next->next) {   // A -> A' -> B -> B' ...
        Node* c = new Node(p->val);
        c->next = p->next;
        p->next = c;
    }
    for (Node* p = head; p; p = p->next->next)
        if (p->random) p->next->random = p->random->next;   // copy of random = random's next
    Node dummy(0);
    Node* tail = &dummy;
    for (Node* p = head; p; p = p->next) {     // split, restoring the original
        tail = tail->next = p->next;
        p->next = p->next->next;
    }
    return dummy.next;
}

// ---------- Driver ----------
Node* build(const vector<pair<int, int>>& spec) {   // (val, random index or -1)
    vector<Node*> nodes;
    for (auto& [v, r] : spec) nodes.push_back(new Node(v));
    for (size_t i = 0; i < nodes.size(); i++) {
        if (i + 1 < nodes.size()) nodes[i]->next = nodes[i + 1];
        if (spec[i].second >= 0) nodes[i]->random = nodes[spec[i].second];
    }
    return nodes.empty() ? nullptr : nodes[0];
}

void print(const string& label, Node* orig, Node* cp) {
    unordered_set<Node*> origNodes;
    for (Node* p = orig; p; p = p->next) origNodes.insert(p);
    unordered_map<Node*, int> idx;
    int i = 0;
    for (Node* p = cp; p; p = p->next) idx[p] = i++;
    bool deep = true;
    cout << label << ": [";
    for (Node* p = cp; p; p = p->next) {
        if (origNodes.count(p) || (p->random && origNodes.count(p->random))) deep = false;
        cout << (p == cp ? "" : ",") << "[" << p->val << ",";
        if (p->random) cout << idx[p->random]; else cout << "null";
        cout << "]";
    }
    cout << "] deep=" << (deep ? "true" : "false") << "\n";
}

int main() {
    vector<vector<pair<int, int>>> tests = {
        {{7, -1}, {13, 0}, {11, 4}, {10, 2}, {1, 0}}, {{1, 1}, {2, 1}}, {{3, -1}, {3, 0}, {3, -1}}, {}
    };
    for (auto& spec : tests) {
        Node* a = build(spec);
        print("hashmap   ", a, copyRandomList(a));
        Node* b = build(spec);
        print("interleave", b, copyRandomListInterleave(b));   // print also checks b was restored
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - unordered_map<Node*, Node*> keys on pointer identity.
 * - Seeding {nullptr, nullptr} makes copy[p->random] safe when random is null.
 * - Default member initializers: `Node *next = nullptr, *random = nullptr;`.
 * - `tail = tail->next = p->next;` appends and advances in one statement.
 */
