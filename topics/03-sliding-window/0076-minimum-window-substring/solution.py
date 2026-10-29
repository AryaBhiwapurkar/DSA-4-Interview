"""
0076. Minimum Window Substring  |  Hard  |  Sliding Window
Link: https://leetcode.com/problems/minimum-window-substring/

Problem: Return the shortest substring of s containing every character
         of t (with multiplicity), or "" if none exists.

Examples:
  s="ADOBECODEBANC", t="ABC"  -> "BANC"
  s="a", t="a"                -> "a"
  s="a", t="aa"               -> ""
  s="aAbB", t="AB"            -> "AbB"

Approaches:
  1. Brute force                         O(|s|^2 * σ) time, O(σ) space
  2. Window, compare full counts         O(σ * |s|) time, O(σ) space
  3. Window with have/need  ⭐            O(|s| + |t|) time, O(σ) space   <- go-to
"""

from collections import Counter


def covers(win: Counter, tc: Counter) -> bool:
    return all(win[c] >= k for c, k in tc.items())


# ---------- Approach 1: Brute Force ----------
def min_window_brute(s: str, t: str) -> str:
    tc = Counter(t)
    best = (float("inf"), 0)
    for i in range(len(s)):
        win: Counter = Counter()
        for j in range(i, len(s)):
            win[s[j]] += 1
            if covers(win, tc):
                best = min(best, (j - i + 1, i))
                break  # longer windows from i can't be shorter
    length, start = best
    return "" if length == float("inf") else s[start : start + int(length)]


# ---------- Approach 2: Window, Compare Full Counts ----------
def min_window_compare(s: str, t: str) -> str:
    tc, win = Counter(t), Counter()
    l, best = 0, (float("inf"), 0)
    for r, c in enumerate(s):
        win[c] += 1
        while covers(win, tc):  # O(σ) validity check
            best = min(best, (r - l + 1, l))
            win[s[l]] -= 1
            l += 1
    length, start = best
    return "" if length == float("inf") else s[start : start + int(length)]


# ---------- Approach 3: Window With have/need ⭐ ----------
def min_window(s: str, t: str) -> str:
    tc = Counter(t)
    win: dict[str, int] = {}
    need, have = len(tc), 0  # distinct chars to satisfy
    l, best_len, best_l = 0, float("inf"), 0
    for r, c in enumerate(s):
        win[c] = win.get(c, 0) + 1
        if c in tc and win[c] == tc[c]:  # c just became satisfied
            have += 1
        while have == need:
            if r - l + 1 < best_len:
                best_len, best_l = r - l + 1, l
            d = s[l]
            if d in tc and win[d] == tc[d]:  # d is about to drop below its requirement
                have -= 1
            win[d] -= 1
            l += 1
    return "" if best_len == float("inf") else s[best_l : best_l + int(best_len)]  # slice once at the end


# ---------- Driver ----------
if __name__ == "__main__":
    for s, t in [("ADOBECODEBANC", "ABC"), ("a", "a"), ("a", "aa"), ("aAbB", "AB")]:
        print(f'brute   : "{min_window_brute(s, t)}"')
        print(f'compare : "{min_window_compare(s, t)}"')
        print(f'have/need: "{min_window(s, t)}"')
        print("---")

"""
Syntax notes (Python):
- Counter returns 0 for missing keys (no KeyError), handy for window counts.
- Tuples compare lexicographically: min((len, start), ...) keeps the shortest, then earliest.
- len(Counter(t)) is the number of distinct characters in t.
"""
