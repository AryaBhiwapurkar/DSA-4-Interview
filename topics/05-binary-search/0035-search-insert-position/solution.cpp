/*
 * 0035. Search Insert Position  |  Easy  |  Binary Search
 * Link: https://leetcode.com/problems/search-insert-position/
 *
 * Problem: Sorted distinct ints. Return target's index, or the index where
 *          it would be inserted to keep order. O(log n).
 *
 * Examples:
 *   [1,3,5,6], target 5  -> 2
 *   [1,3,5,6], target 2  -> 1
 *   [1,3,5,6], target 7  -> 4
 *   [1,3,5,6], target 0  -> 0
 *   [1],       target 1  -> 0
 *
 * Approaches:
 *   1. Linear scan       O(n) time, O(1) space
 *   2. Lower bound  ⭐    O(log n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Linear Scan ----------
int searchInsertLinear(const vector<int>& nums, int target) {
    for (int i = 0; i < (int)nums.size(); i++)
        if (nums[i] >= target) return i;
    return nums.size();
}

// ---------- Approach 2: Lower Bound ⭐ ----------
int searchInsert(const vector<int>& nums, int target) {
    int lo = 0, hi = nums.size();          // half-open [lo, hi): answer can be n
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] < target) lo = mid + 1;
        else hi = mid;                     // mid might be the answer: keep it
    }
    return lo;
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<int>, int>> tests = {
        {{1, 3, 5, 6}, 5}, {{1, 3, 5, 6}, 2}, {{1, 3, 5, 6}, 7}, {{1, 3, 5, 6}, 0}, {{1}, 1}
    };
    for (auto& [nums, target] : tests) {
        cout << "linear: " << searchInsertLinear(nums, target) << "\n";
        cout << "lower : " << searchInsert(nums, target) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Library one-liner: lower_bound(nums.begin(), nums.end(), target) - nums.begin().
 * - upper_bound gives the first element > target (same template with <=).
 * - Half-open [lo, hi) pairs with `while (lo < hi)` and `hi = mid`.
 */
