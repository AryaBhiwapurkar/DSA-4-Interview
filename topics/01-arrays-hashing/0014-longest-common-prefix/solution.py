"""
0014. Longest Common Prefix  |  Easy  |  Arrays & Hashing
Link: https://leetcode.com/problems/longest-common-prefix/

Problem: Return the longest prefix shared by all strings, or "" if none.

Examples:
  ["flower","flow","flight"]  -> "fl"
  ["dog","racecar","car"]     -> ""
  ["ab","a"]                  -> "a"
  ["alone"]                   -> "alone"

Approaches:
  1. Horizontal scan         O(S) time, O(1) extra space
  2. Sort, first vs last     O(S log n) time, O(n) space (sorted copy)
  3. Vertical scan  ⭐        O(S) time, O(1) extra space   <- go-to
  (S = total number of characters)
"""


# ---------- Approach 1: Horizontal Scan ----------
def longest_common_prefix_horizontal(strs: list[str]) -> str:
    prefix = strs[0]
    for s in strs[1:]:
        while not s.startswith(prefix):
            prefix = prefix[:-1]
    return prefix


# ---------- Approach 2: Sort, Compare First and Last ----------
def longest_common_prefix_sorted(strs: list[str]) -> str:
    s = sorted(strs)
    a, b = s[0], s[-1]  # most different pair after sorting
    i = 0
    while i < min(len(a), len(b)) and a[i] == b[i]:
        i += 1
    return a[:i]


# ---------- Approach 3: Vertical Scan ⭐ ----------
def longest_common_prefix(strs: list[str]) -> str:
    first = strs[0]
    for i, c in enumerate(first):
        for s in strs[1:]:
            if i >= len(s) or s[i] != c:
                return first[:i]
    return first


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [["flower", "flow", "flight"], ["dog", "racecar", "car"], ["ab", "a"], ["alone"]]
    for strs in tests:
        print(f'horizontal: "{longest_common_prefix_horizontal(strs)}"')
        print(f'sorted    : "{longest_common_prefix_sorted(strs)}"')
        print(f'vertical  : "{longest_common_prefix(strs)}"')
        print("---")

"""
Syntax notes (Python):
- s.startswith(p) checks a prefix; "".startswith("") is True.
- s[:-1] drops the last char; s[:i] is the first i chars.
- Strings compare lexicographically, so sorted() works on them directly.
"""
