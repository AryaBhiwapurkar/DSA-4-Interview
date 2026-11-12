"""
0340. Longest Substring with At Most K Distinct Characters  |  Medium  |  Sliding Window  |  LC Premium
Link: https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/

Problem: Length of the longest substring with at most k distinct characters.

Examples:
  s = "eceba",   k = 2  -> 3
  s = "aa",      k = 1  -> 2
  s = "abc",     k = 0  -> 0
  s = "abaccc",  k = 2  -> 4
  s = "a@a@b",   k = 2  -> 4    (non-letters allowed)

Approaches:
  1. Every start, extend              O(n^2) time, O(k) space
  2. Shrinking window + map  ⭐       O(n) time, O(k) space   <- go-to
"""

from collections import defaultdict


# ---------- Approach 1: Every Start ----------
def length_of_longest_substring_k_distinct_brute(s: str, k: int) -> int:
    best = 0
    for l in range(len(s)):
        seen: set[str] = set()
        for r in range(l, len(s)):
            seen.add(s[r])
            if len(seen) > k:
                break
            best = max(best, r - l + 1)
    return best


# ---------- Approach 2: Shrinking Window ⭐ ----------
def length_of_longest_substring_k_distinct(s: str, k: int) -> int:
    cnt: defaultdict[str, int] = defaultdict(int)
    l = best = 0
    for r, c in enumerate(s):
        cnt[c] += 1
        while len(cnt) > k:
            cnt[s[l]] -= 1
            if cnt[s[l]] == 0:
                del cnt[s[l]]  # keep len == distinct count
            l += 1
        best = max(best, r - l + 1)
    return best


# ---------- Driver ----------
if __name__ == "__main__":
    for s, k in [("eceba", 2), ("aa", 1), ("abc", 0), ("abaccc", 2), ("a@a@b", 2)]:
        print("brute :", length_of_longest_substring_k_distinct_brute(s, k))
        print("window:", length_of_longest_substring_k_distinct(s, k))
        print("---")

"""
Syntax notes (Python):
- del d[key] removes a key; len(d) is then the distinct count.
- defaultdict(int) starts missing keys at 0 for += 1.
- Reading cnt[s[l]] on a defaultdict would re-insert a deleted key; here it's always present.
"""
