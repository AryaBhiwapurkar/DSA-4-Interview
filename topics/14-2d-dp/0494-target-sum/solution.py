"""
0494. Target Sum  |  Medium  |  2-D Dynamic Programming
Link: https://leetcode.com/problems/target-sum/

Problem: Put + or - in front of every number; count the sign choices whose
         total equals target.

Examples:
  [1,1,1,1,1], 3            -> 5
  [1], 1                    -> 1
  [0,0,0,0,0,0,0,0,1], 1    -> 256  (each 0 can take either sign)
  [100], -200               -> 0
  [1,2,1], 0                -> 2

Approaches:
  1. Brute-force recursion                 O(2^n) time, O(n) space
  2. Memo on (index, running sum)          O(n * total) time, O(n * total) space
  3. Count subsets summing to (total+target)/2  ⭐   O(n * P) time, O(P) space   <- go-to
"""

from functools import cache


# ---------- Approach 1: Brute Force ----------
def find_target_sum_ways_brute(nums: list[int], target: int) -> int:
    def go(i: int, s: int) -> int:
        if i == len(nums):
            return int(s == target)
        return go(i + 1, s + nums[i]) + go(i + 1, s - nums[i])

    return go(0, 0)


# ---------- Approach 2: Memo on (index, sum) ----------
def find_target_sum_ways_memo(nums: list[int], target: int) -> int:
    @cache
    def go(i: int, s: int) -> int:
        if i == len(nums):
            return int(s == target)
        return go(i + 1, s + nums[i]) + go(i + 1, s - nums[i])

    return go(0, 0)


# ---------- Approach 3: Subset-Sum Count ⭐ ----------
def find_target_sum_ways(nums: list[int], target: int) -> int:
    total = sum(nums)
    if abs(target) > total or (total + target) % 2:
        return 0
    want = (total + target) // 2  # sum of the numbers that get a '+'
    dp = [1] + [0] * want  # dp[s]: subsets so far summing to s
    for x in nums:
        for s in range(want, x - 1, -1):  # backwards: each number used once
            dp[s] += dp[s - x]  # x = 0 doubles every count: +0 and -0
    return dp[want]


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([1, 1, 1, 1, 1], 3), ([1], 1), ([0, 0, 0, 0, 0, 0, 0, 0, 1], 1), ([100], -200), ([1, 2, 1], 0)]
    for nums, target in tests:
        print("brute :", find_target_sum_ways_brute(nums, target))
        print("memo  :", find_target_sum_ways_memo(nums, target))
        print("subset:", find_target_sum_ways(nums, target))
        print("---")

"""
Syntax notes (Python):
- int(True) == 1, so int(s == target) counts a match as one way.
- Negative running sums are fine as @cache keys (no offset needed, unlike an array).
- (total + target) % 2 is truthy when odd: no integer split exists.
"""
