/*
 * 0445. Add Two Numbers II  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/add-two-numbers-ii/
 *
 * Problem: Add two numbers stored most-significant-digit first;
 *          return the sum in the same format.
 *
 * Examples:
 *   [7,2,4,3] + [5,6,4]   -> [7,8,0,7]
 *   [2,4,3]   + [5,6,4]   -> [8,0,7]
 *   [0]       + [0]       -> [0]
 *   [9,9]     + [1]       -> [1,0,0]
 *   [5]       + [5]       -> [1,0]
 *
 * Approaches:
 *   1. Reverse, add (LC 2), reverse   O(m + n) time, O(1) extra (mutates input)
 *   2. Two stacks + prepend  ⭐        O(m + n) time, O(m + n) space   <- go-to
 *   3. Pad + recursion                O(m + n) time, O(m + n) stack
 */

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

// ---------- Approach 1: Reverse, Add, Reverse ----------
ListNode* reverseList(ListNode* h) {
    ListNode* prev = nullptr;
    while (h) { ListNode* nx = h->next; h->next = prev; prev = h; h = nx; }
    return prev;
}

ListNode* addTwoNumbersReverse(ListNode* l1, ListNode* l2) {
    l1 = reverseList(l1); l2 = reverseList(l2);          // note: mutates the input
    ListNode dummy;
    ListNode* t = &dummy;
    int carry = 0;
    for (ListNode *a = l1, *b = l2; a || b || carry;) {
        int s = carry + (a ? a->val : 0) + (b ? b->val : 0);
        t = t->next = new ListNode(s % 10);
        carry = s / 10;
        if (a) a = a->next;
        if (b) b = b->next;
    }
    return reverseList(dummy.next);
}

// ---------- Approach 2: Two Stacks + Prepend ⭐ ----------
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    stack<int> s1, s2;
    for (; l1; l1 = l1->next) s1.push(l1->val);
    for (; l2; l2 = l2->next) s2.push(l2->val);
    ListNode* head = nullptr;
    int carry = 0;
    while (!s1.empty() || !s2.empty() || carry) {          // carry may add a leading 1
        int s = carry;
        if (!s1.empty()) { s += s1.top(); s1.pop(); }
        if (!s2.empty()) { s += s2.top(); s2.pop(); }
        head = new ListNode(s % 10, head);                  // prepend: no final reverse
        carry = s / 10;
    }
    return head;
}

// ---------- Approach 3: Pad + Recursion ----------
int length(ListNode* p) { int n = 0; for (; p; p = p->next) n++; return n; }

// a and b have the same remaining length; returns the carry out of this position
int addSame(ListNode* a, ListNode* b, ListNode*& head) {
    if (!a) return 0;
    int s = a->val + b->val + addSame(a->next, b->next, head);
    head = new ListNode(s % 10, head);
    return s / 10;
}

ListNode* addTwoNumbersRecursive(ListNode* l1, ListNode* l2) {
    int n1 = length(l1), n2 = length(l2);
    for (; n1 < n2; n1++) l1 = new ListNode(0, l1);        // pad with leading zeros
    for (; n2 < n1; n2++) l2 = new ListNode(0, l2);
    ListNode* head = nullptr;
    int carry = addSame(l1, l2, head);
    return carry ? new ListNode(carry, head) : head;
}

// ---------- Driver ----------
ListNode* build(const vector<int>& v) {
    ListNode dummy;
    ListNode* t = &dummy;
    for (int x : v) t = t->next = new ListNode(x);
    return dummy.next;
}

string str(ListNode* p) {
    string s = "[";
    for (; p; p = p->next) s += to_string(p->val) + (p->next ? "," : "");
    return s + "]";
}

int main() {
    vector<pair<vector<int>, vector<int>>> tests = {
        {{7, 2, 4, 3}, {5, 6, 4}}, {{2, 4, 3}, {5, 6, 4}}, {{0}, {0}}, {{9, 9}, {1}}, {{5}, {5}}};
    for (auto& [a, b] : tests) {
        cout << "reverse  : " << str(addTwoNumbersReverse(build(a), build(b))) << "\n";
        cout << "stacks   : " << str(addTwoNumbers(build(a), build(b))) << "\n";
        cout << "recursive: " << str(addTwoNumbersRecursive(build(a), build(b))) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - std::stack: top() reads, pop() removes (pop returns void).
 * - new ListNode(d, head) prepends in one expression.
 * - ListNode*& head lets the recursion prepend into the caller's pointer.
 */
