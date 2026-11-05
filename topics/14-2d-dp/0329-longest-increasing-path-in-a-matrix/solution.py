"""
0329. Longest Increasing Path in a Matrix  |  Hard  |  2-D Dynamic Programming
Link: https://leetcode.com/problems/longest-increasing-path-in-a-matrix/

Problem: Length of the longest strictly increasing path moving up/down/left/
         right in a grid.

Examples:
  [[9,9,4],[6,6,8],[2,1,1]]   -> 4
  [[3,4,5],[3,2,6],[2,2,1]]   -> 4
  [[1]]                       -> 1
  [[7,7],[7,7]]               -> 1
  [[1,2,3],[6,5,4],[7,8,9]]   -> 9

Approaches:
  1. Plain DFS from every cell          exponential worst case, O(m*n) space
  2. DFS + memo  ⭐                      O(m*n) time, O(m*n) space   <- go-to
  3. Topological sort (peel by layers)  O(m*n) time, O(m*n) space
"""

import sys
from collections import deque
from functools import cache

sys.setrecursionlimit(100_000)  # a snake path can be m*n deep

DIRS = ((1, 0), (-1, 0), (0, 1), (0, -1))


# ---------- Approach 1: Plain DFS ----------
def longest_increasing_path_brute(g: list[list[int]]) -> int:
    m, n = len(g), len(g[0])

    def dfs(r: int, c: int) -> int:
        best = 1
        for dr, dc in DIRS:
            nr, nc = r + dr, c + dc
            if 0 <= nr < m and 0 <= nc < n and g[nr][nc] > g[r][c]:
                best = max(best, 1 + dfs(nr, nc))
        return best

    return max(dfs(r, c) for r in range(m) for c in range(n))


# ---------- Approach 2: DFS + Memo ⭐ ----------
def longest_increasing_path(g: list[list[int]]) -> int:
    m, n = len(g), len(g[0])

    @cache
    def dfs(r: int, c: int) -> int:  # longest path starting at (r, c)
        best = 1
        for dr, dc in DIRS:
            nr, nc = r + dr, c + dc
            if 0 <= nr < m and 0 <= nc < n and g[nr][nc] > g[r][c]:  # strictly larger: no cycles
                best = max(best, 1 + dfs(nr, nc))
        return best

    return max(dfs(r, c) for r in range(m) for c in range(n))


# ---------- Approach 3: Topological Sort ----------
def longest_increasing_path_topo(g: list[list[int]]) -> int:
    m, n = len(g), len(g[0])
    out = [[0] * n for _ in range(m)]  # number of strictly larger neighbours
    for r in range(m):
        for c in range(n):
            for dr, dc in DIRS:
                nr, nc = r + dr, c + dc
                if 0 <= nr < m and 0 <= nc < n and g[nr][nc] > g[r][c]:
                    out[r][c] += 1
    q = deque((r, c) for r in range(m) for c in range(n) if out[r][c] == 0)  # local maxima
    layers = 0
    while q:
        layers += 1
        for _ in range(len(q)):
            r, c = q.popleft()
            for dr, dc in DIRS:
                nr, nc = r + dr, c + dc
                if 0 <= nr < m and 0 <= nc < n and g[nr][nc] < g[r][c]:
                    out[nr][nc] -= 1
                    if out[nr][nc] == 0:
                        q.append((nr, nc))
    return layers


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        [[9, 9, 4], [6, 6, 8], [2, 1, 1]],
        [[3, 4, 5], [3, 2, 6], [2, 2, 1]],
        [[1]],
        [[7, 7], [7, 7]],
        [[1, 2, 3], [6, 5, 4], [7, 8, 9]],
    ]
    for g in tests:
        print("brute:", longest_increasing_path_brute(g))
        print("memo :", longest_increasing_path(g))
        print("topo :", longest_increasing_path_topo(g))
        print("---")

"""
Syntax notes (Python):
- No visited set is needed: "strictly increasing" means a path can never loop back.
- A generator inside max() scans every cell without building a list.
- `for _ in range(len(q))` processes exactly one BFS layer (len is read once).
"""
