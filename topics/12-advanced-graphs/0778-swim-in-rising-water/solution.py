"""
0778. Swim in Rising Water  |  Hard  |  Advanced Graphs
Link: https://leetcode.com/problems/swim-in-rising-water/

Problem: n x n grid of distinct heights 0..n^2-1. At time t you can move
         between adjacent cells with height <= t. Least t to go from
         (0,0) to (n-1,n-1).

Examples:
  [[0,2],[1,3]]  -> 3
  [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]  -> 16
  [[0]]          -> 0
  [[3,2],[0,1]]  -> 3 (the start cell itself is the bottleneck)

Approaches:
  1. Binary search on t + DFS          O(n^2 log n) time, O(n^2) space
  2. Dijkstra on the max height  ⭐     O(n^2 log n) time, O(n^2) space   <- go-to
"""

import heapq

DIRS = ((1, 0), (-1, 0), (0, 1), (0, -1))


# ---------- Approach 1: Binary search on t + DFS ----------
def can_reach(g: list[list[int]], t: int) -> bool:
    n = len(g)
    if g[0][0] > t:
        return False
    seen = {(0, 0)}
    st = [(0, 0)]
    while st:
        r, c = st.pop()
        if (r, c) == (n - 1, n - 1):
            return True
        for dr, dc in DIRS:
            nr, nc = r + dr, c + dc
            if 0 <= nr < n and 0 <= nc < n and (nr, nc) not in seen and g[nr][nc] <= t:
                seen.add((nr, nc))
                st.append((nr, nc))
    return False


def swim_in_water_binary(g: list[list[int]]) -> int:
    lo, hi = 0, len(g) ** 2 - 1
    while lo < hi:  # smallest t with can_reach(t) true
        mid = (lo + hi) // 2
        if can_reach(g, mid):
            hi = mid
        else:
            lo = mid + 1
    return lo


# ---------- Approach 2: Dijkstra on the max height ⭐ ----------
def swim_in_water(g: list[list[int]]) -> int:
    n = len(g)
    pq = [(g[0][0], 0, 0)]  # (time needed, r, c)
    seen = {(0, 0)}
    while True:
        t, r, c = heapq.heappop(pq)
        if (r, c) == (n - 1, n - 1):
            return t
        for dr, dc in DIRS:
            nr, nc = r + dr, c + dc
            if 0 <= nr < n and 0 <= nc < n and (nr, nc) not in seen:
                seen.add((nr, nc))  # safe on push: key only grows with t
                heapq.heappush(pq, (max(t, g[nr][nc]), nr, nc))  # path cost = highest cell on it


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        [[0, 2], [1, 3]],
        [[0, 1, 2, 3, 4], [24, 23, 22, 21, 5], [12, 13, 14, 15, 16], [11, 17, 18, 19, 20], [10, 9, 8, 7, 6]],
        [[0]],
        [[3, 2], [0, 1]],
    ]
    for g in tests:
        print("binary  :", swim_in_water_binary(g))
        print("dijkstra:", swim_in_water(g))
        print("---")

"""
Syntax notes (Python):
- Tuple comparison `(r, c) == (n - 1, n - 1)` checks both coordinates at once.
- A set of (r, c) tuples is a quick visited structure for grids.
- heapq on (key, r, c) tuples pops the smallest key first.
"""
