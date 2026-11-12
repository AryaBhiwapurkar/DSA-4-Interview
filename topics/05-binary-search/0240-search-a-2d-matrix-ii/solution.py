"""
0240. Search a 2D Matrix II  |  Medium  |  Binary Search
Link: https://leetcode.com/problems/search-a-2d-matrix-ii/

Problem: Rows sorted left->right, columns sorted top->bottom.
         Return whether target is in the matrix.

Examples:
  M (5x5 below), target = 5    -> True
  M,             target = 20   -> False
  [[-5]],        target = -5   -> True
  [[1,4],[2,5]], target = 2    -> True
  [[1,4],[2,5]], target = 3    -> False
  M,             target = 30   -> True    (bottom-right corner)
  M,             target = 0    -> False   (below everything)

Approaches:
  1. Scan everything             O(m n) time, O(1) space
  2. Binary search each row      O(m log n) time, O(1) space
  3. Staircase from top-right ⭐ O(m + n) time, O(1) space   <- go-to
"""

from bisect import bisect_left


# ---------- Approach 1: Scan Everything ----------
def search_matrix_brute(m: list[list[int]], target: int) -> bool:
    return any(target in row for row in m)


# ---------- Approach 2: Binary Search Each Row ----------
def search_matrix_rows(m: list[list[int]], target: int) -> bool:
    for row in m:
        i = bisect_left(row, target)
        if i < len(row) and row[i] == target:
            return True
    return False


# ---------- Approach 3: Staircase from Top-right ⭐ ----------
def search_matrix(m: list[list[int]], target: int) -> bool:
    r, c = 0, len(m[0]) - 1
    while r < len(m) and c >= 0:
        if m[r][c] == target:
            return True
        if m[r][c] > target:
            c -= 1  # whole column below is even bigger
        else:
            r += 1  # whole row to the left is even smaller
    return False


# ---------- Driver ----------
if __name__ == "__main__":
    M = [[1, 4, 7, 11, 15], [2, 5, 8, 12, 19], [3, 6, 9, 16, 22], [10, 13, 14, 17, 24], [18, 21, 23, 26, 30]]
    tests = [(M, 5), (M, 20), ([[-5]], -5), ([[1, 4], [2, 5]], 2), ([[1, 4], [2, 5]], 3), (M, 30), (M, 0)]
    for m, t in tests:
        print("brute    :", search_matrix_brute(m, t))
        print("rows     :", search_matrix_rows(m, t))
        print("staircase:", search_matrix(m, t))
        print("---")

"""
Syntax notes (Python):
- bisect_left returns an insertion index; check i < len and row[i] == target.
- any(generator) short-circuits on the first True.
- `x in list` is a linear scan; fine for the brute force only.
"""
