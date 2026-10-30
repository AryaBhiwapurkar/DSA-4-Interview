/*
 * 0148. Sort List  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/sort-list/
 *
 * Problem: Sort a linked list ascending in O(n log n) time.
 *
 * Examples:
 *   [4,2,1,3]      -> [1,2,3,4]
 *   [-1,5,3,4,0]   -> [-1,0,3,4,5]
 *   []             -> []
 *   [1]            -> [1]
 *   [2,1,2,1]      -> [1,1,2,2]
 *
 * Approaches:
 *   1. Copy values, sort, write back   O(n log n) time, O(n) space
 *   2. Top-down merge sort  ⭐          O(n log n) time, O(log n) stack   <- go-to
 *   3. Bottom-up merge sort            O(n log n) time, O(1) space
 */

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

ListNode* merge(ListNode* a, ListNode* b) {
    ListNode dummy;
    ListNode* tail = &dummy;
    while (a && b) {
        if (a->val <= b->val) { tail->next = a; a = a->next; }   // <= keeps it stable
        else { tail->next = b; b = b->next; }
        tail = tail->next;
    }
    tail->next = a ? a : b;
    return dummy.next;
}

// ---------- Approach 1: Copy Values, Sort, Write Back ----------
ListNode* sortListCopy(ListNode* head) {
    vector<int> vals;
    for (ListNode* p = head; p; p = p->next) vals.push_back(p->val);
    sort(vals.begin(), vals.end());
    int i = 0;
    for (ListNode* p = head; p; p = p->next) p->val = vals[i++];
    return head;
}

// ---------- Approach 2: Top-Down Merge Sort ⭐ ----------
ListNode* sortList(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode *slow = head, *fast = head->next;   // head->next: 2 nodes split 1 + 1
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode* right = slow->next;
    slow->next = nullptr;                  // cut before recursing
    return merge(sortList(head), sortList(right));
}

// ---------- Approach 3: Bottom-Up Merge Sort ----------
ListNode* split(ListNode* head, int n) {   // cut after n nodes, return the rest
    for (int i = 1; head && i < n; i++) head = head->next;
    if (!head) return nullptr;
    ListNode* rest = head->next;
    head->next = nullptr;
    return rest;
}

ListNode* sortListBottomUp(ListNode* head) {
    int n = 0;
    for (ListNode* p = head; p; p = p->next) n++;
    ListNode dummy(0, head);
    for (int width = 1; width < n; width *= 2) {
        ListNode *tail = &dummy, *curr = dummy.next;
        while (curr) {
            ListNode* left = curr;
            ListNode* right = split(left, width);
            curr = split(right, width);
            tail->next = merge(left, right);
            while (tail->next) tail = tail->next;   // advance to the end of the merged run
        }
    }
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
    vector<vector<int>> tests = {{4, 2, 1, 3}, {-1, 5, 3, 4, 0}, {}, {1}, {2, 1, 2, 1}};
    for (auto& v : tests) {
        print("copy    ", sortListCopy(build(v)));
        print("topDown ", sortList(build(v)));
        print("bottomUp", sortListBottomUp(build(v)));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - A shared merge() helper serves both merge sort variants.
 * - `for (int width = 1; width < n; width *= 2)` doubles the run size.
 * - Writing values back (p->val = ...) is allowed but isn't a list sort.
 */
