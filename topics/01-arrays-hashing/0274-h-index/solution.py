"""
0274. H-Index  |  Medium  |  Arrays & Hashing
Link: https://leetcode.com/problems/h-index/

Problem: Return the largest h such that at least h papers have at least
         h citations each.

Examples:
  [3,0,6,1,5]  -> 3
  [1,3,1]      -> 1
  [0,0]        -> 0
  [100]        -> 1

Approaches:
  1. Try every h          O(n^2) time, O(1) space
  2. Sort descending      O(n log n) time, O(n) space (sorted copy)
  3. Counting buckets  ⭐  O(n) time, O(n) space   <- go-to
"""


# ---------- Approach 1: Try Every h ----------
def h_index_brute(citations: list[int]) -> int:
    for h in range(len(citations), -1, -1):
        if sum(c >= h for c in citations) >= h:
            return h
    return 0


# ---------- Approach 2: Sort Descending ----------
def h_index_sorted(citations: list[int]) -> int:
    c = sorted(citations, reverse=True)
    h = 0
    while h < len(c) and c[h] >= h + 1:  # (h+1)-th best paper has >= h+1 citations
        h += 1
    return h


# ---------- Approach 3: Counting Buckets ⭐ ----------
def h_index(citations: list[int]) -> int:
    n = len(citations)
    bucket = [0] * (n + 1)
    for c in citations:
        bucket[min(c, n)] += 1  # h <= n, so cap at n
    total = 0  # papers with >= h citations
    for h in range(n, -1, -1):
        total += bucket[h]
        if total >= h:
            return h
    return 0


# ---------- Driver ----------
if __name__ == "__main__":
    for c in [[3, 0, 6, 1, 5], [1, 3, 1], [0, 0], [100]]:
        print("brute :", h_index_brute(c))
        print("sorted:", h_index_sorted(c))
        print("bucket:", h_index(c))
        print("---")

"""
Syntax notes (Python):
- sum(bool_generator) counts Trues (True == 1).
- sorted(x, reverse=True) sorts descending into a new list.
- range(n, -1, -1) runs n, n-1, ..., 0.
"""
