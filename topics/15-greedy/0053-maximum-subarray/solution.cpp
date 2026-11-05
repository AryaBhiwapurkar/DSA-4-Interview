/*
 * 0053. Maximum Subarray  |  Medium  |  Greedy
 * Link: https://leetcode.com/problems/maximum-subarray/
 *
 * Problem: Largest sum of a non-empty contiguous subarray.
 *
 * Examples:
 *   [-2,1,-3,4,-1,2,1,-5,4]   -> 6
 *   [1]                       -> 1
 *   [5,4,-1,7,8]              -> 23
 *   [-3,-1,-2]                -> -1  (all negative: best single element)
 *
 * Approaches:
 *   1. Brute force, all subarrays   O(n^2) time, O(1) space
 *   2. Divide and conquer           O(n log n) time, O(log n) space
 *   3. Kadane  ⭐                    O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force ----------
int maxSubArrayBrute(const vector<int>& nums) {
    int best = nums[0];
    for (size_t i = 0; i < nums.size(); i++) {
        int s = 0;
        for (size_t j = i; j < nums.size(); j++) {   // extend the subarray starting at i
            s += nums[j];
            best = max(best, s);
        }
    }
    return best;
}

// ---------- Approach 2: Divide and Conquer ----------
int solve(const vector<int>& nums, int lo, int hi) {   // inclusive range
    if (lo == hi) return nums[lo];
    int mid = lo + (hi - lo) / 2;
    int leftBest = INT_MIN, rightBest = INT_MIN, s = 0;
    for (int i = mid; i >= lo; i--) { s += nums[i]; leftBest = max(leftBest, s); }        // ends at mid
    s = 0;
    for (int i = mid + 1; i <= hi; i++) { s += nums[i]; rightBest = max(rightBest, s); }  // starts at mid+1
    return max({solve(nums, lo, mid), solve(nums, mid + 1, hi), leftBest + rightBest});
}

int maxSubArrayDC(const vector<int>& nums) { return solve(nums, 0, nums.size() - 1); }

// ---------- Approach 3: Kadane ⭐ ----------
int maxSubArray(const vector<int>& nums) {
    int best = nums[0], cur = nums[0];
    for (size_t i = 1; i < nums.size(); i++) {
        cur = max(nums[i], cur + nums[i]);         // a negative running sum only hurts: restart
        best = max(best, cur);
    }
    return best;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{-2, 1, -3, 4, -1, 2, 1, -5, 4}, {1}, {5, 4, -1, 7, 8}, {-3, -1, -2}};
    for (auto& t : tests) {
        cout << "brute : " << maxSubArrayBrute(t) << "\n";
        cout << "divide: " << maxSubArrayDC(t) << "\n";
        cout << "kadane: " << maxSubArray(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Seed best/cur with nums[0], not 0, or all-negative input returns 0.
 * - lo + (hi - lo) / 2 is the overflow-safe midpoint.
 * - max({a, b, c}) compares three values at once.
 */
