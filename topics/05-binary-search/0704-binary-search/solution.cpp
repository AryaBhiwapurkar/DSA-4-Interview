/*
 * 0704. Binary Search  |  Easy  |  Binary Search
 * Link: https://leetcode.com/problems/binary-search/
 *
 * Problem: Sorted array of distinct ints; return target's index or -1,
 *          in O(log n).
 *
 * Examples:
 *   [-1,0,3,5,9,12], target 9   -> 4
 *   [-1,0,3,5,9,12], target 2   -> -1
 *   [5],             target 5   -> 0
 *   [5],             target -5  -> -1
 *   [1,3],           target 3   -> 1
 *
 * Approaches:
 *   1. Linear scan            O(n) time, O(1) space
 *   2. Binary search  ⭐       O(log n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Linear Scan ----------
int searchLinear(const vector<int>& nums, int target) {
    for (int i = 0; i < (int)nums.size(); i++)
        if (nums[i] == target) return i;
    return -1;
}

// ---------- Approach 2: Iterative Binary Search ⭐ ----------
int search(const vector<int>& nums, int target) {
    int lo = 0, hi = (int)nums.size() - 1;     // inclusive window; int, not size_t
    while (lo <= hi) {                         // <= : a 1-element window is still a candidate
        int mid = lo + (hi - lo) / 2;          // no overflow
        if (nums[mid] == target) return mid;
        if (nums[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<int>, int>> tests = {
        {{-1, 0, 3, 5, 9, 12}, 9}, {{-1, 0, 3, 5, 9, 12}, 2}, {{5}, 5}, {{5}, -5}, {{1, 3}, 3}
    };
    for (auto& [nums, target] : tests) {
        cout << "linear: " << searchLinear(nums, target) << "\n";
        cout << "binary: " << search(nums, target) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - lo + (hi - lo) / 2 avoids int overflow of lo + hi.
 * - Cast size() to int before subtracting: size_t(0) - 1 wraps to a huge number.
 * - Library: lower_bound(a.begin(), a.end(), x) returns the first >= x.
 */
