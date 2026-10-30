"""
0875. Koko Eating Bananas  |  Medium  |  Binary Search
Link: https://leetcode.com/problems/koko-eating-bananas/

Problem: Each hour Koko eats up to k bananas from one pile. Return the
         minimum integer k to finish all piles within h hours.

Examples:
  [3,6,7,11],       h 8   -> 4
  [30,11,23,4,20],  h 5   -> 30
  [30,11,23,4,20],  h 6   -> 23
  [5],              h 5   -> 1
  [1,1,1,1],        h 4   -> 1

Approaches:
  1. Try every speed               O(n * max) time, O(1) space
  2. Binary search on speed  ⭐     O(n log max) time, O(1) space   <- go-to
"""


def hours_at(piles: list[int], k: int) -> int:
    return sum((p + k - 1) // k for p in piles)  # ceil(p / k), exact


# ---------- Approach 1: Try Every Speed ----------
def min_eating_speed_brute(piles: list[int], h: int) -> int:
    k = 1
    while hours_at(piles, k) > h:  # k = max(piles) always works
        k += 1
    return k


# ---------- Approach 2: Binary Search on Speed ⭐ ----------
def min_eating_speed(piles: list[int], h: int) -> int:
    lo, hi = 1, max(piles)  # lo = 1: never divide by 0
    while lo < hi:
        mid = (lo + hi) // 2
        if hours_at(piles, mid) <= h:
            hi = mid  # fast enough: try slower
        else:
            lo = mid + 1
    return lo


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([3, 6, 7, 11], 8), ([30, 11, 23, 4, 20], 5), ([30, 11, 23, 4, 20], 6), ([5], 5), ([1, 1, 1, 1], 4)]
    for piles, h in tests:
        print("brute :", min_eating_speed_brute(piles, h))
        print("binary:", min_eating_speed(piles, h))
        print("---")

"""
Syntax notes (Python):
- Ceil division: (p + k - 1) // k, or -(-p // k).
- math.ceil(p / k) goes through floats; fine here, but // is exact.
- sum(generator) avoids building an intermediate list.
"""
