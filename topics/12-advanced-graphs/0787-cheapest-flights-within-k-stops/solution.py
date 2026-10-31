"""
0787. Cheapest Flights Within K Stops  |  Medium  |  Advanced Graphs
Link: https://leetcode.com/problems/cheapest-flights-within-k-stops/

Problem: Directed flights (from, to, price) between n cities. Cheapest price
         from src to dst using at most k stops (k+1 flights), or -1.

Examples:
  n=4, [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], 0->3, k=1  -> 700
  n=3, [[0,1,100],[1,2,100],[0,2,500]], 0->2, k=1                      -> 200
  n=3, [[0,1,100],[1,2,100],[0,2,500]], 0->2, k=0                      -> 500
  n=2, [[0,1,100]], 1->0, k=1                                          -> -1

Approaches:
  1. Dijkstra on (node, flights used)   O(E*k log(E*k)) time, O(n*k + E) space
  2. Bellman-Ford, k+1 rounds  ⭐         O(k*E) time, O(n) space   <- go-to
"""

import heapq
from collections import defaultdict

INF = float("inf")


# ---------- Approach 1: Dijkstra with stop count in the state ----------
def find_cheapest_price_dijkstra(n: int, flights: list[list[int]], src: int, dst: int, k: int) -> int:
    adj: dict[int, list[tuple[int, int]]] = defaultdict(list)
    for u, v, w in flights:
        adj[u].append((v, w))
    best_edges = [INF] * n  # fewest flights seen when popping each city
    pq = [(0, src, 0)]  # (cost, city, flights used)
    while pq:
        cost, u, e = heapq.heappop(pq)
        if u == dst:  # first pop of dst is the cheapest valid one
            return cost
        if e == k + 1 or e >= best_edges[u]:  # out of flights, or dominated
            continue
        best_edges[u] = e
        for v, w in adj[u]:
            heapq.heappush(pq, (cost + w, v, e + 1))
    return -1


# ---------- Approach 2: Bellman-Ford, k+1 rounds ⭐ ----------
def find_cheapest_price(n: int, flights: list[list[int]], src: int, dst: int, k: int) -> int:
    price = [INF] * n
    price[src] = 0
    for _ in range(k + 1):  # round i allows i+1 flights
        nxt = price[:]  # read old prices only: one more flight per round
        for u, v, w in flights:
            if price[u] + w < nxt[v]:
                nxt[v] = price[u] + w
        price = nxt
    return -1 if price[dst] == INF else price[dst]


# ---------- Driver ----------
if __name__ == "__main__":
    tri = [[0, 1, 100], [1, 2, 100], [0, 2, 500]]
    tests = [
        (4, [[0, 1, 100], [1, 2, 100], [2, 0, 100], [1, 3, 600], [2, 3, 200]], 0, 3, 1),
        (3, tri, 0, 2, 1),
        (3, tri, 0, 2, 0),
        (2, [[0, 1, 100]], 1, 0, 1),
    ]
    for n, flights, src, dst, k in tests:
        print("dijkstra:", find_cheapest_price_dijkstra(n, flights, src, dst, k))
        print("bellman :", find_cheapest_price(n, flights, src, dst, k))
        print("---")

"""
Syntax notes (Python):
- price[:] is a shallow copy of a list of numbers, enough for the per-round snapshot.
- Tuples in heapq compare element by element: (cost, city, flights).
- float("inf") + w is still inf, so relaxation needs no reachability guard.
"""
