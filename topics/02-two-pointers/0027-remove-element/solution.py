"""
0027. Remove Element  |  Easy  |  Two Pointers
Link: https://leetcode.com/problems/remove-element/

Problem: Remove all occurrences of val in place; return k, the count
         of remaining elements, which must fill the first k slots
         (any order).

Examples (k, then first k elements sorted):
  [3,2,2,3], val=3            -> 2, [2,2]
  [0,1,2,2,3,0,4,2], val=2    -> 5, [0,0,1,3,4]
  [], val=1                   -> 0, []
  [4,4], val=4                -> 0, []

Approaches:
  1. Read/write pointers  ⭐   O(n) time, O(1) space   <- go-to
  2. Swap with end            O(n) time, O(1) space
"""

from typing import Callable


# ---------- Approach 1: Read/Write Pointers ⭐ ----------
def remove_element(nums: list[int], val: int) -> int:
    k = 0
    for x in nums:
        if x != val:
            nums[k] = x
            k += 1
    return k


# ---------- Approach 2: Swap With End ----------
def remove_element_swap(nums: list[int], val: int) -> int:
    i, n = 0, len(nums)
    while i < n:
        if nums[i] == val:
            n -= 1
            nums[i] = nums[n]  # don't advance i: the moved-in value is unchecked
        else:
            i += 1
    return n


# ---------- Driver ----------
def show(label: str, nums: list[int], val: int, fn: Callable[[list[int], int], int]) -> None:
    nums = nums[:]
    k = fn(nums, val)
    print(f"{label}: {k}, {sorted(nums[:k])}")  # sorted: any order is accepted


if __name__ == "__main__":
    for nums, val in [([3, 2, 2, 3], 3), ([0, 1, 2, 2, 3, 0, 4, 2], 2), ([], 1), ([4, 4], 4)]:
        show("read/write", nums, val, remove_element)
        show("swap end  ", nums, val, remove_element_swap)
        print("---")

"""
Syntax notes (Python):
- Iterating `for x in nums` while assigning nums[k] (k <= index) is safe; no resizing.
- Avoid nums.remove(val) in a loop: each call is O(n).
- nums[:] copies a list (shallow).
"""
