/*
 * 0974. Subarray Sums Divisible by K  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/subarray-sums-divisible-by-k/
 *
 * Problem: Count non-empty subarrays whose sum is divisible by k (values may be negative).
 *
 * Examples:
 *   [4,5,0,-2,-3,1], k = 5  -> 7
 *   [5],             k = 9  -> 0
 *   [0,0],           k = 3  -> 3
 *   [-5],            k = 5  -> 1
 *   [-1,2,9],        k = 2  -> 2
 *
 * Approaches:
 *   1. All subarrays             O(n^2) time, O(1) space
 *   2. Remainder counts  ⭐      O(n) time, O(k) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: All Subarrays ----------
int subarraysDivByKBrute(const vector<int>& nums, int k) {
    int n = nums.size(), count = 0;
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += nums[j];
            if (sum % k == 0) count++;             // -10 % 5 == 0 too, so no normalising needed here
        }
    }
    return count;
}

// ---------- Approach 2: Remainder Counts ⭐ ----------
int subarraysDivByK(const vector<int>& nums, int k) {
    vector<int> cnt(k, 0);
    cnt[0] = 1;                                    // empty prefix
    int r = 0, count = 0;
    for (int x : nums) {
        r = ((r + x) % k + k) % k;                 // keep r in 0..k-1 even for negatives
        count += cnt[r]++;                         // pair with every earlier equal remainder
    }
    return count;
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<int>, int>> tests = {
        {{4, 5, 0, -2, -3, 1}, 5}, {{5}, 9}, {{0, 0}, 3}, {{-5}, 5}, {{-1, 2, 9}, 2}};
    for (auto& [nums, k] : tests) {
        cout << "brute    : " << subarraysDivByKBrute(nums, k) << "\n";
        cout << "remainder: " << subarraysDivByK(nums, k) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - C++ % takes the sign of the dividend: -2 % 5 == -2. (a % k + k) % k normalises.
 * - count += cnt[r]++ reads the old count, then increments (post-increment).
 * - Reducing r every step keeps it small, so the running value never overflows.
 */
