"""
0056. Merge Intervals  |  Medium  |  Intervals
Link: https://leetcode.com/problems/merge-intervals/

Problem: Merge all overlapping intervals and return the result.

Examples:
  [[1,3],[2,6],[8,10],[15,18]]   -> [[1,6],[8,10],[15,18]]
  [[1,4],[4,5]]                  -> [[1,5]]
  [[4,7],[1,4]]                  -> [[1,7]]
  [[1,4],[2,3]]                  -> [[1,4]]   (one inside another)
  [[5,6]]                        -> [[5,6]]

Approaches:
  1. Repeatedly merge any overlapping pair   O(n^3) time, O(n) space
  2. Sort by start + one merge pass  ⭐       O(n log n) time, O(n) space   <- go-to
"""


# ---------- Approach 1: Repeated Pair Merging ----------
def merge_brute(intervals: list[list[int]]) -> list[list[int]]:
    res = [iv[:] for iv in intervals]
    merged = True
    while merged:  # keep going until no pair overlaps
        merged = False
        for i in range(len(res)):
            for j in range(i + 1, len(res)):
                a, b = res[i], res[j]
                if a[0] <= b[1] and b[0] <= a[1]:  # overlap (touching counts)
                    res[i] = [min(a[0], b[0]), max(a[1], b[1])]
                    res.pop(j)
                    merged = True
                    break
            if merged:
                break
    return sorted(res)


# ---------- Approach 2: Sort + Merge ⭐ ----------
def merge(intervals: list[list[int]]) -> list[list[int]]:
    res: list[list[int]] = []
    for start, end in sorted(intervals):  # by start
        if res and start <= res[-1][1]:  # overlaps the last merged interval
            res[-1][1] = max(res[-1][1], end)  # max: the new one may sit inside
        else:
            res.append([start, end])
    return res


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [[[1, 3], [2, 6], [8, 10], [15, 18]], [[1, 4], [4, 5]], [[4, 7], [1, 4]], [[1, 4], [2, 3]], [[5, 6]]]
    for t in tests:
        print("brute:", merge_brute(t))
        print("sort :", merge(t))
        print("---")

"""
Syntax notes (Python):
- sorted() on lists of lists compares element by element, so it sorts by start.
- `for start, end in ...` unpacks each 2-element interval.
- res[-1][1] edits the last merged interval in place.
"""
