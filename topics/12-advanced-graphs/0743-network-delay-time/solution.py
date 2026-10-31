"""
0743. Network Delay Time  |  Medium  |  Advanced Graphs
Link: https://leetcode.com/problems/network-delay-time/

Problem: Directed weighted edges (u, v, w), nodes 1..n. A signal starts at k.
         Return the time until every node has it, or -1 if some never does.

Examples:
  [[2,1,1],[2,3,1],[3,4,1]], n=4, k=2          -> 2
  [[1,2,1]], n=2, k=1                          -> 1
  [[1,2,1]], n=2, k=2                          -> -1
  [[1,2,4],[1,3,1],[3,2,1],[2,4,1]], n=4, k=1  -> 3 (detour beats direct edge)

Approaches:
  1. Bellman-Ford        O(V*E) time, O(V) space
  2. Dijkstra (heap)  ⭐  O(E log V) time, O(V + E) space   <- go-to
"""

import heapq
from collections import defaultdict

INF = float("inf")


# ---------- Approach 1: Bellman-Ford ----------
def network_delay_time_bf(times: list[list[int]], n: int, k: int) -> int:
    dist = [INF] * (n + 1)
    dist[k] = 0
    for _ in range(n - 1):  # a shortest path has at most n-1 edges
        changed = False
        for u, v, w in times:
            if dist[u] + w < dist[v]:
                dist[v] = dist[u] + w
                changed = True
        if not changed:
            break
    ans = max(dist[1:])
    return -1 if ans == INF else ans


# ---------- Approach 2: Dijkstra ⭐ ----------
def network_delay_time(times: list[list[int]], n: int, k: int) -> int:
    adj: dict[int, list[tuple[int, int]]] = defaultdict(list)
    for u, v, w in times:
        adj[u].append((v, w))
    dist = [INF] * (n + 1)
    dist[k] = 0
    pq = [(0, k)]  # (dist, node)
    while pq:
        d, u = heapq.heappop(pq)
        if d > dist[u]:  # stale entry: u was already settled cheaper
            continue
        for v, w in adj[u]:
            if d + w < dist[v]:
                dist[v] = d + w
                heapq.heappush(pq, (dist[v], v))
    ans = max(dist[1:])  # node 0 unused
    return -1 if ans == INF else ans


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        ([[2, 1, 1], [2, 3, 1], [3, 4, 1]], 4, 2),
        ([[1, 2, 1]], 2, 1),
        ([[1, 2, 1]], 2, 2),
        ([[1, 2, 4], [1, 3, 1], [3, 2, 1], [2, 4, 1]], 4, 1),
    ]
    for times, n, k in tests:
        print("bellman :", network_delay_time_bf(times, n, k))
        print("dijkstra:", network_delay_time(times, n, k))
        print("---")

"""
Syntax notes (Python):
- heapq is a min-heap on tuples: (dist, node) pops the smallest distance first.
- float("inf") + w stays inf, so no overflow guard is needed.
- max(dist[1:]) skips the unused index 0.
- heapq has no decrease-key: push a new entry and skip stale ones on pop.
"""
