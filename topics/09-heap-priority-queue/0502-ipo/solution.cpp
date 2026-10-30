/*
 * 0502. IPO  |  Hard  |  Heap / Priority Queue
 * Link: https://leetcode.com/problems/ipo/
 *
 * Problem: Start with capital w; do at most k distinct projects, each needing
 *          capital[i] and adding profits[i]. Maximize final capital.
 *
 * Examples:
 *   k 2, w 0, profits [1,2,3], capital [0,1,1]    -> 4
 *   k 3, w 0, profits [1,2,3], capital [0,1,2]    -> 6
 *   k 1, w 0, profits [1],     capital [1]        -> 0   (nothing affordable)
 *   k 10, w 0, profits [1,2,3], capital [0,1,1]   -> 6   (runs out of projects)
 *
 * Approaches:
 *   1. Rescan each round        O(k * n) time, O(n) space
 *   2. Sort + max-heap  ⭐       O(n log n + k log n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Rescan Each Round ----------
int findMaximizedCapitalBrute(int k, int w, const vector<int>& profits, const vector<int>& capital) {
    int n = profits.size();
    vector<bool> used(n, false);
    while (k--) {
        int best = -1;
        for (int i = 0; i < n; i++)
            if (!used[i] && capital[i] <= w && (best == -1 || profits[i] > profits[best])) best = i;
        if (best == -1) break;             // nothing affordable
        used[best] = true;
        w += profits[best];
    }
    return w;
}

// ---------- Approach 2: Sort + Max-Heap ⭐ ----------
int findMaximizedCapital(int k, int w, const vector<int>& profits, const vector<int>& capital) {
    int n = profits.size();
    vector<pair<int, int>> proj(n);        // (capital needed, profit)
    for (int i = 0; i < n; i++) proj[i] = {capital[i], profits[i]};
    sort(proj.begin(), proj.end());
    priority_queue<int> pq;                // profits of affordable projects
    int i = 0;
    while (k--) {
        while (i < n && proj[i].first <= w) pq.push(proj[i++].second);   // newly affordable
        if (pq.empty()) break;
        w += pq.top();                     // greedy: best affordable (capital never shrinks)
        pq.pop();
    }
    return w;
}

// ---------- Driver ----------
int main() {
    vector<tuple<int, int, vector<int>, vector<int>>> tests = {
        {2, 0, {1, 2, 3}, {0, 1, 1}}, {3, 0, {1, 2, 3}, {0, 1, 2}}, {1, 0, {1}, {1}}, {10, 0, {1, 2, 3}, {0, 1, 1}}
    };
    for (auto& [k, w, p, c] : tests) {
        cout << "brute: " << findMaximizedCapitalBrute(k, w, p, c) << "\n";
        cout << "heap : " << findMaximizedCapital(k, w, p, c) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Pairs sort by .first: sorting (capital, profit) orders by requirement.
 * - `while (k--)` runs k times (tests then decrements).
 */
