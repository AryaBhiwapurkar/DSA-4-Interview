"""
0084. Largest Rectangle in Histogram  |  Hard  |  Stack
Link: https://leetcode.com/problems/largest-rectangle-in-histogram/

Problem: Bars of width 1 with given heights. Return the area of the
         largest rectangle that fits inside the histogram.

Examples:
  [2,1,5,6,2,3]  -> 10
  [2,4]          -> 4
  [5]            -> 5
  [1,2,3,4,5]    -> 9
  [2,2,2]        -> 6
  [2,0,2]        -> 2

Approaches:
  1. Brute force, running min     O(n^2) time, O(1) space
  2. Monotonic increasing stack ⭐ O(n) time, O(n) space   <- go-to
"""


# ---------- Approach 1: Brute Force, Running Min ----------
def largest_rectangle_area_brute(h: list[int]) -> int:
    best = 0
    for i in range(len(h)):
        mn = h[i]
        for j in range(i, len(h)):
            mn = min(mn, h[j])  # shortest bar in [i, j] limits the height
            best = max(best, mn * (j - i + 1))
    return best


# ---------- Approach 2: Monotonic Increasing Stack ⭐ ----------
def largest_rectangle_area(h: list[int]) -> int:
    best = 0
    st: list[int] = []  # indices, heights increasing
    for i in range(len(h) + 1):
        cur = 0 if i == len(h) else h[i]  # sentinel 0 flushes the stack; input untouched
        while st and h[st[-1]] >= cur:
            height = h[st.pop()]
            left = st[-1] if st else -1  # previous smaller (NEW top)
            best = max(best, height * (i - left - 1))  # i is the next smaller
        st.append(i)
    return best


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [[2, 1, 5, 6, 2, 3], [2, 4], [5], [1, 2, 3, 4, 5], [2, 2, 2], [2, 0, 2]]
    for h in tests:
        print("brute:", largest_rectangle_area_brute(h))
        print("stack:", largest_rectangle_area(h))
        print("---")

"""
Syntax notes (Python):
- h[st.pop()] pops an index and reads its height in one expression.
- range(len(h) + 1) visits one extra position for the sentinel.
- `st[-1] if st else -1` guards the empty-stack case inline.
"""
