"""
0973. K Closest Points to Origin  |  Medium  |  Heap / Priority Queue
Link: https://leetcode.com/problems/k-closest-points-to-origin/

Problem: Return the k points closest to (0,0). Any order.

Examples (printed sorted):
  [[1,3],[-2,2]],          k 1  -> [[-2,2]]
  [[3,3],[5,-1],[-2,4]],   k 2  -> [[-2,4],[3,3]]
  [[0,1],[1,0]],           k 2  -> [[0,1],[1,0]]

Approaches:
  1. Sort by distance         O(n log n) time, O(n) space
  2. Max-heap of size k  ⭐    O(n log k) time, O(k) space   <- go-to
"""

import heapq


# ---------- Approach 1: Sort by Distance ----------
def k_closest_sort(points: list[list[int]], k: int) -> list[list[int]]:
    return sorted(points, key=lambda p: p[0] ** 2 + p[1] ** 2)[:k]


# ---------- Approach 2: Max-Heap of Size k ⭐ ----------
def k_closest(points: list[list[int]], k: int) -> list[list[int]]:
    h: list[tuple[int, int]] = []  # (-distance^2, index): negated for a max-heap
    for i, (x, y) in enumerate(points):
        heapq.heappush(h, (-(x * x + y * y), i))
        if len(h) > k:
            heapq.heappop(h)  # evict the farthest of the current k
    return [points[i] for _, i in h]


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([[1, 3], [-2, 2]], 1), ([[3, 3], [5, -1], [-2, 4]], 2), ([[0, 1], [1, 0]], 2)]
    for pts, k in tests:
        print("sort:", sorted(k_closest_sort(pts, k)))  # any order is accepted
        print("heap:", sorted(k_closest(pts, k)))
        print("---")

"""
Syntax notes (Python):
- sorted(..., key=f) sorts by a computed key.
- Library one-liner: heapq.nsmallest(k, points, key=lambda p: p[0]**2 + p[1]**2).
- Store an index in the heap tuple so ties never compare lists.
"""
