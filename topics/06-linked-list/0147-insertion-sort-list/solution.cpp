/*
 * 0147. Insertion Sort List  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/insertion-sort-list/
 *
 * Problem: Sort a singly linked list with insertion sort (relink nodes).
 *
 * Examples:
 *   [4,2,1,3]       -> [1,2,3,4]
 *   [-1,5,3,4,0]    -> [-1,0,3,4,5]
 *   [1]             -> [1]
 *   [3,3,1]         -> [1,3,3]
 *   [1,2,3]         -> [1,2,3]
 *   [5,4,3,2,1]     -> [1,2,3,4,5]
 *
 * Approaches:
 *   1. Copy values, sort, write back           O(n log n) time, O(n) space
 *   2. Insertion into a dummy-headed list ⭐   O(n^2) time, O(1) space   <- go-to
 *   3. With a sorted-tail shortcut             O(n^2) worst, O(n) if sorted, O(1) space
 */

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

// ---------- Approach 1: Copy Values, Sort, Write Back ----------
ListNode* insertionSortListValues(ListNode* head) {
    vector<int> v;
    for (ListNode* p = head; p; p = p->next) v.push_back(p->val);
    sort(v.begin(), v.end());
    int i = 0;
    for (ListNode* p = head; p; p = p->next) p->val = v[i++];
    return head;
}

// ---------- Approach 2: Insertion into a Dummy-headed List ⭐ ----------
ListNode* insertionSortList(ListNode* head) {
    ListNode dummy;                            // dummy.next is the sorted list
    while (head) {
        ListNode* cur = head;
        head = head->next;                     // save the rest of the input first
        ListNode* prev = &dummy;
        while (prev->next && prev->next->val <= cur->val) prev = prev->next;   // <= keeps it stable
        cur->next = prev->next;
        prev->next = cur;
    }
    return dummy.next;
}

// ---------- Approach 3: With a Sorted-tail Shortcut ----------
ListNode* insertionSortListTail(ListNode* head) {
    if (!head) return head;
    ListNode dummy(0, head);
    ListNode* last = head;                     // end of the sorted prefix
    while (last->next) {
        ListNode* cur = last->next;
        if (last->val <= cur->val) { last = cur; continue; }   // already in place
        last->next = cur->next;                // unlink cur
        ListNode* prev = &dummy;
        while (prev->next->val <= cur->val) prev = prev->next; // stops before last
        cur->next = prev->next;
        prev->next = cur;
    }
    return dummy.next;
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
    vector<vector<int>> tests = {{4, 2, 1, 3}, {-1, 5, 3, 4, 0}, {1}, {3, 3, 1}, {1, 2, 3}, {5, 4, 3, 2, 1}};
    for (auto& t : tests) {
        cout << "values   : " << str(insertionSortListValues(build(t))) << "\n";
        cout << "insertion: " << str(insertionSortList(build(t))) << "\n";
        cout << "tailCheck: " << str(insertionSortListTail(build(t))) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - ListNode dummy; on the stack; &dummy is the "node before the head".
 * - continue skips the insert when the node is already in place.
 * - p->val = v[i++] writes then advances i (post-increment).
 */
