"""
0115. Distinct Subsequences  |  Hard  |  2-D Dynamic Programming
Link: https://leetcode.com/problems/distinct-subsequences/

Problem: Count the ways to pick positions in s that spell t (subsequences of
         s equal to t).

Examples:
  "rabbbit", "rabbit"   -> 3
  "babgbag", "bag"      -> 5
  "abc", ""             -> 1  (the empty subsequence)
  "", "a"               -> 0
  "aaa", "aa"           -> 3

Approaches:
  1. Memoized recursion (i, j)        O(m*n) time, O(m*n) space
  2. 2-D table  ⭐                     O(m*n) time, O(m*n) space   <- go-to
  3. 1-D row, j iterated backwards    O(m*n) time, O(n) space
"""

import sys
from functools import cache

sys.setrecursionlimit(10_000)  # depth reaches m + n


# ---------- Approach 1: Memoized Recursion ----------
def num_distinct_memo(s: str, t: str) -> int:
    @cache
    def ways(i: int, j: int) -> int:  # ways for s[i:] to produce t[j:]
        if j == len(t):
            return 1
        if len(s) - i < len(t) - j:  # not enough characters left
            return 0
        skip = ways(i + 1, j)
        return skip + ways(i + 1, j + 1) if s[i] == t[j] else skip

    return ways(0, 0)


# ---------- Approach 2: 2-D Table ⭐ ----------
def num_distinct(s: str, t: str) -> int:
    m, n = len(s), len(t)
    dp = [[0] * (n + 1) for _ in range(m + 1)]  # dp[i][j]: ways s[:i] produces t[:j]
    for i in range(m + 1):
        dp[i][0] = 1  # empty t: one way (pick nothing)
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            dp[i][j] = dp[i - 1][j]  # don't use s[i-1]
            if s[i - 1] == t[j - 1]:
                dp[i][j] += dp[i - 1][j - 1]  # use s[i-1] as t[j-1]
    return dp[m][n]


# ---------- Approach 3: 1-D Row ----------
def num_distinct_row(s: str, t: str) -> int:
    n = len(t)
    row = [1] + [0] * n
    for c in s:
        for j in range(n, 0, -1):  # backwards: row[j-1] is still the previous row
            if c == t[j - 1]:
                row[j] += row[j - 1]
    return row[n]


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [("rabbbit", "rabbit"), ("babgbag", "bag"), ("abc", ""), ("", "a"), ("aaa", "aa")]
    for s, t in tests:
        print("memo :", num_distinct_memo(s, t))
        print("table:", num_distinct(s, t))
        print("row  :", num_distinct_row(s, t))
        print("---")

"""
Syntax notes (Python):
- range(n, 0, -1) walks j from n down to 1.
- Python ints are unbounded, so intermediate counts can't overflow.
- `x + y if cond else x` parses as (x + y) if cond else x.
"""
