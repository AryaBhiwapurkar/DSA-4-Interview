"""
0062. Unique Paths  |  Medium  |  2-D Dynamic Programming
Link: https://leetcode.com/problems/unique-paths/

Problem: Count paths from the top-left to the bottom-right of an m x n grid
         moving only right or down.

Examples:
  m=3, n=7     -> 28
  m=3, n=2     -> 3
  m=1, n=1     -> 1
  m=1, n=5     -> 1
  m=10, n=10   -> 48620

Approaches:
  1. Memoized recursion   O(m*n) time, O(m*n) space
  2. 2-D table            O(m*n) time, O(m*n) space
  3. 1-D rolling row  ⭐   O(m*n) time, O(n) space     <- go-to
  4. Combinatorics        O(min(m,n)) time, O(1) space
"""

from functools import cache
from math import comb


# ---------- Approach 1: Memoized Recursion ----------
def unique_paths_memo(m: int, n: int) -> int:
    @cache
    def paths(r: int, c: int) -> int:
        if r == 0 or c == 0:  # first row / column: one straight path
            return 1
        return paths(r - 1, c) + paths(r, c - 1)

    return paths(m - 1, n - 1)


# ---------- Approach 2: 2-D Table ----------
def unique_paths_table(m: int, n: int) -> int:
    dp = [[1] * n for _ in range(m)]
    for r in range(1, m):
        for c in range(1, n):
            dp[r][c] = dp[r - 1][c] + dp[r][c - 1]  # from above + from the left
    return dp[m - 1][n - 1]


# ---------- Approach 3: 1-D Rolling Row ⭐ ----------
def unique_paths(m: int, n: int) -> int:
    row = [1] * n
    for _ in range(1, m):
        for c in range(1, n):
            row[c] += row[c - 1]  # row[c] is still "above"
    return row[-1]


# ---------- Approach 4: Combinatorics ----------
def unique_paths_math(m: int, n: int) -> int:
    return comb(m + n - 2, m - 1)  # choose which moves are downs


# ---------- Driver ----------
if __name__ == "__main__":
    for m, n in [(3, 7), (3, 2), (1, 1), (1, 5), (10, 10)]:
        print("memo :", unique_paths_memo(m, n))
        print("table:", unique_paths_table(m, n))
        print("row  :", unique_paths(m, n))
        print("math :", unique_paths_math(m, n))
        print("---")

"""
Syntax notes (Python):
- [[1] * n for _ in range(m)] builds independent rows; [[1] * n] * m would alias one row.
- math.comb(n, k) computes binomial coefficients exactly (Python 3.8+).
- @cache on a nested function memoizes per call of the outer function.
"""
