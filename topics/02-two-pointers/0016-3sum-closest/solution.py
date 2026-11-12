"""
0016. 3Sum Closest  |  Medium  |  Two Pointers
Link: https://leetcode.com/problems/3sum-closest/

Problem: Return the sum of three distinct-index elements closest to target.

Examples:
  [-1,2,1,-4], target = 1    -> 2
  [0,0,0],     target = 1    -> 0
  [1,1,1,0],   target = -100 -> 2
  [4,0,5,-5,3,3,0,-4,-5], target = -2 -> -2

Approaches:
  1. All triples                    O(n^3) time, O(1) space
  2. Sort + two pointers  ⭐        O(n^2) time, O(1) extra   <- go-to
"""

from itertools import combinations


# ---------- Approach 1: All Triples ----------
def three_sum_closest_brute(nums: list[int], target: int) -> int:
    return min((sum(c) for c in combinations(nums, 3)), key=lambda s: abs(s - target))


# ---------- Approach 2: Sort + Two Pointers ⭐ ----------
def three_sum_closest(nums: list[int], target: int) -> int:
    nums = sorted(nums)
    best = nums[0] + nums[1] + nums[2]
    for i in range(len(nums) - 2):
        lo, hi = i + 1, len(nums) - 1
        while lo < hi:
            s = nums[i] + nums[lo] + nums[hi]
            if abs(s - target) < abs(best - target):
                best = s
            if s < target:
                lo += 1  # need bigger
            elif s > target:
                hi -= 1  # need smaller
            else:
                return s  # exact: can't beat it
    return best


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([-1, 2, 1, -4], 1), ([0, 0, 0], 1), ([1, 1, 1, 0], -100), ([4, 0, 5, -5, 3, 3, 0, -4, -5], -2)]
    for nums, t in tests:
        print("brute   :", three_sum_closest_brute(nums, t))
        print("pointers:", three_sum_closest(nums, t))
        print("---")

"""
Syntax notes (Python):
- min(iterable, key=...) picks the element with the smallest key.
- itertools.combinations(nums, 3) yields index-distinct triples.
- sorted(nums) returns a new list, leaving the caller's input alone.
"""
