"""
0198. House Robber  |  Medium  |  1-D Dynamic Programming
Link: https://leetcode.com/problems/house-robber/

Problem: Houses in a row with money nums[i]. You can't rob two adjacent
         houses. Return the most money you can take.

Examples:
  [1,2,3,1]    -> 4
  [2,7,9,3,1]  -> 12
  [5]          -> 5
  [2,1,1,2]    -> 4 (skipping two in a row can be best)

Approaches:
  1. Memoized recursion (take / skip)  O(n) time, O(n) space
  2. Two variables (bottom-up)  ⭐      O(n) time, O(1) space   <- go-to
"""

from functools import cache


# ---------- Approach 1: Memoized Recursion ----------
def rob_memo(nums: list[int]) -> int:
    @cache
    def best(i: int) -> int:  # most money from houses i..n-1
        if i >= len(nums):
            return 0
        return max(best(i + 1), nums[i] + best(i + 2))  # skip i, or take i and skip i+1

    return best(0)


# ---------- Approach 2: Two Variables ⭐ ----------
def rob(nums: list[int]) -> int:
    prev2 = prev1 = 0  # best up to i-2, best up to i-1
    for x in nums:
        prev2, prev1 = prev1, max(prev1, prev2 + x)  # skip x, or take x on top of i-2
    return prev1


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[1, 2, 3, 1], [2, 7, 9, 3, 1], [5], [2, 1, 1, 2]]:
        print("memo:", rob_memo(t))
        print("dp  :", rob(t))
        print("---")

"""
Syntax notes (Python):
- Tuple assignment reads the old prev1/prev2 before writing either.
- @cache on a nested function avoids a manual memo dict.
- Recursion depth is n ≤ 100 here; bottom-up avoids the limit entirely for large n.
"""
