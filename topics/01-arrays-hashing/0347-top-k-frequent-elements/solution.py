"""
0347. Top K Frequent Elements  |  Medium  |  Arrays & Hashing
Link: https://leetcode.com/problems/top-k-frequent-elements/

Problem: Return the k most frequent values (any order; answer is unique).

Examples (printed sorted for stable output):
  [1,1,1,2,2,3], k=2             -> [1,2]
  [1], k=1                       -> [1]
  [1,2,1,2,1,2,3,1,3,2], k=2     -> [1,2]
  [4,4,-1,-1,-1,7], k=1          -> [-1]

Approaches:
  1. Sort by frequency     O(n log n) time, O(n) space
  2. Min-heap of size k    O(n log k) time, O(n) space
  3. Bucket sort  ⭐        O(n) time, O(n) space   <- go-to
"""

import heapq
from collections import Counter


# ---------- Approach 1: Sort by Frequency ----------
def top_k_frequent_sorted(nums: list[int], k: int) -> list[int]:
    cnt = Counter(nums)
    return sorted(cnt, key=lambda v: cnt[v], reverse=True)[:k]


# ---------- Approach 2: Min-Heap of Size k ----------
def top_k_frequent_heap(nums: list[int], k: int) -> list[int]:
    heap: list[tuple[int, int]] = []  # (count, value), min-heap
    for val, c in Counter(nums).items():
        heapq.heappush(heap, (c, val))
        if len(heap) > k:
            heapq.heappop(heap)  # evict the least frequent
    return [val for _, val in heap]


# ---------- Approach 3: Bucket Sort ⭐ ----------
def top_k_frequent(nums: list[int], k: int) -> list[int]:
    buckets: list[list[int]] = [[] for _ in range(len(nums) + 1)]  # index = frequency, max n
    for val, c in Counter(nums).items():
        buckets[c].append(val)
    res: list[int] = []
    for f in range(len(nums), 0, -1):
        for val in buckets[f]:
            res.append(val)
            if len(res) == k:
                return res
    return res


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([1, 1, 1, 2, 2, 3], 2), ([1], 1), ([1, 2, 1, 2, 1, 2, 3, 1, 3, 2], 2), ([4, 4, -1, -1, -1, 7], 1)]
    for nums, k in tests:
        print("sorted:", sorted(top_k_frequent_sorted(nums, k)))  # sorted: order is unspecified
        print("heap  :", sorted(top_k_frequent_heap(nums, k)))
        print("bucket:", sorted(top_k_frequent(nums, k)))
        print("---")

"""
Syntax notes (Python):
- Counter(nums).most_common(k) solves it in one call (uses a heap internally).
- heapq is a min-heap on lists; tuples compare element by element.
- [[] for _ in range(n)] makes n independent lists; [[]] * n would alias one list.
- range(n, 0, -1) counts down from n to 1.
"""
