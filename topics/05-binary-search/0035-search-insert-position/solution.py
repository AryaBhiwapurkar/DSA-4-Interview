"""
0035. Search Insert Position  |  Easy  |  Binary Search
Link: https://leetcode.com/problems/search-insert-position/

Problem: Sorted distinct ints. Return target's index, or the index where
         it would be inserted to keep order. O(log n).

Examples:
  [1,3,5,6], target 5  -> 2
  [1,3,5,6], target 2  -> 1
  [1,3,5,6], target 7  -> 4
  [1,3,5,6], target 0  -> 0
  [1],       target 1  -> 0

Approaches:
  1. Linear scan       O(n) time, O(1) space
  2. Lower bound  ⭐    O(log n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Linear Scan ----------
def search_insert_linear(nums: list[int], target: int) -> int:
    return next((i for i, x in enumerate(nums) if x >= target), len(nums))


# ---------- Approach 2: Lower Bound ⭐ ----------
def search_insert(nums: list[int], target: int) -> int:
    lo, hi = 0, len(nums)  # half-open [lo, hi): answer can be n
    while lo < hi:
        mid = (lo + hi) // 2
        if nums[mid] < target:
            lo = mid + 1
        else:
            hi = mid  # mid might be the answer: keep it
    return lo


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([1, 3, 5, 6], 5), ([1, 3, 5, 6], 2), ([1, 3, 5, 6], 7), ([1, 3, 5, 6], 0), ([1], 1)]
    for nums, target in tests:
        print("linear:", search_insert_linear(nums, target))
        print("lower :", search_insert(nums, target))
        print("---")

"""
Syntax notes (Python):
- Library one-liner: bisect.bisect_left(nums, target).
- next(generator, default) returns default if the generator is empty.
- bisect_right gives the first index with value > target.
"""
