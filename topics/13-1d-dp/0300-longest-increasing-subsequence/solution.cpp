/*
 * 0300. Longest Increasing Subsequence  |  Medium  |  1-D Dynamic Programming
 * Link: https://leetcode.com/problems/longest-increasing-subsequence/
 *
 * Problem: Length of the longest strictly increasing subsequence (elements in
 *          order, not necessarily adjacent).
 *
 * Examples:
 *   [10,9,2,5,3,7,101,18]  -> 4
 *   [0,1,0,3,2,3]          -> 4
 *   [7,7,7,7,7,7,7]        -> 1
 *   [5]                    -> 1
 *   [4,10,4,3,8,9]         -> 3
 *
 * Approaches:
 *   1. DP: longest ending at i                 O(n^2) time, O(n) space
 *   2. Tails array + binary search  ⭐          O(n log n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: O(n^2) DP ----------
int lengthOfLISDP(const vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, 1);                         // dp[i]: LIS that ends exactly at i
    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
            if (nums[j] < nums[i]) dp[i] = max(dp[i], dp[j] + 1);
    return *max_element(dp.begin(), dp.end());
}

// ---------- Approach 2: Tails + Binary Search ⭐ ----------
int lengthOfLIS(const vector<int>& nums) {
    vector<int> tails;                            // tails[k]: smallest tail of any increasing run of length k+1
    for (int x : nums) {
        auto it = lower_bound(tails.begin(), tails.end(), x);   // first tail >= x (strict increase)
        if (it == tails.end()) tails.push_back(x);              // x extends the longest run
        else *it = x;                                           // x is a smaller tail for that length
    }
    return tails.size();
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {
        {10, 9, 2, 5, 3, 7, 101, 18}, {0, 1, 0, 3, 2, 3}, {7, 7, 7, 7, 7, 7, 7}, {5}, {4, 10, 4, 3, 8, 9}
    };
    for (auto& t : tests) {
        cout << "dp    : " << lengthOfLISDP(t) << "\n";
        cout << "tails : " << lengthOfLIS(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - lower_bound: first element >= x; upper_bound: first element > x.
 *   Use lower_bound for strictly increasing, upper_bound for non-decreasing.
 * - `*it = x` overwrites through the iterator.
 * - *max_element(...) returns the value, not the iterator.
 */
