"""
0703. Kth Largest Element in a Stream  |  Easy  |  Heap / Priority Queue
Link: https://leetcode.com/problems/kth-largest-element-in-a-stream/

Problem: KthLargest(k, nums); add(val) returns the k-th largest so far.

Examples:
  k 3, [4,5,8,2]; add 3, 5, 10, 9, 4      -> [null,4,5,5,8,8]
  k 4, [7,7,7,7,8,3]; add 2, 10, 9, 9     -> [null,7,7,7,8]
  k 1, []; add -3, -2, -4                 -> [null,-3,-2,-2]

Approaches:
  1. Sorted list with insertion   O(n) per add, O(n) space
  2. Min-heap of size k  ⭐        O(log k) per add, O(k) space   <- go-to
"""

import bisect
import heapq


# ---------- Approach 1: Sorted List With Insertion ----------
class KthLargestSorted:
    def __init__(self, k: int, nums: list[int]) -> None:
        self.k, self.a = k, sorted(nums)

    def add(self, val: int) -> int:
        bisect.insort(self.a, val)  # O(n) shift
        return self.a[-self.k]


# ---------- Approach 2: Min-Heap of Size k ⭐ ----------
class KthLargest:
    def __init__(self, k: int, nums: list[int]) -> None:
        self.k = k
        self.h: list[int] = []  # min-heap of the k largest
        for x in nums:
            self.add(x)

    def add(self, val: int) -> int:
        heapq.heappush(self.h, val)
        if len(self.h) > self.k:
            heapq.heappop(self.h)  # drop the smallest: it's not in the top k
        return self.h[0]  # smallest of the top k = k-th largest


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [(3, [4, 5, 8, 2], [3, 5, 10, 9, 4]), (4, [7, 7, 7, 7, 8, 3], [2, 10, 9, 9]), (1, [], [-3, -2, -4])]
    for k, nums, adds in tests:
        for label, cls in (("sorted", KthLargestSorted), ("heap  ", KthLargest)):
            obj = cls(k, nums)
            print(f"{label}:", "[" + ",".join(["null"] + [str(obj.add(v)) for v in adds]) + "]")
        print("---")

"""
Syntax notes (Python):
- heapq is a min-heap; h[0] is the smallest.
- heapq.heappushpop(h, x) pushes then pops in one call (faster than both).
- bisect.insort(a, x) inserts into a sorted list (O(n) because of shifting).
"""
