"""
0214. Shortest Palindrome  |  Hard  |  Arrays & Hashing
Link: https://leetcode.com/problems/shortest-palindrome/

Problem: Add characters only in front of s to make the shortest possible palindrome.

Examples:
  "aacecaaa"  -> "aaacecaaa"
  "abcd"      -> "dcbabcd"
  ""          -> ""
  "aba"       -> "aba"
  "aaaab"     -> "baaaab"

Approaches:
  1. Check prefixes from longest           O(n^2) time, O(n) space
  2. KMP on s + '#' + reverse(s)  ⭐       O(n) time, O(n) space   <- go-to
"""


# ---------- Approach 1: Check Prefixes ----------
def shortest_palindrome_brute(s: str) -> str:
    k = len(s)
    while k > 0 and s[:k] != s[:k][::-1]:  # longest palindromic prefix
        k -= 1
    return s[k:][::-1] + s


# ---------- Approach 2: KMP ⭐ ----------
def shortest_palindrome(s: str) -> str:
    rev = s[::-1]
    t = s + "#" + rev  # '#' stops matches crossing the middle
    lps = [0] * len(t)
    k = 0
    for i in range(1, len(t)):
        while k > 0 and t[i] != t[k]:
            k = lps[k - 1]
        if t[i] == t[k]:
            k += 1
        lps[i] = k
    k = lps[-1]  # longest palindromic prefix length
    return rev[:len(s) - k] + s  # rev's first n-k chars = reverse(s[k:])


# ---------- Driver ----------
if __name__ == "__main__":
    for s in ["aacecaaa", "abcd", "", "aba", "aaaab"]:
        print(f'brute: "{shortest_palindrome_brute(s)}"')
        print(f'kmp  : "{shortest_palindrome(s)}"')
        print("---")

"""
Syntax notes (Python):
- s[::-1] reverses; s[k:][::-1] reverses the suffix from k.
- lps[-1] reads the last entry.
- Mixing quote styles (f'..."..."...') prints quotes without escaping.
"""
