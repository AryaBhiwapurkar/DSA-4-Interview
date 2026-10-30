/*
 * 0084. Largest Rectangle in Histogram  |  Hard  |  Stack
 * Link: https://leetcode.com/problems/largest-rectangle-in-histogram/
 *
 * Problem: Bars of width 1 with given heights. Return the area of the
 *          largest rectangle that fits inside the histogram.
 *
 * Examples:
 *   [2,1,5,6,2,3]  -> 10
 *   [2,4]          -> 4
 *   [5]            -> 5
 *   [1,2,3,4,5]    -> 9
 *   [2,2,2]        -> 6
 *   [2,0,2]        -> 2
 *
 * Approaches:
 *   1. Brute force, running min     O(n^2) time, O(1) space
 *   2. Monotonic increasing stack ⭐ O(n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force, Running Min ----------
int largestRectangleAreaBrute(const vector<int>& h) {
    int n = h.size(), best = 0;
    for (int i = 0; i < n; i++) {
        int mn = INT_MAX;
        for (int j = i; j < n; j++) {
            mn = min(mn, h[j]);            // shortest bar in [i, j] limits the height
            best = max(best, mn * (j - i + 1));
        }
    }
    return best;
}

// ---------- Approach 2: Monotonic Increasing Stack ⭐ ----------
int largestRectangleArea(const vector<int>& h) {
    int n = h.size(), best = 0;
    vector<int> st;                        // indices, heights increasing
    for (int i = 0; i <= n; i++) {
        int cur = i == n ? 0 : h[i];       // sentinel 0 flushes the stack at the end
        while (!st.empty() && h[st.back()] >= cur) {
            int height = h[st.back()];
            st.pop_back();
            int left = st.empty() ? -1 : st.back();    // previous smaller (NEW top)
            best = max(best, height * (i - left - 1)); // i is the next smaller
        }
        st.push_back(i);
    }
    return best;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{2, 1, 5, 6, 2, 3}, {2, 4}, {5}, {1, 2, 3, 4, 5}, {2, 2, 2}, {2, 0, 2}};
    for (auto& h : tests) {
        cout << "brute: " << largestRectangleAreaBrute(h) << "\n";
        cout << "stack: " << largestRectangleArea(h) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Looping to i <= n with `cur = i == n ? 0 : h[i]` adds a sentinel
 *   without copying the input.
 * - The sentinel index n is pushed but never read through h[] (loop ends).
 * - INT_MAX as the initial running min; max area 1e9 fits in int.
 */
