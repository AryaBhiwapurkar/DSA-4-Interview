"""
0392. Is Subsequence  |  Easy  |  Two Pointers
Link: https://leetcode.com/problems/is-subsequence/

Problem: Return true if s can be formed by deleting some characters of t
         without reordering the rest.

Examples:
  s="abc", t="ahbgdc"  -> True
  s="axc", t="ahbgdc"  -> False
  s="",    t="abc"     -> True
  s="aa",  t="a"       -> False

Approaches:
  1. Two pointers  ⭐                 O(|t|) time, O(1) space   <- go-to
  2. Index t + binary search         O(|s| log |t|) per query, O(|t|) space
"""

from bisect import bisect_right
from collections import defaultdict


# ---------- Approach 1: Two Pointers ⭐ ----------
def is_subsequence(s: str, t: str) -> bool:
    i = 0
    for c in t:
        if i < len(s) and c == s[i]:  # greedy: match as early as possible
            i += 1
    return i == len(s)


# ---------- Approach 2: Index t + Binary Search ----------
def is_subsequence_indexed(s: str, t: str) -> bool:
    pos: defaultdict[str, list[int]] = defaultdict(list)  # pos[c] = sorted indices of c in t
    for j, c in enumerate(t):
        pos[c].append(j)
    prev = -1
    for c in s:
        p = pos[c]
        k = bisect_right(p, prev)  # first index strictly after prev
        if k == len(p):
            return False
        prev = p[k]
    return True


# ---------- Driver ----------
if __name__ == "__main__":
    for s, t in [("abc", "ahbgdc"), ("axc", "ahbgdc"), ("", "abc"), ("aa", "a")]:
        print("pointers:", is_subsequence(s, t))
        print("indexed :", is_subsequence_indexed(s, t))
        print("---")

"""
Syntax notes (Python):
- bisect_right(a, x) returns the insertion point after any existing x (upper bound).
- bisect_left(a, x) is the lower bound.
- One-liner trick: it = iter(t); all(c in it for c in s) consumes t as it matches.
"""
