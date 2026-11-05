"""
0063. Unique Paths II  |  Medium  |  2-D Dynamic Programming
Link: https://leetcode.com/problems/unique-paths-ii/

Problem: Count right/down paths from top-left to bottom-right that avoid
         blocked cells (1 = blocked).

Examples:
  [[0,0,0],[0,1,0],[0,0,0]]   -> 2
  [[0,1],[0,0]]               -> 1
  [[1]]                       -> 0  (start blocked)
  [[0,0],[0,1]]               -> 0  (end blocked)
  [[0],[1],[0]]               -> 0

Approaches:
  1. Memoized recursion   O(m*n) time, O(m*n) space
  2. 2-D table            O(m*n) time, O(m*n) space
  3. 1-D rolling row  ⭐   O(m*n) time, O(n) space     <- go-to
"""

from functools import cache


# ---------- Approach 1: Memoized Recursion ----------
def unique_paths_with_obstacles_memo(grid: list[list[int]]) -> int:
    @cache
    def paths(r: int, c: int) -> int:
        if r < 0 or c < 0 or grid[r][c] == 1:
            return 0
        if r == 0 and c == 0:
            return 1
        return paths(r - 1, c) + paths(r, c - 1)

    return paths(len(grid) - 1, len(grid[0]) - 1)


# ---------- Approach 2: 2-D Table ----------
def unique_paths_with_obstacles_table(grid: list[list[int]]) -> int:
    m, n = len(grid), len(grid[0])
    dp = [[0] * n for _ in range(m)]
    for r in range(m):
        for c in range(n):
            if grid[r][c] == 1:  # blocked stays 0
                continue
            if r == 0 and c == 0:
                dp[r][c] = 1
                continue
            dp[r][c] = (dp[r - 1][c] if r else 0) + (dp[r][c - 1] if c else 0)
    return dp[-1][-1]


# ---------- Approach 3: 1-D Rolling Row ⭐ ----------
def unique_paths_with_obstacles(grid: list[list[int]]) -> int:
    n = len(grid[0])
    row = [1] + [0] * (n - 1)  # a blocked start zeroes it below
    for cells in grid:
        for c in range(n):
            if cells[c] == 1:
                row[c] = 0
            elif c > 0:
                row[c] += row[c - 1]  # above + left
    return row[-1]


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        [[0, 0, 0], [0, 1, 0], [0, 0, 0]],
        [[0, 1], [0, 0]],
        [[1]],
        [[0, 0], [0, 1]],
        [[0], [1], [0]],
    ]
    for g in tests:
        print("memo :", unique_paths_with_obstacles_memo(g))
        print("table:", unique_paths_with_obstacles_table(g))
        print("row  :", unique_paths_with_obstacles(g))
        print("---")

"""
Syntax notes (Python):
- dp[r - 1][c] if r else 0 guards the edge; dp[-1] would silently read the last row.
- [1] + [0] * (n - 1) seeds only the start column.
- dp[-1][-1] is the bottom-right cell.
"""
