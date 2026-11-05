"""
0221. Maximal Square  |  Medium  |  2-D Dynamic Programming
Link: https://leetcode.com/problems/maximal-square/

Problem: Area of the largest all-'1' square in a grid of '0'/'1' chars.

Examples:
  [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]] -> 4
  [["0","1"],["1","0"]]                    -> 1
  [["0"]]                                  -> 0
  [["1","1","1"],["1","1","1"],["1","1","1"]] -> 9
  [["1","1"],["1","0"]]                    -> 1

Approaches:
  1. Brute-force expansion   O(m*n*min(m,n)^2) time, O(1) space
  2. 2-D DP  ⭐               O(m*n) time, O(m*n) space    <- go-to
  3. 1-D rolling row         O(m*n) time, O(n) space
"""


# ---------- Approach 1: Brute-force Expansion ----------
def maximal_square_brute(g: list[list[str]]) -> int:
    m, n, best = len(g), len(g[0]), 0
    for r in range(m):
        for c in range(n):
            if g[r][c] != "1":
                continue
            k = 1  # current side, top-left at (r, c)
            while r + k < m and c + k < n and all(
                g[r + k][c + i] == "1" and g[r + i][c + k] == "1" for i in range(k + 1)
            ):  # new bottom row and right column
                k += 1
            best = max(best, k)
    return best * best


# ---------- Approach 2: 2-D DP ⭐ ----------
def maximal_square(g: list[list[str]]) -> int:
    m, n = len(g), len(g[0])
    dp = [[0] * (n + 1) for _ in range(m + 1)]  # padded: row 0 / col 0 are zeros
    side = 0
    for r in range(1, m + 1):
        for c in range(1, n + 1):
            if g[r - 1][c - 1] == "1":
                dp[r][c] = 1 + min(dp[r - 1][c], dp[r][c - 1], dp[r - 1][c - 1])
                side = max(side, dp[r][c])
    return side * side


# ---------- Approach 3: 1-D Rolling Row ----------
def maximal_square_row(g: list[list[str]]) -> int:
    n = len(g[0])
    row = [0] * (n + 1)
    side = 0
    for cells in g:
        diag = 0  # old row[c-1] = top-left
        for c in range(1, n + 1):
            top = row[c]
            row[c] = 1 + min(top, row[c - 1], diag) if cells[c - 1] == "1" else 0
            diag = top
            side = max(side, row[c])
    return side * side


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        [list("10100"), list("10111"), list("11111"), list("10010")],
        [list("01"), list("10")],
        [list("0")],
        [list("111"), list("111"), list("111")],
        [list("11"), list("10")],
    ]
    for g in tests:
        print("brute:", maximal_square_brute(g))
        print("dp   :", maximal_square(g))
        print("row  :", maximal_square_row(g))
        print("---")

"""
Syntax notes (Python):
- list("10100") splits a string into single-character cells.
- all(generator) short-circuits on the first False.
- a if cond else b keeps the row update on one line.
"""
