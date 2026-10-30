/*
 * 0023. Merge k Sorted Lists  |  Hard  |  Linked List
 * Link: https://leetcode.com/problems/merge-k-sorted-lists/
 *
 * Problem: Merge k sorted linked lists into one sorted list.
 *
 * Examples:
 *   [[1,4,5],[1,3,4],[2,6]]  -> [1,1,2,3,4,4,5,6]
 *   []                       -> []
 *   [[]]                     -> []
 *   [[2],[],[1]]             -> [1,2]
 *
 * Approaches:
 *   1. Collect, sort, rebuild        O(N log N) time, O(N) space
 *   2. Min-heap of heads  ⭐          O(N log k) time, O(k) space   <- go-to
 *   3. Divide & conquer merging      O(N log k) time, O(1) extra space
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
ListNode* mergeKListsSort(vector<ListNode*>& lists) {
    vector<int> vals;
    for (ListNode* l : lists)
        for (ListNode* p = l; p; p = p->next) vals.push_back(p->val);
    sort(vals.begin(), vals.end());
    return build(vals);
}

// ---------- Approach 2: Min-Heap of Heads ⭐ ----------
ListNode* mergeKLists(vector<ListNode*>& lists) {
    auto cmp = [](ListNode* a, ListNode* b) { return a->val > b->val; };   // > : MIN-heap
    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);
    for (ListNode* l : lists)
        if (l) pq.push(l);                 // skip empty lists
    ListNode dummy;
    ListNode* tail = &dummy;
    while (!pq.empty()) {
        ListNode* n = pq.top();
        pq.pop();
        tail = tail->next = n;
        if (n->next) pq.push(n->next);
    }
    return dummy.next;
}

// ---------- Approach 3: Divide & Conquer Merging ----------
ListNode* mergeTwo(ListNode* a, ListNode* b) {
    ListNode dummy;
    ListNode* tail = &dummy;
    while (a && b) {
        if (a->val <= b->val) { tail->next = a; a = a->next; }
        else { tail->next = b; b = b->next; }
        tail = tail->next;
    }
    tail->next = a ? a : b;
    return dummy.next;
}

ListNode* mergeKListsDivide(vector<ListNode*>& lists) {
    int k = lists.size();
    if (k == 0) return nullptr;
    for (int step = 1; step < k; step *= 2)          // log k rounds
        for (int i = 0; i + step < k; i += 2 * step)
            lists[i] = mergeTwo(lists[i], lists[i + step]);
    return lists[0];
}

// ---------- Driver ----------
void print(const string& label, ListNode* head) {
    cout << label << ": [";
    for (ListNode* p = head; p; p = p->next) cout << p->val << (p->next ? "," : "");
    cout << "]\n";
}

vector<ListNode*> buildAll(const vector<vector<int>>& vs) {
    vector<ListNode*> out;
    for (auto& v : vs) out.push_back(build(v));
    return out;
}

int main() {
    vector<vector<vector<int>>> tests = {{{1, 4, 5}, {1, 3, 4}, {2, 6}}, {}, {{}}, {{2}, {}, {1}}};
    for (auto& t : tests) {                // fresh lists per approach: merging splices nodes
        auto a = buildAll(t), b = buildAll(t), c = buildAll(t);
        print("sort  ", mergeKListsSort(a));
        print("heap  ", mergeKLists(b));
        print("divide", mergeKListsDivide(c));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Lambda comparator + decltype(cmp) as the third template argument; pass
 *   cmp to the constructor too.
 * - priority_queue is a max-heap by default; "a > b" flips it to a min-heap.
 * - Doubling step loop (step *= 2) is the bottom-up merge sort skeleton.
 */
