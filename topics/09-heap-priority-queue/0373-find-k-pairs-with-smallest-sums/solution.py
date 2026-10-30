"""
0373. Find K Pairs with Smallest Sums  |  Medium  |  Heap / Priority Queue
Link: https://leetcode.com/problems/find-k-pairs-with-smallest-sums/

Problem: Two ascending arrays; return the k pairs (u, v) with the
         smallest sums u + v.

Examples:
  [1,7,11], [2,4,6], k 3   -> [[1,2],[1,4],[1,6]]
  [1,1,2],  [1,2,3], k 2   -> [[1,1],[1,1]]
  [1,2],    [3],     k 3   -> [[1,3],[2,3]]   (k > number of pairs)

Approaches:
  1. All pairs, sort           O(m*n log(m*n)) time, O(m*n) space
  2. Min-heap frontier  ⭐      O(k log k) time, O(k) space   <- go-to
"""

import heapq


# ---------- Approach 1: All Pairs, Sort ----------
def k_smallest_pairs_brute(a: list[int], b: list[int], k: int) -> list[list[int]]:
    allp = sorted((a[i] + b[j], i, j) for i in range(len(a)) for j in range(len(b)))  # ties by index
    return [[a[i], b[j]] for _, i, j in allp[:k]]


# ---------- Approach 2: Min-Heap Frontier ⭐ ----------
def k_smallest_pairs(a: list[int], b: list[int], k: int) -> list[list[int]]:
    h = [(a[i] + b[0], i, 0) for i in range(min(k, len(a)))]  # head of each row
    heapq.heapify(h)
    res: list[list[int]] = []
    while h and len(res) < k:
        _, i, j = heapq.heappop(h)
        res.append([a[i], b[j]])
        if j + 1 < len(b):  # move right in row i
            heapq.heappush(h, (a[i] + b[j + 1], i, j + 1))
    return res


# ---------- Driver ----------
if __name__ == "__main__":
    for a, b, k in [([1, 7, 11], [2, 4, 6], 3), ([1, 1, 2], [1, 2, 3], 2), ([1, 2], [3], 3)]:
        print("brute:", k_smallest_pairs_brute(a, b, k))
        print("heap :", k_smallest_pairs(a, b, k))
        print("---")

"""
Syntax notes (Python):
- Tuples (sum, i, j) order the heap by sum, then indices: deterministic ties.
- heapq.heapify on a pre-built list is O(len).
"""
