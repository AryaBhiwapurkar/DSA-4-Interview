"""
0054. Spiral Matrix  |  Medium  |  Math & Geometry
Link: https://leetcode.com/problems/spiral-matrix/

Problem: Return all elements of an m x n matrix in clockwise spiral order.

Examples:
  [[1,2,3],[4,5,6],[7,8,9]]             -> [1,2,3,6,9,8,7,4,5]
  [[1,2,3,4],[5,6,7,8],[9,10,11,12]]    -> [1,2,3,4,8,12,11,10,9,5,6,7]
  [[1,2,3]]                             -> [1,2,3]
  [[1],[2],[3]]                         -> [1,2,3]
  [[7]]                                 -> [7]

Approaches:
  1. Direction vectors + visited grid   O(m*n) time, O(m*n) space
  2. Shrinking boundaries  ⭐            O(m*n) time, O(1) extra   <- go-to
"""


# ---------- Approach 1: Direction Vectors ----------
def spiral_order_visited(mat: list[list[int]]) -> list[int]:
    m, n = len(mat), len(mat[0])
    seen = [[False] * n for _ in range(m)]
    dirs = [(0, 1), (1, 0), (0, -1), (-1, 0)]  # right, down, left, up
    out: list[int] = []
    r = c = d = 0
    for _ in range(m * n):
        out.append(mat[r][c])
        seen[r][c] = True
        nr, nc = r + dirs[d][0], c + dirs[d][1]
        if not (0 <= nr < m and 0 <= nc < n) or seen[nr][nc]:
            d = (d + 1) % 4  # turn right
            nr, nc = r + dirs[d][0], c + dirs[d][1]
        r, c = nr, nc
    return out


# ---------- Approach 2: Shrinking Boundaries ⭐ ----------
def spiral_order(mat: list[list[int]]) -> list[int]:
    top, bottom, left, right = 0, len(mat) - 1, 0, len(mat[0]) - 1
    out: list[int] = []
    while top <= bottom and left <= right:
        out.extend(mat[top][c] for c in range(left, right + 1))
        top += 1
        out.extend(mat[r][right] for r in range(top, bottom + 1))
        right -= 1
        if top <= bottom:  # a row is still left
            out.extend(mat[bottom][c] for c in range(right, left - 1, -1))
            bottom -= 1
        if left <= right:  # a column is still left
            out.extend(mat[r][left] for r in range(bottom, top - 1, -1))
            left += 1
    return out


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        [[1, 2, 3], [4, 5, 6], [7, 8, 9]],
        [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]],
        [[1, 2, 3]],
        [[1], [2], [3]],
        [[7]],
    ]
    for t in tests:
        print("visited :", spiral_order_visited(t))
        print("boundary:", spiral_order(t))
        print("---")

"""
Syntax notes (Python):
- 0 <= nr < m chains comparisons for a bounds check.
- out.extend(gen) appends every item a generator yields.
- range(right, left - 1, -1) walks backwards inclusive of left.
- Peel-and-rotate one-liner: res += mat.pop(0); mat = [list(r) for r in zip(*mat)][::-1].
"""
