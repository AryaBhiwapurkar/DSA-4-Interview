"""
1143. Longest Common Subsequence  |  Medium  |  2-D Dynamic Programming
Link: https://leetcode.com/problems/longest-common-subsequence/

Problem: Length of the longest subsequence shared by two strings.

Examples:
  "abcde", "ace"   -> 3
  "abc", "abc"     -> 3
  "abc", "def"     -> 0
  "aaaa", "aa"     -> 2
  "bsbininm", "jmjkbkjkv" -> 1

Approaches:
  1. Memoized recursion   O(m*n) time, O(m*n) space
  2. 2-D table  ⭐         O(m*n) time, O(m*n) space    <- go-to
  3. Two rows             O(m*n) time, O(n) space
"""

import sys
from functools import cache

sys.setrecursionlimit(10_000)  # memo depth reaches m + n


# ---------- Approach 1: Memoized Recursion ----------
def longest_common_subsequence_memo(a: str, b: str) -> int:
    @cache
    def lcs(i: int, j: int) -> int:
        if i == len(a) or j == len(b):  # a suffix is empty
            return 0
        if a[i] == b[j]:
            return 1 + lcs(i + 1, j + 1)
        return max(lcs(i + 1, j), lcs(i, j + 1))

    return lcs(0, 0)


# ---------- Approach 2: 2-D Table ⭐ ----------
def longest_common_subsequence(a: str, b: str) -> int:
    m, n = len(a), len(b)
    dp = [[0] * (n + 1) for _ in range(m + 1)]  # row/col 0 = empty prefix
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if a[i - 1] == b[j - 1]:
                dp[i][j] = dp[i - 1][j - 1] + 1  # pair them up
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])  # drop one
    return dp[m][n]


# ---------- Approach 3: Two Rows ----------
def longest_common_subsequence_rows(a: str, b: str) -> int:
    n = len(b)
    prev = [0] * (n + 1)
    for x in a:
        cur = [0] * (n + 1)  # fresh list: no aliasing with prev
        for j in range(1, n + 1):
            cur[j] = prev[j - 1] + 1 if x == b[j - 1] else max(prev[j], cur[j - 1])
        prev = cur
    return prev[n]


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [("abcde", "ace"), ("abc", "abc"), ("abc", "def"), ("aaaa", "aa"), ("bsbininm", "jmjkbkjkv")]
    for a, b in tests:
        print("memo :", longest_common_subsequence_memo(a, b))
        print("table:", longest_common_subsequence(a, b))
        print("rows :", longest_common_subsequence_rows(a, b))
        print("---")

"""
Syntax notes (Python):
- sys.setrecursionlimit raises the default depth (1000) for deep memo recursion.
- A fresh `cur` list per row avoids prev/cur pointing at the same list.
- [[0] * (n + 1) for _ in range(m + 1)] builds independent rows.
"""
