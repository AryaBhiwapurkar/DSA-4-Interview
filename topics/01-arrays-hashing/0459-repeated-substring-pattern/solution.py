"""
0459. Repeated Substring Pattern  |  Easy  |  Arrays & Hashing
Link: https://leetcode.com/problems/repeated-substring-pattern/

Problem: Can s be formed by repeating one of its substrings at least twice?

Examples:
  "abab"          -> True
  "aba"           -> False
  "abcabcabcabc"  -> True
  "a"             -> False
  "aaaa"          -> True
  "abac"          -> False

Approaches:
  1. Divisor-length check  ⭐   O(n * d(n)) time, O(n) space   <- go-to
  2. Doubled string             O(n) with a linear search, O(n) space
  3. KMP prefix function        O(n) time, O(n) space
"""


# ---------- Approach 1: Divisor-length Check ⭐ ----------
def repeated_substring_pattern(s: str) -> bool:
    n = len(s)
    return any(n % k == 0 and s[:k] * (n // k) == s
               for k in range(1, n // 2 + 1))  # block must repeat at least twice


# ---------- Approach 2: Doubled String ----------
def repeated_substring_pattern_doubled(s: str) -> bool:
    return s in (s + s)[1:-1]  # trim first and last char


# ---------- Approach 3: KMP Prefix Function ----------
def repeated_substring_pattern_kmp(s: str) -> bool:
    n = len(s)
    lps = [0] * n
    k = 0
    for i in range(1, n):
        while k > 0 and s[i] != s[k]:
            k = lps[k - 1]
        if s[i] == s[k]:
            k += 1
        lps[i] = k
    p = n - lps[-1]  # smallest period
    return lps[-1] > 0 and n % p == 0


# ---------- Driver ----------
if __name__ == "__main__":
    for s in ["abab", "aba", "abcabcabcabc", "a", "aaaa", "abac"]:
        print("divisor:", repeated_substring_pattern(s))
        print("doubled:", repeated_substring_pattern_doubled(s))
        print("kmp    :", repeated_substring_pattern_kmp(s))
        print("---")

"""
Syntax notes (Python):
- s[:k] * m repeats a string m times.
- any(generator) short-circuits on the first True.
- (s + s)[1:-1] drops the first and last characters.
"""
