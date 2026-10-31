"""
0994. Rotting Oranges  |  Medium  |  Graphs
Link: https://leetcode.com/problems/rotting-oranges/

Problem: 0 empty, 1 fresh, 2 rotten. Each minute rot spreads to 4-neighbours.
         Minutes until no fresh orange remains, or -1.

Examples:
  [[2,1,1],[1,1,0],[0,1,1]]  -> 4
  [[2,1,1],[0,1,1],[1,0,1]]  -> -1
  [[0,2]]                    -> 0
  [[1]]                      -> -1 (no rotten source)
  [[0]]                      -> 0

Approaches:
  1. Repeated full-grid simulation    O((m*n)^2) time, O(m*n) space
  2. Multi-source BFS  ⭐              O(m*n) time, O(m*n) space   <- go-to
"""

from collections import deque

DIRS = ((1, 0), (-1, 0), (0, 1), (0, -1))


# ---------- Approach 1: Repeated Full-Grid Simulation ----------
def oranges_rotting_sim(grid: list[list[int]]) -> int:
    g = [row[:] for row in grid]
    m, n, minutes = len(g), len(g[0]), 0
    while True:
        nxt = [row[:] for row in g]  # rot spreads one step per minute
        changed = fresh = False
        for r in range(m):
            for c in range(n):
                if g[r][c] != 1:
                    continue
                fresh = True
                if any(0 <= r + dr < m and 0 <= c + dc < n and g[r + dr][c + dc] == 2 for dr, dc in DIRS):
                    nxt[r][c] = 2
                    changed = True
        if not fresh:
            return minutes
        if not changed:
            return -1
        g = nxt
        minutes += 1


# ---------- Approach 2: Multi-Source BFS ⭐ ----------
def oranges_rotting(grid: list[list[int]]) -> int:
    g = [row[:] for row in grid]
    m, n = len(g), len(g[0])
    q = deque((r, c) for r in range(m) for c in range(n) if g[r][c] == 2)  # every rotten orange starts at once
    fresh = sum(row.count(1) for row in g)
    minutes = 0
    while q and fresh:  # stop as soon as nothing is fresh
        for _ in range(len(q)):
            r, c = q.popleft()
            for dr, dc in DIRS:
                nr, nc = r + dr, c + dc
                if 0 <= nr < m and 0 <= nc < n and g[nr][nc] == 1:
                    g[nr][nc] = 2
                    fresh -= 1
                    q.append((nr, nc))
        minutes += 1
    return minutes if fresh == 0 else -1


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [[[2, 1, 1], [1, 1, 0], [0, 1, 1]], [[2, 1, 1], [0, 1, 1], [1, 0, 1]], [[0, 2]], [[1]], [[0]]]
    for g in tests:
        print("sim:", oranges_rotting_sim(g))
        print("bfs:", oranges_rotting(g))
        print("---")

"""
Syntax notes (Python):
- `for _ in range(len(q))` evaluates len(q) once, so new pushes wait for the next level.
- sum(row.count(1) for row in g) counts fresh oranges.
- `changed = fresh = False` chains assignment of immutable values safely.
"""
