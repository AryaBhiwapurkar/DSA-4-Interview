"""
0057. Insert Interval  |  Medium  |  Intervals
Link: https://leetcode.com/problems/insert-interval/

Problem: Insert newInterval into a sorted, non-overlapping list, merging as
         needed so the result stays sorted and non-overlapping.

Examples:
  [[1,3],[6,9]], [2,5]                        -> [[1,5],[6,9]]
  [[1,2],[3,5],[6,7],[8,10],[12,16]], [4,8]   -> [[1,2],[3,10],[12,16]]
  [], [5,7]                                   -> [[5,7]]
  [[1,5]], [6,8]                              -> [[1,5],[6,8]]
  [[3,5]], [1,2]                              -> [[1,2],[3,5]]

Approaches:
  1. Append + sort + merge (LC 56)       O(n log n) time, O(n) space
  2. Three phases: before, overlap, after  ⭐   O(n) time, O(n) space   <- go-to
"""


# ---------- Approach 1: Append + Sort + Merge ----------
def insert_sort(intervals: list[list[int]], new: list[int]) -> list[list[int]]:
    res: list[list[int]] = []
    for s, e in sorted(intervals + [new]):
        if res and s <= res[-1][1]:
            res[-1][1] = max(res[-1][1], e)
        else:
            res.append([s, e])
    return res


# ---------- Approach 2: Three Phases ⭐ ----------
def insert(intervals: list[list[int]], new: list[int]) -> list[list[int]]:
    res: list[list[int]] = []
    i, n = 0, len(intervals)
    s, e = new
    while i < n and intervals[i][1] < s:  # ends before new starts: untouched
        res.append(intervals[i])
        i += 1
    while i < n and intervals[i][0] <= e:  # overlaps: absorb into [s, e]
        s = min(s, intervals[i][0])
        e = max(e, intervals[i][1])
        i += 1
    res.append([s, e])
    res.extend(intervals[i:])  # starts after new ends: untouched
    return res


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        ([[1, 3], [6, 9]], [2, 5]),
        ([[1, 2], [3, 5], [6, 7], [8, 10], [12, 16]], [4, 8]),
        ([], [5, 7]),
        ([[1, 5]], [6, 8]),
        ([[3, 5]], [1, 2]),
    ]
    for intervals, new in tests:
        print("sort  :", insert_sort(intervals, new))
        print("phases:", insert(intervals, new))
        print("---")

"""
Syntax notes (Python):
- `s, e = new` unpacks the interval into two names.
- res.extend(intervals[i:]) appends the whole tail at once.
- intervals + [new] builds a new list; the input isn't modified.
"""
