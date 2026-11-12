"""
0316. Remove Duplicate Letters  |  Medium  |  Stack
Link: https://leetcode.com/problems/remove-duplicate-letters/

Problem: Keep each letter exactly once, preserving order, so the result is lexicographically smallest.

Examples:
  "bcabc"     -> "abc"
  "cbacdcbc"  -> "acdb"
  "aabbcc"    -> "abc"
  "zyx"       -> "zyx"
  "abacb"     -> "abc"

Approaches:
  1. Recursive smallest-first choice     O(26 * n) time
  2. Greedy stack  ⭐                    O(n) time, O(1) space   <- go-to
"""

from collections import Counter


# ---------- Approach 1: Recursive Choice ----------
def remove_duplicate_letters_rec(s: str) -> str:
    if not s:
        return ""
    cnt = Counter(s)
    pos = 0  # first index of the chosen letter
    for i, c in enumerate(s):
        if c < s[pos]:
            pos = i
        cnt[c] -= 1
        if cnt[c] == 0:
            break  # c never appears again: must choose by here
    c = s[pos]
    return c + remove_duplicate_letters_rec(s[pos + 1:].replace(c, ""))


# ---------- Approach 2: Greedy Stack ⭐ ----------
def remove_duplicate_letters(s: str) -> str:
    last = {c: i for i, c in enumerate(s)}
    used: set[str] = set()
    st: list[str] = []
    for i, c in enumerate(s):
        if c in used:
            continue  # an earlier copy is already placed
        while st and st[-1] > c and last[st[-1]] > i:
            used.discard(st.pop())  # it recurs later, so it can come back
        st.append(c)
        used.add(c)
    return "".join(st)


# ---------- Driver ----------
if __name__ == "__main__":
    for s in ["bcabc", "cbacdcbc", "aabbcc", "zyx", "abacb"]:
        print(f'recursive: "{remove_duplicate_letters_rec(s)}"')
        print(f'stack    : "{remove_duplicate_letters(s)}"')
        print("---")

"""
Syntax notes (Python):
- {c: i for i, c in enumerate(s)} keeps the LAST index (later keys overwrite).
- set.discard(x) removes without raising if x is missing.
- str.replace(c, "") deletes every copy of c.
"""
