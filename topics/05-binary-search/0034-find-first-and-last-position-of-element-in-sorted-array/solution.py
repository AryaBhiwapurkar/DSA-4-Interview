"""
0034. Find First and Last Position of Element in Sorted Array  |  Medium  |  Binary Search
Link: https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/

Problem: Sorted array with duplicates. Return [first, last] index of
         target, or [-1,-1]. O(log n).

Examples:
  [5,7,7,8,8,10], target 8  -> [3,4]
  [5,7,7,8,8,10], target 6  -> [-1,-1]
  [],             target 0  -> [-1,-1]
  [1],            target 1  -> [0,0]
  [2,2,2],        target 2  -> [0,2]
  [1,2,3],        target 4  -> [-1,-1]

Approaches:
  1. Linear scan           O(n) time, O(1) space
  2. Two lower bounds  ⭐   O(log n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Linear Scan ----------
def search_range_linear(nums: list[int], target: int) -> list[int]:
    idx = [i for i, x in enumerate(nums) if x == target]
    return [idx[0], idx[-1]] if idx else [-1, -1]


# ---------- Approach 2: Two Lower Bounds ⭐ ----------
def lower_bound(nums: list[int], x: int) -> int:  # first index with nums[i] >= x
    lo, hi = 0, len(nums)
    while lo < hi:
        mid = (lo + hi) // 2
        if nums[mid] < x:
            lo = mid + 1
        else:
            hi = mid
    return lo


def search_range(nums: list[int], target: int) -> list[int]:
    first = lower_bound(nums, target)
    if first == len(nums) or nums[first] != target:  # bounds check first
        return [-1, -1]
    return [first, lower_bound(nums, target + 1) - 1]


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([5, 7, 7, 8, 8, 10], 8), ([5, 7, 7, 8, 8, 10], 6), ([], 0), ([1], 1), ([2, 2, 2], 2), ([1, 2, 3], 4)]
    for nums, target in tests:
        print("linear:", search_range_linear(nums, target))
        print("bounds:", search_range(nums, target))
        print("---")

"""
Syntax notes (Python):
- bisect_left(a, x) is lower_bound; bisect_right(a, x) is the first index > x,
  so the last occurrence is bisect_right(a, x) - 1.
- idx[0], idx[-1] read the first and last element of a list.
- `A if cond else B` returns early for the empty case.
"""
