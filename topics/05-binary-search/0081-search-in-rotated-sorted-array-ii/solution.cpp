/*
 * 0081. Search in Rotated Sorted Array II  |  Medium  |  Binary Search
 * Link: https://leetcode.com/problems/search-in-rotated-sorted-array-ii/
 *
 * Problem: A sorted array with duplicates was rotated. Return whether
 *          target is present.
 *
 * Examples:
 *   [2,5,6,0,0,1,2], target = 0                          -> true
 *   [2,5,6,0,0,1,2], target = 3                          -> false
 *   [1,0,1,1,1],     target = 0                          -> true   (breaks plain LC 33)
 *   [1,1,1,1,1,1,1,1,1,13,1,1,1,1,1,1,1,1,1,1,1,1], 13   -> true
 *   [1],             target = 0                          -> false
 *   [3,1],           target = 1                          -> true
 *
 * Approaches:
 *   1. Linear scan                                  O(n) time, O(1) space
 *   2. Rotated binary search + tie shrinking ⭐     O(log n) typical, O(n) worst   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Linear Scan ----------
bool searchLinear(const vector<int>& nums, int target) {
    return find(nums.begin(), nums.end(), target) != nums.end();
}

// ---------- Approach 2: Rotated Binary Search ⭐ ----------
bool search(const vector<int>& nums, int target) {
    int lo = 0, hi = nums.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) return true;
        if (nums[lo] == nums[mid] && nums[mid] == nums[hi]) {
            lo++; hi--;                           // can't tell which half is sorted
        } else if (nums[lo] <= nums[mid]) {       // left half sorted
            if (nums[lo] <= target && target < nums[mid]) hi = mid - 1;
            else lo = mid + 1;
        } else {                                  // right half sorted
            if (nums[mid] < target && target <= nums[hi]) lo = mid + 1;
            else hi = mid - 1;
        }
    }
    return false;
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<int>, int>> tests = {
        {{2, 5, 6, 0, 0, 1, 2}, 0}, {{2, 5, 6, 0, 0, 1, 2}, 3}, {{1, 0, 1, 1, 1}, 0},
        {{1, 1, 1, 1, 1, 1, 1, 1, 1, 13, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 13},
        {{1}, 0}, {{3, 1}, 1}};
    cout << boolalpha;
    for (auto& [nums, t] : tests) {
        cout << "linear: " << searchLinear(nums, t) << "\n";
        cout << "binary: " << search(nums, t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - find(begin, end, x) != end is the idiomatic "contains" for a vector.
 * - lo++; hi--; on one line keeps the tie case visually compact.
 * - Half-open range checks: nums[lo] <= target && target < nums[mid].
 */
