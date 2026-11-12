"""
0719. Find K-th Smallest Pair Distance  |  Hard  |  Binary Search
Link: https://leetcode.com/problems/find-k-th-smallest-pair-distance/

Problem: Over all pairs i < j, return the k-th smallest |nums[i] - nums[j]|.

Examples:
  [1,3,1],    k = 1   -> 0
  [1,1,1],    k = 2   -> 0
  [1,6,1],    k = 3   -> 5
  [1,3,5,9],  k = 4   -> 4
  [62,100,4], k = 2   -> 58
  [9,10,7,10,6,1,5,4,9,8], k = 18   -> 2

Approaches:
  1. All pairs + sort                               O(n^2 log n) time, O(n^2) space
  2. Binary search on distance + two-pointer count ⭐ O(n log n + n log W), O(1) extra   <- go-to
"""

from itertools import combinations


# ---------- Approach 1: All Pairs + Sort ----------
def smallest_distance_pair_brute(nums: list[int], k: int) -> int:
    return sorted(abs(a - b) for a, b in combinations(nums, 2))[k - 1]


# ---------- Approach 2: Binary Search + Two-pointer Count ⭐ ----------
def count_at_most(a: list[int], d: int) -> int:
    cnt = l = 0
    for r, x in enumerate(a):
        while x - a[l] > d:  # l only moves forward
            l += 1
        cnt += r - l  # pairs (l..r-1, r)
    return cnt


def smallest_distance_pair(nums: list[int], k: int) -> int:
    a = sorted(nums)
    lo, hi = 0, a[-1] - a[0]
    while lo < hi:
        mid = (lo + hi) // 2
        if count_at_most(a, mid) >= k:
            hi = mid
        else:
            lo = mid + 1
    return lo


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([1, 3, 1], 1), ([1, 1, 1], 2), ([1, 6, 1], 3), ([1, 3, 5, 9], 4), ([62, 100, 4], 2),
             ([9, 10, 7, 10, 6, 1, 5, 4, 9, 8], 18)]
    for nums, k in tests:
        print("brute :", smallest_distance_pair_brute(nums, k))
        print("binary:", smallest_distance_pair(nums, k))
        print("---")

"""
Syntax notes (Python):
- itertools.combinations(nums, 2) yields each unordered pair once.
- sorted(generator)[k - 1] picks the k-th smallest (1-indexed k).
- cnt = l = 0 binds both names to 0 (fine for immutable ints).
"""
