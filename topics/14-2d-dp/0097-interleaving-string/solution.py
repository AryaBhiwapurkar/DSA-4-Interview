"""
0097. Interleaving String  |  Medium  |  2-D Dynamic Programming
Link: https://leetcode.com/problems/interleaving-string/

Problem: Can s3 be formed by merging s1 and s2 while keeping each one's
         character order?

Examples:
  "aabcc", "dbbca", "aadbbcbcac"   -> true
  "aabcc", "dbbca", "aadbbbaccc"   -> false
  "", "", ""                       -> true
  "a", "", "a"                     -> true
  "ab", "c", "abcd"                -> false  (length mismatch)

Approaches:
  1. Memoized recursion (i, j)    O(m*n) time, O(m*n) space
  2. 2-D table  ⭐                 O(m*n) time, O(m*n) space   <- go-to
  3. 1-D row                      O(m*n) time, O(n) space
"""

from functools import cache


# ---------- Approach 1: Memoized Recursion ----------
def is_interleave_memo(s1: str, s2: str, s3: str) -> bool:
    m, n = len(s1), len(s2)
    if m + n != len(s3):
        return False

    @cache
    def ok(i: int, j: int) -> bool:  # can s1[i:] and s2[j:] form s3[i+j:]?
        if i == m and j == n:
            return True
        k = i + j
        return (i < m and s1[i] == s3[k] and ok(i + 1, j)) or (j < n and s2[j] == s3[k] and ok(i, j + 1))

    return ok(0, 0)


# ---------- Approach 2: 2-D Table ⭐ ----------
def is_interleave(s1: str, s2: str, s3: str) -> bool:
    m, n = len(s1), len(s2)
    if m + n != len(s3):
        return False
    dp = [[False] * (n + 1) for _ in range(m + 1)]  # dp[i][j]: s1[:i] + s2[:j] form s3[:i+j]
    dp[0][0] = True
    for i in range(m + 1):
        for j in range(n + 1):
            if i > 0 and s1[i - 1] == s3[i + j - 1] and dp[i - 1][j]:  # last char from s1
                dp[i][j] = True
            if j > 0 and s2[j - 1] == s3[i + j - 1] and dp[i][j - 1]:  # last char from s2
                dp[i][j] = True
    return dp[m][n]


# ---------- Approach 3: 1-D Row ----------
def is_interleave_row(s1: str, s2: str, s3: str) -> bool:
    m, n = len(s1), len(s2)
    if m + n != len(s3):
        return False
    row = [False] * (n + 1)
    for i in range(m + 1):
        for j in range(n + 1):
            if i == 0 and j == 0:
                row[j] = True
                continue
            from_s1 = i > 0 and row[j] and s1[i - 1] == s3[i + j - 1]  # row[j] is still dp[i-1][j]
            from_s2 = j > 0 and row[j - 1] and s2[j - 1] == s3[i + j - 1]
            row[j] = from_s1 or from_s2
    return row[n]


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        ("aabcc", "dbbca", "aadbbcbcac"),
        ("aabcc", "dbbca", "aadbbbaccc"),
        ("", "", ""),
        ("a", "", "a"),
        ("ab", "c", "abcd"),
    ]
    for s1, s2, s3 in tests:
        print("memo :", str(is_interleave_memo(s1, s2, s3)).lower())
        print("table:", str(is_interleave(s1, s2, s3)).lower())
        print("row  :", str(is_interleave_row(s1, s2, s3)).lower())
        print("---")

"""
Syntax notes (Python):
- `a and b and f()` short-circuits, so the recursive call runs only when the char matches.
- str(True).lower() prints "true" to match the C++ output.
- The k index of s3 is always i + j, so it isn't part of the state.
"""
