"""
0073. Set Matrix Zeroes  |  Medium  |  Math & Geometry
Link: https://leetcode.com/problems/set-matrix-zeroes/

Problem: For every 0 in an m x n matrix, set its whole row and column to 0, in place.

Examples:
  [[1,1,1],[1,0,1],[1,1,1]]         -> [[1,0,1],[0,0,0],[1,0,1]]
  [[0,1,2,0],[3,4,5,2],[1,3,1,5]]   -> [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
  [[1,0],[1,1]]                     -> [[0,0],[1,0]]
  [[1],[0]]                         -> [[0],[0]]
  [[5]]                             -> [[5]]

Approaches:
  1. Copy the matrix                O(m*n) time, O(m*n) space
  2. Row and column sets            O(m*n) time, O(m+n) space
  3. First row/col markers  ⭐      O(m*n) time, O(1) space   <- go-to
"""

import copy


# ---------- Approach 1: Copy ----------
def set_zeroes_copy(mat: list[list[int]]) -> None:
    orig = copy.deepcopy(mat)
    m, n = len(mat), len(mat[0])
    for i in range(m):
        for j in range(n):
            if orig[i][j] == 0:  # read the copy, write the real one
                for c in range(n):
                    mat[i][c] = 0
                for r in range(m):
                    mat[r][j] = 0


# ---------- Approach 2: Row and Column Sets ----------
def set_zeroes_sets(mat: list[list[int]]) -> None:
    rows = {i for i, row in enumerate(mat) if 0 in row}
    cols = {j for row in mat for j, v in enumerate(row) if v == 0}
    for i, row in enumerate(mat):
        for j in range(len(row)):
            if i in rows or j in cols:
                row[j] = 0


# ---------- Approach 3: First Row/Col Markers ⭐ ----------
def set_zeroes(mat: list[list[int]]) -> None:
    m, n = len(mat), len(mat[0])
    col0 = False  # mat[0][0] already flags row 0
    for i in range(m):
        for j in range(n):
            if mat[i][j] == 0:
                mat[i][0] = 0  # row i flag
                if j == 0:
                    col0 = True
                else:
                    mat[0][j] = 0  # column j flag
    for i in range(1, m):  # inner cells first: flags still intact
        for j in range(1, n):
            if mat[i][0] == 0 or mat[0][j] == 0:
                mat[i][j] = 0
    if mat[0][0] == 0:
        for j in range(n):
            mat[0][j] = 0
    if col0:
        for i in range(m):
            mat[i][0] = 0


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        [[1, 1, 1], [1, 0, 1], [1, 1, 1]],
        [[0, 1, 2, 0], [3, 4, 5, 2], [1, 3, 1, 5]],
        [[1, 0], [1, 1]],
        [[1], [0]],
        [[5]],
    ]
    for t in tests:
        a, b, c = copy.deepcopy(t), copy.deepcopy(t), copy.deepcopy(t)
        set_zeroes_copy(a)
        set_zeroes_sets(b)
        set_zeroes(c)
        print("copy   :", a)
        print("sets   :", b)
        print("markers:", c)
        print("---")

"""
Syntax notes (Python):
- Set comprehensions: {i for i, row in enumerate(mat) if 0 in row}.
- `0 in row` is a linear scan of a list.
- Mutating row[j] through `for row in mat` changes the matrix (rows are shared references).
"""
