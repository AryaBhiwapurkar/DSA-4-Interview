"""
0200. Number of Islands  |  Medium  |  Graphs
Link: https://leetcode.com/problems/number-of-islands/

Problem: Count groups of 4-connected '1' cells in a grid of '1'/'0'.

Examples:
  11110/11010/11000/00000  -> 1
  11000/11000/00100/00011  -> 3
  0                        -> 0
  101/010/101              -> 5

Approaches:
  1. DFS flood fill  ⭐   O(m*n) time, O(m*n) stack   <- go-to
  2. BFS flood fill       O(m*n) time, O(min(m,n)) queue typically
  3. Union-Find           O(m*n * alpha) time, O(m*n) space
"""

from collections import deque

DIRS = ((1, 0), (-1, 0), (0, 1), (0, -1))


# ---------- Approach 1: DFS Flood Fill ⭐ ----------
def num_islands(grid: list[list[str]]) -> int:
    g = [row[:] for row in grid]
    m, n = len(g), len(g[0])

    def sink(r: int, c: int) -> None:
        stack = [(r, c)]  # explicit stack: 9e4 cells would exceed the recursion limit
        while stack:
            r, c = stack.pop()
            if 0 <= r < m and 0 <= c < n and g[r][c] == "1":
                g[r][c] = "0"  # visited = sunk
                stack.extend((r + dr, c + dc) for dr, dc in DIRS)

    count = 0
    for r in range(m):
        for c in range(n):
            if g[r][c] == "1":
                count += 1
                sink(r, c)
    return count


# ---------- Approach 2: BFS Flood Fill ----------
def num_islands_bfs(grid: list[list[str]]) -> int:
    g = [row[:] for row in grid]
    m, n, count = len(g), len(g[0]), 0
    for i in range(m):
        for j in range(n):
            if g[i][j] != "1":
                continue
            count += 1
            g[i][j] = "0"  # mark on push, not on pop
            q = deque([(i, j)])
            while q:
                r, c = q.popleft()
                for dr, dc in DIRS:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < m and 0 <= nc < n and g[nr][nc] == "1":
                        g[nr][nc] = "0"
                        q.append((nr, nc))
    return count


# ---------- Approach 3: Union-Find ----------
def num_islands_uf(grid: list[list[str]]) -> int:
    m, n = len(grid), len(grid[0])
    parent = list(range(m * n))

    def find(x: int) -> int:
        while parent[x] != x:
            parent[x] = parent[parent[x]]  # path halving
            x = parent[x]
        return x

    def unite(a: int, b: int) -> bool:
        ra, rb = find(a), find(b)
        if ra == rb:
            return False
        parent[rb] = ra
        return True

    count = 0
    for r in range(m):
        for c in range(n):
            if grid[r][c] != "1":
                continue
            count += 1
            if r + 1 < m and grid[r + 1][c] == "1" and unite(r * n + c, (r + 1) * n + c):
                count -= 1
            if c + 1 < n and grid[r][c + 1] == "1" and unite(r * n + c, r * n + c + 1):
                count -= 1
    return count


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [["11110", "11010", "11000", "00000"], ["11000", "11000", "00100", "00011"], ["0"], ["101", "010", "101"]]
    for rows in tests:
        g = [list(s) for s in rows]
        print("dfs:", num_islands(g))
        print("bfs:", num_islands_bfs(g))
        print("uf :", num_islands_uf(g))
        print("---")

"""
Syntax notes (Python):
- [row[:] for row in grid] copies a 2-D list (grid[:] alone shares the rows).
- Path halving `parent[x] = parent[parent[x]]` is an iterative path compression.
- Iterative DFS: push neighbours, bounds-check on pop.
"""
