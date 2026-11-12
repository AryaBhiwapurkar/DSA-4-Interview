"""
0081. Search in Rotated Sorted Array II  |  Medium  |  Binary Search
Link: https://leetcode.com/problems/search-in-rotated-sorted-array-ii/

Problem: A sorted array with duplicates was rotated. Return whether
         target is present.

Examples:
  [2,5,6,0,0,1,2], target = 0                          -> True
  [2,5,6,0,0,1,2], target = 3                          -> False
  [1,0,1,1,1],     target = 0                          -> True   (breaks plain LC 33)
  [1,1,1,1,1,1,1,1,1,13,1,1,1,1,1,1,1,1,1,1,1,1], 13   -> True
  [1],             target = 0                          -> False
  [3,1],           target = 1                          -> True

Approaches:
  1. Linear scan                                  O(n) time, O(1) space
  2. Rotated binary search + tie shrinking ⭐     O(log n) typical, O(n) worst   <- go-to
"""


# ---------- Approach 1: Linear Scan ----------
def search_linear(nums: list[int], target: int) -> bool:
    return target in nums


# ---------- Approach 2: Rotated Binary Search ⭐ ----------
def search(nums: list[int], target: int) -> bool:
    lo, hi = 0, len(nums) - 1
    while lo <= hi:
        mid = (lo + hi) // 2
        if nums[mid] == target:
            return True
        if nums[lo] == nums[mid] == nums[hi]:
            lo, hi = lo + 1, hi - 1  # can't tell which half is sorted
        elif nums[lo] <= nums[mid]:  # left half sorted
            if nums[lo] <= target < nums[mid]:
                hi = mid - 1
            else:
                lo = mid + 1
        else:  # right half sorted
            if nums[mid] < target <= nums[hi]:
                lo = mid + 1
            else:
                hi = mid - 1
    return False


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([2, 5, 6, 0, 0, 1, 2], 0), ([2, 5, 6, 0, 0, 1, 2], 3), ([1, 0, 1, 1, 1], 0),
             ([1, 1, 1, 1, 1, 1, 1, 1, 1, 13, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1], 13),
             ([1], 0), ([3, 1], 1)]
    for nums, t in tests:
        print("linear:", search_linear(nums, t))
        print("binary:", search(nums, t))
        print("---")

"""
Syntax notes (Python):
- Chained comparisons: a == b == c and lo <= x < hi read like math.
- lo, hi = lo + 1, hi - 1 updates both ends in one statement.
- `target in nums` is a linear scan on a list.
"""
