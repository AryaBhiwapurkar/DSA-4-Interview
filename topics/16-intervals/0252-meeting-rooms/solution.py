"""
0252. Meeting Rooms  |  Easy  |  Intervals
Link: https://leetcode.com/problems/meeting-rooms/  (LC Premium)

Problem: Given meeting [start, end) times, can one person attend all of them?

Examples:
  [[0,30],[5,10],[15,20]]   -> false
  [[7,10],[2,4]]            -> true
  [[1,2],[2,3]]             -> true   (end == next start is fine)
  []                        -> true
  [[5,8],[6,8]]             -> false

Approaches:
  1. Check every pair             O(n^2) time, O(1) space
  2. Sort by start, compare neighbours  ⭐   O(n log n) time, O(1) extra   <- go-to
"""


# ---------- Approach 1: Every Pair ----------
def can_attend_meetings_brute(intervals: list[list[int]]) -> bool:
    for i in range(len(intervals)):
        for j in range(i + 1, len(intervals)):
            a, b = intervals[i], intervals[j]
            if a[0] < b[1] and b[0] < a[1]:  # strict: touching is allowed
                return False
    return True


# ---------- Approach 2: Sort + Neighbours ⭐ ----------
def can_attend_meetings(intervals: list[list[int]]) -> bool:
    intervals = sorted(intervals)
    for prev, cur in zip(intervals, intervals[1:]):
        if cur[0] < prev[1]:  # next starts before this one ends
            return False
    return True


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[[0, 30], [5, 10], [15, 20]], [[7, 10], [2, 4]], [[1, 2], [2, 3]], [], [[5, 8], [6, 8]]]:
        print("brute:", str(can_attend_meetings_brute(t)).lower())
        print("sort :", str(can_attend_meetings(t)).lower())
        print("---")

"""
Syntax notes (Python):
- zip(a, a[1:]) walks adjacent pairs; it yields nothing for 0 or 1 items.
- sorted() returns a new list, so the caller's list keeps its order.
- Two intervals overlap iff each starts before the other ends.
"""
