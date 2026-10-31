# 11. Graphs

## Core Idea
A graph problem is usually three decisions: **what the nodes and edges are** (grid cells, words, courses, variables), **which traversal** (DFS for reachability and components, BFS for shortest paths in unweighted graphs, topological sort for dependencies, Union-Find for incremental connectivity), and **how to mark visited** (a set, a distance array, or overwriting the input). Most grid and implicit-graph problems are one of these templates with a custom neighbour function.

## When to Use
- Count or measure connected regions: flood fill (0200, 0695, 0323).
- "Fewest steps / minimum moves" with equal-cost moves: BFS (0127, 0433, 0909).
- Spreading from many places at once, nearest of many sources: multi-source BFS (0994, 0286).
- Prerequisites, ordering, "is there a cycle in a directed graph": topological sort (0207, 0210).
- Edges arrive one at a time, "does this edge close a cycle", component counts: Union-Find (0684, 0261, 0323).
- Cells that can reach a border / target: reverse search from the target (0130, 0417).
- Ratios or weighted relations: weighted edges, multiply along paths (0399).

## Templates

### Grid DFS / flood fill
```cpp
void dfs(vector<vector<char>>& g, int r, int c) {
    if (r < 0 || c < 0 || r >= (int)g.size() || c >= (int)g[0].size() || g[r][c] != '1') return;
    g[r][c] = '0';                                   // mark visited
    for (int d = 0; d < 4; d++) dfs(g, r + DR[d], c + DC[d]);
}
```
```python
def dfs(r, c):                                       # iterative: no recursion limit
    st = [(r, c)]
    while st:
        r, c = st.pop()
        if 0 <= r < m and 0 <= c < n and g[r][c] == "1":
            g[r][c] = "0"
            st.extend((r + dr, c + dc) for dr, dc in DIRS)
```

### BFS shortest path (single or multi-source)
```cpp
queue<pair<int, int>> q;                             // push every source first for multi-source
for (auto s : sources) { q.push(s); dist[s] = 0; }
while (!q.empty()) {
    auto [r, c] = q.front(); q.pop();
    for (int d = 0; d < 4; d++) {
        int nr = r + DR[d], nc = c + DC[d];
        if (!inside(nr, nc) || blocked(nr, nc) || dist[nr][nc] != -1) continue;
        dist[nr][nc] = dist[r][c] + 1;               // mark on push
        q.push({nr, nc});
    }
}
```
```python
q = deque(sources)
while q:
    for _ in range(len(q)):                          # one level = one step / minute
        u = q.popleft()
        for v in neighbours(u):
            if v not in seen:
                seen.add(v)
                q.append(v)
    steps += 1
```

### Topological sort (Kahn's)
```python
indeg = [0] * n
for a, b in pre:                                     # b -> a
    adj[b].append(a); indeg[a] += 1
q = deque(u for u in range(n) if indeg[u] == 0)
order = []
while q:
    u = q.popleft(); order.append(u)
    for v in adj[u]:
        indeg[v] -= 1
        if indeg[v] == 0:
            q.append(v)
return order if len(order) == n else []              # shorter -> cycle
```

### Union-Find
```cpp
struct DSU {
    vector<int> parent, rank_;
    DSU(int n) : parent(n), rank_(n, 0) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    bool unite(int a, int b) {                       // false: already connected (cycle edge)
        a = find(a), b = find(b);
        if (a == b) return false;
        if (rank_[a] < rank_[b]) swap(a, b);
        parent[b] = a;
        if (rank_[a] == rank_[b]) rank_[a]++;
        return true;
    }
};
```
```python
parent = list(range(n))
def find(x):
    while parent[x] != x:
        parent[x] = parent[parent[x]]                # path halving
        x = parent[x]
    return x
```

## Common Variations
- **Return a size, not a count:** DFS returns `1 + sum(neighbours)` (0695).
- **Reverse the direction:** start from the border / ocean and walk the allowed moves backwards (0130, 0417).
- **Implicit graph of strings:** neighbours by single-letter substitution, or wildcard buckets (`h*t`) to avoid the alphabet factor (0433, 0127).
- **Board numbering quirks:** flatten to a 1-D array first, then BFS on integers (0909).
- **Directed cycle detection by DFS:** three colors (new / on path / done); two colors give false positives.
- **Count components with Union-Find:** start at n, decrement on each successful union (0323).
- **Tree check:** exactly n - 1 edges and no failed union (0261).
- **Deep copy:** old → new map doubles as the visited set (0133).

## ⚠️ Pitfalls
- **Python recursion limit** (~1000) on grids up to 300 × 300: use an explicit stack or BFS.
- **Marking visited on pop** instead of on push makes BFS enqueue the same node many times.
- **Edge direction** in prerequisite pairs: [a, b] means b → a.
- **C++ `map[key]` inserts** a default; use `count`/`find` for existence (e.g. unknown variables in 0399).
- **Off-by-one in level counting:** decide whether the answer counts nodes (0127) or edges (0433).

## Problems

| # | Problem | Difficulty | Pattern | Status |
|---|---------|------------|---------|--------|
| 0130 | [Surrounded Regions](0130-surrounded-regions/) | Medium | DFS from border | ✅ |
| 0133 | [Clone Graph](0133-clone-graph/) | Medium | DFS + hashmap old→new | ✅ |
| 0200 | [Number of Islands](0200-number-of-islands/) | Medium | Grid DFS/BFS flood fill | ✅ |
| 0207 | [Course Schedule](0207-course-schedule/) | Medium | Cycle detection / Kahn's | ✅ |
| 0210 | [Course Schedule II](0210-course-schedule-ii/) | Medium | Topological sort | ✅ |
| 0261 | [Graph Valid Tree](0261-graph-valid-tree/) | Medium | n-1 edges + connected | ✅ |
| 0286 | [Walls and Gates](0286-walls-and-gates/) | Medium | Multi-source BFS | ✅ |
| 0323 | [Number of Connected Components in an Undirected Graph](0323-number-of-connected-components-in-an-undirected-graph/) | Medium | Union-Find / DFS | ✅ |
| 0399 | [Evaluate Division](0399-evaluate-division/) | Medium | Weighted graph DFS / weighted Union-Find | ✅ |
| 0417 | [Pacific Atlantic Water Flow](0417-pacific-atlantic-water-flow/) | Medium | Reverse DFS from both oceans | ✅ |
| 0433 | [Minimum Genetic Mutation](0433-minimum-genetic-mutation/) | Medium | BFS over strings | ✅ |
| 0684 | [Redundant Connection](0684-redundant-connection/) | Medium | Union-Find | ✅ |
| 0695 | [Max Area of Island](0695-max-area-of-island/) | Medium | Grid DFS | ✅ |
| 0909 | [Snakes and Ladders](0909-snakes-and-ladders/) | Medium | BFS on board | ✅ |
| 0994 | [Rotting Oranges](0994-rotting-oranges/) | Medium | Multi-source BFS | ✅ |
| 0127 | [Word Ladder](0127-word-ladder/) | Hard | BFS with wildcard buckets | ✅ |
