"""
0167. Two Sum II - Input Array Is Sorted  |  Medium  |  Two Pointers
Link: https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/

Problem: Sorted array, return 1-based indices [i, j] (i < j) of the two
         numbers summing to target. Exactly one answer; O(1) extra space.

Examples:
  [2,7,11,15], target 9  -> [1,2]
  [2,3,4],     target 6  -> [1,3]
  [-1,0],      target -1 -> [1,2]
  [1,1,3],     target 2  -> [1,2]

Approaches:
  1. Binary search per element   O(n log n) time, O(1) space
  2. Hashmap                     O(n) time, O(n) space
  3. Two pointers  ⭐             O(n) time, O(1) space   <- go-to
"""

from bisect import bisect_left


# ---------- Approach 1: Binary Search per Element ----------
def two_sum_binary(a: list[int], target: int) -> list[int]:
    for i, x in enumerate(a):
        j = bisect_left(a, target - x, i + 1)  # search only to the right of i
        if j < len(a) and a[j] == target - x:
            return [i + 1, j + 1]
    return []


# ---------- Approach 2: Hashmap ----------
def two_sum_hash(a: list[int], target: int) -> list[int]:
    seen: dict[int, int] = {}
    for i, x in enumerate(a):
        if target - x in seen:
            return [seen[target - x] + 1, i + 1]
        seen[x] = i
    return []


# ---------- Approach 3: Two Pointers ⭐ ----------
def two_sum(a: list[int], target: int) -> list[int]:
    l, r = 0, len(a) - 1
    while l < r:
        s = a[l] + a[r]
        if s == target:
            return [l + 1, r + 1]  # 1-based
        if s < target:
            l += 1  # a[l] is too small for every remaining partner
        else:
            r -= 1  # a[r] is too big for every remaining partner
    return []


# ---------- Driver ----------
if __name__ == "__main__":
    for a, target in [([2, 7, 11, 15], 9), ([2, 3, 4], 6), ([-1, 0], -1), ([1, 1, 3], 2)]:
        print("binary  :", two_sum_binary(a, target))
        print("hash    :", two_sum_hash(a, target))
        print("pointers:", two_sum(a, target))
        print("---")

"""
Syntax notes (Python):
- bisect_left(a, x, lo) searches only a[lo:] without slicing (no copy).
- l, r = 0, len(a) - 1 initializes both pointers in one line.
"""
