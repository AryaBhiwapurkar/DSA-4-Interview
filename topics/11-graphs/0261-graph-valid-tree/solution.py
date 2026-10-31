"""
0261. Graph Valid Tree  |  Medium  |  Graphs
Link: https://leetcode.com/problems/graph-valid-tree/

Problem: Do n nodes and these undirected edges form a tree
         (connected and acyclic)?

Examples:
  5, [[0,1],[0,2],[0,3],[1,4]]         -> true
  5, [[0,1],[1,2],[2,3],[1,3],[1,4]]   -> false
  1, []                                -> true
  4, [[0,1],[2,3]]                     -> false (two components)
  4, [[0,1],[1,2],[2,0]]               -> false (cycle, node 3 isolated)

Approaches:
  1. DFS connectivity + edge count     O(n + E) time, O(n + E) space
  2. Edge count + Union-Find  ⭐        O(n + E * alpha) time, O(n) space   <- go-to
"""


# ---------- Approach 1: DFS Connectivity + Edge Count ----------
def valid_tree_dfs(n: int, edges: list[list[int]]) -> bool:
    if len(edges) != n - 1:
        return False
    adj: list[list[int]] = [[] for _ in range(n)]
    for a, b in edges:
        adj[a].append(b)
        adj[b].append(a)
    seen, st = {0}, [0]
    while st:
        for v in adj[st.pop()]:
            if v not in seen:
                seen.add(v)
                st.append(v)
    return len(seen) == n  # n-1 edges + connected => acyclic


# ---------- Approach 2: Edge Count + Union-Find ⭐ ----------
def valid_tree(n: int, edges: list[list[int]]) -> bool:
    if len(edges) != n - 1:
        return False
    parent = list(range(n))

    def find(x: int) -> int:
        while parent[x] != x:
            parent[x] = parent[parent[x]]  # path halving
            x = parent[x]
        return x

    for a, b in edges:
        ra, rb = find(a), find(b)
        if ra == rb:
            return False  # already connected: this edge closes a cycle
        parent[rb] = ra
    return True


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        (5, [[0, 1], [0, 2], [0, 3], [1, 4]]), (5, [[0, 1], [1, 2], [2, 3], [1, 3], [1, 4]]),
        (1, []), (4, [[0, 1], [2, 3]]), (4, [[0, 1], [1, 2], [2, 0]]),
    ]
    for n, edges in tests:
        print("dfs:", valid_tree_dfs(n, edges))
        print("uf :", valid_tree(n, edges))
        print("---")

"""
Syntax notes (Python):
- list(range(n)) initialises each node as its own parent.
- `seen, st = {0}, [0]` sets up the visited set and stack in one line.
"""
