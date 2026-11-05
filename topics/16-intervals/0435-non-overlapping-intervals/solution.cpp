/*
 * 0435. Non-overlapping Intervals  |  Medium  |  Intervals
 * Link: https://leetcode.com/problems/non-overlapping-intervals/
 *
 * Problem: Fewest intervals to delete so the rest don't overlap (touching is OK).
 *
 * Examples:
 *   [[1,2],[2,3],[3,4],[1,3]]   -> 1
 *   [[1,2],[1,2],[1,2]]         -> 2
 *   [[1,2],[2,3]]               -> 0
 *   [[1,100],[11,22],[1,11],[2,12]] -> 2
 *   [[0,2],[1,3],[2,4],[3,5],[4,6]] -> 2
 *
 * Approaches:
 *   1. DP: longest chain of non-overlapping (sort by start)   O(n^2) time, O(n) space
 *   2. Sort by end, keep greedily  ⭐                           O(n log n) time, O(1) extra   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: DP ----------
int eraseOverlapIntervalsDP(vector<vector<int>> iv) {
    sort(iv.begin(), iv.end());
    int n = iv.size();
    vector<int> keep(n, 1);                        // longest chain ending with iv[i]
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            if (iv[j][1] <= iv[i][0]) keep[i] = max(keep[i], keep[j] + 1);
    return n - *max_element(keep.begin(), keep.end());
}

// ---------- Approach 2: Greedy by End ⭐ ----------
int eraseOverlapIntervals(vector<vector<int>> iv) {
    sort(iv.begin(), iv.end(), [](const vector<int>& a, const vector<int>& b) { return a[1] < b[1]; });
    int removed = 0;
    long long end = LLONG_MIN;                     // first interval always fits
    for (auto& x : iv) {
        if (x[0] >= end) end = x[1];               // keep it
        else removed++;                            // overlaps the kept one, which ends sooner
    }
    return removed;
}

// ---------- Driver ----------
int main() {
    vector<vector<vector<int>>> tests = {
        {{1, 2}, {2, 3}, {3, 4}, {1, 3}}, {{1, 2}, {1, 2}, {1, 2}}, {{1, 2}, {2, 3}},
        {{1, 100}, {11, 22}, {1, 11}, {2, 12}}, {{0, 2}, {1, 3}, {2, 4}, {3, 5}, {4, 6}}
    };
    for (auto& t : tests) {
        cout << "dp    : " << eraseOverlapIntervalsDP(t) << "\n";
        cout << "greedy: " << eraseOverlapIntervals(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Lambda comparator `a[1] < b[1]` sorts by end; it must be strict (<, not <=).
 * - LLONG_MIN as the initial end avoids special-casing the first interval.
 * - *max_element(...) returns the largest kept chain.
 */
