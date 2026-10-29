"""
0026. Remove Duplicates from Sorted Array  |  Easy  |  Two Pointers
Link: https://leetcode.com/problems/remove-duplicates-from-sorted-array/

Problem: In a sorted array, keep one copy of each value at the front
         (in order), in place. Return k = number of unique values.

Examples (k, then first k elements):
  [1,1,2]                 -> 2, [1,2]
  [0,0,1,1,1,2,2,3,3,4]   -> 5, [0,1,2,3,4]
  [7]                     -> 1, [7]

Approaches:
  1. Collect uniques, copy back   O(n) time, O(n) space
  2. Read/write pointers  ⭐       O(n) time, O(1) space   <- go-to
"""

from typing import Callable


# ---------- Approach 1: Collect Uniques, Copy Back ----------
def remove_duplicates_copy(nums: list[int]) -> int:
    uniq = list(dict.fromkeys(nums))  # dict keeps insertion order
    nums[: len(uniq)] = uniq
    return len(uniq)


# ---------- Approach 2: Read/Write Pointers ⭐ ----------
def remove_duplicates(nums: list[int]) -> int:
    k = 1  # nums[0] is always kept
    for i in range(1, len(nums)):
        if nums[i] != nums[k - 1]:  # compare with last WRITTEN value
            nums[k] = nums[i]
            k += 1
    return k


# ---------- Driver ----------
def show(label: str, nums: list[int], fn: Callable[[list[int]], int]) -> None:
    nums = nums[:]  # don't mutate the shared test case
    k = fn(nums)
    print(f"{label}: {k}, {nums[:k]}")


if __name__ == "__main__":
    for nums in [[1, 1, 2], [0, 0, 1, 1, 1, 2, 2, 3, 3, 4], [7]]:
        show("copy      ", nums, remove_duplicates_copy)
        show("read/write", nums, remove_duplicates)
        print("---")

"""
Syntax notes (Python):
- dict.fromkeys(seq) dedupes while keeping first-seen order.
- nums[:k] = other replaces a slice in place (caller sees it).
- Callable[[args], ret] types a function parameter.
"""
