"""
0064. Minimum Path Sum  |  Medium  |  2-D Dynamic Programming
Link: https://leetcode.com/problems/minimum-path-sum/

Problem: Smallest sum of cells on a right/down path from the top-left to the
         bottom-right of a grid of non-negative costs.

Examples:
  [[1,3,1],[1,5,1],[4,2,1]]   -> 7
  [[1,2,3],[4,5,6]]           -> 12
  [[5]]                       -> 5
  [[1,2,3]]                   -> 6
  [[1],[2],[3]]               -> 6

Approaches:
  1. Memoized recursion   O(m*n) time, O(m*n) space
  2. 2-D table            O(m*n) time, O(m*n) space
  3. 1-D rolling row  ⭐   O(m*n) time, O(n) space     <- go-to
"""

from functools import cache

INF = float("inf")


# ---------- Approach 1: Memoized Recursion ----------
def min_path_sum_memo(grid: list[list[int]]) -> int:
    @cache
    def cost(r: int, c: int) -> float:
        if r < 0 or c < 0:
            return INF  # never chosen by min
        if r == 0 and c == 0:
            return grid[0][0]
        return grid[r][c] + min(cost(r - 1, c), cost(r, c - 1))

    return int(cost(len(grid) - 1, len(grid[0]) - 1))


# ---------- Approach 2: 2-D Table ----------
def min_path_sum_table(grid: list[list[int]]) -> int:
    m, n = len(grid), len(grid[0])
    dp = [[0] * n for _ in range(m)]
    for r in range(m):
        for c in range(n):
            if r == 0 and c == 0:
                dp[r][c] = grid[r][c]
            elif r == 0:
                dp[r][c] = grid[r][c] + dp[r][c - 1]  # only left
            elif c == 0:
                dp[r][c] = grid[r][c] + dp[r - 1][c]  # only top
            else:
                dp[r][c] = grid[r][c] + min(dp[r - 1][c], dp[r][c - 1])
    return dp[-1][-1]


# ---------- Approach 3: 1-D Rolling Row ⭐ ----------
def min_path_sum(grid: list[list[int]]) -> int:
    n = len(grid[0])
    row = [0] + [INF] * (n - 1)  # so the start cell adds to 0
    for cells in grid:
        row[0] += cells[0]
        for c in range(1, n):
            row[c] = cells[c] + min(row[c], row[c - 1])  # top vs left
    return int(row[-1])


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        [[1, 3, 1], [1, 5, 1], [4, 2, 1]],
        [[1, 2, 3], [4, 5, 6]],
        [[5]],
        [[1, 2, 3]],
        [[1], [2], [3]],
    ]
    for g in tests:
        print("memo :", min_path_sum_memo(g))
        print("table:", min_path_sum_table(g))
        print("row  :", min_path_sum(g))
        print("---")

"""
Syntax notes (Python):
- float("inf") works as a sentinel in min(); int() converts the final answer back.
- if / elif chains keep the edge cases for the first row and column readable.
- @cache keys on (r, c), so each cell is solved once.
"""
