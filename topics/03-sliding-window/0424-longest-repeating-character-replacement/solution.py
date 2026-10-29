"""
0424. Longest Repeating Character Replacement  |  Medium  |  Sliding Window
Link: https://leetcode.com/problems/longest-repeating-character-replacement/

Problem: Uppercase string, at most k character changes; return the
         longest substring that can become one repeated letter.

Examples:
  "ABAB", k=2       -> 4
  "AABABBA", k=1    -> 4
  "AAAA", k=0       -> 4
  "ABCDE", k=1      -> 2

Approaches:
  1. Brute force                   O(n^2) time, O(26) space
  2. Per-letter window             O(26*n) time, O(1) space
  3. Window + max frequency  ⭐     O(n) time, O(26) space   <- go-to
"""

from string import ascii_uppercase


# ---------- Approach 1: Brute Force ----------
def character_replacement_brute(s: str, k: int) -> int:
    best = 0
    for i in range(len(s)):
        cnt = [0] * 26
        maxf = 0
        for j in range(i, len(s)):
            cnt[ord(s[j]) - ord("A")] += 1
            maxf = max(maxf, cnt[ord(s[j]) - ord("A")])
            if (j - i + 1) - maxf > k:  # needs more than k changes
                break
            best = max(best, j - i + 1)
    return best


# ---------- Approach 2: Per-Letter Window ----------
def character_replacement_per_letter(s: str, k: int) -> int:
    best = 0
    for c in ascii_uppercase:
        l = others = 0  # chars in window that aren't c
        for r, x in enumerate(s):
            others += x != c
            while others > k:
                others -= s[l] != c
                l += 1
            best = max(best, r - l + 1)
    return best


# ---------- Approach 3: Window + Max Frequency ⭐ ----------
def character_replacement(s: str, k: int) -> int:
    cnt = [0] * 26
    l = maxf = best = 0
    for r, x in enumerate(s):
        cnt[ord(x) - ord("A")] += 1
        maxf = max(maxf, cnt[ord(x) - ord("A")])
        if (r - l + 1) - maxf > k:  # slide, don't shrink: maxf may be stale, that's fine
            cnt[ord(s[l]) - ord("A")] -= 1
            l += 1
        best = max(best, r - l + 1)
    return best


# ---------- Driver ----------
if __name__ == "__main__":
    for s, k in [("ABAB", 2), ("AABABBA", 1), ("AAAA", 0), ("ABCDE", 1)]:
        print("brute     :", character_replacement_brute(s, k))
        print("per-letter:", character_replacement_per_letter(s, k))
        print("maxfreq   :", character_replacement(s, k))
        print("---")

"""
Syntax notes (Python):
- Booleans are ints: `others += x != c` adds 1 when True.
- string.ascii_uppercase is "ABC...Z".
- l = maxf = best = 0 initializes several counters together.
"""
