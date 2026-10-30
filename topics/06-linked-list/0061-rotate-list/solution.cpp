/*
 * 0061. Rotate List  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/rotate-list/
 *
 * Problem: Rotate a linked list to the right by k places. k can be huge.
 *
 * Examples:
 *   [1,2,3,4,5], k 2   -> [4,5,1,2,3]
 *   [0,1,2],     k 4   -> [2,0,1]
 *   [],          k 0   -> []
 *   [1],         k 99  -> [1]
 *   [1,2],       k 2   -> [1,2]
 *
 * Approaches:
 *   1. Rotate one step, (k mod n) times   O(n * (k mod n)) time, O(1) space
 *   2. Ring and cut  ⭐                    O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

// ---------- Approach 1: Rotate One Step at a Time ----------
ListNode* rotateRightSteps(ListNode* head, int k) {
    if (!head || !head->next) return head;
    int n = 0;
    for (ListNode* p = head; p; p = p->next) n++;
    for (int s = 0; s < k % n; s++) {      // without % n, k = 2e9 never finishes
        ListNode* prev = head;
        while (prev->next->next) prev = prev->next;   // second-to-last
        ListNode* last = prev->next;
        prev->next = nullptr;
        last->next = head;
        head = last;
    }
    return head;
}

// ---------- Approach 2: Ring and Cut ⭐ ----------
ListNode* rotateRight(ListNode* head, int k) {
    if (!head) return head;
    int n = 1;
    ListNode* tail = head;
    while (tail->next) { tail = tail->next; n++; }
    k %= n;                                // n > 0 here: safe
    if (k == 0) return head;               // check BEFORE making the ring
    tail->next = head;                     // close the ring
    ListNode* newTail = head;
    for (int i = 0; i < n - k - 1; i++) newTail = newTail->next;
    ListNode* newHead = newTail->next;
    newTail->next = nullptr;               // cut the ring
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
    vector<pair<vector<int>, int>> tests = {{{1, 2, 3, 4, 5}, 2}, {{0, 1, 2}, 4}, {{}, 0}, {{1}, 99}, {{1, 2}, 2}};
    for (auto& [v, k] : tests) {
        print("steps", rotateRightSteps(build(v), k));
        print("ring ", rotateRight(build(v), k));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - k %= n is k = k % n; only valid when n != 0.
 * - `while (prev->next->next)` finds the second-to-last node (needs n >= 2).
 * - Count the length starting at n = 1 when the loop starts on the head.
 */
