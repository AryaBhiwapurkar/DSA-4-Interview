/*
 * 0024. Swap Nodes in Pairs  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/swap-nodes-in-pairs/
 *
 * Problem: Swap every two adjacent nodes (links, not values).
 *
 * Examples:
 *   [1,2,3,4]     -> [2,1,4,3]
 *   []            -> []
 *   [1]           -> [1]
 *   [1,2,3]       -> [2,1,3]
 *   [1,2,3,4,5]   -> [2,1,4,3,5]
 *
 * Approaches:
 *   1. Recursion                     O(n) time, O(n) stack
 *   2. Iterative with a dummy  ⭐     O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

// ---------- Approach 1: Recursion ----------
ListNode* swapPairsRecursive(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode* second = head->next;
    head->next = swapPairsRecursive(second->next);   // rest is already swapped
    second->next = head;
    return second;
}

// ---------- Approach 2: Iterative with a Dummy ⭐ ----------
ListNode* swapPairs(ListNode* head) {
    ListNode dummy(0, head);
    ListNode* prev = &dummy;
    while (prev->next && prev->next->next) {
        ListNode *a = prev->next, *b = a->next;
        a->next = b->next;                     // keep the rest before b->next changes
        b->next = a;
        prev->next = b;
        prev = a;                              // a now ends this pair
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
    vector<vector<int>> tests = {{1, 2, 3, 4}, {}, {1}, {1, 2, 3}, {1, 2, 3, 4, 5}};
    for (auto& t : tests) {                    // each approach rewires: fresh list each
        cout << "recursive: " << str(swapPairsRecursive(build(t))) << "\n";
        cout << "iterative: " << str(swapPairs(build(t))) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - ListNode dummy(0, head); on the stack: no new/delete for the sentinel.
 * - ListNode *a = prev->next, *b = a->next;  b's initialiser can use a.
 * - Return dummy.next, not &dummy: the sentinel dies when the function returns.
 */
