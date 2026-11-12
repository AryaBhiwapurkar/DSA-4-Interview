/*
 * 0154. Find Minimum in Rotated Sorted Array II  |  Hard  |  Binary Search
 * Link: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/
 *
 * Problem: A sorted array with duplicates was rotated. Return its minimum.
 *
 * Examples:
 *   [1,3,5]            -> 1
 *   [2,2,2,0,1]        -> 0
 *   [3,3,1,3]          -> 1
 *   [10,1,10,10,10]    -> 1
 *   [1,1]              -> 1
 *   [4,5,6,7,0,1,4]    -> 0
 *
 * Approaches:
 *   1. Linear scan                          O(n) time, O(1) space
 *   2. Binary search vs hi, hi-- on ties ⭐ O(log n) typical, O(n) worst   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Linear Scan ----------
int findMinLinear(const vector<int>& nums) {
    return *min_element(nums.begin(), nums.end());
}

// ---------- Approach 2: Binary Search vs hi ⭐ ----------
int findMin(const vector<int>& nums) {
    int lo = 0, hi = nums.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] < nums[hi]) hi = mid;        // min is at mid or left of it
        else if (nums[mid] > nums[hi]) lo = mid + 1;   // the drop is right of mid
        else hi--;                                 // nums[mid] keeps hi's value in range
    }
    return nums[lo];
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {
        {1, 3, 5}, {2, 2, 2, 0, 1}, {3, 3, 1, 3}, {10, 1, 10, 10, 10}, {1, 1}, {4, 5, 6, 7, 0, 1, 4}};
    for (auto& t : tests) {
        cout << "linear: " << findMinLinear(t) << "\n";
        cout << "binary: " << findMin(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - *min_element(begin, end) gives the smallest value (the iterator dereferenced).
 * - if / else if / else covers <, >, == in one chain.
 * - while (lo < hi) with hi = mid ends with lo == hi pointing at the answer.
 */
