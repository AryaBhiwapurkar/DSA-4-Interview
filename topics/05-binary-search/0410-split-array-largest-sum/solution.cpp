/*
 * 0410. Split Array Largest Sum  |  Hard  |  Binary Search
 * Link: https://leetcode.com/problems/split-array-largest-sum/
 *
 * Problem: Split nums into k non-empty contiguous pieces minimising the
 *          largest piece sum; return that sum.
 *
 * Examples:
 *   [7,2,5,10,8], k = 2     -> 18
 *   [1,2,3,4,5],  k = 2     -> 9
 *   [1,4,4],      k = 3     -> 4
 *   [2,3,1,2,4,3], k = 5    -> 4
 *   [0,0,5],      k = 3     -> 5
 *   [10,5,13],    k = 1     -> 28
 *
 * Approaches:
 *   1. DP over prefixes                     O(k n^2) time, O(k n) space
 *   2. Binary search on the cap + greedy ⭐ O(n log sum) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: DP over Prefixes ----------
int splitArrayDP(const vector<int>& nums, int k) {
    int n = nums.size();
    vector<long long> pre(n + 1, 0);
    for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + nums[i];
    const long long INF = LLONG_MAX;
    vector<vector<long long>> dp(k + 1, vector<long long>(n + 1, INF));
    dp[0][0] = 0;                              // 0 numbers in 0 pieces
    for (int j = 1; j <= k; j++)
        for (int i = 1; i <= n; i++)
            for (int p = j - 1; p < i; p++)    // last piece is nums[p..i-1]
                if (dp[j - 1][p] != INF)
                    dp[j][i] = min(dp[j][i], max(dp[j - 1][p], pre[i] - pre[p]));
    return dp[k][n];
}

// ---------- Approach 2: Binary Search on the Cap ⭐ ----------
int piecesNeeded(const vector<int>& nums, long long cap) {
    int pieces = 1;
    long long cur = 0;
    for (int x : nums) {
        if (cur + x > cap) { pieces++; cur = 0; }   // cut before x
        cur += x;
    }
    return pieces;
}

int splitArray(const vector<int>& nums, int k) {
    long long lo = *max_element(nums.begin(), nums.end());
    long long hi = accumulate(nums.begin(), nums.end(), 0LL);
    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (piecesNeeded(nums, mid) <= k) hi = mid;   // fewer pieces is fine too
        else lo = mid + 1;
    }
    return lo;
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<int>, int>> tests = {
        {{7, 2, 5, 10, 8}, 2}, {{1, 2, 3, 4, 5}, 2}, {{1, 4, 4}, 3},
        {{2, 3, 1, 2, 4, 3}, 5}, {{0, 0, 5}, 3}, {{10, 5, 13}, 1}};
    for (auto& [nums, k] : tests) {
        cout << "dp    : " << splitArrayDP(nums, k) << "\n";
        cout << "binary: " << splitArray(nums, k) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - accumulate(..., 0LL) sums in long long; plain 0 would sum in int.
 * - *max_element(begin, end) dereferences the iterator to the largest value.
 * - LLONG_MAX as "unreachable" in DP; check it before using it in max().
 */
