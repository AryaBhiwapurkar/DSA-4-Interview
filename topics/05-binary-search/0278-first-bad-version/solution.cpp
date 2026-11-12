/*
 * 0278. First Bad Version  |  Easy  |  Binary Search
 * Link: https://leetcode.com/problems/first-bad-version/
 *
 * Problem: Versions 1..n; from some version on all are bad. Using
 *          isBadVersion(v), return the first bad version.
 *
 * Examples:
 *   n = 5,          bad = 4           -> 4
 *   n = 1,          bad = 1           -> 1
 *   n = 10,         bad = 7           -> 7
 *   n = 10,         bad = 1           -> 1
 *   n = 2126753390, bad = 1702766719  -> 1702766719   (lo + hi overflows int)
 *
 * Approaches:
 *   1. Linear scan                 O(n) calls
 *   2. Lower-bound binary search ⭐ O(log n) calls, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

int BAD = 1;                                   // the hidden first bad version
bool isBadVersion(int v) { return v >= BAD; }  // stand-in for the LeetCode API

// ---------- Approach 1: Linear Scan ----------
int firstBadVersionLinear(int n) {
    for (int v = 1; v < n; v++)
        if (isBadVersion(v)) return v;
    return n;                                  // at least version n is bad
}

// ---------- Approach 2: Lower-bound Binary Search ⭐ ----------
int firstBadVersion(int n) {
    int lo = 1, hi = n;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;          // (lo + hi) / 2 overflows near INT_MAX
        if (isBadVersion(mid)) hi = mid;       // mid might be the first bad one
        else lo = mid + 1;
    }
    return lo;
}

// ---------- Driver ----------
int main() {
    vector<pair<int, int>> tests = {{5, 4}, {1, 1}, {10, 7}, {10, 1}, {2126753390, 1702766719}};
    for (auto [n, bad] : tests) {
        BAD = bad;
        if (n <= 1000000) cout << "linear: " << firstBadVersionLinear(n) << "\n";
        else cout << "linear: skipped (n too large)\n";
        cout << "binary: " << firstBadVersion(n) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - lo + (hi - lo) / 2 never exceeds hi, so it can't overflow int.
 * - while (lo < hi) with hi = mid / lo = mid + 1 ends with lo == hi.
 * - Structured bindings: for (auto [n, bad] : tests) unpacks each pair.
 */
