"""
0133. Clone Graph  |  Medium  |  Graphs
Link: https://leetcode.com/problems/clone-graph/

Problem: Deep-copy a connected undirected graph given one of its nodes.
         Test input/output is an adjacency list (node i+1's neighbours).

Examples:
  [[2,4],[1,3],[2,4],[1,3]]  -> [[2,4],[1,3],[2,4],[1,3]]
  [[]]                       -> [[]]
  []                         -> []
  [[2],[1,3],[2]]            -> [[2],[1,3],[2]]   (path 1-2-3)

Approaches:
  1. DFS + map  ⭐   O(V + E) time, O(V) space   <- go-to
  2. BFS + map       O(V + E) time, O(V) space
"""

from collections import deque
from typing import Optional


class Node:
    def __init__(self, val: int = 0, neighbors: Optional[list["Node"]] = None):
        self.val = val
        self.neighbors = neighbors if neighbors is not None else []  # no shared mutable default


# ---------- Approach 1: DFS + Map ⭐ ----------
def clone_graph(node: Optional[Node]) -> Optional[Node]:
    copy: dict[Node, Node] = {}

    def dfs(n: Node) -> Node:
        if n in copy:
            return copy[n]
        c = Node(n.val)
        copy[n] = c  # before recursing: cycles find it
        c.neighbors = [dfs(nb) for nb in n.neighbors]
        return c

    return dfs(node) if node else None


# ---------- Approach 2: BFS + Map ----------
def clone_graph_bfs(node: Optional[Node]) -> Optional[Node]:
    if not node:
        return None
    copy = {node: Node(node.val)}
    q = deque([node])
    while q:
        cur = q.popleft()
        for nb in cur.neighbors:
            if nb not in copy:
                copy[nb] = Node(nb.val)
                q.append(nb)
            copy[cur].neighbors.append(copy[nb])
    return copy[node]


# ---------- Driver ----------
def build(adj: list[list[int]]) -> list[Node]:
    nodes = [Node(i + 1) for i in range(len(adj))]
    for i, nbs in enumerate(adj):
        nodes[i].neighbors = [nodes[v - 1] for v in nbs]
    return nodes


def collect(start: Optional[Node]) -> list[Node]:
    if not start:
        return []
    seen, st = {start}, [start]
    while st:
        cur = st.pop()
        for nb in cur.neighbors:
            if nb not in seen:
                seen.add(nb)
                st.append(nb)
    return sorted(seen, key=lambda n: n.val)


def show(clone: Optional[Node], orig: list[Node]) -> str:
    nodes = collect(clone)
    deep = all(all(n is not o for o in orig) for n in nodes)
    return f"{[[nb.val for nb in n.neighbors] for n in nodes]} deep copy: {str(deep).lower()}"


if __name__ == "__main__":
    tests = [[[2, 4], [1, 3], [2, 4], [1, 3]], [[]], [], [[2], [1, 3], [2]]]
    for adj in tests:
        orig = build(adj)
        start = orig[0] if orig else None
        print("dfs:", show(clone_graph(start), orig))
        print("bfs:", show(clone_graph_bfs(start), orig))
        print("---")

"""
Syntax notes (Python):
- Objects without __eq__ hash by identity, so dict[Node, Node] works as-is.
- `a is not b` compares identity (same object), not value.
- neighbors=None + `if neighbors is not None else []` avoids the mutable default trap.
"""
