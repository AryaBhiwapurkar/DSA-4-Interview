"""
0010. Regular Expression Matching  |  Hard  |  2-D Dynamic Programming
Link: https://leetcode.com/problems/regular-expression-matching/

Problem: Does pattern p (with '.' = any char, 'x*' = zero or more x) match
         the whole string s?

Examples:
  "aa", "a"                 -> false
  "aa", "a*"                -> true
  "ab", ".*"                -> true
  "aab", "c*a*b"            -> true
  "mississippi", "mis*is*p*." -> false
  "", "a*b*"                -> true

Approaches:
  1. Plain recursion            exponential time, O(m+n) space
  2. Top-down memo (i, j)  ⭐    O(m*n) time, O(m*n) space   <- go-to
  3. Bottom-up table            O(m*n) time, O(m*n) space
"""

from functools import cache


# ---------- Approach 1: Plain Recursion ----------
def is_match_brute(s: str, p: str) -> bool:
    def go(i: int, j: int) -> bool:
        if j == len(p):
            return i == len(s)
        first = i < len(s) and p[j] in (s[i], ".")
        if j + 1 < len(p) and p[j + 1] == "*":
            return go(i, j + 2) or (first and go(i + 1, j))  # zero copies, or one more
        return first and go(i + 1, j + 1)

    return go(0, 0)


# ---------- Approach 2: Top-down Memo ⭐ ----------
def is_match(s: str, p: str) -> bool:
    @cache
    def go(i: int, j: int) -> bool:  # does s[i:] match p[j:]?
        if j == len(p):
            return i == len(s)
        first = i < len(s) and p[j] in (s[i], ".")
        if j + 1 < len(p) and p[j + 1] == "*":
            return go(i, j + 2) or (first and go(i + 1, j))  # skip "x*", or eat one char and stay
        return first and go(i + 1, j + 1)

    return go(0, 0)


# ---------- Approach 3: Bottom-up Table ----------
def is_match_table(s: str, p: str) -> bool:
    m, n = len(s), len(p)
    dp = [[False] * (n + 1) for _ in range(m + 1)]  # dp[i][j]: s[i:] matches p[j:]
    dp[m][n] = True
    for i in range(m, -1, -1):
        for j in range(n - 1, -1, -1):
            first = i < m and p[j] in (s[i], ".")
            if j + 1 < n and p[j + 1] == "*":
                dp[i][j] = dp[i][j + 2] or (first and dp[i + 1][j])
            else:
                dp[i][j] = first and dp[i + 1][j + 1]
    return dp[0][0]


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [("aa", "a"), ("aa", "a*"), ("ab", ".*"), ("aab", "c*a*b"), ("mississippi", "mis*is*p*."), ("", "a*b*")]
    for s, p in tests:
        print("brute:", str(is_match_brute(s, p)).lower())
        print("memo :", str(is_match(s, p)).lower())
        print("table:", str(is_match_table(s, p)).lower())
        print("---")

"""
Syntax notes (Python):
- p[j] in (s[i], ".") tests "same char or wildcard" in one expression.
- `first and go(...)` short-circuits, so i + 1 is only used when s[i] exists.
- range(m, -1, -1) includes i = m: an empty rest of s can still match "x*" pairs.
"""
