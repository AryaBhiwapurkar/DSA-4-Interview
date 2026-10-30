/*
 * 0141. Linked List Cycle  |  Easy  |  Linked List
 * Link: https://leetcode.com/problems/linked-list-cycle/
 *
 * Problem: Return whether a linked list contains a cycle. (pos below only
 *          says where the tail links back; it isn't an input.)
 *
 * Examples:
 *   [3,2,0,-4], pos 1   -> true
 *   [1,2],      pos 0   -> true
 *   [1],        pos -1  -> false
 *   [],         pos -1  -> false
 *   [1],        pos 0   -> true   (self-loop)
 *   [1,2,3],    pos -1  -> false
 *
 * Approaches:
 *   1. Hash set of visited nodes   O(n) time, O(n) space
 *   2. Floyd fast/slow  ⭐          O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

// ---------- Approach 1: Hash Set of Visited Nodes ----------
bool hasCycleSet(ListNode* head) {
    unordered_set<ListNode*> seen;         // node identity, not values
    for (ListNode* p = head; p; p = p->next)
        if (!seen.insert(p).second) return true;   // already present
    return false;
}

// ---------- Approach 2: Floyd Fast/Slow ⭐ ----------
bool hasCycle(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {           // both needed before fast->next->next
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;     // check AFTER moving: they start equal
    }
    return false;
}

// ---------- Driver ----------
ListNode* buildCycle(const vector<int>& v, int pos) {
    ListNode dummy;
    ListNode *tail = &dummy, *entry = nullptr;
    for (int i = 0; i < (int)v.size(); i++) {
        tail = tail->next = new ListNode(v[i]);
        if (i == pos) entry = tail;
    }
    if (entry) tail->next = entry;         // close the loop
    return dummy.next;
}

int main() {
    vector<pair<vector<int>, int>> tests = {
        {{3, 2, 0, -4}, 1}, {{1, 2}, 0}, {{1}, -1}, {{}, -1}, {{1}, 0}, {{1, 2, 3}, -1}
    };
    cout << boolalpha;
    for (auto& [v, pos] : tests) {
        ListNode* head = buildCycle(v, pos);   // read-only approaches: one list is enough
        cout << "hashSet: " << hasCycleSet(head) << "\n";
        cout << "floyd  : " << hasCycle(head) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - unordered_set<ListNode*> hashes the pointer (identity).
 * - insert(x).second is false when x was already in the set.
 * - `ListNode *slow = head, *fast = head;` declares two pointers.
 */
