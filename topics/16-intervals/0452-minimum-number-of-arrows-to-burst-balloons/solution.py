"""
0452. Minimum Number of Arrows to Burst Balloons  |  Medium  |  Intervals
Link: https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/

Problem: Each balloon spans [x_start, x_end]. A vertical arrow at x bursts every
         balloon with x_start <= x <= x_end. Fewest arrows to burst them all.

Examples:
  [[10,16],[2,8],[1,6],[7,12]]       -> 2
  [[1,2],[3,4],[5,6],[7,8]]          -> 4
  [[1,2],[2,3],[3,4],[4,5]]          -> 2
  [[-2147483646,-2147483645],[2147483646,2147483647]] -> 2
  [[1,10],[2,3],[4,5]]               -> 2

Approaches:
  1. Sort by start, shrink the shared window   O(n log n) time, O(1) extra
  2. Sort by end, shoot at the earliest end  ⭐  O(n log n) time, O(1) extra   <- go-to
"""


# ---------- Approach 1: Sort by Start ----------
def find_min_arrow_shots_start(points: list[list[int]]) -> int:
    pts = sorted(points)
    arrows, end = 1, pts[0][1]  # end: rightmost x that still hits the whole group
    for s, e in pts[1:]:
        if s > end:  # can't join the group: new arrow
            arrows += 1
            end = e
        else:
            end = min(end, e)  # group's common window shrinks
    return arrows


# ---------- Approach 2: Sort by End ⭐ ----------
def find_min_arrow_shots(points: list[list[int]]) -> int:
    arrows, arrow_x = 0, None
    for s, e in sorted(points, key=lambda p: p[1]):
        if arrow_x is None or s > arrow_x:  # last arrow misses this balloon
            arrows += 1
            arrow_x = e  # shoot as far right as this balloon allows
    return arrows


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        [[10, 16], [2, 8], [1, 6], [7, 12]],
        [[1, 2], [3, 4], [5, 6], [7, 8]],
        [[1, 2], [2, 3], [3, 4], [4, 5]],
        [[-2147483646, -2147483645], [2147483646, 2147483647]],
        [[1, 10], [2, 3], [4, 5]],
    ]
    for t in tests:
        print("start:", find_min_arrow_shots_start(t))
        print("end  :", find_min_arrow_shots(t))
        print("---")

"""
Syntax notes (Python):
- key=lambda p: p[1] sorts by end; Python ints can't overflow in comparisons.
- `arrow_x is None` marks "no arrow yet" without picking a magic number.
- min(end, e) narrows the window every balloon in the group shares.
"""
