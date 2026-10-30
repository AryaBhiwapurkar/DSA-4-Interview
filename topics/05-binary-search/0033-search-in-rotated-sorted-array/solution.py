"""
0033. Search in Rotated Sorted Array  |  Medium  |  Binary Search
Link: https://leetcode.com/problems/search-in-rotated-sorted-array/

Problem: A sorted array of distinct ints was rotated. Return the index of
         target or -1, in O(log n).

Examples:
  [4,5,6,7,0,1,2], target 0  -> 4
  [4,5,6,7,0,1,2], target 3  -> -1
  [1],             target 0  -> -1
  [1,3],           target 3  -> 1
  [3,1],           target 1  -> 1
  [5,1,3],         target 5  -> 0

Approaches:
  1. Linear scan                  O(n) time, O(1) space
  2. Find pivot, then search      O(log n) time, O(1) space
  3. One-pass sorted half  ⭐      O(log n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Linear Scan ----------
def search_linear(nums: list[int], target: int) -> int:
    return nums.index(target) if target in nums else -1


# ---------- Approach 2: Find Pivot, Then Binary Search ----------
def binary_search(nums: list[int], lo: int, hi: int, target: int) -> int:
    while lo <= hi:
        mid = (lo + hi) // 2
        if nums[mid] == target:
            return mid
        if nums[mid] < target:
            lo = mid + 1
        else:
            hi = mid - 1
    return -1


def search_pivot(nums: list[int], target: int) -> int:
    lo, hi = 0, len(nums) - 1
    while lo < hi:  # index of the minimum (LC 0153)
        mid = (lo + hi) // 2
        if nums[mid] > nums[hi]:
            lo = mid + 1
        else:
            hi = mid
    p = lo
    if nums[p] <= target <= nums[-1]:
        return binary_search(nums, p, len(nums) - 1, target)
    return binary_search(nums, 0, p - 1, target)


# ---------- Approach 3: One-Pass Sorted Half ⭐ ----------
def search(nums: list[int], target: int) -> int:
    lo, hi = 0, len(nums) - 1
    while lo <= hi:
        mid = (lo + hi) // 2
        if nums[mid] == target:
            return mid
        if nums[lo] <= nums[mid]:  # left half sorted (<=: lo may equal mid)
            if nums[lo] <= target < nums[mid]:
                hi = mid - 1
            else:
                lo = mid + 1
        else:  # right half sorted
            if nums[mid] < target <= nums[hi]:
                lo = mid + 1
            else:
                hi = mid - 1
    return -1


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([4, 5, 6, 7, 0, 1, 2], 0), ([4, 5, 6, 7, 0, 1, 2], 3), ([1], 0), ([1, 3], 3), ([3, 1], 1), ([5, 1, 3], 5)]
    for nums, target in tests:
        print("linear :", search_linear(nums, target))
        print("pivot  :", search_pivot(nums, target))
        print("onePass:", search(nums, target))
        print("---")

"""
Syntax notes (Python):
- Chained comparisons: nums[lo] <= target < nums[mid] reads like math.
- list.index(x) raises ValueError if absent, so test `x in list` first.
- nums[-1] is the last element.
"""
