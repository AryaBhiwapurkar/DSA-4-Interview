/*
 * 0025. Reverse Nodes in k-Group  |  Hard  |  Linked List
 * Link: https://leetcode.com/problems/reverse-nodes-in-k-group/
 *
 * Problem: Reverse the list k nodes at a time; a final group shorter than
 *          k stays as is. Relink nodes, don't change values.
 *
 * Examples:
 *   [1,2,3,4,5], k 2  -> [2,1,4,3,5]
 *   [1,2,3,4,5], k 3  -> [3,2,1,4,5]
 *   [1,2,3,4],   k 4  -> [4,3,2,1]
 *   [1,2],       k 1  -> [1,2]
 *   [1],         k 1  -> [1]
 *
 * Approaches:
 *   1. Values array, reverse chunks   O(n) time, O(n) space
 *   2. Iterative group reversal  ⭐    O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

ListNode* build(const vector<int>& v) {
    ListNode dummy;
    ListNode* tail = &dummy;
    for (int x : v) tail = tail->next = new ListNode(x);
    return dummy.next;
}

// ---------- Approach 1: Values Array, Reverse Chunks ----------
ListNode* reverseKGroupArray(ListNode* head, int k) {
    vector<int> vals;
    for (ListNode* p = head; p; p = p->next) vals.push_back(p->val);
    for (size_t i = 0; i + k <= vals.size(); i += k)  // full chunks only
        reverse(vals.begin() + i, vals.begin() + i + k);
    return build(vals);
}

// ---------- Approach 2: Iterative Group Reversal ⭐ ----------
ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode dummy(0, head);
    ListNode* groupPrev = &dummy;
    while (true) {
        ListNode* kth = groupPrev;
        for (int i = 0; i < k && kth; i++) kth = kth->next;
        if (!kth) break;                   // fewer than k left: keep as is
        ListNode* groupNext = kth->next;

        ListNode *prev = groupNext, *curr = groupPrev->next;   // prev = groupNext, NOT null
        while (curr != groupNext) {
            ListNode* nxt = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt;
        }

        ListNode* oldFirst = groupPrev->next;   // now the group's last node
        groupPrev->next = kth;
        groupPrev = oldFirst;
    }
    return dummy.next;
}

// ---------- Driver ----------
void print(const string& label, ListNode* head) {
    cout << label << ": [";
    for (ListNode* p = head; p; p = p->next) cout << p->val << (p->next ? "," : "");
    cout << "]\n";
}

int main() {
    vector<pair<vector<int>, int>> tests = {
        {{1, 2, 3, 4, 5}, 2}, {{1, 2, 3, 4, 5}, 3}, {{1, 2, 3, 4}, 4}, {{1, 2}, 1}, {{1}, 1}
    };
    for (auto& [v, k] : tests) {
        print("array    ", reverseKGroupArray(build(v), k));
        print("iterative", reverseKGroup(build(v), k));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - reverse(b + i, b + i + k) reverses a sub-range in place.
 * - `for (...; i < k && kth; ...)` stops early if the list runs out.
 * - while (true) with a break keeps the "check k nodes exist" step at the top.
 */
