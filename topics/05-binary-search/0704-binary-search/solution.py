"""
0704. Binary Search  |  Easy  |  Binary Search
Link: https://leetcode.com/problems/binary-search/

Problem: Sorted array of distinct ints; return target's index or -1,
         in O(log n).

Examples:
  [-1,0,3,5,9,12], target 9   -> 4
  [-1,0,3,5,9,12], target 2   -> -1
  [5],             target 5   -> 0
  [5],             target -5  -> -1
  [1,3],           target 3   -> 1

Approaches:
  1. Linear scan            O(n) time, O(1) space
  2. Binary search  ⭐       O(log n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Linear Scan ----------
def search_linear(nums: list[int], target: int) -> int:
    for i, x in enumerate(nums):
        if x == target:
            return i
    return -1


# ---------- Approach 2: Iterative Binary Search ⭐ ----------
def search(nums: list[int], target: int) -> int:
    lo, hi = 0, len(nums) - 1  # inclusive window
    while lo <= hi:  # <= : a 1-element window is still a candidate
        mid = (lo + hi) // 2  # Python ints don't overflow
        if nums[mid] == target:
            return mid
        if nums[mid] < target:
            lo = mid + 1
        else:
            hi = mid - 1
    return -1


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([-1, 0, 3, 5, 9, 12], 9), ([-1, 0, 3, 5, 9, 12], 2), ([5], 5), ([5], -5), ([1, 3], 3)]
    for nums, target in tests:
        print("linear:", search_linear(nums, target))
        print("binary:", search(nums, target))
        print("---")

"""
Syntax notes (Python):
- (lo + hi) // 2 is integer floor division; no overflow in Python.
- Library: bisect.bisect_left(a, x) returns the first index with a[i] >= x;
  check i < len(a) and a[i] == x to test membership.
"""
