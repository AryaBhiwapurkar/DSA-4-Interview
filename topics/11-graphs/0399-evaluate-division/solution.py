"""
0399. Evaluate Division  |  Medium  |  Graphs
Link: https://leetcode.com/problems/evaluate-division/

Problem: Given equations a / b = k, answer queries x / y, or -1.0 if
         they can't be determined.

Examples:
  [a/b=2, b/c=3]; a/c, b/a, a/e, a/a, x/x        -> [6.00000,0.50000,-1.00000,1.00000,-1.00000]
  [a/b=1.5, b/c=2.5, bc/cd=5]; a/c, c/b, bc/cd, cd/bc -> [3.75000,0.40000,5.00000,0.20000]
  [a/b=0.5]; a/b, b/a, a/c, x/y                  -> [0.50000,2.00000,-1.00000,-1.00000]

Approaches:
  1. DFS per query  ⭐         O(Q * (V + E)) time, O(V + E) space   <- go-to
  2. Weighted Union-Find       O((E + Q) * alpha) time, O(V) space
"""

from collections import defaultdict


# ---------- Approach 1: DFS per Query ⭐ ----------
def calc_equation(eq: list[list[str]], vals: list[float], queries: list[list[str]]) -> list[float]:
    adj: defaultdict[str, list[tuple[str, float]]] = defaultdict(list)
    for (a, b), k in zip(eq, vals):
        adj[a].append((b, k))
        adj[b].append((a, 1.0 / k))  # reverse edge

    def dfs(u: str, target: str, seen: set[str]) -> float:
        if u == target:
            return 1.0
        seen.add(u)
        for v, w in adj[u]:
            if v not in seen:
                r = dfs(v, target, seen)
                if r >= 0:
                    return w * r  # u/target = u/v * v/target
        return -1.0

    return [dfs(x, y, set()) if x in adj and y in adj else -1.0 for x, y in queries]  # unknown, even x/x


# ---------- Approach 2: Weighted Union-Find ----------
def calc_equation_uf(eq: list[list[str]], vals: list[float], queries: list[list[str]]) -> list[float]:
    parent: dict[str, str] = {}
    weight: dict[str, float] = {}  # weight[x] = x / parent[x]

    def find(x: str) -> str:  # afterwards weight[x] = x / root
        if parent[x] == x:
            return x
        p = parent[x]
        root = find(p)
        weight[x] *= weight[p]
        parent[x] = root
        return root

    for (a, b), k in zip(eq, vals):
        for x in (a, b):
            if x not in parent:
                parent[x], weight[x] = x, 1.0
        ra, rb = find(a), find(b)
        if ra != rb:
            parent[ra] = rb
            weight[ra] = k * weight[b] / weight[a]  # a / b = k

    res = []
    for x, y in queries:
        if x not in parent or y not in parent or find(x) != find(y):
            res.append(-1.0)
        else:
            res.append(weight[x] / weight[y])  # (x/root) / (y/root)
    return res


# ---------- Driver ----------
def fmt(v: list[float]) -> str:
    return "[" + ",".join(f"{x:.5f}" for x in v) + "]"


if __name__ == "__main__":
    tests = [
        ([["a", "b"], ["b", "c"]], [2.0, 3.0], [["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"]]),
        ([["a", "b"], ["b", "c"], ["bc", "cd"]], [1.5, 2.5, 5.0], [["a", "c"], ["c", "b"], ["bc", "cd"], ["cd", "bc"]]),
        ([["a", "b"]], [0.5], [["a", "b"], ["b", "a"], ["a", "c"], ["x", "y"]]),
    ]
    for eq, vals, q in tests:
        print("dfs:", fmt(calc_equation(eq, vals, q)))
        print("uf :", fmt(calc_equation_uf(eq, vals, q)))
        print("---")

"""
Syntax notes (Python):
- `for (a, b), k in zip(eq, vals)` unpacks nested pairs in the loop header.
- `x in adj` on a defaultdict doesn't create the key; adj[x] would.
- f"{x:.5f}" formats a float with 5 decimals.
"""
