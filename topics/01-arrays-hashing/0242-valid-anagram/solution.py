"""
0242. Valid Anagram  |  Easy  |  Arrays & Hashing
Link: https://leetcode.com/problems/valid-anagram/

Problem: Return true if t uses exactly the same letters as s with
         the same counts (t is a rearrangement of s).

Examples:
  s="anagram", t="nagaram"  -> True
  s="rat",     t="car"      -> False
  s="ab",      t="a"        -> False

Approaches:
  1. Sort both          O(n log n) time, O(n) space
  2. Count array  ⭐     O(n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Sort Both ----------
def is_anagram_sorted(s: str, t: str) -> bool:
    return sorted(s) == sorted(t)


# ---------- Approach 2: Count Array ⭐ ----------
def is_anagram(s: str, t: str) -> bool:
    if len(s) != len(t):
        return False
    cnt = [0] * 26
    for a, b in zip(s, t):
        cnt[ord(a) - ord("a")] += 1
        cnt[ord(b) - ord("a")] -= 1
    return all(c == 0 for c in cnt)


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [("anagram", "nagaram"), ("rat", "car"), ("ab", "a")]
    for s, t in tests:
        print("sorted:", is_anagram_sorted(s, t))
        print("count :", is_anagram(s, t))
        print("---")

"""
Syntax notes (Python):
- ord(c) - ord("a") maps 'a'..'z' to 0..25.
- zip(a, b) pairs elements and stops at the shorter input.
- Counter(s) == Counter(t) is the idiomatic one-liner (works for Unicode).
- sorted(str) returns a list of characters.
"""
