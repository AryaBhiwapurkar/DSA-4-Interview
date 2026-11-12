/*
 * 0876. Middle of the Linked List  |  Easy  |  Linked List
 * Link: https://leetcode.com/problems/middle-of-the-linked-list/
 *
 * Problem: Return the middle node; for even length, the second middle.
 *
 * Examples:
 *   [1,2,3,4,5]     -> [3,4,5]
 *   [1,2,3,4,5,6]   -> [4,5,6]
 *   [1]             -> [1]
 *   [1,2]           -> [2]
 *
 * Approaches:
 *   1. Count, then walk n/2      O(n) time, O(1) space
 *   2. Fast/slow pointers  ⭐     O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

// ---------- Approach 1: Count, then Walk ----------
ListNode* middleNodeCount(ListNode* head) {
    int n = 0;
    for (ListNode* p = head; p; p = p->next) n++;
    for (int i = 0; i < n / 2; i++) head = head->next;   // n/2 -> second middle
    return head;
}

// ---------- Approach 2: Fast/Slow Pointers ⭐ ----------
ListNode* middleNode(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {               // this condition -> second middle
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
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
    vector<vector<int>> tests = {{1, 2, 3, 4, 5}, {1, 2, 3, 4, 5, 6}, {1}, {1, 2}};
    for (auto& t : tests) {
        ListNode* head = build(t);
        cout << "count   : " << str(middleNodeCount(head)) << "\n";
        cout << "fastSlow: " << str(middleNode(head)) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - while (fast && fast->next) checks null before each dereference (short-circuit &&).
 * - head is a by-value pointer parameter; advancing it doesn't affect the caller.
 * - Ternary inside string building: (p->next ? "," : "").
 */
