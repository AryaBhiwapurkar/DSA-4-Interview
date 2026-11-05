"""
0763. Partition Labels  |  Medium  |  Greedy
Link: https://leetcode.com/problems/partition-labels/

Problem: Cut s into as many pieces as possible so that each letter appears
         in only one piece. Return the piece sizes.

Examples:
  "ababcbacadefegdehijhklij"   -> [9,7,8]
  "eccbbbbdec"                 -> [10]
  "a"                          -> [1]
  "abc"                        -> [1,1,1]
  "abac"                       -> [3,1]

Approaches:
  1. Merge letter intervals [first, last]       O(n) time, O(1) space (26 letters)
  2. Last occurrence + running window end  ⭐    O(n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Merge Intervals ----------
def partition_labels_intervals(s: str) -> list[int]:
    first: dict[str, int] = {}
    last: dict[str, int] = {}
    for i, ch in enumerate(s):
        first.setdefault(ch, i)
        last[ch] = i
    spans = sorted((first[c], last[c]) for c in first)  # one interval per letter
    sizes, start, end = [], spans[0][0], spans[0][1]
    for a, b in spans[1:]:
        if a > end:  # gap: close the current piece
            sizes.append(end - start + 1)
            start, end = a, b
        else:
            end = max(end, b)
    sizes.append(end - start + 1)
    return sizes


# ---------- Approach 2: Last Occurrence ⭐ ----------
def partition_labels(s: str) -> list[int]:
    last = {ch: i for i, ch in enumerate(s)}  # later indices overwrite earlier ones
    sizes, start, end = [], 0, 0
    for i, ch in enumerate(s):
        end = max(end, last[ch])  # the piece must reach this letter's last copy
        if i == end:  # everything inside closes here
            sizes.append(end - start + 1)
            start = i + 1
    return sizes


# ---------- Driver ----------
if __name__ == "__main__":
    for s in ["ababcbacadefegdehijhklij", "eccbbbbdec", "a", "abc", "abac"]:
        print("intervals:", partition_labels_intervals(s))
        print("last     :", partition_labels(s))
        print("---")

"""
Syntax notes (Python):
- {ch: i for i, ch in enumerate(s)} keeps the LAST index, since later keys overwrite.
- dict.setdefault(k, v) stores v only if k is new (first occurrence).
- Sorting tuples orders by the first element, then the second.
"""
