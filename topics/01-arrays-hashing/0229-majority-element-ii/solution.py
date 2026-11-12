"""
0229. Majority Element II  |  Medium  |  Arrays & Hashing
Link: https://leetcode.com/problems/majority-element-ii/

Problem: Return all values appearing more than floor(n/3) times.

Examples:
  [3,2,3]          -> [3]
  [1]              -> [1]
  [1,2]            -> [1,2]
  [1,2,3,1,2,1]    -> [1]
  [1,2,3]          -> []
  [0]              -> [0]     (sentinel trap: must not print [0,0])
  [2,2,1,1,1,2,2]  -> [1,2]

Approaches:
  1. Hashmap counts                         O(n) time, O(n) space
  2. Sort + runs                            O(n log n) time, O(1) extra
  3. Two-candidate Boyer-Moore  ⭐          O(n) time, O(1) space   <- go-to
  (Output order: approaches print values in ascending order to compare easily.)
"""

from collections import Counter
from itertools import groupby


# ---------- Approach 1: Hashmap Counts ----------
def majority_element_map(nums: list[int]) -> list[int]:
    return [v for v, c in Counter(nums).items() if c > len(nums) // 3]


# ---------- Approach 2: Sort + Runs ----------
def majority_element_sort(nums: list[int]) -> list[int]:
    n = len(nums)
    return [v for v, run in groupby(sorted(nums)) if sum(1 for _ in run) > n // 3]


# ---------- Approach 3: Boyer-Moore, Two Candidates ⭐ ----------
def majority_element(nums: list[int]) -> list[int]:
    c1, c2, k1, k2 = 0, 1, 0, 0  # distinct starting candidates
    for x in nums:
        if x == c1:  # matches first...
            k1 += 1
        elif x == c2:
            k2 += 1
        elif k1 == 0:  # ...then empty slots
            c1, k1 = x, 1
        elif k2 == 0:
            c2, k2 = x, 1
        else:  # cancel three distinct values
            k1 -= 1
            k2 -= 1
    return [c for c in (c1, c2) if nums.count(c) > len(nums) // 3]  # verify


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [[3, 2, 3], [1], [1, 2], [1, 2, 3, 1, 2, 1], [1, 2, 3], [0], [2, 2, 1, 1, 1, 2, 2]]
    for t in tests:
        print("map  :", sorted(majority_element_map(t)))
        print("sort :", sorted(majority_element_sort(t)))
        print("voting:", sorted(majority_element(t)))
        print("---")

"""
Syntax notes (Python):
- itertools.groupby(sorted(xs)) yields (value, run_iterator) for each run of equal values.
- sum(1 for _ in it) counts an iterator's items without building a list.
- list.count(x) is O(n); fine for two verification calls.
"""
