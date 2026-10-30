"""
0004. Median of Two Sorted Arrays  |  Hard  |  Binary Search
Link: https://leetcode.com/problems/median-of-two-sorted-arrays/

Problem: Return the median of two sorted arrays combined, in
         O(log(m + n)). One array may be empty.

Examples:
  [1,3],   [2]       -> 2.00000
  [1,2],   [3,4]     -> 2.50000
  [],      [1]       -> 1.00000
  [2],     []        -> 2.00000
  [0,0],   [0,0]     -> 0.00000
  [1,3,5], [2,4,6]   -> 3.50000
  [1,2],   [-1,3]    -> 1.50000

Approaches:
  1. Merge, pick middle            O(m+n) time, O(m+n) space
  2. Partition binary search  ⭐    O(log min(m,n)) time, O(1) space   <- go-to
"""

from heapq import merge

INF = float("inf")


# ---------- Approach 1: Merge, Then Pick the Middle ----------
def find_median_sorted_arrays_merge(a: list[int], b: list[int]) -> float:
    m = list(merge(a, b))
    n = len(m)
    if n % 2:
        return float(m[n // 2])
    return (m[n // 2 - 1] + m[n // 2]) / 2


# ---------- Approach 2: Partition Binary Search ⭐ ----------
def find_median_sorted_arrays(nums1: list[int], nums2: list[int]) -> float:
    A, B = (nums1, nums2) if len(nums1) <= len(nums2) else (nums2, nums1)  # search the SHORTER one
    m, n = len(A), len(B)
    half = (m + n + 1) // 2  # left side gets the extra element when odd
    lo, hi = 0, m
    while lo <= hi:
        i = (lo + hi) // 2  # taken from A
        j = half - i  # taken from B
        a_l = A[i - 1] if i > 0 else -INF
        a_r = A[i] if i < m else INF
        b_l = B[j - 1] if j > 0 else -INF
        b_r = B[j] if j < n else INF
        if a_l > b_r:
            hi = i - 1  # too many from A
        elif b_l > a_r:
            lo = i + 1  # too few from A
        elif (m + n) % 2:
            return float(max(a_l, b_l))
        else:
            return (max(a_l, b_l) + min(a_r, b_r)) / 2
    return 0.0  # unreachable for sorted input


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([1, 3], [2]), ([1, 2], [3, 4]), ([], [1]), ([2], []), ([0, 0], [0, 0]),
             ([1, 3, 5], [2, 4, 6]), ([1, 2], [-1, 3])]
    for a, b in tests:
        print(f"merge    : {find_median_sorted_arrays_merge(a, b):.5f}")
        print(f"partition: {find_median_sorted_arrays(a, b):.5f}")
        print("---")

"""
Syntax notes (Python):
- heapq.merge(a, b) lazily merges sorted iterables.
- float("inf") / -float("inf") compare correctly with ints.
- Tuple swap with a conditional: A, B = (x, y) if cond else (y, x).
- f"{x:.5f}" formats a float with 5 decimals.
"""
