/*
 * 0213. House Robber II  |  Medium  |  1-D Dynamic Programming
 * Link: https://leetcode.com/problems/house-robber-ii/
 *
 * Problem: House Robber, but the houses form a circle: the first and last
 *          are neighbours too. Return the most money you can take.
 *
 * Examples:
 *   [2,3,2]          -> 3
 *   [1,2,3,1]        -> 4
 *   [1,2,3]          -> 3
 *   [5]              -> 5
 *   [1,3,1,3,100]    -> 103
 *
 * Approaches:
 *   1. Memoized recursion with a "took first" flag  O(n) time, O(n) space
 *   2. Two linear passes (skip first / skip last)  ⭐  O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Memoized Recursion with a Flag ----------
int best(const vector<int>& nums, int i, int tookFirst, vector<vector<int>>& memo) {
    int n = nums.size();
    if (i >= n) return 0;
    if (memo[tookFirst][i] != -1) return memo[tookFirst][i];
    int res = best(nums, i + 1, tookFirst, memo);                 // skip i
    if (!(i == n - 1 && tookFirst))                               // last house touches the first
        res = max(res, nums[i] + best(nums, i + 2, tookFirst || i == 0, memo));
    return memo[tookFirst][i] = res;
}

int robMemo(const vector<int>& nums) {
    vector<vector<int>> memo(2, vector<int>(nums.size(), -1));
    return best(nums, 0, 0, memo);
}

// ---------- Approach 2: Two Linear Passes ⭐ ----------
int robLine(const vector<int>& nums, int lo, int hi) {   // House Robber I on nums[lo..hi]
    int prev2 = 0, prev1 = 0;
    for (int i = lo; i <= hi; i++) {
        int cur = max(prev1, prev2 + nums[i]);
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

int rob(const vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];                   // both ranges below would be empty
    return max(robLine(nums, 0, n - 2), robLine(nums, 1, n - 1));   // first and last never both
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{2, 3, 2}, {1, 2, 3, 1}, {1, 2, 3}, {5}, {1, 3, 1, 3, 100}};
    for (auto& t : tests) {
        cout << "memo  : " << robMemo(t) << "\n";
        cout << "passes: " << rob(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Passing (lo, hi) indices avoids copying sub-vectors for each pass.
 * - memo[flag][i] with flag as int 0/1 indexes a 2-row table.
 * - `tookFirst || i == 0` converts to bool, then to int on the call.
 */
