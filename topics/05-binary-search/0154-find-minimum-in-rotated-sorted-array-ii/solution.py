"""
0154. Find Minimum in Rotated Sorted Array II  |  Hard  |  Binary Search
Link: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/

Problem: A sorted array with duplicates was rotated. Return its minimum.

Examples:
  [1,3,5]            -> 1
  [2,2,2,0,1]        -> 0
  [3,3,1,3]          -> 1
  [10,1,10,10,10]    -> 1
  [1,1]              -> 1
  [4,5,6,7,0,1,4]    -> 0

Approaches:
  1. Linear scan                          O(n) time, O(1) space
  2. Binary search vs hi, hi-- on ties ⭐ O(log n) typical, O(n) worst   <- go-to
"""


# ---------- Approach 1: Linear Scan ----------
def find_min_linear(nums: list[int]) -> int:
    return min(nums)


# ---------- Approach 2: Binary Search vs hi ⭐ ----------
def find_min(nums: list[int]) -> int:
    lo, hi = 0, len(nums) - 1
    while lo < hi:
        mid = (lo + hi) // 2
        if nums[mid] < nums[hi]:
            hi = mid  # min is at mid or left of it
        elif nums[mid] > nums[hi]:
            lo = mid + 1  # the drop is right of mid
        else:
            hi -= 1  # nums[mid] keeps hi's value in range
    return nums[lo]


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[1, 3, 5], [2, 2, 2, 0, 1], [3, 3, 1, 3], [10, 1, 10, 10, 10], [1, 1], [4, 5, 6, 7, 0, 1, 4]]:
        print("linear:", find_min_linear(t))
        print("binary:", find_min(t))
        print("---")

"""
Syntax notes (Python):
- min(list) is the O(n) baseline in one call.
- if / elif / else covers <, >, == in one chain.
- hi -= 1 is the in-place decrement (no -- operator in Python).
"""
