/*
 * 0011. Container With Most Water  |  Medium  |  Two Pointers
 * Link: https://leetcode.com/problems/container-with-most-water/
 *
 * Problem: Choose two lines that, with the x-axis, hold the most water;
 *          area = min(h[l], h[r]) * (r - l). Return the max area.
 *
 * Examples:
 *   [1,8,6,2,5,4,8,3,7]  -> 49
 *   [1,1]                -> 1
 *   [4,3,2,1,4]          -> 16
 *   [0,0]                -> 0
 *
 * Approaches:
 *   1. Brute force        O(n^2) time, O(1) space
 *   2. Two pointers  ⭐    O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force ----------
int maxAreaBrute(const vector<int>& h) {
    int best = 0, n = h.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            best = max(best, min(h[i], h[j]) * (j - i));
    return best;
}

// ---------- Approach 2: Two Pointers ⭐ ----------
int maxArea(const vector<int>& h) {
    int l = 0, r = h.size() - 1, best = 0;
    while (l < r) {
        best = max(best, min(h[l], h[r]) * (r - l));
        if (h[l] < h[r]) l++;            // shorter wall is the bottleneck: only moving it can help
        else r--;
    }
    return best;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{1, 8, 6, 2, 5, 4, 8, 3, 7}, {1, 1}, {4, 3, 2, 1, 4}, {0, 0}};
    for (auto& h : tests) {
        cout << "brute   : " << maxAreaBrute(h) << "\n";
        cout << "pointers: " << maxArea(h) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - max/min from <algorithm> need both arguments of the same type.
 * - int l = 0, r = h.size() - 1 converts size_t to int (fine for n >= 1).
 * - Max area 1e4 * 1e5 = 1e9 < INT_MAX, so int is safe.
 */
