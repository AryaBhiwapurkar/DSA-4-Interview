"""
0268. Missing Number  |  Easy  |  Bit Manipulation
Link: https://leetcode.com/problems/missing-number/

Problem: nums holds n distinct numbers from 0..n. Return the one missing.

Examples:
  [3,0,1]               -> 2
  [0,1]                 -> 2
  [9,6,4,2,3,5,7,0,1]   -> 8
  [1]                   -> 0
  [0]                   -> 1

Approaches:
  1. Sort, find the first index != value   O(n log n) time, O(1) extra
  2. Hash set of values                    O(n) time, O(n) space
  3. Gauss sum: n(n+1)/2 - sum             O(n) time, O(1) space
  4. XOR indices and values  ⭐             O(n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Sort ----------
def missing_number_sort(nums: list[int]) -> int:
    for i, x in enumerate(sorted(nums)):
        if i != x:
            return i
    return len(nums)  # every 0..n-1 present: n is missing


# ---------- Approach 2: Hash Set ----------
def missing_number_set(nums: list[int]) -> int:
    seen = set(nums)
    return next(i for i in range(len(nums) + 1) if i not in seen)


# ---------- Approach 3: Gauss Sum ----------
def missing_number_sum(nums: list[int]) -> int:
    n = len(nums)
    return n * (n + 1) // 2 - sum(nums)


# ---------- Approach 4: XOR ⭐ ----------
def missing_number(nums: list[int]) -> int:
    x = len(nums)  # n itself has no index to pair with
    for i, v in enumerate(nums):
        x ^= i ^ v  # every present value cancels its matching index
    return x


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[3, 0, 1], [0, 1], [9, 6, 4, 2, 3, 5, 7, 0, 1], [1], [0]]:
        print("sort:", missing_number_sort(t))
        print("set :", missing_number_set(t))
        print("sum :", missing_number_sum(t))
        print("xor :", missing_number(t))
        print("---")

"""
Syntax notes (Python):
- next(generator) returns the first match.
- // is integer division, so the Gauss sum stays an int.
- x ^= i ^ v folds both the index and the value into the running XOR.
"""
