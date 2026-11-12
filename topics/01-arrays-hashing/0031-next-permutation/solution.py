"""
0031. Next Permutation  |  Medium  |  Arrays & Hashing
Link: https://leetcode.com/problems/next-permutation/

Problem: Rearrange nums in place into the next lexicographically greater
         permutation; wrap to ascending order after the largest one.

Examples:
  [1,2,3]      -> [1,3,2]
  [3,2,1]      -> [1,2,3]
  [1,1,5]      -> [1,5,1]
  [1,3,5,4,2]  -> [1,4,2,3,5]
  [2,2,2]      -> [2,2,2]
  [1]          -> [1]

Approaches:
  1. Generate all permutations           O(n! * n) time and space
  2. Pivot + swap + reverse suffix  ⭐   O(n) time, O(1) space   <- go-to
"""

from itertools import permutations


# ---------- Approach 1: Generate All ----------
def next_permutation_brute(nums: list[int]) -> None:
    perms = sorted(set(permutations(nums)))  # distinct permutations in order
    i = perms.index(tuple(nums))
    nums[:] = perms[(i + 1) % len(perms)]  # wrap after the last one


# ---------- Approach 2: Pivot + Swap + Reverse ⭐ ----------
def next_permutation(nums: list[int]) -> None:
    i = len(nums) - 2
    while i >= 0 and nums[i] >= nums[i + 1]:  # skip the non-increasing suffix
        i -= 1
    if i >= 0:
        j = len(nums) - 1
        while nums[j] <= nums[i]:  # rightmost value > pivot
            j -= 1
        nums[i], nums[j] = nums[j], nums[i]
    nums[i + 1:] = reversed(nums[i + 1:])  # suffix ascending = smallest


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[1, 2, 3], [3, 2, 1], [1, 1, 5], [1, 3, 5, 4, 2], [2, 2, 2], [1]]:
        a, b = t[:], t[:]
        next_permutation_brute(a)
        next_permutation(b)
        print("brute:", a)
        print("pivot:", b)
        print("---")

"""
Syntax notes (Python):
- nums[i + 1:] = reversed(nums[i + 1:]) replaces a slice in place (works for i = -1 too).
- itertools.permutations yields tuples; set() removes duplicates from repeated values.
- nums[:] = ... mutates the caller's list; nums = ... would only rebind the local name.
"""
