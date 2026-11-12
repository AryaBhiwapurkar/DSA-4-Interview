"""
0304. Range Sum Query 2D - Immutable  |  Medium  |  Arrays & Hashing
Link: https://leetcode.com/problems/range-sum-query-2d-immutable/

Problem: Fixed matrix, many queries: sum of the rectangle (r1,c1)..(r2,c2) inclusive.

Examples:
  matrix = [[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]]
  sumRegion(2,1,4,3) -> 8
  sumRegion(1,1,2,2) -> 11
  sumRegion(1,2,2,4) -> 12
  sumRegion(0,0,0,0) -> 3    (single cell)
  sumRegion(0,0,4,4) -> 58   (whole matrix)

Approaches:
  1. Loop over the rectangle   O(1) build, O(m*n) per query
  2. Row prefix sums           O(m*n) build, O(m) per query
  3. 2-D prefix sums  ⭐       O(m*n) build, O(1) per query   <- go-to
"""

from itertools import accumulate


# ---------- Approach 1: Loop ----------
class NumMatrixBrute:
    def __init__(self, matrix: list[list[int]]) -> None:
        self.a = matrix

    def sumRegion(self, r1: int, c1: int, r2: int, c2: int) -> int:
        return sum(sum(row[c1:c2 + 1]) for row in self.a[r1:r2 + 1])


# ---------- Approach 2: Row Prefix Sums ----------
class NumMatrixRows:
    def __init__(self, matrix: list[list[int]]) -> None:
        self.P = [list(accumulate(row, initial=0)) for row in matrix]

    def sumRegion(self, r1: int, c1: int, r2: int, c2: int) -> int:
        return sum(self.P[r][c2 + 1] - self.P[r][c1] for r in range(r1, r2 + 1))


# ---------- Approach 3: 2-D Prefix Sums ⭐ ----------
class NumMatrix:
    def __init__(self, matrix: list[list[int]]) -> None:
        R, C = len(matrix), len(matrix[0])
        P = [[0] * (C + 1) for _ in range(R + 1)]  # zero row/col padding
        for r in range(R):
            for c in range(C):
                P[r + 1][c + 1] = matrix[r][c] + P[r][c + 1] + P[r + 1][c] - P[r][c]
        self.P = P

    def sumRegion(self, r1: int, c1: int, r2: int, c2: int) -> int:
        P = self.P
        return P[r2 + 1][c2 + 1] - P[r1][c2 + 1] - P[r2 + 1][c1] + P[r1][c1]  # add back the corner


# ---------- Driver ----------
if __name__ == "__main__":
    m = [[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]
    b, rw, p = NumMatrixBrute(m), NumMatrixRows(m), NumMatrix(m)
    for q in [(2, 1, 4, 3), (1, 1, 2, 2), (1, 2, 2, 4), (0, 0, 0, 0), (0, 0, 4, 4)]:
        print("brute:", b.sumRegion(*q))
        print("rows :", rw.sumRegion(*q))
        print("2-D  :", p.sumRegion(*q))
        print("---")

"""
Syntax notes (Python):
- [[0] * (C + 1) for _ in range(R + 1)] builds independent rows (never [[0] * C] * R).
- f(*q) unpacks a tuple into positional arguments.
- A local alias (P = self.P) shortens repeated attribute lookups.
"""
