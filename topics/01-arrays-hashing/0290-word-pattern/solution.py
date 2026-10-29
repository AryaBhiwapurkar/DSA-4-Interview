"""
0290. Word Pattern  |  Easy  |  Arrays & Hashing
Link: https://leetcode.com/problems/word-pattern/

Problem: Return true if the words in s follow the letter pattern with
         a one-to-one mapping between letters and words.

Examples:
  "abba", "dog cat cat dog"   -> True
  "abba", "dog cat cat fish"  -> False
  "aaaa", "dog cat cat dog"   -> False
  "abba", "dog dog dog dog"   -> False

Approaches:
  1. First-occurrence signature   O(n+m) time, O(n+m) space
  2. Two hashmaps  ⭐              O(n+m) time, O(k) space   <- go-to
"""


# ---------- Approach 1: First-Occurrence Signature ----------
def word_pattern_signature(pattern: str, s: str) -> bool:
    words = s.split()
    if len(words) != len(pattern):
        return False
    pf: dict[str, int] = {}
    wf: dict[str, int] = {}
    return all(pf.setdefault(c, i) == wf.setdefault(w, i) for i, (c, w) in enumerate(zip(pattern, words)))


# ---------- Approach 2: Two Hashmaps ⭐ ----------
def word_pattern(pattern: str, s: str) -> bool:
    words = s.split()
    if len(words) != len(pattern):
        return False
    pw: dict[str, str] = {}
    wp: dict[str, str] = {}
    for c, w in zip(pattern, words):
        if c not in pw and w not in wp:
            pw[c] = w
            wp[w] = c
        elif pw.get(c) != w or wp.get(w) != c:
            return False
    return True


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        ("abba", "dog cat cat dog"),
        ("abba", "dog cat cat fish"),
        ("aaaa", "dog cat cat dog"),
        ("abba", "dog dog dog dog"),
    ]
    for p, s in tests:
        print("signature:", word_pattern_signature(p, s))
        print("two maps :", word_pattern(p, s))
        print("---")

"""
Syntax notes (Python):
- s.split() with no argument splits on any run of whitespace.
- enumerate(zip(a, b)) yields (i, (x, y)); unpack with i, (x, y).
- all(...) short-circuits on the first False.
"""
