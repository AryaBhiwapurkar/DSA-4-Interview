/*
 * 0206. Reverse Linked List  |  Easy  |  Linked List
 * Link: https://leetcode.com/problems/reverse-linked-list/
 *
 * Problem: Reverse a singly linked list and return the new head.
 *
 * Examples:
 *   [1,2,3,4,5]  -> [5,4,3,2,1]
 *   [1,2]        -> [2,1]
 *   []           -> []
 *   [1]          -> [1]
 *
 * Approaches:
 *   1. Copy values, rebuild     O(n) time, O(n) space
 *   2. Iterative  ⭐             O(n) time, O(1) space   <- go-to
 *   3. Recursive                O(n) time, O(n) stack
 */

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

// ---------- Approach 1: Copy Values, Rebuild ----------
ListNode* reverseListCopy(ListNode* head) {
    ListNode* res = nullptr;
    for (ListNode* p = head; p; p = p->next) res = new ListNode(p->val, res);   // prepend each value
    return res;
}

// ---------- Approach 2: Iterative ⭐ ----------
ListNode* reverseList(ListNode* head) {
    ListNode *prev = nullptr, *curr = head;
    while (curr) {
        ListNode* nxt = curr->next;        // save BEFORE rewiring
        curr->next = prev;
        prev = curr;
        curr = nxt;
    }
    return prev;                           // old tail
}

// ---------- Approach 3: Recursive ----------
ListNode* reverseListRecursive(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode* newHead = reverseListRecursive(head->next);
    head->next->next = head;               // the node after me now points back to me
    head->next = nullptr;                  // otherwise a 2-node cycle remains
    return newHead;
}

// ---------- Driver ----------
ListNode* build(const vector<int>& v) {
    ListNode dummy;
    ListNode* tail = &dummy;
    for (int x : v) tail = tail->next = new ListNode(x);
    return dummy.next;
}

void print(const string& label, ListNode* head) {
    cout << label << ": [";
    for (ListNode* p = head; p; p = p->next) cout << p->val << (p->next ? "," : "");
    cout << "]\n";
}

int main() {
    vector<vector<int>> tests = {{1, 2, 3, 4, 5}, {1, 2}, {}, {1}};
    for (auto& v : tests) {                // fresh list per approach: reversal mutates
        print("copy     ", reverseListCopy(build(v)));
        print("iterative", reverseList(build(v)));
        print("recursive", reverseListRecursive(build(v)));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Declaring two pointers: `ListNode *prev = nullptr, *curr = head;`
 *   (the * binds to each name, not the type).
 * - `tail = tail->next = new ListNode(x)` assigns right to left.
 * - A stack-allocated dummy node (ListNode dummy;) avoids a head special case.
 * - Nodes are leaked here for brevity; real code would delete them.
 */
