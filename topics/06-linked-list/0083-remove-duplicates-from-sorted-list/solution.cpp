/*
 * 0083. Remove Duplicates from Sorted List  |  Easy  |  Linked List
 * Link: https://leetcode.com/problems/remove-duplicates-from-sorted-list/
 *
 * Problem: Remove duplicates from a sorted list so each value appears once.
 *
 * Examples:
 *   [1,1,2]         -> [1,2]
 *   [1,1,2,3,3]     -> [1,2,3]
 *   []              -> []
 *   [1,1,1]         -> [1]
 *   [1,2,3]         -> [1,2,3]
 *   [1,1,1,2]       -> [1,2]
 *
 * Approaches:
 *   1. Recursion                O(n) time, O(n) stack
 *   2. Iterative skip  ⭐        O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

// ---------- Approach 1: Recursion ----------
ListNode* deleteDuplicatesRecursive(ListNode* head) {
    if (!head || !head->next) return head;
    head->next = deleteDuplicatesRecursive(head->next);   // rest is deduped
    if (head->next->val == head->val) {
        ListNode* dup = head->next;
        head->next = dup->next;
        delete dup;
    }
    return head;
}

// ---------- Approach 2: Iterative Skip ⭐ ----------
ListNode* deleteDuplicates(ListNode* head) {
    ListNode* cur = head;
    while (cur && cur->next) {
        if (cur->next->val == cur->val) {
            ListNode* dup = cur->next;
            cur->next = dup->next;             // unlink; stay on cur
            delete dup;
        } else {
            cur = cur->next;
        }
    }
    return head;
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
    vector<vector<int>> tests = {{1, 1, 2}, {1, 1, 2, 3, 3}, {}, {1, 1, 1}, {1, 2, 3}, {1, 1, 1, 2}};
    for (auto& t : tests) {
        cout << "recursive: " << str(deleteDuplicatesRecursive(build(t))) << "\n";
        cout << "iterative: " << str(deleteDuplicates(build(t))) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Save the node in a temp before unlinking, then delete it.
 * - while (cur && cur->next) guards both pointers before reading values.
 * - if / else so cur only advances when nothing was removed.
 */
