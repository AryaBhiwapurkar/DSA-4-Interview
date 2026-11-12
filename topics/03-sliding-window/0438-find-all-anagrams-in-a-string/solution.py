"""
0438. Find All Anagrams in a String  |  Medium  |  Sliding Window
Link: https://leetcode.com/problems/find-all-anagrams-in-a-string/

Problem: Start indices of every substring of s that is an anagram of p.

Examples:
  s = "cbaebabacd", p = "abc"  -> [0,6]
  s = "abab",       p = "ab"   -> [0,1,2]
  s = "a",          p = "ab"   -> []
  s = "aaab",       p = "aab"  -> [1]

Approaches:
  1. Count each window from scratch     O(n * |p|) time
  2. Sliding count arrays               O(26 * n) time, O(1) space
  3. Sliding window + matches  ⭐       O(n) time, O(1) space   <- go-to
"""

from collections import Counter


# ---------- Approach 1: Count Each Window ----------
def find_anagrams_brute(s: str, p: str) -> list[int]:
    need, m = Counter(p), len(p)
    return [i for i in range(len(s) - m + 1) if Counter(s[i:i + m]) == need]


# ---------- Approach 2: Sliding Count Arrays ----------
def find_anagrams_arrays(s: str, p: str) -> list[int]:
    m = len(p)
    need, have = [0] * 26, [0] * 26
    for c in p:
        need[ord(c) - 97] += 1
    out = []
    for r, c in enumerate(s):
        have[ord(c) - 97] += 1
        if r >= m:
            have[ord(s[r - m]) - 97] -= 1  # drop the char leaving the window
        if r >= m - 1 and have == need:
            out.append(r - m + 1)
    return out


# ---------- Approach 3: Matches Counter ⭐ ----------
def find_anagrams(s: str, p: str) -> list[int]:
    m = len(p)
    diff = [0] * 26  # window count - p count, per letter
    for c in p:
        diff[ord(c) - 97] -= 1
    matches = diff.count(0)  # letters whose counts agree

    def bump(k: int, d: int) -> None:
        nonlocal matches
        if diff[k] == 0:
            matches -= 1
        diff[k] += d
        if diff[k] == 0:
            matches += 1

    out = []
    for r, c in enumerate(s):
        bump(ord(c) - 97, 1)
        if r >= m:
            bump(ord(s[r - m]) - 97, -1)
        if r >= m - 1 and matches == 26:
            out.append(r - m + 1)
    return out


# ---------- Driver ----------
if __name__ == "__main__":
    for s, p in [("cbaebabacd", "abc"), ("abab", "ab"), ("a", "ab"), ("aaab", "aab")]:
        print("brute  :", find_anagrams_brute(s, p))
        print("arrays :", find_anagrams_arrays(s, p))
        print("matches:", find_anagrams(s, p))
        print("---")

"""
Syntax notes (Python):
- Counter equality compares letter multisets directly (Counter(a) == Counter(b)).
- nonlocal lets a nested function rebind a variable of the enclosing function.
- ord(c) - 97 is the same as ord(c) - ord("a").
"""
