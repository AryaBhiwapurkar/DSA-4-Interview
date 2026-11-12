/*
 * 0328. Odd Even Linked List  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/odd-even-linked-list/
 *
 * Problem: Put nodes at odd positions first, then even positions,
 *          preserving order within each group. O(1) extra space.
 *
 * Examples:
 *   [1,2,3,4,5]       -> [1,3,5,2,4]
 *   [2,1,3,5,6,4,7]   -> [2,3,6,7,1,5,4]
 *   []                -> []
 *   [1]               -> [1]
 *   [1,2]             -> [1,2]
 *   [1,2,3,4]         -> [1,3,2,4]
 *
 * Approaches:
 *   1. Collect nodes into two arrays   O(n) time, O(n) space
 *   2. In-place two chains  ⭐          O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

// ---------- Approach 1: Collect Nodes into Two Arrays ----------
ListNode* oddEvenListArrays(ListNode* head) {
    vector<ListNode*> odd, even;
    for (int i = 1; head; head = head->next, i++) (i % 2 ? odd : even).push_back(head);
    odd.insert(odd.end(), even.begin(), even.end());
    for (size_t i = 0; i < odd.size(); i++) odd[i]->next = i + 1 < odd.size() ? odd[i + 1] : nullptr;
    return odd.empty() ? nullptr : odd[0];
}

// ---------- Approach 2: In-place Two Chains ⭐ ----------
ListNode* oddEvenList(ListNode* head) {
    if (!head) return head;
    ListNode *odd = head, *even = head->next, *evenHead = even;
    while (even && even->next) {               // covers both odd and even lengths
        odd->next = even->next;
        odd = odd->next;
        even->next = odd->next;
        even = even->next;
    }
    odd->next = evenHead;                      // odd chain, then even chain
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
    vector<vector<int>> tests = {{1, 2, 3, 4, 5}, {2, 1, 3, 5, 6, 4, 7}, {}, {1}, {1, 2}, {1, 2, 3, 4}};
    for (auto& t : tests) {
        cout << "arrays : " << str(oddEvenListArrays(build(t))) << "\n";
        cout << "inPlace: " << str(oddEvenList(build(t))) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - (cond ? odd : even).push_back(x) picks which vector to append to.
 * - v.insert(v.end(), w.begin(), w.end()) concatenates two vectors.
 * - Comma in the for increment: head = head->next, i++.
 */
