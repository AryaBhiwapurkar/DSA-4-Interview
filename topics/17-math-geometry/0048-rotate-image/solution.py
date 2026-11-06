"""
0048. Rotate Image  |  Medium  |  Math & Geometry
Link: https://leetcode.com/problems/rotate-image/

Problem: Rotate an n x n matrix 90 degrees clockwise, in place.

Examples:
  [[1,2,3],[4,5,6],[7,8,9]]  -> [[7,4,1],[8,5,2],[9,6,3]]
  [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
      -> [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
  [[1]]                      -> [[1]]
  [[1,2],[3,4]]              -> [[3,1],[4,2]]

Approaches:
  1. Copy into a new matrix       O(n^2) time, O(n^2) space
  2. Transpose + reverse rows  ⭐  O(n^2) time, O(1) space   <- go-to
  3. Rotate four cells at a time  O(n^2) time, O(1) space
"""

import copy


# ---------- Approach 1: Copy ----------
def rotate_copy(m: list[list[int]]) -> None:
    n = len(m)
    out = [[0] * n for _ in range(n)]
    for r in range(n):
        for c in range(n):
            out[c][n - 1 - r] = m[r][c]
    m[:] = out  # slice-assign so the caller sees it


# ---------- Approach 2: Transpose + Reverse ⭐ ----------
def rotate(m: list[list[int]]) -> None:
    n = len(m)
    for r in range(n):
        for c in range(r + 1, n):  # above the diagonal only
            m[r][c], m[c][r] = m[c][r], m[r][c]
    for row in m:
        row.reverse()


# ---------- Approach 3: Four-way Swap ----------
def rotate_four(m: list[list[int]]) -> None:
    n = len(m)
    for r in range(n // 2):  # rings
        for c in range(r, n - 1 - r):  # each cell on the ring's top edge
            m[r][c], m[c][n - 1 - r], m[n - 1 - r][n - 1 - c], m[n - 1 - c][r] = (
                m[n - 1 - c][r],          # left -> top
                m[r][c],                  # top -> right
                m[c][n - 1 - r],          # right -> bottom
                m[n - 1 - r][n - 1 - c],  # bottom -> left
            )


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        [[1, 2, 3], [4, 5, 6], [7, 8, 9]],
        [[5, 1, 9, 11], [2, 4, 8, 10], [13, 3, 6, 7], [15, 14, 12, 16]],
        [[1]],
        [[1, 2], [3, 4]],
    ]
    for t in tests:
        a, b, c = copy.deepcopy(t), copy.deepcopy(t), copy.deepcopy(t)
        rotate_copy(a)
        rotate(b)
        rotate_four(c)
        print("copy     :", a)
        print("transpose:", b)
        print("four-way :", c)
        print("---")

"""
Syntax notes (Python):
- m[:] = out replaces the contents of the caller's list; m = out would only rebind locally.
- Tuple assignment swaps cells: a[i][j], a[j][i] = a[j][i], a[i][j].
- copy.deepcopy copies nested lists; t[:] or list(t) would share the rows.
- One-liner alternative: m[:] = [list(row) for row in zip(*m[::-1])].
"""
