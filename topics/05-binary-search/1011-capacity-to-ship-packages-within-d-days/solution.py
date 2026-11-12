"""
1011. Capacity To Ship Packages Within D Days  |  Medium  |  Binary Search
Link: https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/

Problem: Ship packages in order, one load per day, each load <= capacity.
         Return the smallest capacity that finishes within `days` days.

Examples:
  [1,2,3,4,5,6,7,8,9,10], days = 5   -> 15
  [3,2,2,4,1,4],          days = 3   -> 6
  [1,2,3,1,1],            days = 4   -> 3
  [10],                   days = 1   -> 10
  [1,1,1,1],              days = 4   -> 1

Approaches:
  1. Try every capacity                O(n (sum - max)) time, O(1) space
  2. Binary search on capacity ⭐      O(n log sum) time, O(1) space   <- go-to
"""


def days_needed(w: list[int], cap: int) -> int:
    d, load = 1, 0
    for x in w:
        if load + x > cap:  # x goes on the next day
            d += 1
            load = 0
        load += x
    return d


# ---------- Approach 1: Try Every Capacity ----------
def ship_within_days_linear(w: list[int], days: int) -> int:
    cap = max(w)
    while days_needed(w, cap) > days:
        cap += 1
    return cap


# ---------- Approach 2: Binary Search on Capacity ⭐ ----------
def ship_within_days(w: list[int], days: int) -> int:
    lo, hi = max(w), sum(w)  # heaviest package .. everything in one day
    while lo < hi:
        mid = (lo + hi) // 2
        if days_needed(w, mid) <= days:
            hi = mid
        else:
            lo = mid + 1
    return lo


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([1, 2, 3, 4, 5, 6, 7, 8, 9, 10], 5), ([3, 2, 2, 4, 1, 4], 3), ([1, 2, 3, 1, 1], 4),
             ([10], 1), ([1, 1, 1, 1], 4)]
    for w, days in tests:
        print("linear:", ship_within_days_linear(w, days))
        print("binary:", ship_within_days(w, days))
        print("---")

"""
Syntax notes (Python):
- lo, hi = max(w), sum(w) sets both bounds in one line.
- A module-level helper keeps the search loop short and testable.
- bisect_left(range(lo, hi + 1), True, key=lambda c: days_needed(w, c) <= days)
  is a library alternative (Python 3.10+ for key=).
"""
