/*
 * 0142. Linked List Cycle II  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/linked-list-cycle-ii/
 *
 * Problem: Return the node where the cycle begins, or null. (pos below only
 *          says where the tail links back; output shows the node's index.)
 *
 * Examples:
 *   [3,2,0,-4],    pos 1   -> 1
 *   [1,2],         pos 0   -> 0
 *   [1],           pos -1  -> null
 *   [],            pos -1  -> null
 *   [1],           pos 0   -> 0     (self-loop)
 *   [1,2,3,4,5,6], pos 2   -> 2
 *
 * Approaches:
 *   1. Hash set of visited nodes   O(n) time, O(n) space
 *   2. Floyd's two phases  ⭐       O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

// ---------- Approach 1: Hash Set of Visited Nodes ----------
ListNode* detectCycleSet(ListNode* head) {
    unordered_set<ListNode*> seen;
    for (ListNode* p = head; p; p = p->next)
        if (!seen.insert(p).second) return p;   // first node seen twice
    return nullptr;
}

// ---------- Approach 2: Floyd's Two Phases ⭐ ----------
ListNode* detectCycle(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {                     // phase 1 done: inside the cycle
            ListNode* p = head;                 // a = k*c - b: walk both at speed 1
            while (p != slow) { p = p->next; slow = slow->next; }
            return p;
        }
    }
    return nullptr;
}

// ---------- Driver ----------
vector<ListNode*> buildCycle(const vector<int>& v, int pos) {
    vector<ListNode*> nodes;
    for (int x : v) nodes.push_back(new ListNode(x));
    for (size_t i = 0; i + 1 < nodes.size(); i++) nodes[i]->next = nodes[i + 1];
    if (pos >= 0) nodes.back()->next = nodes[pos];   // close the loop
    return nodes;
}

string indexOf(const vector<ListNode*>& nodes, ListNode* p) {
    if (!p) return "null";
    return to_string(find(nodes.begin(), nodes.end(), p) - nodes.begin());
}

int main() {
    vector<pair<vector<int>, int>> tests = {
        {{3, 2, 0, -4}, 1}, {{1, 2}, 0}, {{1}, -1}, {{}, -1}, {{1}, 0}, {{1, 2, 3, 4, 5, 6}, 2}};
    for (auto& [v, pos] : tests) {
        auto nodes = buildCycle(v, pos);
        ListNode* head = nodes.empty() ? nullptr : nodes[0];   // read-only: share one list
        cout << "hashSet: " << indexOf(nodes, detectCycleSet(head)) << "\n";
        cout << "floyd  : " << indexOf(nodes, detectCycle(head)) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - unordered_set::insert returns {iterator, bool}; .second is false if already present.
 * - find(...) - begin() turns an iterator into an index.
 * - ListNode *slow = head, *fast = head;  the * binds to each name, not the type.
 */
