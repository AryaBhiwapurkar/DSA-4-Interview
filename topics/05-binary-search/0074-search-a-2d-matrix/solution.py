"""
0074. Search a 2D Matrix  |  Medium  |  Binary Search
Link: https://leetcode.com/problems/search-a-2d-matrix/

Problem: Rows are sorted and each row starts after the previous row ends.
         Return whether target is in the matrix. O(log(m*n)).

Examples:
  [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target 3   -> True
  [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target 13  -> False
  [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target 60  -> True
  [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target 0   -> False
  [[1]], target 1                                     -> True
  [[1],[3]], target 3                                 -> True

Approaches:
  1. Scan everything         O(m*n) time, O(1) space
  2. Staircase (top-right)   O(m+n) time, O(1) space
  3. Flat binary search  ⭐   O(log(m*n)) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Scan Everything ----------
def search_matrix_brute(m: list[list[int]], target: int) -> bool:
    return any(target in row for row in m)


# ---------- Approach 2: Staircase From the Top-Right ----------
def search_matrix_staircase(m: list[list[int]], target: int) -> bool:
    r, c = 0, len(m[0]) - 1
    while r < len(m) and c >= 0:
        if m[r][c] == target:
            return True
        if m[r][c] > target:
            c -= 1  # everything below in this column is bigger too
        else:
            r += 1  # everything left in this row is smaller too
    return False


# ---------- Approach 3: Flat Binary Search ⭐ ----------
def search_matrix(m: list[list[int]], target: int) -> bool:
    cols = len(m[0])
    lo, hi = 0, len(m) * cols - 1
    while lo <= hi:
        mid = (lo + hi) // 2
        r, c = divmod(mid, cols)  # divide by COLUMNS
        if m[r][c] == target:
            return True
        if m[r][c] < target:
            lo = mid + 1
        else:
            hi = mid - 1
    return False


# ---------- Driver ----------
if __name__ == "__main__":
    big = [[1, 3, 5, 7], [10, 11, 16, 20], [23, 30, 34, 60]]
    tests = [(big, 3), (big, 13), (big, 60), (big, 0), ([[1]], 1), ([[1], [3]], 3)]
    for m, target in tests:
        print("brute    :", search_matrix_brute(m, target))
        print("staircase:", search_matrix_staircase(m, target))
        print("flat     :", search_matrix(m, target))
        print("---")

"""
Syntax notes (Python):
- divmod(k, cols) returns (row, col) in one call.
- any(gen) short-circuits on the first True.
- `x in row` is a linear scan of a list.
"""
