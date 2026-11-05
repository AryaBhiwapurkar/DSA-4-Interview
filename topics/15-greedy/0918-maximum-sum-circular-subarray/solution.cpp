/*
 * 0918. Maximum Sum Circular Subarray  |  Medium  |  Greedy
 * Link: https://leetcode.com/problems/maximum-sum-circular-subarray/
 *
 * Problem: Largest sum of a non-empty subarray of a circular array (a subarray
 *          may wrap past the end, but uses each element at most once).
 *
 * Examples:
 *   [1,-2,3,-2]   -> 3
 *   [5,-3,5]      -> 10
 *   [-3,-2,-3]    -> -2
 *   [3,-1,2,-1]   -> 4
 *   [-2]          -> -2
 *
 * Approaches:
 *   1. Brute force, every start and length   O(n^2) time, O(1) space
 *   2. Kadane on max and min  ⭐              O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force ----------
int maxSubarraySumCircularBrute(const vector<int>& nums) {
    int n = nums.size(), best = nums[0];
    for (int i = 0; i < n; i++) {
        int s = 0;
        for (int k = 0; k < n; k++) {              // lengths 1..n starting at i, wrapping
            s += nums[(i + k) % n];
            best = max(best, s);
        }
    }
    return best;
}

// ---------- Approach 2: Kadane on Max and Min ⭐ ----------
int maxSubarraySumCircular(const vector<int>& nums) {
    int total = 0, curMax = 0, curMin = 0, bestMax = nums[0], bestMin = nums[0];
    for (int x : nums) {
        curMax = max(x, curMax + x);
        bestMax = max(bestMax, curMax);            // best non-wrapping subarray
        curMin = min(x, curMin + x);
        bestMin = min(bestMin, curMin);            // removing the worst block gives the wrap
        total += x;
    }
    if (bestMax < 0) return bestMax;               // all negative: the wrap would be empty
    return max(bestMax, total - bestMin);
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{1, -2, 3, -2}, {5, -3, 5}, {-3, -2, -3}, {3, -1, 2, -1}, {-2}};
    for (auto& t : tests) {
        cout << "brute : " << maxSubarraySumCircularBrute(t) << "\n";
        cout << "kadane: " << maxSubarraySumCircular(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - n <= 3*10^4 and |x| <= 3*10^4: total stays within ±9*10^8, fine for int.
 * - Seeding curMax/curMin with 0 works because max(x, 0 + x) = x on the first step.
 * - (i + k) % n wraps the index.
 */
