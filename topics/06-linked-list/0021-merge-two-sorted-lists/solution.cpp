/*
 * 0021. Merge Two Sorted Lists  |  Easy  |  Linked List
 * Link: https://leetcode.com/problems/merge-two-sorted-lists/
 *
 * Problem: Splice two sorted linked lists into one sorted list.
 *
 * Examples:
 *   [1,2,4], [1,3,4]  -> [1,1,2,3,4,4]
 *   [],      []       -> []
 *   [],      [0]      -> [0]
 *   [5],     [1,2,3]  -> [1,2,3,5]
 *
 * Approaches:
 *   1. Collect, sort, rebuild      O((m+n) log(m+n)) time, O(m+n) space
 *   2. Recursive merge             O(m+n) time, O(m+n) stack
 *   3. Iterative with dummy  ⭐     O(m+n) time, O(1) space   <- go-to
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

// ---------- Approach 1: Collect, Sort, Rebuild ----------
ListNode* mergeTwoListsSort(ListNode* l1, ListNode* l2) {
    vector<int> vals;
    for (ListNode* p = l1; p; p = p->next) vals.push_back(p->val);
    for (ListNode* p = l2; p; p = p->next) vals.push_back(p->val);
    sort(vals.begin(), vals.end());
    return build(vals);
}

// ---------- Approach 2: Recursive Merge ----------
ListNode* mergeTwoListsRecursive(ListNode* l1, ListNode* l2) {
    if (!l1) return l2;
    if (!l2) return l1;
    if (l1->val <= l2->val) {
        l1->next = mergeTwoListsRecursive(l1->next, l2);
        return l1;
    }
    l2->next = mergeTwoListsRecursive(l1, l2->next);
    return l2;
}

// ---------- Approach 3: Iterative With Dummy ⭐ ----------
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy;                        // removes the "who is head?" case
    ListNode* tail = &dummy;
    while (l1 && l2) {
        if (l1->val <= l2->val) { tail->next = l1; l1 = l1->next; }   // <= keeps it stable
        else { tail->next = l2; l2 = l2->next; }
        tail = tail->next;
    }
    tail->next = l1 ? l1 : l2;             // attach the leftover in one step
    return dummy.next;
}

// ---------- Driver ----------
void print(const string& label, ListNode* head) {
    cout << label << ": [";
    for (ListNode* p = head; p; p = p->next) cout << p->val << (p->next ? "," : "");
    cout << "]\n";
}

int main() {
    vector<pair<vector<int>, vector<int>>> tests = {
        {{1, 2, 4}, {1, 3, 4}}, {{}, {}}, {{}, {0}}, {{5}, {1, 2, 3}}
    };
    for (auto& [a, b] : tests) {           // fresh lists per approach: merging splices nodes
        print("sort     ", mergeTwoListsSort(build(a), build(b)));
        print("recursive", mergeTwoListsRecursive(build(a), build(b)));
        print("iterative", mergeTwoLists(build(a), build(b)));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `ListNode dummy;` on the stack + `&dummy` avoids new/delete for the dummy.
 * - `tail->next = l1 ? l1 : l2;` picks the non-null leftover.
 * - Pointers test as booleans: while (l1 && l2).
 */
