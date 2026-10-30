/*
 * 1046. Last Stone Weight  |  Easy  |  Heap / Priority Queue
 * Link: https://leetcode.com/problems/last-stone-weight/
 *
 * Problem: Repeatedly smash the two heaviest stones; equal ones vanish,
 *          otherwise the difference remains. Return the last weight or 0.
 *
 * Examples:
 *   [2,7,4,1,8,1]  -> 1
 *   [1]            -> 1
 *   [2,2]          -> 0
 *   [10,4,2,10]    -> 2
 *
 * Approaches:
 *   1. Sort every round   O(n^2 log n) time, O(1) extra
 *   2. Max-heap  ⭐        O(n log n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Sort Every Round ----------
int lastStoneWeightSort(vector<int> s) {
    while (s.size() > 1) {
        sort(s.begin(), s.end());
        int y = s.back(); s.pop_back();
        int x = s.back(); s.pop_back();
        if (y > x) s.push_back(y - x);
    }
    return s.empty() ? 0 : s[0];
}

// ---------- Approach 2: Max-Heap ⭐ ----------
int lastStoneWeight(const vector<int>& stones) {
    priority_queue<int> pq(stones.begin(), stones.end());   // max-heap by default
    while (pq.size() > 1) {
        int y = pq.top(); pq.pop();
        int x = pq.top(); pq.pop();
        if (y > x) pq.push(y - x);         // equal stones both vanish
    }
    return pq.empty() ? 0 : pq.top();
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{2, 7, 4, 1, 8, 1}, {1}, {2, 2}, {10, 4, 2, 10}};
    for (auto& s : tests) {
        cout << "sort: " << lastStoneWeightSort(s) << "\n";
        cout << "heap: " << lastStoneWeight(s) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - priority_queue<int> pq(b, e) heapifies a range in O(n).
 * - top() then pop(): pop() returns void.
 */
