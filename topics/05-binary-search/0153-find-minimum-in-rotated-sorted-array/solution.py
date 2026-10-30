"""
0153. Find Minimum in Rotated Sorted Array  |  Medium  |  Binary Search
Link: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/

Problem: A sorted array of distinct ints was rotated. Return its minimum
         in O(log n).

Examples:
  [3,4,5,1,2]      -> 1
  [4,5,6,7,0,1,2]  -> 0
  [11,13,15,17]    -> 11
  [2,1]            -> 1
  [1]              -> 1

Approaches:
  1. Linear scan                   O(n) time, O(1) space
  2. Binary search vs right end ⭐  O(log n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Linear Scan ----------
def find_min_linear(nums: list[int]) -> int:
    return min(nums)


# ---------- Approach 2: Binary Search vs Right End ⭐ ----------
def find_min(nums: list[int]) -> int:
    lo, hi = 0, len(nums) - 1
    while lo < hi:
        mid = (lo + hi) // 2
        if nums[mid] > nums[hi]:
            lo = mid + 1  # drop is strictly right of mid
        else:
            hi = mid  # mid..hi sorted: min at mid or left
    return nums[lo]


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [[3, 4, 5, 1, 2], [4, 5, 6, 7, 0, 1, 2], [11, 13, 15, 17], [2, 1], [1]]
    for nums in tests:
        print("linear:", find_min_linear(nums))
        print("binary:", find_min(nums))
        print("---")

"""
Syntax notes (Python):
- min(list) is O(n); fine as a baseline, not what's asked.
- The loop condition lo < hi pairs with hi = mid (half-open style).
"""
