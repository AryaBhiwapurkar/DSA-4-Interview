/*
 * 0240. Search a 2D Matrix II  |  Medium  |  Binary Search
 * Link: https://leetcode.com/problems/search-a-2d-matrix-ii/
 *
 * Problem: Rows sorted left->right, columns sorted top->bottom.
 *          Return whether target is in the matrix.
 *
 * Examples:
 *   M (5x5 below), target = 5    -> true
 *   M,             target = 20   -> false
 *   [[-5]],        target = -5   -> true
 *   [[1,4],[2,5]], target = 2    -> true
 *   [[1,4],[2,5]], target = 3    -> false
 *   M,             target = 30   -> true    (bottom-right corner)
 *   M,             target = 0    -> false   (below everything)
 *
 * Approaches:
 *   1. Scan everything             O(m n) time, O(1) space
 *   2. Binary search each row      O(m log n) time, O(1) space
 *   3. Staircase from top-right ⭐ O(m + n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Scan Everything ----------
bool searchMatrixBrute(const vector<vector<int>>& m, int target) {
    for (auto& row : m)
        for (int x : row)
            if (x == target) return true;
    return false;
}

// ---------- Approach 2: Binary Search Each Row ----------
bool searchMatrixRows(const vector<vector<int>>& m, int target) {
    for (auto& row : m)
        if (binary_search(row.begin(), row.end(), target)) return true;
    return false;
}

// ---------- Approach 3: Staircase from Top-right ⭐ ----------
bool searchMatrix(const vector<vector<int>>& m, int target) {
    int r = 0, c = m[0].size() - 1;
    while (r < (int)m.size() && c >= 0) {
        if (m[r][c] == target) return true;
        if (m[r][c] > target) c--;            // whole column below is even bigger
        else r++;                             // whole row to the left is even smaller
    }
    return false;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> M = {{1, 4, 7, 11, 15}, {2, 5, 8, 12, 19}, {3, 6, 9, 16, 22},
                             {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30}};
    vector<pair<vector<vector<int>>, int>> tests = {
        {M, 5}, {M, 20}, {{{-5}}, -5}, {{{1, 4}, {2, 5}}, 2}, {{{1, 4}, {2, 5}}, 3}, {M, 30}, {M, 0}};
    cout << boolalpha;
    for (auto& [m, t] : tests) {
        cout << "brute    : " << searchMatrixBrute(m, t) << "\n";
        cout << "rows     : " << searchMatrixRows(m, t) << "\n";
        cout << "staircase: " << searchMatrix(m, t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - std::binary_search(begin, end, x) returns only a bool; use lower_bound for the index.
 * - {{{-5}}} is a test pair whose first member is the 1x1 matrix {{-5}}.
 * - Cast m.size() to int before comparing with a signed loop variable.
 */
