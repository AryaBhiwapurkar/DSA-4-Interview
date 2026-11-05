"""
1851. Minimum Interval to Include Each Query  |  Hard  |  Intervals
Link: https://leetcode.com/problems/minimum-interval-to-include-each-query/

Problem: For each query q, return the size (right - left + 1) of the smallest
         interval with left <= q <= right, or -1 if none contains q.

Examples:
  [[1,4],[2,4],[3,6],[4,4]], [2,3,4,5]       -> [3,3,1,4]
  [[2,3],[2,5],[1,8],[20,25]], [2,19,5,22]   -> [2,-1,4,6]
  [[1,1]], [1,2]                             -> [1,-1]
  [[5,10]], [1,5,10,11]                      -> [-1,6,6,-1]

Approaches:
  1. Brute force: scan all intervals per query        O(n*q) time, O(1) extra
  2. Offline: sorted queries + min-heap by size  ⭐    O((n+q) log(n+q)) time, O(n+q) space   <- go-to
"""

import heapq


# ---------- Approach 1: Brute Force ----------
def min_interval_brute(intervals: list[list[int]], queries: list[int]) -> list[int]:
    res = []
    for q in queries:
        best = min((r - l + 1 for l, r in intervals if l <= q <= r), default=-1)
        res.append(best)
    return res


# ---------- Approach 2: Sorted Queries + Min-heap ⭐ ----------
def min_interval(intervals: list[list[int]], queries: list[int]) -> list[int]:
    intervals = sorted(intervals)  # by left end
    res = [-1] * len(queries)
    heap: list[tuple[int, int]] = []  # (size, right end)
    i = 0
    for q, idx in sorted((q, idx) for idx, q in enumerate(queries)):  # answer in sorted order
        while i < len(intervals) and intervals[i][0] <= q:  # every interval starting by q
            l, r = intervals[i]
            heapq.heappush(heap, (r - l + 1, r))
            i += 1
        while heap and heap[0][1] < q:  # ended before q: useless for this and later queries
            heapq.heappop(heap)
        if heap:
            res[idx] = heap[0][0]
    return res


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        ([[1, 4], [2, 4], [3, 6], [4, 4]], [2, 3, 4, 5]),
        ([[2, 3], [2, 5], [1, 8], [20, 25]], [2, 19, 5, 22]),
        ([[1, 1]], [1, 2]),
        ([[5, 10]], [1, 5, 10, 11]),
    ]
    for intervals, queries in tests:
        print("brute:", min_interval_brute(intervals, queries))
        print("heap :", min_interval(intervals, queries))
        print("---")

"""
Syntax notes (Python):
- Sorting (query, original_index) pairs answers offline and writes back by index.
- heapq orders tuples by the first item (size), then the second.
- min(generator, default=-1) covers "no interval contains q".
"""
