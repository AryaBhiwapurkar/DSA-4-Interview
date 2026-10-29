"""
0209. Minimum Size Subarray Sum  |  Medium  |  Sliding Window
Link: https://leetcode.com/problems/minimum-size-subarray-sum/

Problem: Positive integers; return the length of the shortest contiguous
         subarray with sum >= target, or 0 if none.

Examples:
  target=7,  [2,3,1,2,4,3]       -> 2
  target=4,  [1,4,4]             -> 1
  target=11, [1,1,1,1,1,1,1,1]   -> 0
  target=15, [1,2,3,4,5]         -> 5

Approaches:
  1. Brute force                    O(n^2) time, O(1) space
  2. Prefix sums + binary search    O(n log n) time, O(n) space
  3. Sliding window  ⭐              O(n) time, O(1) space   <- go-to
"""

from bisect import bisect_left
from itertools import accumulate
from math import inf


# ---------- Approach 1: Brute Force ----------
def min_sub_array_len_brute(target: int, nums: list[int]) -> int:
    best = inf
    for i in range(len(nums)):
        s = 0
        for j in range(i, len(nums)):
            s += nums[j]
            if s >= target:
                best = min(best, j - i + 1)
                break  # longer windows from i can't be shorter
    return 0 if best == inf else int(best)


# ---------- Approach 2: Prefix Sums + Binary Search ----------
def min_sub_array_len_binary(target: int, nums: list[int]) -> int:
    P = [0, *accumulate(nums)]  # P[i] = sum of nums[:i], strictly increasing
    best = inf
    for i in range(len(nums)):
        j = bisect_left(P, P[i] + target, i + 1)  # first j with P[j] - P[i] >= target
        if j < len(P):
            best = min(best, j - i)
    return 0 if best == inf else int(best)


# ---------- Approach 3: Sliding Window ⭐ ----------
def min_sub_array_len(target: int, nums: list[int]) -> int:
    l = s = 0
    best = inf
    for r, x in enumerate(nums):
        s += x
        while s >= target:  # valid: record, then try to shrink
            best = min(best, r - l + 1)
            s -= nums[l]
            l += 1
    return 0 if best == inf else int(best)


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [(7, [2, 3, 1, 2, 4, 3]), (4, [1, 4, 4]), (11, [1, 1, 1, 1, 1, 1, 1, 1]), (15, [1, 2, 3, 4, 5])]
    for target, nums in tests:
        print("brute :", min_sub_array_len_brute(target, nums))
        print("binary:", min_sub_array_len_binary(target, nums))
        print("window:", min_sub_array_len(target, nums))
        print("---")

"""
Syntax notes (Python):
- [0, *accumulate(nums)] builds prefix sums with a leading 0.
- bisect_left(a, x, lo) searches a[lo:] without copying.
- math.inf is a float; convert with int() before returning.
"""
