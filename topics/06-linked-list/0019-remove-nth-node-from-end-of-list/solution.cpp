/*
 * 0019. Remove Nth Node From End of List  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/remove-nth-node-from-end-of-list/
 *
 * Problem: Remove the n-th node from the end and return the head.
 *          n is always valid.
 *
 * Examples:
 *   [1,2,3,4,5], n 2  -> [1,2,3,5]
 *   [1],         n 1  -> []
 *   [1,2],       n 1  -> [1]
 *   [1,2],       n 2  -> [2]
 *
 * Approaches:
 *   1. Two passes (count length)   O(L) time, O(1) space
 *   2. One pass with n-gap  ⭐      O(L) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

// ---------- Approach 1: Two Passes ----------
ListNode* removeNthFromEndTwoPass(ListNode* head, int n) {
    int len = 0;
    for (ListNode* p = head; p; p = p->next) len++;
    ListNode dummy(0, head);
    ListNode* prev = &dummy;
    for (int i = 0; i < len - n; i++) prev = prev->next;   // predecessor of the target
    prev->next = prev->next->next;
    return dummy.next;
}

// ---------- Approach 2: One Pass With n-Gap ⭐ ----------
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0, head);               // makes removing the head a normal case
    ListNode *slow = &dummy, *fast = &dummy;
    for (int i = 0; i < n; i++) fast = fast->next;   // fast leads by n
    while (fast->next) {                   // stop with fast on the LAST node
        slow = slow->next;
        fast = fast->next;
    }
    slow->next = slow->next->next;         // slow is the predecessor
    return dummy.next;
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
    vector<pair<vector<int>, int>> tests = {{{1, 2, 3, 4, 5}, 2}, {{1}, 1}, {{1, 2}, 1}, {{1, 2}, 2}};
    for (auto& [v, n] : tests) {           // fresh list per approach: removal mutates
        print("twoPass", removeNthFromEndTwoPass(build(v), n));
        print("onePass", removeNthFromEnd(build(v), n));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - ListNode dummy(0, head) constructs the dummy on the stack, already linked.
 * - Unlinking: prev->next = prev->next->next (delete the old node in real code).
 * - Return dummy.next, not head: the head may have been removed.
 */
