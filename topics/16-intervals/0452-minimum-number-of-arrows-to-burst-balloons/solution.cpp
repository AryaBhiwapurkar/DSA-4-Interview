/*
 * 0452. Minimum Number of Arrows to Burst Balloons  |  Medium  |  Intervals
 * Link: https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/
 *
 * Problem: Each balloon spans [x_start, x_end]. A vertical arrow at x bursts every
 *          balloon with x_start <= x <= x_end. Fewest arrows to burst them all.
 *
 * Examples:
 *   [[10,16],[2,8],[1,6],[7,12]]       -> 2
 *   [[1,2],[3,4],[5,6],[7,8]]          -> 4
 *   [[1,2],[2,3],[3,4],[4,5]]          -> 2
 *   [[-2147483646,-2147483645],[2147483646,2147483647]] -> 2
 *   [[1,10],[2,3],[4,5]]               -> 2
 *
 * Approaches:
 *   1. Sort by start, shrink the shared window   O(n log n) time, O(1) extra
 *   2. Sort by end, shoot at the earliest end  ⭐  O(n log n) time, O(1) extra   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Sort by Start ----------
int findMinArrowShotsStart(vector<vector<int>> pts) {
    sort(pts.begin(), pts.end());
    int arrows = 1, end = pts[0][1];               // rightmost x that hits the whole group
    for (size_t i = 1; i < pts.size(); i++) {
        if (pts[i][0] > end) { arrows++; end = pts[i][1]; }   // new group
        else end = min(end, pts[i][1]);            // common window shrinks
    }
    return arrows;
}

// ---------- Approach 2: Sort by End ⭐ ----------
int findMinArrowShots(vector<vector<int>> pts) {
    sort(pts.begin(), pts.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[1] < b[1];                        // not a[1] - b[1] < 0: that overflows
    });
    int arrows = 1, arrowX = pts[0][1];
    for (size_t i = 1; i < pts.size(); i++)
        if (pts[i][0] > arrowX) {                  // last arrow misses this balloon
            arrows++;
            arrowX = pts[i][1];
        }
    return arrows;
}

// ---------- Driver ----------
int main() {
    vector<vector<vector<int>>> tests = {
        {{10, 16}, {2, 8}, {1, 6}, {7, 12}}, {{1, 2}, {3, 4}, {5, 6}, {7, 8}}, {{1, 2}, {2, 3}, {3, 4}, {4, 5}},
        {{-2147483646, -2147483645}, {2147483646, 2147483647}}, {{1, 10}, {2, 3}, {4, 5}}
    };
    for (auto& t : tests) {
        cout << "start: " << findMinArrowShotsStart(t) << "\n";
        cout << "end  : " << findMinArrowShots(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Compare with `<`; subtraction-based comparators overflow near INT_MIN / INT_MAX.
 * - n >= 1, so seeding with pts[0] needs no empty check.
 * - Lambda comparators can be written inline as the third argument of sort.
 */
