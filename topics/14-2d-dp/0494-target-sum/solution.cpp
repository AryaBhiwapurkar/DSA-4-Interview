/*
 * 0494. Target Sum  |  Medium  |  2-D Dynamic Programming
 * Link: https://leetcode.com/problems/target-sum/
 *
 * Problem: Put + or - in front of every number; count the sign choices whose
 *          total equals target.
 *
 * Examples:
 *   [1,1,1,1,1], 3            -> 5
 *   [1], 1                    -> 1
 *   [0,0,0,0,0,0,0,0,1], 1    -> 256  (each 0 can take either sign)
 *   [100], -200               -> 0
 *   [1,2,1], 0                -> 2
 *
 * Approaches:
 *   1. Brute-force recursion                 O(2^n) time, O(n) space
 *   2. Memo on (index, running sum)          O(n * total) time, O(n * total) space
 *   3. Count subsets summing to (total+target)/2  ⭐   O(n * P) time, O(P) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force ----------
int goBrute(const vector<int>& nums, int target, int i, int s) {
    if (i == (int)nums.size()) return s == target;
    return goBrute(nums, target, i + 1, s + nums[i]) + goBrute(nums, target, i + 1, s - nums[i]);
}

int findTargetSumWaysBrute(const vector<int>& nums, int target) { return goBrute(nums, target, 0, 0); }

// ---------- Approach 2: Memo on (index, sum) ----------
int goMemo(const vector<int>& nums, int target, int i, int s, int off, vector<vector<int>>& memo) {
    if (i == (int)nums.size()) return s == target;
    int& m = memo[i][s + off];                     // shift: s ranges over [-total, total]
    if (m != -1) return m;
    return m = goMemo(nums, target, i + 1, s + nums[i], off, memo) +
               goMemo(nums, target, i + 1, s - nums[i], off, memo);
}

int findTargetSumWaysMemo(const vector<int>& nums, int target) {
    int total = accumulate(nums.begin(), nums.end(), 0);
    vector<vector<int>> memo(nums.size(), vector<int>(2 * total + 1, -1));
    return goMemo(nums, target, 0, 0, total, memo);
}

// ---------- Approach 3: Subset-Sum Count ⭐ ----------
int findTargetSumWays(const vector<int>& nums, int target) {
    int total = accumulate(nums.begin(), nums.end(), 0);
    if (abs(target) > total || (total + target) % 2 != 0) return 0;
    int want = (total + target) / 2;               // sum of the numbers that get a '+'
    vector<int> dp(want + 1, 0);
    dp[0] = 1;
    for (int x : nums)
        for (int s = want; s >= x; s--)            // backwards: each number used once
            dp[s] += dp[s - x];                    // x = 0 doubles every count: +0 and -0
    return dp[want];
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<int>, int>> tests = {
        {{1, 1, 1, 1, 1}, 3}, {{1}, 1}, {{0, 0, 0, 0, 0, 0, 0, 0, 1}, 1}, {{100}, -200}, {{1, 2, 1}, 0}
    };
    for (auto& [nums, target] : tests) {
        cout << "brute : " << findTargetSumWaysBrute(nums, target) << "\n";
        cout << "memo  : " << findTargetSumWaysMemo(nums, target) << "\n";
        cout << "subset: " << findTargetSumWays(nums, target) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - memo[i][s + off] shifts negative sums into a valid index range.
 * - accumulate(begin, end, 0) sums a vector (from <numeric>).
 * - A bool returned as int converts to 0 or 1.
 */
