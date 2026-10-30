/*
 * 0086. Partition List  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/partition-list/
 *
 * Problem: Move nodes with value < x before nodes with value >= x, keeping
 *          the original order within each group.
 *
 * Examples:
 *   [1,4,3,2,5,2], x 3  -> [1,2,2,4,3,5]
 *   [2,1],         x 2  -> [1,2]
 *   [],            x 0  -> []
 *   [3,1,2],       x 4  -> [3,1,2]
 *   [3,1,2],       x 0  -> [3,1,2]
 *
 * Approaches:
 *   1. Two value arrays, rebuild   O(n) time, O(n) space
 *   2. Two dummy lists  ⭐          O(n) time, O(1) extra space   <- go-to
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

// ---------- Approach 1: Two Value Arrays, Rebuild ----------
ListNode* partitionArray(ListNode* head, int x) {
    vector<int> less, rest;
    for (ListNode* p = head; p; p = p->next) (p->val < x ? less : rest).push_back(p->val);
    less.insert(less.end(), rest.begin(), rest.end());
    return build(less);
}

// ---------- Approach 2: Two Dummy Lists ⭐ ----------
ListNode* partition(ListNode* head, int x) {
    ListNode lessDummy, geDummy;
    ListNode *less = &lessDummy, *ge = &geDummy;
    for (ListNode* p = head; p; p = p->next) {
        if (p->val < x) less = less->next = p;   // appending keeps the order (stable)
        else ge = ge->next = p;
    }
    ge->next = nullptr;                    // or the old link may form a cycle
    less->next = geDummy.next;
    return lessDummy.next;
}

// ---------- Driver ----------
void print(const string& label, ListNode* head) {
    cout << label << ": [";
    for (ListNode* p = head; p; p = p->next) cout << p->val << (p->next ? "," : "");
    cout << "]\n";
}

int main() {
    vector<pair<vector<int>, int>> tests = {
        {{1, 4, 3, 2, 5, 2}, 3}, {{2, 1}, 2}, {{}, 0}, {{3, 1, 2}, 4}, {{3, 1, 2}, 0}
    };
    for (auto& [v, x] : tests) {
        print("arrays ", partitionArray(build(v), x));
        print("dummies", partition(build(v), x));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `(cond ? a : b).push_back(v)` picks which vector to append to.
 * - v.insert(v.end(), w.begin(), w.end()) concatenates vectors.
 * - Two stack dummies: `ListNode lessDummy, geDummy;`.
 */
