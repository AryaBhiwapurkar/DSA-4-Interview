"""
0275. H-Index II  |  Medium  |  Binary Search
Link: https://leetcode.com/problems/h-index-ii/

Problem: Citations are sorted ascending. Return the largest h such that
         h papers have >= h citations each, in O(log n).

Examples:
  [0,1,3,5,6]   -> 3
  [1,2,100]     -> 2
  [0]           -> 0
  [100]         -> 1
  [0,0,0]       -> 0
  [11,15]       -> 2
  [0,3,3]       -> 2

Approaches:
  1. Linear scan                   O(n) time, O(1) space
  2. Binary search on the index ⭐ O(log n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Linear Scan ----------
def h_index_linear(c: list[int]) -> int:
    n = len(c)
    for i, x in enumerate(c):
        if x >= n - i:  # n - i papers have >= x citations
            return n - i
    return 0


# ---------- Approach 2: Binary Search on the Index ⭐ ----------
def h_index(c: list[int]) -> int:
    n = len(c)
    lo, hi = 0, n  # hi = n means "no index works"
    while lo < hi:
        mid = (lo + hi) // 2
        if c[mid] >= n - mid:
            hi = mid
        else:
            lo = mid + 1
    return n - lo


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[0, 1, 3, 5, 6], [1, 2, 100], [0], [100], [0, 0, 0], [11, 15], [0, 3, 3]]:
        print("linear:", h_index_linear(t))
        print("binary:", h_index(t))
        print("---")

"""
Syntax notes (Python):
- enumerate gives (index, value) pairs.
- Searching [0, n] lets lo == n mean "predicate never true".
- bisect can't express this predicate directly (it mixes index and value);
  write the loop.
"""
