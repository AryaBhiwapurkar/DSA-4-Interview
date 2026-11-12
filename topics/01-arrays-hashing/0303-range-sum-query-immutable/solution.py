"""
0303. Range Sum Query - Immutable  |  Easy  |  Arrays & Hashing
Link: https://leetcode.com/problems/range-sum-query-immutable/

Problem: Fixed array, many queries: sum of nums[left..right] inclusive.

Examples:
  NumArray([-2,0,3,-5,2,-1])
  sumRange(0,2) -> 1
  sumRange(2,5) -> -1
  sumRange(0,5) -> -3
  sumRange(3,3) -> -5   (single element)

Approaches:
  1. Loop on every query        O(1) build, O(n) per query
  2. Prefix sums  ⭐            O(n) build, O(1) per query, O(n) space   <- go-to
"""

from itertools import accumulate


# ---------- Approach 1: Loop per Query ----------
class NumArrayBrute:
    def __init__(self, nums: list[int]) -> None:
        self.a = nums

    def sumRange(self, left: int, right: int) -> int:
        return sum(self.a[left:right + 1])


# ---------- Approach 2: Prefix Sums ⭐ ----------
class NumArray:
    def __init__(self, nums: list[int]) -> None:
        self.P = list(accumulate(nums, initial=0))  # P[i] = sum of the first i elements

    def sumRange(self, left: int, right: int) -> int:
        return self.P[right + 1] - self.P[left]


# ---------- Driver ----------
if __name__ == "__main__":
    nums = [-2, 0, 3, -5, 2, -1]
    b, p = NumArrayBrute(nums), NumArray(nums)
    for l, r in [(0, 2), (2, 5), (0, 5), (3, 3)]:
        print("brute :", b.sumRange(l, r))
        print("prefix:", p.sumRange(l, r))
        print("---")

"""
Syntax notes (Python):
- accumulate(nums, initial=0) yields 0, then each running sum (n + 1 values, 3.8+).
- Slices are half-open: a[left:right + 1] includes index right.
- LeetCode keeps camelCase method names (sumRange) because its harness calls them by name.
"""
