"""
0003. Longest Substring Without Repeating Characters  |  Medium  |  Sliding Window
Link: https://leetcode.com/problems/longest-substring-without-repeating-characters/

Problem: Return the length of the longest substring with all-distinct
         characters.

Examples:
  "abcabcbb"  -> 3
  "bbbbb"     -> 1
  "pwwkew"    -> 3
  ""          -> 0
  "abba"      -> 2

Approaches:
  1. Brute force                   O(n^2) time, O(alphabet) space
  2. Window + set  ⭐               O(n) time, O(min(n, alphabet)) space   <- go-to
  3. Window + last-seen index      O(n) time, O(alphabet) space
"""


# ---------- Approach 1: Brute Force ----------
def length_of_longest_substring_brute(s: str) -> int:
    best = 0
    for i in range(len(s)):
        seen: set[str] = set()
        for j in range(i, len(s)):
            if s[j] in seen:
                break
            seen.add(s[j])
            best = max(best, j - i + 1)
    return best


# ---------- Approach 2: Window + Set ⭐ ----------
def length_of_longest_substring(s: str) -> int:
    window: set[str] = set()
    l = best = 0
    for r, c in enumerate(s):
        while c in window:  # shrink until c is no longer inside
            window.remove(s[l])
            l += 1
        window.add(c)
        best = max(best, r - l + 1)  # window is valid here
    return best


# ---------- Approach 3: Window + Last-Seen Index ----------
def length_of_longest_substring_jump(s: str) -> int:
    last: dict[str, int] = {}
    l = best = 0
    for r, c in enumerate(s):
        if c in last:
            l = max(l, last[c] + 1)  # max: never move l backwards ("abba")
        last[c] = r
        best = max(best, r - l + 1)
    return best


# ---------- Driver ----------
if __name__ == "__main__":
    for s in ["abcabcbb", "bbbbb", "pwwkew", "", "abba"]:
        print("brute:", length_of_longest_substring_brute(s))
        print("set  :", length_of_longest_substring(s))
        print("jump :", length_of_longest_substring_jump(s))
        print("---")

"""
Syntax notes (Python):
- enumerate(s) yields (index, char) for the right edge.
- l = best = 0 initializes two counters at once.
- set.remove raises if missing; here the shrink loop guarantees presence.
"""
