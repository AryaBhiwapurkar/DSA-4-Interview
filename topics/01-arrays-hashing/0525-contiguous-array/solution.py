"""
0525. Contiguous Array  |  Medium  |  Arrays & Hashing
Link: https://leetcode.com/problems/contiguous-array/

Problem: Longest contiguous subarray of a binary array with equally many 0s and 1s.

Examples:
  [0,1]                -> 2
  [0,1,0]              -> 2
  [0,1,1,1,1,1,0,0,0]  -> 6
  [0,0,1,0,1,1]        -> 6
  [0,0,0]              -> 0

Approaches:
  1. All subarrays with running counts   O(n^2) time, O(1) space
  2. Balance + first-index map  ⭐       O(n) time, O(n) space   <- go-to
"""


# ---------- Approach 1: All Subarrays ----------
def find_max_length_brute(nums: list[int]) -> int:
    best = 0
    for i in range(len(nums)):
        bal = 0
        for j in range(i, len(nums)):
            bal += 1 if nums[j] else -1
            if bal == 0:
                best = max(best, j - i + 1)
    return best


# ---------- Approach 2: Balance + First-Index Map ⭐ ----------
def find_max_length(nums: list[int]) -> int:
    first = {0: -1}  # balance 0 before index 0
    bal = best = 0
    for i, x in enumerate(nums):
        bal += 1 if x else -1  # a 0 counts as -1
        if bal in first:
            best = max(best, i - first[bal])
        else:
            first[bal] = i  # keep only the earliest index
    return best


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[0, 1], [0, 1, 0], [0, 1, 1, 1, 1, 1, 0, 0, 0], [0, 0, 1, 0, 1, 1], [0, 0, 0]]:
        print("brute  :", find_max_length_brute(t))
        print("balance:", find_max_length(t))
        print("---")

"""
Syntax notes (Python):
- 1 if x else -1 is the conditional expression (ternary).
- first.setdefault(bal, i) also keeps the earliest index, but the explicit if/else reads clearer here.
- bal = best = 0 chains assignment of an immutable value (safe for ints, not for lists).
"""
