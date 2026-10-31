"""
1584. Min Cost to Connect All Points  |  Medium  |  Advanced Graphs
Link: https://leetcode.com/problems/min-cost-to-connect-all-points/

Problem: Points on a plane; connecting two costs their Manhattan distance.
         Return the minimum total cost so every point is connected.

Examples:
  [[0,0],[2,2],[3,10],[5,2],[7,0]]  -> 20
  [[3,12],[-2,5],[-4,1]]            -> 18
  [[0,0]]                           -> 0
  [[0,0],[1,1],[1,0],[-1,1]]        -> 4

Approaches:
  1. Kruskal (sort all edges + Union-Find)  O(n^2 log n) time, O(n^2) space
  2. Prim with a heap                       O(n^2 log n) time, O(n^2) space
  3. Prim with an array  ⭐                  O(n^2) time, O(n) space   <- go-to
"""

import heapq


def manhattan(a: list[int], b: list[int]) -> int:
    return abs(a[0] - b[0]) + abs(a[1] - b[1])


# ---------- Approach 1: Kruskal ----------
def min_cost_connect_points_kruskal(pts: list[list[int]]) -> int:
    n = len(pts)
    edges = sorted((manhattan(pts[i], pts[j]), i, j) for i in range(n) for j in range(i + 1, n))
    parent = list(range(n))

    def find(x: int) -> int:
        while parent[x] != x:
            parent[x] = parent[parent[x]]  # path halving
            x = parent[x]
        return x

    total = used = 0
    for w, i, j in edges:
        a, b = find(i), find(j)
        if a == b:  # would form a cycle
            continue
        parent[a] = b
        total += w
        used += 1
        if used == n - 1:
            break
    return total


# ---------- Approach 2: Prim with a heap ----------
def min_cost_connect_points_heap(pts: list[list[int]]) -> int:
    n = len(pts)
    seen = [False] * n
    pq = [(0, 0)]  # (cost to reach, point)
    total = added = 0
    while added < n:
        w, u = heapq.heappop(pq)
        if seen[u]:  # already attached by a cheaper edge
            continue
        seen[u] = True
        total += w
        added += 1
        for v in range(n):
            if not seen[v]:
                heapq.heappush(pq, (manhattan(pts[u], pts[v]), v))
    return total


# ---------- Approach 3: Prim with an array ⭐ ----------
def min_cost_connect_points(pts: list[list[int]]) -> int:
    n = len(pts)
    dist = [float("inf")] * n  # cheapest edge from the tree to each point
    in_tree = [False] * n
    dist[0] = 0
    total = 0
    for _ in range(n):
        u = min((v for v in range(n) if not in_tree[v]), key=lambda v: dist[v])  # closest outside point
        in_tree[u] = True
        total += dist[u]
        for v in range(n):
            if not in_tree[v]:
                dist[v] = min(dist[v], manhattan(pts[u], pts[v]))
    return int(total)


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        [[0, 0], [2, 2], [3, 10], [5, 2], [7, 0]],
        [[3, 12], [-2, 5], [-4, 1]],
        [[0, 0]],
        [[0, 0], [1, 1], [1, 0], [-1, 1]],
    ]
    for p in tests:
        print("kruskal   :", min_cost_connect_points_kruskal(p))
        print("prim heap :", min_cost_connect_points_heap(p))
        print("prim array:", min_cost_connect_points(p))
        print("---")

"""
Syntax notes (Python):
- min(iterable, key=...) picks the argmin directly, no manual index loop.
- sorted() of a generator of tuples sorts edges by cost, then endpoints.
- `total = used = 0` chains assignment of ints safely (immutable).
- A nested def can read and mutate an enclosing list (parent) without `nonlocal`.
"""
