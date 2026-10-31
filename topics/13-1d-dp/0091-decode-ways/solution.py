"""
0091. Decode Ways  |  Medium  |  1-D Dynamic Programming
Link: https://leetcode.com/problems/decode-ways/

Problem: Digits map to letters 1->A ... 26->Z. Count the ways to split the
         digit string into valid codes (no leading zeros, nothing above 26).

Examples:
  "12"     -> 2
  "226"    -> 3
  "06"     -> 0
  "10"     -> 1
  "2101"   -> 1
  "11106"  -> 2
  "27"     -> 1

Approaches:
  1. Memoized recursion            O(n) time, O(n) space
  2. Two variables (bottom-up)  ⭐  O(n) time, O(1) space   <- go-to
"""

from functools import cache


# ---------- Approach 1: Memoized Recursion ----------
def num_decodings_memo(s: str) -> int:
    @cache
    def ways(i: int) -> int:  # decodings of s[i:]
        if i == len(s):  # consumed everything: one valid decoding
            return 1
        if s[i] == "0":  # no code starts with 0
            return 0
        res = ways(i + 1)
        if i + 1 < len(s) and 10 <= int(s[i : i + 2]) <= 26:
            res += ways(i + 2)
        return res

    return ways(0)


# ---------- Approach 2: Two Variables ⭐ ----------
def num_decodings(s: str) -> int:
    prev2, prev1 = 1, int(s[0] != "0")  # dp[0] (empty prefix), dp[1]
    for i in range(2, len(s) + 1):
        cur = prev1 if s[i - 1] != "0" else 0  # last char as a single code
        if 10 <= int(s[i - 2 : i]) <= 26:  # last two chars as one code
            cur += prev2
        prev2, prev1 = prev1, cur
    return prev1


# ---------- Driver ----------
if __name__ == "__main__":
    for s in ["12", "226", "06", "10", "2101", "11106", "27"]:
        print("memo:", num_decodings_memo(s))
        print("dp  :", num_decodings(s))
        print("---")

"""
Syntax notes (Python):
- int(s[i-2:i]) parses a two-char slice; "06" -> 6, which the 10 <= x check rejects.
- Chained comparison `10 <= x <= 26` reads like math.
- int(bool) gives 0/1 for the base case.
"""
