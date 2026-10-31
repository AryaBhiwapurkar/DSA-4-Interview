# 12. Advanced Graphs

## Core Idea
Once edges have **weights**, or the path has to satisfy a global property, BFS isn't enough. Four tools cover this topic: **Dijkstra** (shortest path, non-negative weights; works for any path cost that never decreases as the path grows, like sum or max), **Bellman-Ford** (relax every edge in rounds; round i = paths with at most i edges, so it handles edge-count limits and negative weights), **MST** (Prim's grows a tree from a node, Kruskal's adds the cheapest edges with Union-Find), and **Eulerian paths** (Hierholzer: use every edge once via post-order DFS). Topological sort from 11 Graphs comes back when the graph has to be built from indirect clues.

## When to Use
- Shortest path / earliest arrival with non-negative weights: Dijkstra (0743).
- Path cost is the max (or min) cell / edge on the path: Dijkstra with `max` instead of `+`, or binary search + flood fill (0778).
- "At most k stops / edges": Bellman-Ford with k+1 rounds on a copied array (0787).
- Connect everything at minimum total cost: MST. Complete graph → array Prim's O(n²) (1584); sparse edge list → Kruskal.
- Use every edge exactly once: Hierholzer (0332).
- Order hidden in sorted data: build edges from adjacent pairs, then topological sort (0269).

## Templates

### Dijkstra (lazy heap)
```cpp
vector<int> dist(n, INT_MAX);
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;   // (dist, node)
dist[src] = 0; pq.push({0, src});
while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (d > dist[u]) continue;                       // stale entry
    for (auto [v, w] : adj[u])
        if (d + w < dist[v]) { dist[v] = d + w; pq.push({dist[v], v}); }
}
```
```python
dist = [inf] * n; dist[src] = 0
pq = [(0, src)]
while pq:
    d, u = heapq.heappop(pq)
    if d > dist[u]:
        continue
    for v, w in adj[u]:
        if d + w < dist[v]:
            dist[v] = d + w
            heapq.heappush(pq, (dist[v], v))
```

### Bellman-Ford with an edge limit
```python
price = [inf] * n; price[src] = 0
for _ in range(k + 1):                               # round i: paths with <= i+1 edges
    nxt = price[:]                                   # read old, write new
    for u, v, w in edges:
        nxt[v] = min(nxt[v], price[u] + w)
    price = nxt
```

### Prim's on a complete graph (O(n²))
```cpp
vector<int> dist(n, INT_MAX); vector<bool> in(n, false);
dist[0] = 0; int total = 0;
for (int it = 0; it < n; it++) {
    int u = -1;
    for (int v = 0; v < n; v++) if (!in[v] && (u == -1 || dist[v] < dist[u])) u = v;
    in[u] = true; total += dist[u];
    for (int v = 0; v < n; v++) if (!in[v]) dist[v] = min(dist[v], cost(u, v));
}
```

### Hierholzer (Eulerian path)
```python
for a, b in sorted(edges, reverse=True):             # pop() gives the smallest
    adj[a].append(b)
route = []
def visit(u):
    while adj[u]:
        visit(adj[u].pop())
    route.append(u)                                  # post-order
visit(start)
return route[::-1]
```

## Common Variations
- **Minimax path cost:** key = `max(key, w)` in Dijkstra (0778, 1631).
- **State-augmented Dijkstra:** put extra info (stops used, fuel, time) into the heap entry and dominate on it (0787 approach 1).
- **Kruskal vs Prim:** Kruskal = sort edges + DSU, best for sparse explicit edges; Prim with an array = O(n²), best for dense or complete graphs.
- **Topological sort from comparisons:** first differing letter of adjacent words gives one edge (0269).
- **Lexicographically smallest Eulerian path:** sort the adjacency lists, then Hierholzer (0332).

## ⚠️ Pitfalls
- **Dijkstra with negative edges** is wrong; use Bellman-Ford.
- **Plain Dijkstra with a stop limit** fails: the cheapest route to a node may use too many stops (0787).
- **Relaxing in place** in a limited-round Bellman-Ford chains several edges in one round.
- **C++ `INT_MAX + w` overflow:** check reachability before adding.
- **Pre-order append in Hierholzer** produces the greedy (possibly invalid) route; append after the loop.

## Problems

| # | Problem | Difficulty | Pattern | Status |
|---|---------|------------|---------|--------|
| 0743 | [Network Delay Time](0743-network-delay-time/) | Medium | Dijkstra | ✅ |
| 0787 | [Cheapest Flights Within K Stops](0787-cheapest-flights-within-k-stops/) | Medium | Bellman-Ford, k+1 rounds | ✅ |
| 1584 | [Min Cost to Connect All Points](1584-min-cost-to-connect-all-points/) | Medium | MST (Prim's) | ✅ |
| 0269 | [Alien Dictionary](0269-alien-dictionary/) | Hard | Topological sort on chars | ✅ |
| 0332 | [Reconstruct Itinerary](0332-reconstruct-itinerary/) | Hard | Hierholzer (Eulerian path) | ✅ |
| 0778 | [Swim in Rising Water](0778-swim-in-rising-water/) | Hard | Dijkstra on max edge | ✅ |
