/*
 * 0275. H-Index II  |  Medium  |  Binary Search
 * Link: https://leetcode.com/problems/h-index-ii/
 *
 * Problem: Citations are sorted ascending. Return the largest h such that
 *          h papers have >= h citations each, in O(log n).
 *
 * Examples:
 *   [0,1,3,5,6]   -> 3
 *   [1,2,100]     -> 2
 *   [0]           -> 0
 *   [100]         -> 1
 *   [0,0,0]       -> 0
 *   [11,15]       -> 2
 *   [0,3,3]       -> 2
 *
 * Approaches:
 *   1. Linear scan                   O(n) time, O(1) space
 *   2. Binary search on the index ⭐ O(log n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Linear Scan ----------
int hIndexLinear(const vector<int>& c) {
    int n = c.size();
    for (int i = 0; i < n; i++)
        if (c[i] >= n - i) return n - i;      // n - i papers have >= c[i] citations
    return 0;
}

// ---------- Approach 2: Binary Search on the Index ⭐ ----------
int hIndex(const vector<int>& c) {
    int n = c.size(), lo = 0, hi = n;         // hi = n means "no index works"
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (c[mid] >= n - mid) hi = mid;
        else lo = mid + 1;
    }
    return n - lo;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{0, 1, 3, 5, 6}, {1, 2, 100}, {0}, {100}, {0, 0, 0}, {11, 15}, {0, 3, 3}};
    for (auto& t : tests) {
        cout << "linear: " << hIndexLinear(t) << "\n";
        cout << "binary: " << hIndex(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Searching [0, n] (not [0, n-1]) lets lo == n mean "predicate never true".
 * - int n = c.size() once avoids repeated size_t/int mixing in comparisons.
 * - Several ints in one declaration: int n = ..., lo = 0, hi = n;
 */
