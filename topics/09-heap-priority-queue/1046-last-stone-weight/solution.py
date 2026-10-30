"""
1046. Last Stone Weight  |  Easy  |  Heap / Priority Queue
Link: https://leetcode.com/problems/last-stone-weight/

Problem: Repeatedly smash the two heaviest stones; equal ones vanish,
         otherwise the difference remains. Return the last weight or 0.

Examples:
  [2,7,4,1,8,1]  -> 1
  [1]            -> 1
  [2,2]          -> 0
  [10,4,2,10]    -> 2

Approaches:
  1. Sort every round   O(n^2 log n) time, O(1) extra
  2. Max-heap  ⭐        O(n log n) time, O(n) space   <- go-to
"""

import heapq


# ---------- Approach 1: Sort Every Round ----------
def last_stone_weight_sort(stones: list[int]) -> int:
    s = stones[:]
    while len(s) > 1:
        s.sort()
        y, x = s.pop(), s.pop()
        if y > x:
            s.append(y - x)
    return s[0] if s else 0


# ---------- Approach 2: Max-Heap ⭐ ----------
def last_stone_weight(stones: list[int]) -> int:
    h = [-s for s in stones]  # negate: heapq is a min-heap
    heapq.heapify(h)
    while len(h) > 1:
        y, x = -heapq.heappop(h), -heapq.heappop(h)
        if y > x:  # equal stones both vanish
            heapq.heappush(h, -(y - x))
    return -h[0] if h else 0


# ---------- Driver ----------
if __name__ == "__main__":
    for s in [[2, 7, 4, 1, 8, 1], [1], [2, 2], [10, 4, 2, 10]]:
        print("sort:", last_stone_weight_sort(s))
        print("heap:", last_stone_weight(s))
        print("---")

"""
Syntax notes (Python):
- Max-heap with heapq: store negatives, negate again when reading.
- heapq.heapify(list) is O(n).
"""
