"""
0286. Walls and Gates  |  Medium  |  Graphs
Link: https://leetcode.com/problems/walls-and-gates/

Problem: Grid of -1 (wall), 0 (gate), INF (room). Fill each room in place
         with its distance to the nearest gate (INF if unreachable).

Examples (I = INF = 2147483647):
  [[I,-1,0,I],[I,I,I,-1],[I,-1,I,-1],[0,-1,I,I]]  -> [[3,-1,0,1],[2,2,1,-1],[1,-1,2,-1],[0,-1,3,4]]
  [[-1]]                                         -> [[-1]]
  [[I,I],[I,I]]                                  -> unchanged (no gate)
  [[0,-1,I]]                                     -> [[0,-1,I]] (walled off)

Approaches:
  1. BFS from each gate      O(k*m*n) time, O(m*n) space
  2. Multi-source BFS  ⭐     O(m*n) time, O(m*n) space   <- go-to
"""

from collections import deque

INF = 2147483647
DIRS = ((1, 0), (-1, 0), (0, 1), (0, -1))


# ---------- Approach 1: BFS from Each Gate ----------
def walls_and_gates_each(g: list[list[int]]) -> None:
    m, n = len(g), len(g[0])
    for i in range(m):
        for j in range(n):
            if g[i][j] != 0:
                continue
            dist = {(i, j): 0}
            q = deque([(i, j)])
            while q:
                r, c = q.popleft()
                for dr, dc in DIRS:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < m and 0 <= nc < n and (nr, nc) not in dist and g[nr][nc] > 0:
                        dist[(nr, nc)] = dist[(r, c)] + 1
                        g[nr][nc] = min(g[nr][nc], dist[(nr, nc)])  # keep the closest gate
                        q.append((nr, nc))


# ---------- Approach 2: Multi-Source BFS ⭐ ----------
def walls_and_gates(g: list[list[int]]) -> None:
    m, n = len(g), len(g[0])
    q = deque((i, j) for i in range(m) for j in range(n) if g[i][j] == 0)  # all gates start together
    while q:
        r, c = q.popleft()
        for dr, dc in DIRS:
            nr, nc = r + dr, c + dc
            if 0 <= nr < m and 0 <= nc < n and g[nr][nc] == INF:  # INF = unvisited room
                g[nr][nc] = g[r][c] + 1
                q.append((nr, nc))


# ---------- Driver ----------
if __name__ == "__main__":
    I = INF
    tests = [
        [[I, -1, 0, I], [I, I, I, -1], [I, -1, I, -1], [0, -1, I, I]],
        [[-1]], [[I, I], [I, I]], [[0, -1, I]],
    ]
    for t in tests:
        a, b = [row[:] for row in t], [row[:] for row in t]
        walls_and_gates_each(a)
        walls_and_gates(b)
        print("each :", a)
        print("multi:", b)
        print("---")

"""
Syntax notes (Python):
- deque(generator) seeds a multi-source BFS in one line.
- A dict keyed by (r, c) tuples works as a sparse distance map.
- [row[:] for row in t] deep-copies a 2-D list of ints.
"""
