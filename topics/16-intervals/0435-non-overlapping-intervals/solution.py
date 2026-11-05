"""
0435. Non-overlapping Intervals  |  Medium  |  Intervals
Link: https://leetcode.com/problems/non-overlapping-intervals/

Problem: Fewest intervals to delete so the rest don't overlap (touching is OK).

Examples:
  [[1,2],[2,3],[3,4],[1,3]]   -> 1
  [[1,2],[1,2],[1,2]]         -> 2
  [[1,2],[2,3]]               -> 0
  [[1,100],[11,22],[1,11],[2,12]] -> 2
  [[0,2],[1,3],[2,4],[3,5],[4,6]] -> 2

Approaches:
  1. DP: longest chain of non-overlapping (sort by start)   O(n^2) time, O(n) space
  2. Sort by end, keep greedily  ⭐                           O(n log n) time, O(1) extra   <- go-to
"""


# ---------- Approach 1: DP ----------
def erase_overlap_intervals_dp(intervals: list[list[int]]) -> int:
    iv = sorted(intervals)
    n = len(iv)
    keep = [1] * n  # keep[i]: longest non-overlapping chain ending with iv[i]
    for i in range(n):
        for j in range(i):
            if iv[j][1] <= iv[i][0]:
                keep[i] = max(keep[i], keep[j] + 1)
    return n - max(keep)


# ---------- Approach 2: Greedy by End ⭐ ----------
def erase_overlap_intervals(intervals: list[list[int]]) -> int:
    removed, end = 0, float("-inf")
    for s, e in sorted(intervals, key=lambda iv: iv[1]):  # earliest end first
        if s >= end:  # fits after the last kept interval
            end = e
        else:  # overlaps: drop it (it ends later than the kept one)
            removed += 1
    return removed


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        [[1, 2], [2, 3], [3, 4], [1, 3]],
        [[1, 2], [1, 2], [1, 2]],
        [[1, 2], [2, 3]],
        [[1, 100], [11, 22], [1, 11], [2, 12]],
        [[0, 2], [1, 3], [2, 4], [3, 5], [4, 6]],
    ]
    for t in tests:
        print("dp    :", erase_overlap_intervals_dp(t))
        print("greedy:", erase_overlap_intervals(t))
        print("---")

"""
Syntax notes (Python):
- sorted(..., key=lambda iv: iv[1]) sorts by end time.
- float("-inf") as the initial end lets the first interval always fit.
- n - max(keep): removals = total minus the largest set you can keep.
"""
