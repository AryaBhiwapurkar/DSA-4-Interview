/*
 * 0082. Remove Duplicates from Sorted List II  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
 *
 * Problem: In a sorted list, delete every node whose value is duplicated,
 *          keeping only values that appear exactly once.
 *
 * Examples:
 *   [1,2,3,3,4,4,5]  -> [1,2,5]
 *   [1,1,1,2,3]      -> [2,3]
 *   []               -> []
 *   [1,1]            -> []
 *   [1,2,2]          -> [1]
 *
 * Approaches:
 *   1. Count values, then relink   O(n) time, O(n) space
 *   2. Dummy + skip runs  ⭐        O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

// ---------- Approach 1: Count Values, Then Relink ----------
ListNode* deleteDuplicatesCount(ListNode* head) {
    unordered_map<int, int> cnt;
    for (ListNode* p = head; p; p = p->next) cnt[p->val]++;
    ListNode dummy;
    ListNode* tail = &dummy;
    for (ListNode* p = head; p; p = p->next)
        if (cnt[p->val] == 1) tail = tail->next = p;   // keep unique values only
    tail->next = nullptr;                  // cut whatever followed the last kept node
    return dummy.next;
}

// ---------- Approach 2: Dummy + Skip Runs ⭐ ----------
ListNode* deleteDuplicates(ListNode* head) {
    ListNode dummy(0, head);               // a run at the head becomes a normal case
    ListNode *prev = &dummy, *curr = head;
    while (curr) {
        if (curr->next && curr->val == curr->next->val) {
            int v = curr->val;
            while (curr && curr->val == v) curr = curr->next;   // skip the whole run
            prev->next = curr;             // prev stays: curr may start another run
        } else {
            prev = curr;                   // curr is unique
            curr = curr->next;
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
    vector<vector<int>> tests = {{1, 2, 3, 3, 4, 4, 5}, {1, 1, 1, 2, 3}, {}, {1, 1}, {1, 2, 2}};
    for (auto& v : tests) {
        print("count", deleteDuplicatesCount(build(v)));
        print("skip ", deleteDuplicates(build(v)));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - cnt[p->val]++ default-inserts 0 then increments: fine for counting.
 * - `while (curr && curr->val == v)`: the null check must come first.
 * - Relinking kept nodes needs a final tail->next = nullptr to cut the rest.
 */
