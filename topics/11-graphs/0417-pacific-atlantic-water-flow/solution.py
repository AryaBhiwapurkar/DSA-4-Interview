"""
0417. Pacific Atlantic Water Flow  |  Medium  |  Graphs
Link: https://leetcode.com/problems/pacific-atlantic-water-flow/

Problem: Rain flows from a cell to any 4-neighbour of equal or lower height.
         The Pacific touches the top and left edges, the Atlantic the bottom
         and right. Return cells that can drain into both oceans.

Examples:
  [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
      -> [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
  [[1]]            -> [[0,0]]
  [[1,1],[1,1]]    -> all four cells
  [[3,2,1]]        -> all three cells (one row touches both oceans)

Approaches:
  1. DFS from every cell           O((m*n)^2) time, O(m*n) space
  2. Reverse DFS from oceans  ⭐    O(m*n) time, O(m*n) space   <- go-to
"""

DIRS = ((1, 0), (-1, 0), (0, 1), (0, -1))


# ---------- Approach 1: DFS from Every Cell ----------
def pacific_atlantic_brute(h: list[list[int]]) -> list[list[int]]:
    m, n = len(h), len(h[0])
    res = []
    for i in range(m):
        for j in range(n):
            pac = atl = False
            seen = {(i, j)}
            st = [(i, j)]
            while st and not (pac and atl):
                r, c = st.pop()
                pac |= r == 0 or c == 0
                atl |= r == m - 1 or c == n - 1
                for dr, dc in DIRS:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < m and 0 <= nc < n and (nr, nc) not in seen and h[nr][nc] <= h[r][c]:  # downhill
                        seen.add((nr, nc))
                        st.append((nr, nc))
            if pac and atl:
                res.append([i, j])
    return res


# ---------- Approach 2: Reverse DFS from Both Oceans ⭐ ----------
def pacific_atlantic(h: list[list[int]]) -> list[list[int]]:
    m, n = len(h), len(h[0])

    def reach(starts: list[tuple[int, int]]) -> set[tuple[int, int]]:
        seen = set(starts)
        st = list(starts)
        while st:
            r, c = st.pop()
            for dr, dc in DIRS:
                nr, nc = r + dr, c + dc
                if 0 <= nr < m and 0 <= nc < n and (nr, nc) not in seen and h[nr][nc] >= h[r][c]:  # uphill
                    seen.add((nr, nc))
                    st.append((nr, nc))
        return seen

    pac = reach([(0, j) for j in range(n)] + [(i, 0) for i in range(1, m)])
    atl = reach([(m - 1, j) for j in range(n)] + [(i, n - 1) for i in range(m - 1)])
    return sorted([r, c] for r, c in pac & atl)


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        [[1, 2, 2, 3, 5], [3, 2, 3, 4, 4], [2, 4, 5, 3, 1], [6, 7, 1, 4, 5], [5, 1, 1, 2, 4]],
        [[1]], [[1, 1], [1, 1]], [[3, 2, 1]],
    ]
    for h in tests:
        print("brute  :", sorted(pacific_atlantic_brute(h)))  # any order is accepted
        print("reverse:", pacific_atlantic(h))
        print("---")

"""
Syntax notes (Python):
- `pac |= cond` ORs a bool flag in place.
- Set intersection `pac & atl` gives cells reachable from both oceans.
- Iterative DFS with an explicit stack avoids the recursion limit on 200x200.
"""
