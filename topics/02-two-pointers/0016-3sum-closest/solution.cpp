/*
 * 0016. 3Sum Closest  |  Medium  |  Two Pointers
 * Link: https://leetcode.com/problems/3sum-closest/
 *
 * Problem: Return the sum of three distinct-index elements closest to target.
 *
 * Examples:
 *   [-1,2,1,-4], target = 1    -> 2
 *   [0,0,0],     target = 1    -> 0
 *   [1,1,1,0],   target = -100 -> 2
 *   [4,0,5,-5,3,3,0,-4,-5], target = -2 -> -2
 *
 * Approaches:
 *   1. All triples                    O(n^3) time, O(1) space
 *   2. Sort + two pointers  ⭐        O(n^2) time, O(1) extra   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: All Triples ----------
int threeSumClosestBrute(const vector<int>& nums, int target) {
    int n = nums.size(), best = nums[0] + nums[1] + nums[2];
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = j + 1; k < n; k++) {
                int s = nums[i] + nums[j] + nums[k];
                if (abs(s - target) < abs(best - target)) best = s;
            }
    return best;
}

// ---------- Approach 2: Sort + Two Pointers ⭐ ----------
int threeSumClosest(vector<int> nums, int target) {
    sort(nums.begin(), nums.end());
    int n = nums.size(), best = nums[0] + nums[1] + nums[2];   // a real triple, not INT_MAX
    for (int i = 0; i + 2 < n; i++) {
        int lo = i + 1, hi = n - 1;
        while (lo < hi) {
            int s = nums[i] + nums[lo] + nums[hi];
            if (abs(s - target) < abs(best - target)) best = s;
            if (s < target) lo++;                  // need bigger
            else if (s > target) hi--;             // need smaller
            else return s;                         // exact: can't beat it
        }
    }
    return best;
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<int>, int>> tests = {
        {{-1, 2, 1, -4}, 1}, {{0, 0, 0}, 1}, {{1, 1, 1, 0}, -100}, {{4, 0, 5, -5, 3, 3, 0, -4, -5}, -2}};
    for (auto& [nums, t] : tests) {
        cout << "brute   : " << threeSumClosestBrute(nums, t) << "\n";
        cout << "pointers: " << threeSumClosest(nums, t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Loop bound i + 2 < n (signed int) leaves room for lo and hi.
 * - Seed best from real data to avoid INT_MAX - target overflow.
 * - Taking nums by value lets the function sort its own copy.
 */
