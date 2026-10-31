"""
0210. Course Schedule II  |  Medium  |  Graphs
Link: https://leetcode.com/problems/course-schedule-ii/

Problem: n courses, pairs [a, b] meaning b before a. Return any order
         that takes every course, or [] if impossible.

Examples:
  2, [[1,0]]                    -> [0,1]
  4, [[1,0],[2,0],[3,1],[3,2]]  -> [0,2,1,3] or [0,1,2,3]
  1, []                         -> [0]
  2, [[1,0],[0,1]]              -> []

Approaches:
  1. DFS post-order (reversed)   O(V + E) time, O(V + E) space
  2. Kahn's algorithm  ⭐         O(V + E) time, O(V + E) space   <- go-to
"""

from collections import deque


# ---------- Approach 1: DFS Post-Order ----------
def find_order_dfs(n: int, pre: list[list[int]]) -> list[int]:
    adj: list[list[int]] = [[] for _ in range(n)]
    for a, b in pre:
        adj[b].append(a)
    color = [0] * n
    out: list[int] = []

    def post(u: int) -> bool:
        color[u] = 1
        for v in adj[u]:
            if color[v] == 1:
                return False  # back edge: cycle
            if color[v] == 0 and not post(v):
                return False
        color[u] = 2
        out.append(u)  # after everything that depends on u
        return True

    for u in range(n):
        if color[u] == 0 and not post(u):
            return []
    return out[::-1]


# ---------- Approach 2: Kahn's Algorithm ⭐ ----------
def find_order(n: int, pre: list[list[int]]) -> list[int]:
    adj: list[list[int]] = [[] for _ in range(n)]
    indeg = [0] * n
    for a, b in pre:
        adj[b].append(a)
        indeg[a] += 1
    q = deque(u for u in range(n) if indeg[u] == 0)
    order: list[int] = []
    while q:
        u = q.popleft()
        order.append(u)
        for v in adj[u]:
            indeg[v] -= 1
            if indeg[v] == 0:
                q.append(v)
    return order if len(order) == n else []  # cycle -> []


# ---------- Driver ----------
def valid(n: int, pre: list[list[int]], order: list[int]) -> bool:
    if len(order) != n:
        return False
    pos = {u: i for i, u in enumerate(order)}
    return all(pos[b] < pos[a] for a, b in pre)


if __name__ == "__main__":
    tests = [(2, [[1, 0]]), (4, [[1, 0], [2, 0], [3, 1], [3, 2]]), (1, []), (2, [[1, 0], [0, 1]])]
    for n, pre in tests:
        a, b = find_order_dfs(n, pre), find_order(n, pre)
        print("dfs :", a, "valid:", str(valid(n, pre, a)).lower())
        print("kahn:", b, "valid:", str(valid(n, pre, b)).lower())
        print("---")

"""
Syntax notes (Python):
- out[::-1] returns a reversed copy.
- {u: i for i, u in enumerate(order)} inverts a list into value -> index.
- `x if cond else y` keeps the cycle check on the return line.
"""
