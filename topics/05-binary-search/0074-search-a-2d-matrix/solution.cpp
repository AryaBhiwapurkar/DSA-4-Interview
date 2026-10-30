/*
 * 0074. Search a 2D Matrix  |  Medium  |  Binary Search
 * Link: https://leetcode.com/problems/search-a-2d-matrix/
 *
 * Problem: Rows are sorted and each row starts after the previous row ends.
 *          Return whether target is in the matrix. O(log(m*n)).
 *
 * Examples:
 *   [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target 3   -> true
 *   [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target 13  -> false
 *   [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target 60  -> true
 *   [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target 0   -> false
 *   [[1]], target 1                                     -> true
 *   [[1],[3]], target 3                                 -> true
 *
 * Approaches:
 *   1. Scan everything         O(m*n) time, O(1) space
 *   2. Staircase (top-right)   O(m+n) time, O(1) space
 *   3. Flat binary search  ⭐   O(log(m*n)) time, O(1) space   <- go-to
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

// ---------- Approach 2: Staircase From the Top-Right ----------
bool searchMatrixStaircase(const vector<vector<int>>& m, int target) {
    int r = 0, c = m[0].size() - 1;
    while (r < (int)m.size() && c >= 0) {
        if (m[r][c] == target) return true;
        if (m[r][c] > target) c--;         // everything below in this column is bigger too
        else r++;                          // everything left in this row is smaller too
    }
    return false;
}

// ---------- Approach 3: Flat Binary Search ⭐ ----------
bool searchMatrix(const vector<vector<int>>& m, int target) {
    int rows = m.size(), cols = m[0].size();
    int lo = 0, hi = rows * cols - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        int v = m[mid / cols][mid % cols];  // divide by COLUMNS
        if (v == target) return true;
        if (v < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return false;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> big = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    vector<pair<vector<vector<int>>, int>> tests = {
        {big, 3}, {big, 13}, {big, 60}, {big, 0}, {{{1}}, 1}, {{{1}, {3}}, 3}
    };
    cout << boolalpha;
    for (auto& [m, target] : tests) {
        cout << "brute    : " << searchMatrixBrute(m, target) << "\n";
        cout << "staircase: " << searchMatrixStaircase(m, target) << "\n";
        cout << "flat     : " << searchMatrix(m, target) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Flat index k <-> (k / cols, k % cols); back: r * cols + c.
 * - {{{1}}, 1} is a pair whose first element is the 1x1 matrix {{1}}.
 * - m[0].size() - 1 is size_t; assigning to int c makes c >= 0 testable.
 */
