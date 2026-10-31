"""
0213. House Robber II  |  Medium  |  1-D Dynamic Programming
Link: https://leetcode.com/problems/house-robber-ii/

Problem: House Robber, but the houses form a circle: the first and last
         are neighbours too. Return the most money you can take.

Examples:
  [2,3,2]          -> 3
  [1,2,3,1]        -> 4
  [1,2,3]          -> 3
  [5]              -> 5
  [1,3,1,3,100]    -> 103

Approaches:
  1. Memoized recursion with a "took first" flag  O(n) time, O(n) space
  2. Two linear passes (skip first / skip last)  ⭐  O(n) time, O(1) space   <- go-to
"""

from functools import cache


# ---------- Approach 1: Memoized Recursion with a Flag ----------
def rob_memo(nums: list[int]) -> int:
    n = len(nums)

    @cache
    def best(i: int, took_first: bool) -> int:
        if i >= n:
            return 0
        res = best(i + 1, took_first)  # skip i
        if not (i == n - 1 and took_first):  # last house touches the first
            res = max(res, nums[i] + best(i + 2, took_first or i == 0))
        return res

    return best(0, False)


# ---------- Approach 2: Two Linear Passes ⭐ ----------
def rob_line(houses: list[int]) -> int:  # House Robber I
    prev2 = prev1 = 0
    for x in houses:
        prev2, prev1 = prev1, max(prev1, prev2 + x)
    return prev1


def rob(nums: list[int]) -> int:
    if len(nums) == 1:  # both slices below would be empty
        return nums[0]
    return max(rob_line(nums[:-1]), rob_line(nums[1:]))  # first and last never both


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[2, 3, 2], [1, 2, 3, 1], [1, 2, 3], [5], [1, 3, 1, 3, 100]]:
        print("memo  :", rob_memo(t))
        print("passes:", rob(t))
        print("---")

"""
Syntax notes (Python):
- nums[:-1] drops the last element, nums[1:] drops the first (both are copies).
- @cache keys on all arguments, including the bool flag.
- `a or b` on bools returns a bool here (both operands are bools).
"""
