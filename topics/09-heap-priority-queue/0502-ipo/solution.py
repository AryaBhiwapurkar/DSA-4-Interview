"""
0502. IPO  |  Hard  |  Heap / Priority Queue
Link: https://leetcode.com/problems/ipo/

Problem: Start with capital w; do at most k distinct projects, each needing
         capital[i] and adding profits[i]. Maximize final capital.

Examples:
  k 2, w 0, profits [1,2,3], capital [0,1,1]    -> 4
  k 3, w 0, profits [1,2,3], capital [0,1,2]    -> 6
  k 1, w 0, profits [1],     capital [1]        -> 0   (nothing affordable)
  k 10, w 0, profits [1,2,3], capital [0,1,1]   -> 6   (runs out of projects)

Approaches:
  1. Rescan each round        O(k * n) time, O(n) space
  2. Sort + max-heap  ⭐       O(n log n + k log n) time, O(n) space   <- go-to
"""

import heapq


# ---------- Approach 1: Rescan Each Round ----------
def find_maximized_capital_brute(k: int, w: int, profits: list[int], capital: list[int]) -> int:
    used = [False] * len(profits)
    for _ in range(k):
        cand = [i for i in range(len(profits)) if not used[i] and capital[i] <= w]
        if not cand:
            break  # nothing affordable
        best = max(cand, key=lambda i: profits[i])
        used[best] = True
        w += profits[best]
    return w


# ---------- Approach 2: Sort + Max-Heap ⭐ ----------
def find_maximized_capital(k: int, w: int, profits: list[int], capital: list[int]) -> int:
    proj = sorted(zip(capital, profits))  # by capital needed
    h: list[int] = []  # negated profits of affordable projects
    i = 0
    for _ in range(k):
        while i < len(proj) and proj[i][0] <= w:  # newly affordable
            heapq.heappush(h, -proj[i][1])
            i += 1
        if not h:
            break
        w -= heapq.heappop(h)  # greedy: best affordable (capital never shrinks)
    return w


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [(2, 0, [1, 2, 3], [0, 1, 1]), (3, 0, [1, 2, 3], [0, 1, 2]), (1, 0, [1], [1]), (10, 0, [1, 2, 3], [0, 1, 1])]
    for k, w, p, c in tests:
        print("brute:", find_maximized_capital_brute(k, w, p, c))
        print("heap :", find_maximized_capital(k, w, p, c))
        print("---")

"""
Syntax notes (Python):
- sorted(zip(a, b)) pairs two lists and sorts by a.
- w -= heappop(h) adds a profit stored as a negative.
- max(iterable, key=f) picks the argmax.
"""
