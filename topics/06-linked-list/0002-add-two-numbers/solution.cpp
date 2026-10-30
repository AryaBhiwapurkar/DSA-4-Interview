/*
 * 0002. Add Two Numbers  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/add-two-numbers/
 *
 * Problem: Two numbers stored as digit lists, ones digit first. Return
 *          their sum in the same format.
 *
 * Examples:
 *   [2,4,3],         [5,6,4]    -> [7,0,8]
 *   [0],             [0]        -> [0]
 *   [9,9,9,9,9,9,9], [9,9,9,9]  -> [8,9,9,9,0,0,0,1]
 *   [5],             [5]        -> [0,1]
 *   [1,8],           [0]        -> [1,8]
 *
 * Approaches:
 *   1. Iterative with carry  ⭐   O(max(m,n)) time, O(1) extra space   <- go-to
 *   2. Recursive                 O(max(m,n)) time, O(max(m,n)) stack
 */

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

// ---------- Approach 1: Iterative With Carry ⭐ ----------
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode dummy;
    ListNode* tail = &dummy;
    int carry = 0;
    while (l1 || l2 || carry) {            // carry keeps the loop alive for the last digit
        int sum = carry;
        if (l1) { sum += l1->val; l1 = l1->next; }
        if (l2) { sum += l2->val; l2 = l2->next; }
        tail = tail->next = new ListNode(sum % 10);
        carry = sum / 10;
    }
    return dummy.next;
}

// ---------- Approach 2: Recursive ----------
ListNode* addTwoNumbersRecursive(ListNode* l1, ListNode* l2, int carry = 0) {
    if (!l1 && !l2 && !carry) return nullptr;
    int sum = carry + (l1 ? l1->val : 0) + (l2 ? l2->val : 0);
    return new ListNode(sum % 10, addTwoNumbersRecursive(l1 ? l1->next : nullptr,
                                                         l2 ? l2->next : nullptr, sum / 10));
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
    vector<pair<vector<int>, vector<int>>> tests = {
        {{2, 4, 3}, {5, 6, 4}}, {{0}, {0}}, {{9, 9, 9, 9, 9, 9, 9}, {9, 9, 9, 9}}, {{5}, {5}}, {{1, 8}, {0}}
    };
    for (auto& [a, b] : tests) {
        print("iterative", addTwoNumbers(build(a), build(b)));
        print("recursive", addTwoNumbersRecursive(build(a), build(b)));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Default argument `int carry = 0` lets callers omit it.
 * - `l1 ? l1->val : 0` guards a possibly-null list inline.
 * - sum % 10 and sum / 10 split a two-digit sum into digit and carry.
 */
