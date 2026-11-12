"""
0680. Valid Palindrome II  |  Easy  |  Two Pointers
Link: https://leetcode.com/problems/valid-palindrome-ii/

Problem: Can s become a palindrome after deleting at most one character?

Examples:
  "aba"    -> True
  "abca"   -> True
  "abc"    -> False
  "deeee"  -> True    (only skipping the left works)
  "eeeed"  -> True    (only skipping the right works)
  "abcda"  -> False

Approaches:
  1. Try every deletion               O(n^2) time, O(n) space
  2. Two pointers + one branch  ⭐    O(n) time, O(1) space   <- go-to
"""


def is_pal(s: str, lo: int, hi: int) -> bool:
    while lo < hi:
        if s[lo] != s[hi]:
            return False
        lo, hi = lo + 1, hi - 1
    return True


# ---------- Approach 1: Try Every Deletion ----------
def valid_palindrome_brute(s: str) -> bool:
    if s == s[::-1]:
        return True
    return any((t := s[:i] + s[i + 1:]) == t[::-1] for i in range(len(s)))


# ---------- Approach 2: Two Pointers + One Branch ⭐ ----------
def valid_palindrome(s: str) -> bool:
    lo, hi = 0, len(s) - 1
    while lo < hi:
        if s[lo] != s[hi]:  # one of these two must be the deleted char
            return is_pal(s, lo + 1, hi) or is_pal(s, lo, hi - 1)
        lo, hi = lo + 1, hi - 1
    return True


# ---------- Driver ----------
if __name__ == "__main__":
    for s in ["aba", "abca", "abc", "deeee", "eeeed", "abcda"]:
        print("brute   :", valid_palindrome_brute(s))
        print("pointers:", valid_palindrome(s))
        print("---")

"""
Syntax notes (Python):
- The walrus (t := expr) binds a name inside a generator expression (3.8+).
- s[:i] + s[i + 1:] removes the character at i.
- `or` short-circuits like C++ ||.
"""
