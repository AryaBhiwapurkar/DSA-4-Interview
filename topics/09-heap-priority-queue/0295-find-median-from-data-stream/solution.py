"""
0295. Find Median from Data Stream  |  Hard  |  Heap / Priority Queue
Link: https://leetcode.com/problems/find-median-from-data-stream/

Problem: addNum(num) and findMedian() over a stream of integers.

Examples:
  add 1, add 2, median, add 3, median
    -> [null,null,null,1.50000,null,2.00000]
  add -1, median, add -2, median, add -3, median, add -4, median, add -5, median
    -> [null,null,-1.00000,null,-1.50000,null,-2.00000,null,-2.50000,null,-3.00000]

Approaches:
  1. Sorted list with insertion   O(n) add, O(1) median, O(n) space
  2. Two heaps  ⭐                 O(log n) add, O(1) median, O(n) space   <- go-to
"""

import bisect
import heapq


# ---------- Approach 1: Sorted List With Insertion ----------
class MedianFinderSorted:
    def __init__(self) -> None:
        self.a: list[int] = []

    def addNum(self, num: int) -> None:
        bisect.insort(self.a, num)

    def findMedian(self) -> float:
        n = len(self.a)
        return float(self.a[n // 2]) if n % 2 else (self.a[n // 2 - 1] + self.a[n // 2]) / 2


# ---------- Approach 2: Two Heaps ⭐ ----------
class MedianFinder:
    def __init__(self) -> None:
        self.low: list[int] = []  # max-heap via negatives: smaller half
        self.high: list[int] = []  # min-heap: larger half

    def addNum(self, num: int) -> None:
        heapq.heappush(self.low, -num)  # 1) into the lower half
        heapq.heappush(self.high, -heapq.heappop(self.low))  # 2) its max moves up
        if len(self.high) > len(self.low):  # 3) rebalance: low keeps the extra one
            heapq.heappush(self.low, -heapq.heappop(self.high))

    def findMedian(self) -> float:
        if len(self.low) > len(self.high):
            return float(-self.low[0])
        return (-self.low[0] + self.high[0]) / 2


# ---------- Driver ----------
def run(cls: type, ops: list[str], args: list[int]) -> str:
    m = cls()
    out = ["null"]
    for op, a in zip(ops[1:], args[1:]):
        if op == "addNum":
            m.addNum(a)
            out.append("null")
        else:
            out.append(f"{m.findMedian():.5f}")
    return "[" + ",".join(out) + "]"


if __name__ == "__main__":
    tests = [
        (["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"], [0, 1, 2, 0, 3, 0]),
        (["MedianFinder", "addNum", "findMedian", "addNum", "findMedian", "addNum", "findMedian", "addNum",
          "findMedian", "addNum", "findMedian"], [0, -1, 0, -2, 0, -3, 0, -4, 0, -5, 0]),
    ]
    for ops, args in tests:
        print("sorted:", run(MedianFinderSorted, ops, args))
        print("heaps :", run(MedianFinder, ops, args))
        print("---")

"""
Syntax notes (Python):
- heapq only has a min-heap: the lower half stores negated values.
- heapq.heappushpop / heapreplace can merge steps 1 and 2 for speed.
"""
