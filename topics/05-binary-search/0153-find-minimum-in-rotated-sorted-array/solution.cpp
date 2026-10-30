/*
 * 0153. Find Minimum in Rotated Sorted Array  |  Medium  |  Binary Search
 * Link: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
 *
 * Problem: A sorted array of distinct ints was rotated. Return its minimum
 *          in O(log n).
 *
 * Examples:
 *   [3,4,5,1,2]      -> 1
 *   [4,5,6,7,0,1,2]  -> 0
 *   [11,13,15,17]    -> 11
 *   [2,1]            -> 1
 *   [1]              -> 1
 *
 * Approaches:
 *   1. Linear scan                   O(n) time, O(1) space
 *   2. Binary search vs right end ⭐  O(log n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Linear Scan ----------
int findMinLinear(const vector<int>& nums) {
    return *min_element(nums.begin(), nums.end());
}

// ---------- Approach 2: Binary Search vs Right End ⭐ ----------
int findMin(const vector<int>& nums) {
    int lo = 0, hi = nums.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] > nums[hi]) lo = mid + 1;    // drop is strictly right of mid
        else hi = mid;                             // mid..hi sorted: min at mid or left
    }
    return nums[lo];
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{3, 4, 5, 1, 2}, {4, 5, 6, 7, 0, 1, 2}, {11, 13, 15, 17}, {2, 1}, {1}};
    for (auto& nums : tests) {
        cout << "linear: " << findMinLinear(nums) << "\n";
        cout << "binary: " << findMin(nums) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - *min_element(b, e) returns the smallest value (iterator dereferenced).
 * - Comparing with nums[hi] (not nums[lo]) handles the unrotated case.
 */
