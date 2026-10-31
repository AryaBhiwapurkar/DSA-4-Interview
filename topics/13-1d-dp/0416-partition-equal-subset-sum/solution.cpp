/*
 * 0416. Partition Equal Subset Sum  |  Medium  |  1-D Dynamic Programming
 * Link: https://leetcode.com/problems/partition-equal-subset-sum/
 *
 * Problem: Can the array be split into two subsets with equal sums?
 *
 * Examples:
 *   [1,5,11,5]  -> true
 *   [1,2,3,5]   -> false
 *   [1,1]       -> true
 *   [100]       -> false
 *   [2,2,1,1]   -> true
 *   [1,2,5]     -> false (even sum 8, but 4 isn't reachable)
 *
 * Approaches:
 *   1. Memoized recursion (index, remaining)     O(n * S) time, O(n * S) space
 *   2. 1-D boolean DP, sums iterated backwards  ⭐  O(n * S) time, O(S) space   <- go-to
 *   3. Bitset of reachable sums                  O(n * S / 64) time, O(S) space
 *   S = half of the total sum.
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Memoized Recursion ----------
bool canMake(const vector<int>& nums, int i, int rem, vector<vector<int>>& memo) {
    if (rem == 0) return true;
    if (i == (int)nums.size() || rem < 0) return false;
    int& m = memo[i][rem];
    if (m != -1) return m;
    m = canMake(nums, i + 1, rem - nums[i], memo) || canMake(nums, i + 1, rem, memo);   // take or skip
    return m;
}

bool canPartitionMemo(const vector<int>& nums) {
    int total = accumulate(nums.begin(), nums.end(), 0);
    if (total % 2) return false;                  // odd total can't split evenly
    vector<vector<int>> memo(nums.size(), vector<int>(total / 2 + 1, -1));
    return canMake(nums, 0, total / 2, memo);
}

// ---------- Approach 2: 1-D Boolean DP ⭐ ----------
bool canPartition(const vector<int>& nums) {
    int total = accumulate(nums.begin(), nums.end(), 0);
    if (total % 2) return false;
    int target = total / 2;
    vector<bool> dp(target + 1, false);           // dp[s]: some subset of the numbers so far sums to s
    dp[0] = true;
    for (int x : nums)
        for (int s = target; s >= x; s--)         // backwards: each number used at most once
            if (dp[s - x]) dp[s] = true;
    return dp[target];
}

// ---------- Approach 3: Bitset ----------
bool canPartitionBitset(const vector<int>& nums) {
    int total = accumulate(nums.begin(), nums.end(), 0);
    if (total % 2) return false;
    bitset<10001> bits(1);                        // bit s set = sum s reachable; max half-sum 10^4
    for (int x : nums) bits |= bits << x;         // every reachable sum, plus x
    return bits[total / 2];
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{1, 5, 11, 5}, {1, 2, 3, 5}, {1, 1}, {100}, {2, 2, 1, 1}, {1, 2, 5}};
    cout << boolalpha;
    for (auto& t : tests) {
        cout << "memo  : " << canPartitionMemo(t) << "\n";
        cout << "dp    : " << canPartition(t) << "\n";
        cout << "bitset: " << canPartitionBitset(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - accumulate(begin, end, 0) sums a vector (header <numeric>, in bits/stdc++.h).
 * - `int& m = memo[i][rem];` aliases the memo cell to read and write it once.
 * - bitset<N> must have a compile-time size; `bits << x` drops bits past N-1.
 */
