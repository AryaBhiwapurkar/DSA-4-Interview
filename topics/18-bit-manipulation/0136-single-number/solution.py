"""
0136. Single Number  |  Easy  |  Bit Manipulation
Link: https://leetcode.com/problems/single-number/

Problem: Every number appears twice except one. Find it in O(n) time and
         O(1) extra space.

Examples:
  [2,2,1]         -> 1
  [4,1,2,1,2]     -> 4
  [1]             -> 1
  [-3,7,7]        -> -3

Approaches:
  1. Hash set: add, remove on second sighting   O(n) time, O(n) space
  2. Sort, check pairs                          O(n log n) time, O(1) extra
  3. XOR everything  ⭐                          O(n) time, O(1) space   <- go-to
"""

from functools import reduce
from operator import xor


# ---------- Approach 1: Hash Set ----------
def single_number_set(nums: list[int]) -> int:
    seen: set[int] = set()
    for x in nums:
        if x in seen:
            seen.remove(x)  # second copy cancels the first
        else:
            seen.add(x)
    return seen.pop()


# ---------- Approach 2: Sort ----------
def single_number_sort(nums: list[int]) -> int:
    a = sorted(nums)
    for i in range(0, len(a) - 1, 2):  # pairs sit at (0,1), (2,3), ...
        if a[i] != a[i + 1]:
            return a[i]
    return a[-1]  # the single one is last


# ---------- Approach 3: XOR ⭐ ----------
def single_number(nums: list[int]) -> int:
    return reduce(xor, nums)  # x ^ x = 0 and x ^ 0 = x, in any order


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[2, 2, 1], [4, 1, 2, 1, 2], [1], [-3, 7, 7]]:
        print("set :", single_number_set(t))
        print("sort:", single_number_sort(t))
        print("xor :", single_number(t))
        print("---")

"""
Syntax notes (Python):
- reduce(xor, nums) folds ^ over the list (operator.xor is the ^ function).
- set.pop() removes and returns an arbitrary element (here, the only one).
- range(0, n - 1, 2) steps through pair starts.
"""
