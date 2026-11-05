/*
 * 0134. Gas Station  |  Medium  |  Greedy
 * Link: https://leetcode.com/problems/gas-station/
 *
 * Problem: Stations on a circle give gas[i]; driving to the next costs cost[i].
 *          Return the unique start index that completes the loop, or -1.
 *
 * Examples:
 *   gas=[1,2,3,4,5], cost=[3,4,5,1,2]   -> 3
 *   gas=[2,3,4], cost=[3,4,3]           -> -1
 *   gas=[5], cost=[4]                   -> 0
 *   gas=[3,1,1], cost=[1,2,2]           -> 0
 *   gas=[5,1,2,3,4], cost=[4,4,1,5,1]   -> 4
 *
 * Approaches:
 *   1. Simulate from every start    O(n^2) time, O(1) space
 *   2. One pass, reset on negative tank  ⭐   O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Simulate Every Start ----------
int canCompleteCircuitBrute(const vector<int>& gas, const vector<int>& cost) {
    int n = gas.size();
    for (int s = 0; s < n; s++) {
        int tank = 0, k = 0;
        for (; k < n; k++) {
            int i = (s + k) % n;
            tank += gas[i] - cost[i];
            if (tank < 0) break;
        }
        if (k == n) return s;                      // never ran dry
    }
    return -1;
}

// ---------- Approach 2: One Pass ⭐ ----------
int canCompleteCircuit(const vector<int>& gas, const vector<int>& cost) {
    int total = 0, tank = 0, start = 0;
    for (int i = 0; i < (int)gas.size(); i++) {
        int d = gas[i] - cost[i];
        total += d;
        tank += d;
        if (tank < 0) { start = i + 1; tank = 0; }   // no start in [start, i] works
    }
    return total < 0 ? -1 : start;                 // total >= 0 guarantees start works
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<int>, vector<int>>> tests = {
        {{1, 2, 3, 4, 5}, {3, 4, 5, 1, 2}}, {{2, 3, 4}, {3, 4, 3}}, {{5}, {4}}, {{3, 1, 1}, {1, 2, 2}},
        {{5, 1, 2, 3, 4}, {4, 4, 1, 5, 1}}
    };
    for (auto& [gas, cost] : tests) {
        cout << "brute: " << canCompleteCircuitBrute(gas, cost) << "\n";
        cout << "pass : " << canCompleteCircuit(gas, cost) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Declaring k outside the inner for lets you test `k == n` after a possible break.
 * - n <= 10^5 and values <= 10^4, so total fits in int (|total| <= 10^9).
 * - (s + k) % n wraps around the circle.
 */
