/*
 * 0033. Search in Rotated Sorted Array  |  Medium  |  Binary Search
 * Link: https://leetcode.com/problems/search-in-rotated-sorted-array/
 *
 * Problem: A sorted array of distinct ints was rotated. Return the index of
 *          target or -1, in O(log n).
 *
 * Examples:
 *   [4,5,6,7,0,1,2], target 0  -> 4
 *   [4,5,6,7,0,1,2], target 3  -> -1
 *   [1],             target 0  -> -1
 *   [1,3],           target 3  -> 1
 *   [3,1],           target 1  -> 1
 *   [5,1,3],         target 5  -> 0
 *
 * Approaches:
 *   1. Linear scan                  O(n) time, O(1) space
 *   2. Find pivot, then search      O(log n) time, O(1) space
 *   3. One-pass sorted half  ⭐      O(log n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Linear Scan ----------
int searchLinear(const vector<int>& nums, int target) {
    auto it = find(nums.begin(), nums.end(), target);
    return it == nums.end() ? -1 : it - nums.begin();
}

// ---------- Approach 2: Find Pivot, Then Binary Search ----------
int binarySearch(const vector<int>& nums, int lo, int hi, int target) {
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

int searchPivot(const vector<int>& nums, int target) {
    int n = nums.size(), lo = 0, hi = n - 1;
    while (lo < hi) {                      // index of the minimum (LC 0153)
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] > nums[hi]) lo = mid + 1;
        else hi = mid;
    }
    int p = lo;
    if (target >= nums[p] && target <= nums[n - 1]) return binarySearch(nums, p, n - 1, target);
    return binarySearch(nums, 0, p - 1, target);
}

// ---------- Approach 3: One-Pass Sorted Half ⭐ ----------
int search(const vector<int>& nums, int target) {
    int lo = 0, hi = nums.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) return mid;
        if (nums[lo] <= nums[mid]) {       // left half sorted (<=: lo may equal mid)
            if (nums[lo] <= target && target < nums[mid]) hi = mid - 1;
            else lo = mid + 1;
        } else {                           // right half sorted
            if (nums[mid] < target && target <= nums[hi]) lo = mid + 1;
            else hi = mid - 1;
        }
    }
    return -1;
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<int>, int>> tests = {
        {{4, 5, 6, 7, 0, 1, 2}, 0}, {{4, 5, 6, 7, 0, 1, 2}, 3}, {{1}, 0}, {{1, 3}, 3}, {{3, 1}, 1}, {{5, 1, 3}, 5}
    };
    for (auto& [nums, target] : tests) {
        cout << "linear : " << searchLinear(nums, target) << "\n";
        cout << "pivot  : " << searchPivot(nums, target) << "\n";
        cout << "onePass: " << search(nums, target) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - find(b, e, x) returns e if x is absent; it - begin() converts to an index.
 * - The ternary's two branches must have compatible types (int and ptrdiff_t
 *   both convert to int on return).
 * - A helper with explicit lo/hi bounds lets one binary search serve both halves.
 */
