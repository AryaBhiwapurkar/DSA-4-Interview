/*
 * 0713. Subarray Product Less Than K  |  Medium  |  Sliding Window
 * Link: https://leetcode.com/problems/subarray-product-less-than-k/
 *
 * Problem: Count contiguous subarrays (positive values) with product strictly below k.
 *
 * Examples:
 *   [10,5,2,6], k = 100  -> 8
 *   [1,2,3],    k = 0    -> 0
 *   [1,1,1],    k = 2    -> 6
 *   [5],        k = 5    -> 0
 *   [1,2,3],    k = 1    -> 0
 *
 * Approaches:
 *   1. All start/end pairs           O(n^2) time, O(1) space
 *   2. Sliding window + count  ⭐    O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: All Pairs ----------
int numSubarrayProductLessThanKBrute(const vector<int>& nums, int k) {
    int n = nums.size(), count = 0;
    for (int i = 0; i < n; i++) {
        long long prod = 1;
        for (int j = i; j < n; j++) {
            prod *= nums[j];
            if (prod >= k) break;                  // positive values: only grows from here
            count++;
        }
    }
    return count;
}

// ---------- Approach 2: Sliding Window ⭐ ----------
int numSubarrayProductLessThanK(const vector<int>& nums, int k) {
    if (k <= 1) return 0;                          // no positive product is < 1
    long long prod = 1;
    int l = 0, count = 0;
    for (int r = 0; r < (int)nums.size(); r++) {
        prod *= nums[r];
        while (prod >= k) prod /= nums[l++];
        count += r - l + 1;                        // subarrays ending at r: starts l..r
    }
    return count;
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<int>, int>> tests = {
        {{10, 5, 2, 6}, 100}, {{1, 2, 3}, 0}, {{1, 1, 1}, 2}, {{5}, 5}, {{1, 2, 3}, 1}};
    for (auto& [nums, k] : tests) {
        cout << "brute : " << numSubarrayProductLessThanKBrute(nums, k) << "\n";
        cout << "window: " << numSubarrayProductLessThanK(nums, k) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - long long prod: before shrinking it can reach (k - 1) * 1000, about 1e9.
 * - prod /= nums[l++] divides out the leaving element, then advances l.
 * - Early return for k <= 1 keeps the while loop from running past r.
 */
