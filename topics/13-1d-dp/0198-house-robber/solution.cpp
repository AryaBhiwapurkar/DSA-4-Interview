/*
 * 0198. House Robber  |  Medium  |  1-D Dynamic Programming
 * Link: https://leetcode.com/problems/house-robber/
 *
 * Problem: Houses in a row with money nums[i]. You can't rob two adjacent
 *          houses. Return the most money you can take.
 *
 * Examples:
 *   [1,2,3,1]    -> 4
 *   [2,7,9,3,1]  -> 12
 *   [5]          -> 5
 *   [2,1,1,2]    -> 4 (skipping two in a row can be best)
 *
 * Approaches:
 *   1. Memoized recursion (take / skip)  O(n) time, O(n) space
 *   2. Two variables (bottom-up)  ⭐      O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Memoized Recursion ----------
// best(i) = most money from houses i..n-1.
int best(const vector<int>& nums, int i, vector<int>& memo) {
    if (i >= (int)nums.size()) return 0;
    if (memo[i] != -1) return memo[i];
    return memo[i] = max(best(nums, i + 1, memo),               // skip i
                         nums[i] + best(nums, i + 2, memo));    // take i, skip i+1
}

int robMemo(const vector<int>& nums) {
    vector<int> memo(nums.size(), -1);
    return best(nums, 0, memo);
}

// ---------- Approach 2: Two Variables ⭐ ----------
int rob(const vector<int>& nums) {
    int prev2 = 0, prev1 = 0;                     // best up to i-2, best up to i-1
    for (int x : nums) {
        int cur = max(prev1, prev2 + x);          // skip x, or take x on top of i-2
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{1, 2, 3, 1}, {2, 7, 9, 3, 1}, {5}, {2, 1, 1, 2}};
    for (auto& t : tests) {
        cout << "memo: " << robMemo(t) << "\n";
        cout << "dp  : " << rob(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Range-for `for (int x : nums)` when the index isn't needed.
 * - `return memo[i] = max(...)` caches and returns in one line.
 * - Max total 100 * 400 = 40,000 fits in int.
 */
