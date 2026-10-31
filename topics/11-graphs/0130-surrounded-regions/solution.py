"""
0130. Surrounded Regions  |  Medium  |  Graphs
Link: https://leetcode.com/problems/surrounded-regions/

Problem: Flip every 'O' region that doesn't touch the grid border to 'X',
         in place.

Examples:
  XXXX/XOOX/XXOX/XOXX  -> XXXX/XXXX/XXXX/XOXX
  X                    -> X
  OO/OO                -> OO/OO (all on the border)
  XXX/XOX/XXX          -> XXX/XXX/XXX

Approaches:
  1. BFS per region            O(m*n) time, O(m*n) space
  2. DFS from border  ⭐        O(m*n) time, O(m*n) stack   <- go-to
"""

from collections import deque

DIRS = ((1, 0), (-1, 0), (0, 1), (0, -1))


# ---------- Approach 1: BFS per Region ----------
def solve_bfs(b: list[list[str]]) -> None:
    m, n = len(b), len(b[0])
    seen = [[False] * n for _ in range(m)]
    for i in range(m):
        for j in range(n):
            if b[i][j] != "O" or seen[i][j]:
                continue
            region, border = [], False
            q = deque([(i, j)])
            seen[i][j] = True
            while q:
                r, c = q.popleft()
                region.append((r, c))
                if r in (0, m - 1) or c in (0, n - 1):
                    border = True
                for dr, dc in DIRS:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < m and 0 <= nc < n and not seen[nr][nc] and b[nr][nc] == "O":
                        seen[nr][nc] = True
                        q.append((nr, nc))
            if not border:
                for r, c in region:
                    b[r][c] = "X"


# ---------- Approach 2: DFS from the Border ⭐ ----------
def solve(b: list[list[str]]) -> None:
    m, n = len(b), len(b[0])

    def mark_safe(r: int, c: int) -> None:
        stack = [(r, c)]  # explicit stack: 4e4 cells would exceed the recursion limit
        while stack:
            r, c = stack.pop()
            if 0 <= r < m and 0 <= c < n and b[r][c] == "O":
                b[r][c] = "T"  # connected to the border: safe
                stack.extend((r + dr, c + dc) for dr, dc in DIRS)

    for i in range(m):
        mark_safe(i, 0)
        mark_safe(i, n - 1)
    for j in range(n):
        mark_safe(0, j)
        mark_safe(m - 1, j)
    for row in b:
        for j, ch in enumerate(row):
            if ch == "O":
                row[j] = "X"  # enclosed
            elif ch == "T":
                row[j] = "O"  # restore safe cells


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [["XXXX", "XOOX", "XXOX", "XOXX"], ["X"], ["OO", "OO"], ["XXX", "XOX", "XXX"]]
    for rows in tests:
        a, b = [list(s) for s in rows], [list(s) for s in rows]
        solve_bfs(a)
        solve(b)
        print("bfs   :", a)
        print("border:", b)
        print("---")

"""
Syntax notes (Python):
- `r in (0, m - 1)` is a compact "is it on either edge" test.
- stack.extend(generator) pushes all four neighbours; bounds are checked on pop.
- Iterative DFS with a list as a stack avoids RecursionError on big grids.
"""
