"""
0684. Redundant Connection  |  Medium  |  Graphs
Link: https://leetcode.com/problems/redundant-connection/

Problem: A tree on 1..n plus one extra edge. Return an edge whose removal
         leaves a tree (the last such edge in input order).

Examples:
  [[1,2],[1,3],[2,3]]                  -> [2,3]
  [[1,2],[2,3],[3,4],[1,4],[1,5]]      -> [1,4]
  [[1,2],[2,3],[1,3],[3,4]]            -> [1,3]

Approaches:
  1. DFS before each edge     O(n^2) time, O(n) space
  2. Union-Find  ⭐            O(n * alpha) time, O(n) space   <- go-to
"""


# ---------- Approach 1: DFS Before Each Edge ----------
def find_redundant_connection_dfs(edges: list[list[int]]) -> list[int]:
    n = len(edges)
    adj: list[list[int]] = [[] for _ in range(n + 1)]
    for a, b in edges:
        seen, st = {a}, [a]
        while st:
            u = st.pop()
            for v in adj[u]:
                if v not in seen:
                    seen.add(v)
                    st.append(v)
        if b in seen:
            return [a, b]  # already connected: this edge closes the cycle
        adj[a].append(b)
        adj[b].append(a)
    return []


# ---------- Approach 2: Union-Find ⭐ ----------
def find_redundant_connection(edges: list[list[int]]) -> list[int]:
    parent = list(range(len(edges) + 1))  # labels are 1..n

    def find(x: int) -> int:
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    for a, b in edges:
        ra, rb = find(a), find(b)
        if ra == rb:
            return [a, b]
        parent[rb] = ra
    return []


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [[[1, 2], [1, 3], [2, 3]], [[1, 2], [2, 3], [3, 4], [1, 4], [1, 5]], [[1, 2], [2, 3], [1, 3], [3, 4]]]
    for edges in tests:
        print("dfs:", find_redundant_connection_dfs(edges))
        print("uf :", find_redundant_connection(edges))
        print("---")

"""
Syntax notes (Python):
- Path halving in find() keeps trees shallow without recursion.
- Returning [a, b] builds a fresh list rather than aliasing the input edge.
"""
