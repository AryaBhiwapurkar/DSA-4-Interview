"""
0005. Longest Palindromic Substring  |  Medium  |  1-D Dynamic Programming
Link: https://leetcode.com/problems/longest-palindromic-substring/

Problem: Return the longest contiguous substring of s that reads the same
         both ways.

Examples:
  "babad"             -> "bab" ("aba" also valid; all approaches keep the first)
  "cbbd"              -> "bb"
  "a"                 -> "a"
  "ac"                -> "a"
  "forgeeksskeegfor"  -> "geeksskeeg"

Approaches:
  1. Brute force (check every substring)  O(n^3) time, O(1) space
  2. DP table by length                   O(n^2) time, O(n^2) space
  3. Expand around center  ⭐              O(n^2) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Brute Force ----------
def longest_palindrome_brute(s: str) -> str:
    best = s[0]
    for i in range(len(s)):
        for j in range(i + len(best), len(s)):  # only lengths that would beat best
            sub = s[i : j + 1]
            if sub == sub[::-1]:
                best = sub
    return best


# ---------- Approach 2: DP Table by Length ----------
def longest_palindrome_dp(s: str) -> str:
    n = len(s)
    pal = [[False] * n for _ in range(n)]  # pal[i][j]: s[i..j] is a palindrome
    start, best = 0, 1
    for length in range(1, n + 1):
        for i in range(n - length + 1):
            j = i + length - 1
            pal[i][j] = s[i] == s[j] and (length <= 2 or pal[i + 1][j - 1])  # inner part already known
            if pal[i][j] and length > best:
                start, best = i, length
    return s[start : start + best]


# ---------- Approach 3: Expand Around Center ⭐ ----------
def longest_palindrome(s: str) -> str:
    def expand(l: int, r: int) -> int:
        while l >= 0 and r < len(s) and s[l] == s[r]:
            l -= 1
            r += 1
        return r - l - 1  # length of s[l+1..r-1]

    start = best = 0
    for i in range(len(s)):
        length = max(expand(i, i), expand(i, i + 1))  # odd and even centers
        if length > best:
            best, start = length, i - (length - 1) // 2
    return s[start : start + best]


# ---------- Driver ----------
if __name__ == "__main__":
    for s in ["babad", "cbbd", "a", "ac", "forgeeksskeegfor"]:
        print(f'brute : "{longest_palindrome_brute(s)}"')
        print(f'dp    : "{longest_palindrome_dp(s)}"')
        print(f'expand: "{longest_palindrome(s)}"')
        print("---")

"""
Syntax notes (Python):
- sub[::-1] reverses a string; `sub == sub[::-1]` is the one-line palindrome check.
- [[False] * n for _ in range(n)] builds independent rows ([[False]*n]*n would alias them).
- s[start : start + best] slices by end index (exclusive), unlike C++ substr.
"""
