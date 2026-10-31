"""
0323. Number of Connected Components in an Undirected Graph  |  Medium  |  Graphs
Link: https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/

Problem: n nodes, undirected edges. Count the connected components.

Examples:
  5, [[0,1],[1,2],[3,4]]          -> 2
  5, [[0,1],[1,2],[2,3],[3,4]]    -> 1
  3, []                           -> 3
  4, [[0,1],[1,2],[2,0]]          -> 2 (cycle + isolated node)

Approaches:
  1. DFS from each unvisited node    O(n + E) time, O(n + E) space
  2. Union-Find with count  ⭐        O(n + E * alpha) time, O(n) space   <- go-to
"""


# ---------- Approach 1: DFS ----------
def count_components_dfs(n: int, edges: list[list[int]]) -> int:
    adj: list[list[int]] = [[] for _ in range(n)]
    for a, b in edges:
        adj[a].append(b)
        adj[b].append(a)
    seen = [False] * n
    count = 0
    for s in range(n):
        if seen[s]:
            continue
        count += 1  # new component
        seen[s] = True
        st = [s]
        while st:
            for v in adj[st.pop()]:
                if not seen[v]:
                    seen[v] = True
                    st.append(v)
    return count


# ---------- Approach 2: Union-Find with Count ⭐ ----------
def count_components(n: int, edges: list[list[int]]) -> int:
    parent = list(range(n))
    rank = [0] * n

    def find(x: int) -> int:
        while parent[x] != x:
            parent[x] = parent[parent[x]]  # path halving
            x = parent[x]
        return x

    count = n  # every node starts alone
    for a, b in edges:
        ra, rb = find(a), find(b)
        if ra == rb:
            continue  # same component already
        if rank[ra] < rank[rb]:
            ra, rb = rb, ra
        parent[rb] = ra
        if rank[ra] == rank[rb]:
            rank[ra] += 1
        count -= 1
    return count


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [(5, [[0, 1], [1, 2], [3, 4]]), (5, [[0, 1], [1, 2], [2, 3], [3, 4]]), (3, []), (4, [[0, 1], [1, 2], [2, 0]])]
    for n, edges in tests:
        print("dfs:", count_components_dfs(n, edges))
        print("uf :", count_components(n, edges))
        print("---")

"""
Syntax notes (Python):
- `for v in adj[st.pop()]` pops and iterates the neighbours in one line.
- `ra, rb = rb, ra` swaps so the higher-rank root stays on top.
"""
