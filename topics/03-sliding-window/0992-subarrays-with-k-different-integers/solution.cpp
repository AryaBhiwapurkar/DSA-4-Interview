/*
 * 0992. Subarrays with K Different Integers  |  Hard  |  Sliding Window
 * Link: https://leetcode.com/problems/subarrays-with-k-different-integers/
 *
 * Problem: Count contiguous subarrays with exactly k distinct values.
 *
 * Examples:
 *   [1,2,1,2,3], k = 2  -> 7
 *   [1,2,1,3,4], k = 3  -> 3
 *   [1,1,1],     k = 1  -> 6
 *   [1,2],       k = 3  -> 0
 *
 * Approaches:
 *   1. All subarrays with a set                 O(n^2) time, O(n) space
 *   2. atMost(k) - atMost(k - 1)  ⭐            O(n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: All Subarrays ----------
int subarraysWithKDistinctBrute(const vector<int>& nums, int k) {
    int n = nums.size(), count = 0;
    for (int i = 0; i < n; i++) {
        unordered_set<int> seen;
        for (int j = i; j < n; j++) {
            seen.insert(nums[j]);
            if ((int)seen.size() > k) break;
            if ((int)seen.size() == k) count++;
        }
    }
    return count;
}

// ---------- Approach 2: atMost Difference ⭐ ----------
int atMost(const vector<int>& nums, int k) {
    vector<int> cnt(nums.size() + 1, 0);           // values are in 1..n
    int l = 0, distinct = 0, total = 0;
    for (int r = 0; r < (int)nums.size(); r++) {
        if (cnt[nums[r]]++ == 0) distinct++;
        while (distinct > k)
            if (--cnt[nums[l++]] == 0) distinct--;
        total += r - l + 1;                        // subarrays ending at r with <= k distinct
    }
    return total;
}

int subarraysWithKDistinct(const vector<int>& nums, int k) {
    return atMost(nums, k) - atMost(nums, k - 1);
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<int>, int>> tests = {{{1, 2, 1, 2, 3}, 2}, {{1, 2, 1, 3, 4}, 3}, {{1, 1, 1}, 1}, {{1, 2}, 3}};
    for (auto& [nums, k] : tests) {
        cout << "brute : " << subarraysWithKDistinctBrute(nums, k) << "\n";
        cout << "atMost: " << subarraysWithKDistinct(nums, k) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - if (cnt[x]++ == 0) distinct++; tests the old count, then increments.
 * - while (...) if (...) ...; a single-statement loop body without braces.
 * - A vector<int> sized by the value range replaces a hashmap when values are bounded.
 */
