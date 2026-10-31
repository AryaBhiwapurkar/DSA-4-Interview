"""
0416. Partition Equal Subset Sum  |  Medium  |  1-D Dynamic Programming
Link: https://leetcode.com/problems/partition-equal-subset-sum/

Problem: Can the array be split into two subsets with equal sums?

Examples:
  [1,5,11,5]  -> true
  [1,2,3,5]   -> false
  [1,1]       -> true
  [100]       -> false
  [2,2,1,1]   -> true
  [1,2,5]     -> false (even sum 8, but 4 isn't reachable)

Approaches:
  1. Memoized recursion (index, remaining)     O(n * S) time, O(n * S) space
  2. 1-D boolean DP, sums iterated backwards  ⭐  O(n * S) time, O(S) space   <- go-to
  3. Bitset of reachable sums                  O(n * S / 64) time, O(S) space
  S = half of the total sum.
"""

from functools import cache


# ---------- Approach 1: Memoized Recursion ----------
def can_partition_memo(nums: list[int]) -> bool:
    total = sum(nums)
    if total % 2:  # odd total can't split evenly
        return False

    @cache
    def can(i: int, rem: int) -> bool:
        if rem == 0:
            return True
        if i == len(nums) or rem < 0:
            return False
        return can(i + 1, rem - nums[i]) or can(i + 1, rem)  # take or skip

    return can(0, total // 2)


# ---------- Approach 2: 1-D Boolean DP ⭐ ----------
def can_partition(nums: list[int]) -> bool:
    total = sum(nums)
    if total % 2:
        return False
    target = total // 2
    dp = [True] + [False] * target  # dp[s]: some subset so far sums to s
    for x in nums:
        for s in range(target, x - 1, -1):  # backwards: each number used at most once
            dp[s] = dp[s] or dp[s - x]
    return dp[target]


# ---------- Approach 3: Bitset ----------
def can_partition_bitset(nums: list[int]) -> bool:
    total = sum(nums)
    if total % 2:
        return False
    bits = 1  # bit s set = sum s reachable
    for x in nums:
        bits |= bits << x  # every reachable sum, plus x
    return bool(bits >> (total // 2) & 1)


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[1, 5, 11, 5], [1, 2, 3, 5], [1, 1], [100], [2, 2, 1, 1], [1, 2, 5]]:
        print("memo  :", can_partition_memo(t))
        print("dp    :", can_partition(t))
        print("bitset:", can_partition_bitset(t))
        print("---")

"""
Syntax notes (Python):
- range(target, x - 1, -1) counts down from target to x inclusive.
- Python ints are arbitrary precision, so an int works as a bitset of any size.
- `bits >> k & 1`: >> binds tighter than &, so this reads bit k.
"""
