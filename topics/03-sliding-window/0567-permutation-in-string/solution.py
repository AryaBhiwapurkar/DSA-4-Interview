"""
0567. Permutation in String  |  Medium  |  Sliding Window
Link: https://leetcode.com/problems/permutation-in-string/

Problem: Return true if some permutation of s1 is a substring of s2.

Examples:
  s1="ab",  s2="eidbaooo"  -> True
  s1="ab",  s2="eidboaoo"  -> False
  s1="abc", s2="ab"        -> False
  s1="adc", s2="dcda"      -> True

Approaches:
  1. Sort every window            O(n * m log m) time, O(m) space
  2. Fixed window + counts  ⭐     O(26 * n) time, O(1) space   <- go-to
  3. Window + matches counter     O(n) time, O(1) space
"""


def idx(c: str) -> int:
    return ord(c) - ord("a")


# ---------- Approach 1: Sort Every Window ----------
def check_inclusion_sort(s1: str, s2: str) -> bool:
    m, target = len(s1), sorted(s1)
    return any(sorted(s2[i : i + m]) == target for i in range(len(s2) - m + 1))


# ---------- Approach 2: Fixed Window + Count Arrays ⭐ ----------
def check_inclusion(s1: str, s2: str) -> bool:
    m, n = len(s1), len(s2)
    if m > n:
        return False
    need, win = [0] * 26, [0] * 26
    for i in range(m):
        need[idx(s1[i])] += 1
        win[idx(s2[i])] += 1
    if need == win:  # first window
        return True
    for r in range(m, n):
        win[idx(s2[r])] += 1  # char entering
        win[idx(s2[r - m])] -= 1  # char leaving
        if need == win:
            return True
    return False


# ---------- Approach 3: Window + Matches Counter ----------
def check_inclusion_matches(s1: str, s2: str) -> bool:
    m, n = len(s1), len(s2)
    if m > n:
        return False
    need, win = [0] * 26, [0] * 26
    for i in range(m):
        need[idx(s1[i])] += 1
        win[idx(s2[i])] += 1
    matches = sum(a == b for a, b in zip(need, win))  # letters whose counts agree

    def update(c: int, delta: int) -> None:
        nonlocal matches
        if win[c] == need[c]:  # was equal, about to change
            matches -= 1
        win[c] += delta
        if win[c] == need[c]:  # equal after the change
            matches += 1

    for r in range(m, n):
        if matches == 26:
            return True
        update(idx(s2[r]), 1)
        update(idx(s2[r - m]), -1)
    return matches == 26


# ---------- Driver ----------
if __name__ == "__main__":
    for s1, s2 in [("ab", "eidbaooo"), ("ab", "eidboaoo"), ("abc", "ab"), ("adc", "dcda")]:
        print("sort   :", check_inclusion_sort(s1, s2))
        print("counts :", check_inclusion(s1, s2))
        print("matches:", check_inclusion_matches(s1, s2))
        print("---")

"""
Syntax notes (Python):
- Lists compare element-wise with ==.
- nonlocal lets a nested function rebind a variable from the enclosing scope.
- range(len(s2) - m + 1) is empty when m > len(s2).
"""
