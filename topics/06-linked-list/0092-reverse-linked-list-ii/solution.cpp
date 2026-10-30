/*
 * 0092. Reverse Linked List II  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/reverse-linked-list-ii/
 *
 * Problem: Reverse the nodes from position left to right (1-indexed).
 *
 * Examples:
 *   [1,2,3,4,5], left 2, right 4  -> [1,4,3,2,5]
 *   [5],         left 1, right 1  -> [5]
 *   [3,5],       left 1, right 2  -> [5,3]
 *   [1,2,3],     left 1, right 3  -> [3,2,1]
 *   [1,2,3],     left 2, right 2  -> [1,2,3]
 *
 * Approaches:
 *   1. Values array, reverse segment   O(n) time, O(n) space
 *   2. Head insertion with dummy  ⭐    O(n) time, O(1) space   <- go-to
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

// ---------- Approach 1: Values Array, Reverse Segment ----------
ListNode* reverseBetweenArray(ListNode* head, int left, int right) {
    vector<int> vals;
    for (ListNode* p = head; p; p = p->next) vals.push_back(p->val);
    reverse(vals.begin() + left - 1, vals.begin() + right);   // 1-indexed, inclusive
    return build(vals);
}

// ---------- Approach 2: Head Insertion With Dummy ⭐ ----------
ListNode* reverseBetween(ListNode* head, int left, int right) {
    ListNode dummy(0, head);               // left = 1 becomes a normal case
    ListNode* prev = &dummy;
    for (int i = 1; i < left; i++) prev = prev->next;   // node before position left
    ListNode* curr = prev->next;           // stays fixed; ends as the range's tail
    for (int i = 0; i < right - left; i++) {
        ListNode* nxt = curr->next;        // move nxt to right after prev
        curr->next = nxt->next;
        nxt->next = prev->next;
        prev->next = nxt;
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
    vector<tuple<vector<int>, int, int>> tests = {
        {{1, 2, 3, 4, 5}, 2, 4}, {{5}, 1, 1}, {{3, 5}, 1, 2}, {{1, 2, 3}, 1, 3}, {{1, 2, 3}, 2, 2}
    };
    for (auto& [v, l, r] : tests) {
        print("array    ", reverseBetweenArray(build(v), l, r));
        print("headInsert", reverseBetween(build(v), l, r));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - reverse(b + left - 1, b + right) reverses positions left..right (1-indexed).
 * - tuple<vector<int>, int, int> + structured bindings for three-field tests.
 * - Head insertion: three pointer writes move one node to the front.
 */
