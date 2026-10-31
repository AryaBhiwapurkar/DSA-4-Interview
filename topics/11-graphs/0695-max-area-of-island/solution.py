"""
0695. Max Area of Island  |  Medium  |  Graphs
Link: https://leetcode.com/problems/max-area-of-island/

Problem: Largest number of cells in a 4-connected group of 1s (0 if none).

Examples:
  8x13 LeetCode grid       -> 6
  [[0,0,0,0,0,0,0,0]]      -> 0
  [[1,1],[1,0]]            -> 3
  [[1,0],[0,1]]            -> 1 (diagonal doesn't connect)

Approaches:
  1. DFS returning area  ⭐   O(m*n) time, O(m*n) stack   <- go-to
  2. BFS counting pops        O(m*n) time, O(m*n) queue
"""

import sys
from collections import deque

DIRS = ((1, 0), (-1, 0), (0, 1), (0, -1))


# ---------- Approach 1: DFS Returning Area ⭐ ----------
def max_area_of_island(grid: list[list[int]]) -> int:
    g = [row[:] for row in grid]
    m, n = len(g), len(g[0])
    sys.setrecursionlimit(max(1000, 2 * m * n + 10))  # 50x50 all land = depth 2500

    def area(r: int, c: int) -> int:
        if not (0 <= r < m and 0 <= c < n) or g[r][c] != 1:
            return 0
        g[r][c] = 0  # sink before recursing
        return 1 + sum(area(r + dr, c + dc) for dr, dc in DIRS)

    return max((area(r, c) for r in range(m) for c in range(n) if g[r][c] == 1), default=0)


# ---------- Approach 2: BFS Counting Pops ----------
def max_area_of_island_bfs(grid: list[list[int]]) -> int:
    g = [row[:] for row in grid]
    m, n, best = len(g), len(g[0]), 0
    for i in range(m):
        for j in range(n):
            if g[i][j] != 1:
                continue
            a, q = 0, deque([(i, j)])
            g[i][j] = 0
            while q:
                r, c = q.popleft()
                a += 1
                for dr, dc in DIRS:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < m and 0 <= nc < n and g[nr][nc] == 1:
                        g[nr][nc] = 0
                        q.append((nr, nc))
            best = max(best, a)
    return best


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        [[0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0],
         [0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0], [0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0],
         [0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0],
         [0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0]],
        [[0, 0, 0, 0, 0, 0, 0, 0]], [[1, 1], [1, 0]], [[1, 0], [0, 1]],
    ]
    for g in tests:
        print("dfs:", max_area_of_island(g))
        print("bfs:", max_area_of_island_bfs(g))
        print("---")

"""
Syntax notes (Python):
- max(generator, default=0) handles the no-land case without a special branch.
- The generator is lazy, so `if g[r][c] == 1` sees cells sunk by earlier calls.
- sys.setrecursionlimit raises Python's default limit (~1000) for deep DFS.
"""
