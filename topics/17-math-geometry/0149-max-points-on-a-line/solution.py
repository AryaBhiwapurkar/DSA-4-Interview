"""
0149. Max Points on a Line  |  Hard  |  Math & Geometry
Link: https://leetcode.com/problems/max-points-on-a-line/

Problem: Given distinct integer points, return the most that lie on one straight line.

Examples:
  [[1,1],[2,2],[3,3]]                          -> 3
  [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]        -> 4   (x + y = 5)
  [[0,0]]                                      -> 1
  [[1,1],[1,5],[1,-3],[2,2]]                   -> 3   (vertical x = 1)
  [[0,0],[94911151,94911150],[94911152,94911151]] -> 2   (outside LC range; float slopes would say 3)

Approaches:
  1. Every pair + cross-product check     O(n^3) time, O(1) space
  2. Anchor + gcd-normalised slope map ⭐  O(n^2 log C) time, O(n) space   <- go-to
"""

from collections import Counter
from math import gcd


# ---------- Approach 1: Every Pair + Collinearity ----------
def max_points_cubic(p: list[list[int]]) -> int:
    n = len(p)
    if n <= 2:
        return n
    best = 2
    for i in range(n):
        for j in range(i + 1, n):
            dx, dy = p[j][0] - p[i][0], p[j][1] - p[i][1]
            cnt = 2 + sum(  # cross product 0 <=> collinear
                dx * (p[k][1] - p[i][1]) == dy * (p[k][0] - p[i][0]) for k in range(j + 1, n))
            best = max(best, cnt)
    return best


# ---------- Approach 2: Anchor + Slope Map ⭐ ----------
def max_points(p: list[list[int]]) -> int:
    best = 1
    for i in range(len(p)):
        slopes: Counter[tuple[int, int]] = Counter()  # fresh map per anchor
        for j in range(i + 1, len(p)):
            dx, dy = p[j][0] - p[i][0], p[j][1] - p[i][1]
            g = gcd(dx, dy)  # > 0: points are distinct
            dx, dy = dx // g, dy // g
            if dx < 0 or (dx == 0 and dy < 0):  # one key per direction
                dx, dy = -dx, -dy
            slopes[(dx, dy)] += 1
            best = max(best, 1 + slopes[(dx, dy)])
    return best


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        [[1, 1], [2, 2], [3, 3]],
        [[1, 1], [3, 2], [5, 3], [4, 1], [2, 3], [1, 4]],
        [[0, 0]],
        [[1, 1], [1, 5], [1, -3], [2, 2]],
        [[0, 0], [94911151, 94911150], [94911152, 94911151]],
    ]
    for t in tests:
        print("cubic:", max_points_cubic(t))
        print("slope:", max_points(t))
        print("---")

"""
Syntax notes (Python):
- math.gcd(a, b) is always >= 0 and accepts negatives; gcd(0, k) = |k|.
- Exact division after gcd: dx // g is safe because g divides dx (sign is preserved).
- Tuples as Counter keys group equal slopes; floats like dy / dx would risk rounding collisions.
- sum(bool_generator) counts the True values.
"""
