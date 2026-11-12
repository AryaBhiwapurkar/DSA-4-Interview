"""
0283. Move Zeroes  |  Easy  |  Two Pointers
Link: https://leetcode.com/problems/move-zeroes/

Problem: Move all zeros to the end in place, keeping non-zero order.

Examples:
  [0,1,0,3,12]  -> [1,3,12,0,0]
  [0]           -> [0]
  [1,2,3]       -> [1,2,3]
  [0,0,1]       -> [1,0,0]

Approaches:
  1. Copy non-zeros, then fill zeros   O(n) time, O(1) space (two passes)
  2. Swap read/write pointers  ⭐      O(n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Copy + Fill ----------
def move_zeroes_fill(nums: list[int]) -> None:
    w = 0
    for x in nums:
        if x != 0:
            nums[w] = x
            w += 1
    nums[w:] = [0] * (len(nums) - w)


# ---------- Approach 2: Swap Read/Write ⭐ ----------
def move_zeroes(nums: list[int]) -> None:
    w = 0  # next slot for a non-zero
    for r in range(len(nums)):
        if nums[r] != 0:
            if r != w:  # skip self-swaps
                nums[w], nums[r] = nums[r], nums[w]
            w += 1


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[0, 1, 0, 3, 12], [0], [1, 2, 3], [0, 0, 1]]:
        a, b = t[:], t[:]
        move_zeroes_fill(a)
        move_zeroes(b)
        print("fill:", a)
        print("swap:", b)
        print("---")

"""
Syntax notes (Python):
- nums[w:] = [0] * k replaces a tail slice in place.
- Tuple swap: a[i], a[j] = a[j], a[i].
- Iterating `for x in nums` while writing nums[w] (w <= current index) is safe here.
"""
