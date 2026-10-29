"""
0080. Remove Duplicates from Sorted Array II  |  Medium  |  Two Pointers
Link: https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/

Problem: In a sorted array, keep each value at most twice (in order),
         in place. Return k = length of the result.

Examples (k, then first k elements):
  [1,1,1,2,2,3]          -> 5, [1,1,2,2,3]
  [0,0,1,1,1,1,2,3,3]    -> 7, [0,0,1,1,2,3,3]
  [1,1,1,2,2,2]          -> 4, [1,1,2,2]
  [5]                    -> 1, [5]

Approaches:
  1. Run counter               O(n) time, O(1) space
  2. Compare with nums[k-2] ⭐  O(n) time, O(1) space   <- go-to
"""

from typing import Callable


# ---------- Approach 1: Run Counter ----------
def remove_duplicates_counter(nums: list[int]) -> int:
    k, run, prev = 0, 0, None
    for x in nums:
        run = run + 1 if x == prev else 1
        prev = x  # track input value separately: nums may be overwritten
        if run <= 2:
            nums[k] = x
            k += 1
    return k


# ---------- Approach 2: Compare With nums[k-2] ⭐ ----------
def remove_duplicates(nums: list[int]) -> int:
    k = min(len(nums), 2)  # first two always stay
    for i in range(2, len(nums)):
        if nums[i] != nums[k - 2]:  # output already has two copies if equal
            nums[k] = nums[i]
            k += 1
    return k


# ---------- Driver ----------
def show(label: str, nums: list[int], fn: Callable[[list[int]], int]) -> None:
    nums = nums[:]
    k = fn(nums)
    print(f"{label}: {k}, {nums[:k]}")


if __name__ == "__main__":
    for nums in [[1, 1, 1, 2, 2, 3], [0, 0, 1, 1, 1, 1, 2, 3, 3], [1, 1, 1, 2, 2, 2], [5]]:
        show("counter", nums, remove_duplicates_counter)
        show("k-2    ", nums, remove_duplicates)
        print("---")

"""
Syntax notes (Python):
- `for x in nums` reads by index under the hood; writes to earlier slots are safe.
- None as an initial "previous value" sentinel compares unequal to any int.
- min(len(nums), 2) guards tiny inputs.
"""
