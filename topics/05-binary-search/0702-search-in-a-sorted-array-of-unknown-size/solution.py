"""
0702. Search in a Sorted Array of Unknown Size  |  Medium  |  Binary Search
Link: https://leetcode.com/problems/search-in-a-sorted-array-of-unknown-size/

Problem: A sorted array of distinct ints is readable only via reader.get(i),
         which returns 2^31 - 1 past the end. Return target's index or -1.

Examples:
  [-1,0,3,5,9,12], target = 9    -> 4
  [-1,0,3,5,9,12], target = 2    -> -1
  [5],             target = 5    -> 0
  [-1,0,3,5,9,12], target = 13   -> -1   (past the end)
  [1,3],           target = -5   -> -1   (before the start)
  [-1,0,3,5,9,12], target = -1   -> 0

Approaches:
  1. Linear scan                          O(k) time, O(1) space
  2. Exponential bound + binary search ⭐ O(log k) time, O(1) space   <- go-to
"""

SENTINEL = 2**31 - 1


class ArrayReader:  # stand-in for the LeetCode interface
    def __init__(self, a: list[int]):
        self._a = a

    def get(self, i: int) -> int:
        return self._a[i] if i < len(self._a) else SENTINEL


# ---------- Approach 1: Linear Scan ----------
def search_linear(r: ArrayReader, target: int) -> int:
    i = 0
    while r.get(i) <= target:  # the sentinel ends the loop
        if r.get(i) == target:
            return i
        i += 1
    return -1


# ---------- Approach 2: Exponential Bound + Binary Search ⭐ ----------
def search(r: ArrayReader, target: int) -> int:
    lo, hi = 0, 1
    while r.get(hi) < target:  # past-end reads act as +inf
        lo, hi = hi, hi * 2
    while lo <= hi:
        mid = (lo + hi) // 2
        v = r.get(mid)
        if v == target:
            return mid
        if v < target:
            lo = mid + 1
        else:
            hi = mid - 1
    return -1


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([-1, 0, 3, 5, 9, 12], 9), ([-1, 0, 3, 5, 9, 12], 2), ([5], 5),
             ([-1, 0, 3, 5, 9, 12], 13), ([1, 3], -5), ([-1, 0, 3, 5, 9, 12], -1)]
    for v, t in tests:
        r = ArrayReader(v)
        print("linear     :", search_linear(r, t))
        print("exponential:", search(r, t))
        print("---")

"""
Syntax notes (Python):
- 2**31 - 1: ** is exponentiation; Python ints have no fixed width.
- A leading underscore (self._a) marks an attribute as internal by convention.
- lo, hi = hi, hi * 2 evaluates the right side first, then assigns both.
"""
