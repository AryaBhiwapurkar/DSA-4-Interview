/*
 * 1004. Max Consecutive Ones III  |  Medium  |  Sliding Window
 * Link: https://leetcode.com/problems/max-consecutive-ones-iii/
 *
 * Problem: Longest run of 1s after flipping at most k zeros.
 *
 * Examples:
 *   [1,1,1,0,0,0,1,1,1,1,0], k = 2                      -> 6
 *   [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3      -> 10
 *   [1,0,1,0,1], k = 1                                  -> 3
 *   [0,0,0], k = 0                                      -> 0
 *   [0,0,1], k = 5                                      -> 3
 *
 * Approaches:
 *   1. Every start, extend          O(n^2) time, O(1) space
 *   2. Shrinking window  ⭐         O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Every Start ----------
int longestOnesBrute(const vector<int>& nums, int k) {
    int n = nums.size(), best = 0;
    for (int l = 0; l < n; l++) {
        int zeros = 0, r = l;
        while (r < n && zeros + (nums[r] == 0) <= k) zeros += nums[r++] == 0;
        best = max(best, r - l);
    }
    return best;
}

// ---------- Approach 2: Shrinking Window ⭐ ----------
int longestOnes(const vector<int>& nums, int k) {
    int l = 0, zeros = 0, best = 0;
    for (int r = 0; r < (int)nums.size(); r++) {
        zeros += nums[r] == 0;
        while (zeros > k) zeros -= nums[l++] == 0;  // shrink until back within budget
        best = max(best, r - l + 1);
    }
    return best;
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<int>, int>> tests = {
        {{1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0}, 2},
        {{0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1}, 3},
        {{1, 0, 1, 0, 1}, 1}, {{0, 0, 0}, 0}, {{0, 0, 1}, 5}};
    for (auto& [nums, k] : tests) {
        cout << "brute : " << longestOnesBrute(nums, k) << "\n";
        cout << "window: " << longestOnes(nums, k) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - zeros += nums[r] == 0; adds a bool (0 or 1) to an int.
 * - nums[l++] reads index l, then advances it.
 * - while (...) shrink keeps the window valid before every measurement.
 */
