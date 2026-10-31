"""
0647. Palindromic Substrings  |  Medium  |  1-D Dynamic Programming
Link: https://leetcode.com/problems/palindromic-substrings/

Problem: Count substrings of s that are palindromes. Substrings at
         different positions count separately.

Examples:
  "abc"   -> 3
  "aaa"   -> 6
  "abba"  -> 6
  "a"     -> 1

Approaches:
  1. Brute force (check every substring)  O(n^3) time, O(1) space
  2. DP table by length                   O(n^2) time, O(n^2) space
  3. Expand around center  ⭐              O(n^2) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Brute Force ----------
def count_substrings_brute(s: str) -> int:
    n = len(s)
    return sum(1 for i in range(n) for j in range(i + 1, n + 1) if s[i:j] == s[i:j][::-1])


# ---------- Approach 2: DP Table by Length ----------
def count_substrings_dp(s: str) -> int:
    n = len(s)
    pal = [[False] * n for _ in range(n)]
    count = 0
    for length in range(1, n + 1):
        for i in range(n - length + 1):
            j = i + length - 1
            pal[i][j] = s[i] == s[j] and (length <= 2 or pal[i + 1][j - 1])
            count += pal[i][j]
    return count


# ---------- Approach 3: Expand Around Center ⭐ ----------
def count_substrings(s: str) -> int:
    def count_from(l: int, r: int) -> int:
        c = 0
        while l >= 0 and r < len(s) and s[l] == s[r]:  # each step = one more palindrome
            c += 1
            l -= 1
            r += 1
        return c

    return sum(count_from(i, i) + count_from(i, i + 1) for i in range(len(s)))  # odd + even centers


# ---------- Driver ----------
if __name__ == "__main__":
    for s in ["abc", "aaa", "abba", "a"]:
        print("brute :", count_substrings_brute(s))
        print("dp    :", count_substrings_dp(s))
        print("expand:", count_substrings(s))
        print("---")

"""
Syntax notes (Python):
- `count += pal[i][j]` works because True == 1 and False == 0.
- sum(1 for ... if cond) counts matches without building a list.
- s[i:j] is end-exclusive, so j runs to n inclusive in range(i + 1, n + 1).
"""
