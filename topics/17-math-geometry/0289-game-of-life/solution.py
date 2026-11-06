"""
0289. Game of Life  |  Medium  |  Math & Geometry
Link: https://leetcode.com/problems/game-of-life/

Problem: Advance Conway's Game of Life one generation, in place.
         Live: survives with 2 or 3 live neighbours. Dead: born with exactly 3.

Examples:
  [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]  -> [[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
  [[1,1],[1,0]]                      -> [[1,1],[1,1]]
  [[1]]                              -> [[0]]
  [[0,1,0],[0,1,0],[0,1,0]]          -> [[0,0,0],[1,1,1],[0,0,0]]   (blinker)

Approaches:
  1. Copy the board                O(m*n) time, O(m*n) space
  2. Two-bit state encoding  ⭐    O(m*n) time, O(1) extra   <- go-to
"""

import copy

DIRS = [(dr, dc) for dr in (-1, 0, 1) for dc in (-1, 0, 1) if (dr, dc) != (0, 0)]


def live_neighbours(b: list[list[int]], r: int, c: int) -> int:
    m, n = len(b), len(b[0])
    return sum(b[r + dr][c + dc] & 1  # bit 0 = old state
               for dr, dc in DIRS if 0 <= r + dr < m and 0 <= c + dc < n)


# ---------- Approach 1: Copy ----------
def game_of_life_copy(board: list[list[int]]) -> None:
    old = [row[:] for row in board]
    for r in range(len(board)):
        for c in range(len(board[0])):
            k = live_neighbours(old, r, c)
            board[r][c] = 1 if k == 3 or (old[r][c] and k == 2) else 0


# ---------- Approach 2: Bit Encoding ⭐ ----------
def game_of_life(board: list[list[int]]) -> None:
    for r in range(len(board)):
        for c in range(len(board[0])):
            k = live_neighbours(board, r, c)
            if k == 3 or (board[r][c] & 1 and k == 2):
                board[r][c] |= 2  # bit 1 = next state
    for row in board:
        for c in range(len(row)):
            row[c] >>= 1  # promote next state


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        [[0, 1, 0], [0, 0, 1], [1, 1, 1], [0, 0, 0]],
        [[1, 1], [1, 0]],
        [[1]],
        [[0, 1, 0], [0, 1, 0], [0, 1, 0]],
    ]
    for t in tests:
        a, b = copy.deepcopy(t), copy.deepcopy(t)
        game_of_life_copy(a)
        game_of_life(b)
        print("copy:", a)
        print("bits:", b)
        print("---")

"""
Syntax notes (Python):
- A comprehension builds the 8 direction offsets once: skip (0, 0).
- [row[:] for row in board] copies a 2-D list (rows are independent).
- `for x in row: x >>= 1` does nothing to the list; index it: row[c] >>= 1.
"""
