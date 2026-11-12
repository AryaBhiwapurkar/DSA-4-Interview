"""
0410. Split Array Largest Sum  |  Hard  |  Binary Search
Link: https://leetcode.com/problems/split-array-largest-sum/

Problem: Split nums into k non-empty contiguous pieces minimising the
         largest piece sum; return that sum.

Examples:
  [7,2,5,10,8], k = 2     -> 18
  [1,2,3,4,5],  k = 2     -> 9
  [1,4,4],      k = 3     -> 4
  [2,3,1,2,4,3], k = 5    -> 4
  [0,0,5],      k = 3     -> 5
  [10,5,13],    k = 1     -> 28

Approaches:
  1. DP over prefixes                     O(k n^2) time, O(k n) space
  2. Binary search on the cap + greedy ⭐ O(n log sum) time, O(1) space   <- go-to
"""

from itertools import accumulate
from math import inf


# ---------- Approach 1: DP over Prefixes ----------
def split_array_dp(nums: list[int], k: int) -> int:
    n = len(nums)
    pre = [0, *accumulate(nums)]
    dp = [[inf] * (n + 1) for _ in range(k + 1)]
    dp[0][0] = 0  # 0 numbers in 0 pieces
    for j in range(1, k + 1):
        for i in range(1, n + 1):
            for p in range(j - 1, i):  # last piece is nums[p:i]
                dp[j][i] = min(dp[j][i], max(dp[j - 1][p], pre[i] - pre[p]))
    return dp[k][n]


# ---------- Approach 2: Binary Search on the Cap ⭐ ----------
def pieces_needed(nums: list[int], cap: int) -> int:
    pieces, cur = 1, 0
    for x in nums:
        if cur + x > cap:  # cut before x
            pieces += 1
            cur = 0
        cur += x
    return pieces


def split_array(nums: list[int], k: int) -> int:
    lo, hi = max(nums), sum(nums)
    while lo < hi:
        mid = (lo + hi) // 2
        if pieces_needed(nums, mid) <= k:  # fewer pieces is fine too
            hi = mid
        else:
            lo = mid + 1
    return lo


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([7, 2, 5, 10, 8], 2), ([1, 2, 3, 4, 5], 2), ([1, 4, 4], 3),
             ([2, 3, 1, 2, 4, 3], 5), ([0, 0, 5], 3), ([10, 5, 13], 1)]
    for nums, k in tests:
        print("dp    :", split_array_dp(nums, k))
        print("binary:", split_array(nums, k))
        print("---")

"""
Syntax notes (Python):
- [0, *accumulate(nums)] builds prefix sums with a leading 0.
- math.inf compares above any int, so min()/max() work in the DP table.
- max(inf, x) stays inf, so unreachable states never win a min().
"""
