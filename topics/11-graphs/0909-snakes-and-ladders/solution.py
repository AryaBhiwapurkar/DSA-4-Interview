"""
0909. Snakes and Ladders  |  Medium  |  Graphs
Link: https://leetcode.com/problems/snakes-and-ladders/

Problem: Zigzag-numbered n x n board, start at 1, each move rolls 1-6 and
         follows at most one snake/ladder. Fewest moves to reach n^2, or -1.

Examples:
  6x6 LeetCode board (2->15, 14->35, 17->13)   -> 4
  [[-1,-1],[-1,3]]                             -> 1
  [[-1,-1,-1],[-1,9,8],[-1,8,9]]               -> 1 (3 is a ladder to 9)
  [[1,1,-1],[1,1,1],[-1,1,1]]                  -> -1 (every roll slides back to 1)

Approaches:
  1. BFS with on-the-fly coordinates    O(n^2) time, O(n^2) space
  2. Flatten + BFS  ⭐                   O(n^2) time, O(n^2) space   <- go-to
"""

from collections import deque


def cell(s: int, n: int) -> tuple[int, int]:
    """Square s (1-based) -> (row, col) on the zigzag board."""
    q, c = divmod(s - 1, n)
    if q % 2 == 1:
        c = n - 1 - c  # odd rows (from the bottom) run right-to-left
    return n - 1 - q, c


# ---------- Approach 1: BFS with On-the-Fly Coordinates ----------
def snakes_and_ladders_coords(board: list[list[int]]) -> int:
    n = len(board)
    target = n * n
    dist = {1: 0}
    q = deque([1])
    while q:
        s = q.popleft()
        for t in range(s + 1, min(s + 6, target) + 1):
            r, c = cell(t, n)
            dest = t if board[r][c] == -1 else board[r][c]
            if dest in dist:
                continue
            dist[dest] = dist[s] + 1
            if dest == target:
                return dist[dest]
            q.append(dest)
    return -1


# ---------- Approach 2: Flatten + BFS ⭐ ----------
def snakes_and_ladders(board: list[list[int]]) -> int:
    n = len(board)
    target = n * n
    jump = [0] + [board[r][c] for r, c in (cell(s, n) for s in range(1, target + 1))]
    dist = [-1] * (target + 1)
    dist[1] = 0
    q = deque([1])
    while q:
        s = q.popleft()
        for t in range(s + 1, min(s + 6, target) + 1):
            dest = t if jump[t] == -1 else jump[t]  # one jump per roll, no chaining
            if dist[dest] != -1:
                continue  # visit the square you end on
            dist[dest] = dist[s] + 1
            if dest == target:
                return dist[dest]
            q.append(dest)
    return -1


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        [[-1, -1, -1, -1, -1, -1], [-1, -1, -1, -1, -1, -1], [-1, -1, -1, -1, -1, -1],
         [-1, 35, -1, -1, 13, -1], [-1, -1, -1, -1, -1, -1], [-1, 15, -1, -1, -1, -1]],
        [[-1, -1], [-1, 3]],
        [[-1, -1, -1], [-1, 9, 8], [-1, 8, 9]],
        [[1, 1, -1], [1, 1, 1], [-1, 1, 1]],
    ]
    for b in tests:
        print("coords :", snakes_and_ladders_coords(b))
        print("flatten:", snakes_and_ladders(b))
        print("---")

"""
Syntax notes (Python):
- divmod(s - 1, n) gives (row from the bottom, column) in one call.
- [0] + [...] pads index 0 so squares can be used as 1-based indices.
- range(s + 1, min(s + 6, target) + 1) caps the roll at the last square.
"""
