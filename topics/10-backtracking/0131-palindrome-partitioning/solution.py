"""
0131. Palindrome Partitioning  |  Medium  |  Backtracking
Link: https://leetcode.com/problems/palindrome-partitioning/

Problem: Return every way to split s into pieces that are all palindromes.

Examples:
  "aab"  -> [["a","a","b"],["aa","b"]]
  "a"    -> [["a"]]
  "efe"  -> [["e","f","e"],["efe"]]
  "aaa"  -> [["a","a","a"],["a","aa"],["aa","a"],["aaa"]]

Approaches:
  1. Backtracking + inline check  ⭐   O(n * 2^n) time, O(n) extra   <- go-to
  2. Backtracking + pal table         O(n * 2^n) time, O(n^2) space
"""


# ---------- Approach 1: Backtracking + Inline Check ⭐ ----------
def partition(s: str) -> list[list[str]]:
    res: list[list[str]] = []
    path: list[str] = []

    def is_pal(l: int, r: int) -> bool:
        while l < r:
            if s[l] != s[r]:
                return False
            l, r = l + 1, r - 1
        return True

    def dfs(start: int) -> None:
        if start == len(s):
            res.append(path[:])
            return
        for end in range(start, len(s)):
            if is_pal(start, end):
                path.append(s[start : end + 1])
                dfs(end + 1)
                path.pop()

    dfs(0)
    return res


# ---------- Approach 2: Backtracking + Palindrome Table ----------
def partition_dp(s: str) -> list[list[str]]:
    n = len(s)
    pal = [[False] * n for _ in range(n)]
    for i in range(n - 1, -1, -1):  # pal[i][j] needs pal[i+1][j-1]
        for j in range(i, n):
            pal[i][j] = s[i] == s[j] and (j - i < 2 or pal[i + 1][j - 1])

    res: list[list[str]] = []
    path: list[str] = []

    def go(start: int) -> None:
        if start == n:
            res.append(path[:])
            return
        for end in range(start, n):
            if pal[start][end]:
                path.append(s[start : end + 1])
                go(end + 1)
                path.pop()

    go(0)
    return res


# ---------- Driver ----------
if __name__ == "__main__":
    for s in ["aab", "a", "efe", "aaa"]:
        print("inline:", sorted(partition(s)))  # any order is accepted
        print("table :", sorted(partition_dp(s)))
        print("---")

"""
Syntax notes (Python):
- s[start : end + 1] includes index end (slice end is exclusive).
- range(n - 1, -1, -1) counts down to 0 inclusive.
- `a and (b or c)` short-circuits, so pal[i+1][j-1] is never read when j - i < 2.
"""
