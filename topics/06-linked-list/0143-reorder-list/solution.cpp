/*
 * 0143. Reorder List  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/reorder-list/
 *
 * Problem: Relink L0->L1->...->Ln into L0->Ln->L1->Ln-1->... in place.
 *
 * Examples:
 *   [1,2,3,4]    -> [1,4,2,3]
 *   [1,2,3,4,5]  -> [1,5,2,4,3]
 *   [1]          -> [1]
 *   [1,2]        -> [1,2]
 *
 * Approaches:
 *   1. Array of nodes + two pointers   O(n) time, O(n) space
 *   2. Mid + reverse + merge  ⭐        O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

// ---------- Approach 1: Array of Nodes + Two Pointers ----------
void reorderListArray(ListNode* head) {
    vector<ListNode*> nodes;
    for (ListNode* p = head; p; p = p->next) nodes.push_back(p);
    int i = 0, j = nodes.size() - 1;
    while (i < j) {
        nodes[i]->next = nodes[j];
        if (++i == j) break;
        nodes[j]->next = nodes[i];
        j--;
    }
    nodes[i]->next = nullptr;              // new tail: cut the old links
}

// ---------- Approach 2: Mid + Reverse + Merge ⭐ ----------
void reorderList(ListNode* head) {
    ListNode *slow = head, *fast = head;   // find the end of the first half
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode* second = slow->next;
    slow->next = nullptr;                  // cut, or the weave makes a cycle

    ListNode* prev = nullptr;              // reverse the second half
    while (second) {
        ListNode* nxt = second->next;
        second->next = prev;
        prev = second;
        second = nxt;
    }

    ListNode *first = head, *back = prev;  // weave: first is never shorter
    while (back) {
        ListNode *n1 = first->next, *n2 = back->next;   // save both before relinking
        first->next = back;
        back->next = n1;
        first = n1;
        back = n2;
    }
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
    vector<vector<int>> tests = {{1, 2, 3, 4}, {1, 2, 3, 4, 5}, {1}, {1, 2}};
    for (auto& v : tests) {                // fresh list per approach: reordering mutates
        ListNode* a = build(v);
        reorderListArray(a);
        print("array  ", a);
        ListNode* b = build(v);
        reorderList(b);
        print("inPlace", b);
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `if (++i == j) break;` increments first, then compares.
 * - Keep subroutines inline or as helpers; both are fine in an interview.
 * - A void function that mutates the list: print the original head afterward.
 */
