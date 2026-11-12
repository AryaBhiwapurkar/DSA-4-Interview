/*
 * 0560. Subarray Sum Equals K  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/subarray-sum-equals-k/
 *
 * Problem: Count contiguous subarrays whose sum is exactly k (values may be negative).
 *
 * Examples:
 *   [1,1,1],     k = 2  -> 2
 *   [1,2,3],     k = 3  -> 2
 *   [3,4,-7,3],  k = 3  -> 3
 *   [0,0,0],     k = 0  -> 6
 *   [1,-1,0],    k = 0  -> 3
 *
 * Approaches:
 *   1. All start/end pairs           O(n^2) time, O(1) space
 *   2. Prefix sum + count map  ⭐    O(n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: All Pairs ----------
int subarraySumBrute(const vector<int>& nums, int k) {
    int n = nums.size(), count = 0;
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += nums[j];
            if (sum == k) count++;
        }
    }
    return count;
}

// ---------- Approach 2: Prefix Sum + Count Map ⭐ ----------
int subarraySum(const vector<int>& nums, int k) {
    unordered_map<int, int> seen{{0, 1}};          // empty prefix: subarrays starting at 0
    int prefix = 0, count = 0;
    for (int x : nums) {
        prefix += x;
        auto it = seen.find(prefix - k);           // earlier prefix P with prefix - P == k
        if (it != seen.end()) count += it->second;
        seen[prefix]++;                            // add after lookup
    }
    return count;
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<int>, int>> tests = {
        {{1, 1, 1}, 2}, {{1, 2, 3}, 3}, {{3, 4, -7, 3}, 3}, {{0, 0, 0}, 0}, {{1, -1, 0}, 0}};
    for (auto& [nums, k] : tests) {
        cout << "brute : " << subarraySumBrute(nums, k) << "\n";
        cout << "prefix: " << subarraySum(nums, k) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - unordered_map<int,int> m{{0, 1}} seeds a map with an initializer list.
 * - find() for lookups, operator[]++ only when you mean to insert/increment.
 * - Structured bindings over vector<pair<...>>: for (auto& [nums, k] : tests).
 */
