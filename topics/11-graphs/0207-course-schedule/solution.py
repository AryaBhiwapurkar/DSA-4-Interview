"""
0207. Course Schedule  |  Medium  |  Graphs
Link: https://leetcode.com/problems/course-schedule/

Problem: n courses, pairs [a, b] meaning b before a. Can all be taken?
         (Is the prerequisite graph acyclic?)

Examples:
  2, [[1,0]]                       -> true
  2, [[1,0],[0,1]]                 -> false
  3, []                            -> true
  4, [[1,0],[2,1],[3,2],[1,3]]     -> false (cycle 1-2-3)
  4, [[1,0],[2,0],[3,1],[3,2]]     -> true  (diamond)

Approaches:
  1. DFS three-color            O(V + E) time, O(V + E) space
  2. Kahn's algorithm  ⭐        O(V + E) time, O(V + E) space   <- go-to
"""

from collections import deque


# ---------- Approach 1: DFS Three-Color ----------
def can_finish_dfs(n: int, pre: list[list[int]]) -> bool:
    adj: list[list[int]] = [[] for _ in range(n)]
    for a, b in pre:
        adj[b].append(a)
    color = [0] * n  # 0 new, 1 on path, 2 done

    def has_cycle(u: int) -> bool:
        color[u] = 1
        for v in adj[u]:
            if color[v] == 1 or (color[v] == 0 and has_cycle(v)):
                return True  # back edge
        color[u] = 2
        return False

    return not any(color[u] == 0 and has_cycle(u) for u in range(n))


# ---------- Approach 2: Kahn's Algorithm ⭐ ----------
def can_finish(n: int, pre: list[list[int]]) -> bool:
    adj: list[list[int]] = [[] for _ in range(n)]
    indeg = [0] * n
    for a, b in pre:  # b -> a
        adj[b].append(a)
        indeg[a] += 1
    q = deque(u for u in range(n) if indeg[u] == 0)
    taken = 0
    while q:
        u = q.popleft()
        taken += 1
        for v in adj[u]:
            indeg[v] -= 1
            if indeg[v] == 0:
                q.append(v)
    return taken == n  # leftovers sit on a cycle


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        (2, [[1, 0]]), (2, [[1, 0], [0, 1]]), (3, []),
        (4, [[1, 0], [2, 1], [3, 2], [1, 3]]), (4, [[1, 0], [2, 0], [3, 1], [3, 2]]),
    ]
    for n, pre in tests:
        print("dfs :", can_finish_dfs(n, pre))
        print("kahn:", can_finish(n, pre))
        print("---")

"""
Syntax notes (Python):
- [[] for _ in range(n)] makes n independent lists ([[]] * n would share one).
- deque(generator) seeds the queue in one line.
- `for a, b in pre` unpacks each 2-element pair.
"""
