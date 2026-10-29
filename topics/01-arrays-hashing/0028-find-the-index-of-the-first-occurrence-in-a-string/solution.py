"""
0028. Find the Index of the First Occurrence in a String  |  Easy  |  Arrays & Hashing
Link: https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/

Problem: Return the index of the first occurrence of needle in
         haystack, or -1 if it does not occur.

Examples:
  "sadbutsad", "sad"       -> 0
  "leetcode",  "leeto"     -> -1
  "abc",       "c"         -> 2
  "aabaaabaaac", "aabaaac" -> 4

Approaches:
  1. Brute-force window  ⭐  O(n*m) time, O(1) space   <- go-to
  2. KMP                    O(n+m) time, O(m) space
"""


# ---------- Approach 1: Brute-Force Window ⭐ ----------
def str_str(haystack: str, needle: str) -> int:
    n, m = len(haystack), len(needle)
    for i in range(n - m + 1):  # empty range if m > n
        j = 0
        while j < m and haystack[i + j] == needle[j]:
            j += 1
        if j == m:
            return i
    return -1


# ---------- Approach 2: KMP ----------
def str_str_kmp(haystack: str, needle: str) -> int:
    m = len(needle)
    lps = [0] * m  # lps[i]: longest proper prefix == suffix of needle[:i+1]
    length, i = 0, 1
    while i < m:
        if needle[i] == needle[length]:
            length += 1
            lps[i] = length
            i += 1
        elif length > 0:
            length = lps[length - 1]  # fall back, don't advance i
        else:
            i += 1
    j = 0
    for i, c in enumerate(haystack):
        while j > 0 and c != needle[j]:
            j = lps[j - 1]  # reuse the matched prefix
        if c == needle[j]:
            j += 1
            if j == m:
                return i - m + 1
    return -1


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [("sadbutsad", "sad"), ("leetcode", "leeto"), ("abc", "c"), ("aabaaabaaac", "aabaaac")]
    for h, nd in tests:
        print("brute:", str_str(h, nd))
        print("kmp  :", str_str_kmp(h, nd))
        print("---")

"""
Syntax notes (Python):
- range(k) with k <= 0 is empty, so no special case for m > n.
- Built-in: haystack.find(needle) returns -1 if absent (.index raises).
- haystack[i:i+m] == needle is a one-line window compare (but copies).
"""
