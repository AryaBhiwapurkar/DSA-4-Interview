"""
0139. Word Break  |  Medium  |  1-D Dynamic Programming
Link: https://leetcode.com/problems/word-break/

Problem: Can s be split into a sequence of dictionary words (each word
         reusable any number of times)?

Examples:
  "leetcode", ["leet","code"]                         -> true
  "applepenapple", ["apple","pen"]                    -> true
  "catsandog", ["cats","dog","sand","and","cat"]      -> false
  "cars", ["car","ca","rs"]                           -> true (greedy "car" fails)
  "aaaaaaaaaaaaaaaaaaab", ["a","aa","aaa"]            -> false (blows up plain recursion)

Approaches:
  1. Plain recursion over prefixes   O(W^n) worst case, O(n) space
  2. Memoized recursion              O(n * W * L) time, O(n) space
  3. Bottom-up prefix DP  ⭐          O(n * W * L) time, O(n) space   <- go-to
  W = dictionary size, L = max word length.
"""

from functools import cache


# ---------- Approach 1: Plain Recursion ----------
def word_break_brute(s: str, word_dict: list[str]) -> bool:
    def can(i: int) -> bool:
        return i == len(s) or any(s.startswith(w, i) and can(i + len(w)) for w in word_dict)

    return can(0)


# ---------- Approach 2: Memoized Recursion ----------
def word_break_memo(s: str, word_dict: list[str]) -> bool:
    @cache
    def can(i: int) -> bool:  # a False result marks a dead-end suffix: never retried
        return i == len(s) or any(s.startswith(w, i) and can(i + len(w)) for w in word_dict)

    return can(0)


# ---------- Approach 3: Bottom-up Prefix DP ⭐ ----------
def word_break(s: str, word_dict: list[str]) -> bool:
    n = len(s)
    dp = [False] * (n + 1)  # dp[i]: s[:i] can be split
    dp[0] = True
    for i in range(1, n + 1):
        for w in word_dict:
            if len(w) <= i and dp[i - len(w)] and s[i - len(w) : i] == w:
                dp[i] = True
                break
    return dp[n]


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        ("leetcode", ["leet", "code"]),
        ("applepenapple", ["apple", "pen"]),
        ("catsandog", ["cats", "dog", "sand", "and", "cat"]),
        ("cars", ["car", "ca", "rs"]),
        ("aaaaaaaaaaaaaaaaaaab", ["a", "aa", "aaa"]),
    ]
    for s, d in tests:
        print("brute:", word_break_brute(s, d))
        print("memo :", word_break_memo(s, d))
        print("dp   :", word_break(s, d))
        print("---")

"""
Syntax notes (Python):
- s.startswith(w, i) checks for w at position i without slicing.
- any(generator) short-circuits on the first True.
- `i == len(s) or any(...)` returns early at the end of the string.
"""
