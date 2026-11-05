"""
0072. Edit Distance  |  Medium  |  2-D Dynamic Programming
Link: https://leetcode.com/problems/edit-distance/

Problem: Minimum inserts, deletes and replacements to turn word1 into word2.

Examples:
  "horse", "ros"            -> 3
  "intention", "execution"  -> 5
  "", "abc"                 -> 3
  "abc", ""                 -> 3
  "same", "same"            -> 0

Approaches:
  1. Memoized recursion   O(m*n) time, O(m*n) space
  2. 2-D table  ⭐         O(m*n) time, O(m*n) space    <- go-to
  3. Two rows             O(m*n) time, O(n) space
"""

import sys
from functools import cache

sys.setrecursionlimit(10_000)  # memo depth reaches m + n


# ---------- Approach 1: Memoized Recursion ----------
def min_distance_memo(a: str, b: str) -> int:
    @cache
    def ed(i: int, j: int) -> int:
        if i == len(a):
            return len(b) - j  # insert the rest of b
        if j == len(b):
            return len(a) - i  # delete the rest of a
        if a[i] == b[j]:
            return ed(i + 1, j + 1)
        return 1 + min(ed(i + 1, j + 1), ed(i + 1, j), ed(i, j + 1))  # replace, delete, insert

    return ed(0, 0)


# ---------- Approach 2: 2-D Table ⭐ ----------
def min_distance(a: str, b: str) -> int:
    m, n = len(a), len(b)
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    for i in range(m + 1):
        dp[i][0] = i  # delete everything
    for j in range(n + 1):
        dp[0][j] = j  # insert everything
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if a[i - 1] == b[j - 1]:
                dp[i][j] = dp[i - 1][j - 1]
            else:
                dp[i][j] = 1 + min(dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1])
    return dp[m][n]


# ---------- Approach 3: Two Rows ----------
def min_distance_rows(a: str, b: str) -> int:
    n = len(b)
    prev = list(range(n + 1))  # row 0: 0, 1, ..., n
    for i, x in enumerate(a, 1):
        cur = [i] + [0] * n
        for j in range(1, n + 1):
            cur[j] = prev[j - 1] if x == b[j - 1] else 1 + min(prev[j - 1], prev[j], cur[j - 1])
        prev = cur
    return prev[n]


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [("horse", "ros"), ("intention", "execution"), ("", "abc"), ("abc", ""), ("same", "same")]
    for a, b in tests:
        print("memo :", min_distance_memo(a, b))
        print("table:", min_distance(a, b))
        print("rows :", min_distance_rows(a, b))
        print("---")

"""
Syntax notes (Python):
- enumerate(a, 1) starts the counter at 1, matching dp row numbers.
- list(range(n + 1)) builds the base row 0..n.
- min() accepts any number of positional arguments.
"""
