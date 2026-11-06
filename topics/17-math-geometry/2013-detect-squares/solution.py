"""
2013. Detect Squares  |  Medium  |  Math & Geometry
Link: https://leetcode.com/problems/detect-squares/

Problem: add(point) stores a point (duplicates allowed). count(point) returns how
         many ways to pick 3 stored points that form a positive-area, axis-aligned
         square with the query point.

Examples:
  add(3,10) add(11,2) add(3,2)
  count(11,10) -> 1
  count(14,8)  -> 0
  add(11,2)
  count(11,10) -> 2      (two copies of (11,2))
  --- extra: squares on both sides of the query ---
  add(0,0) add(0,1) add(1,0) add(2,0) add(2,1)
  count(1,1)   -> 2      (left square uses x=0, right square uses x=2)
  count(5,5)   -> 0

Approaches:
  1. Scan diagonal candidates  ⭐   add O(1), count O(distinct points)   <- go-to
  2. Scan the query's column        add O(1), count O(points with x = qx)
"""

from collections import Counter, defaultdict


# ---------- Approach 1: Diagonal Candidates ⭐ ----------
class DetectSquares:
    def __init__(self) -> None:
        self.cnt: Counter[tuple[int, int]] = Counter()

    def add(self, point: list[int]) -> None:
        self.cnt[tuple(point)] += 1

    def count(self, point: list[int]) -> int:
        qx, qy = point
        total = 0
        for (x, y), c in self.cnt.items():
            if x == qx or abs(x - qx) != abs(y - qy):  # must be a true diagonal
                continue
            total += c * self.cnt[(qx, y)] * self.cnt[(x, qy)]
        return total


# ---------- Approach 2: Query's Column ----------
class DetectSquaresColumn:
    def __init__(self) -> None:
        self.by_x: defaultdict[int, Counter[int]] = defaultdict(Counter)  # x -> (y -> count)

    def add(self, point: list[int]) -> None:
        self.by_x[point[0]][point[1]] += 1

    def _get(self, x: int, y: int) -> int:
        col = self.by_x.get(x)
        return col[y] if col else 0

    def count(self, point: list[int]) -> int:
        qx, qy = point
        col = self.by_x.get(qx)
        if not col:
            return 0
        total = 0
        for y, c in col.items():
            d = abs(y - qy)
            if d == 0:
                continue
            for x in (qx - d, qx + d):  # square to the left and to the right
                total += c * self._get(x, qy) * self._get(x, y)
        return total


# ---------- Driver ----------
def run(cls: type, name: str) -> None:
    print(name)
    ds = cls()
    for p in ([3, 10], [11, 2], [3, 2]):
        ds.add(p)
    print(ds.count([11, 10]))  # 1
    print(ds.count([14, 8]))  # 0
    ds.add([11, 2])
    print(ds.count([11, 10]))  # 2

    e = cls()
    for p in ([0, 0], [0, 1], [1, 0], [2, 0], [2, 1]):
        e.add(p)
    print(e.count([1, 1]))  # 2
    print(e.count([5, 5]))  # 0
    print("---")


if __name__ == "__main__":
    run(DetectSquares, "diagonal:")
    run(DetectSquaresColumn, "column:")

"""
Syntax notes (Python):
- Counter returns 0 for missing keys on read without inserting them (unlike defaultdict).
- Tuples are hashable, so they work as dict keys; lists don't.
- defaultdict(Counter) builds nested counts: d[x][y] += 1.
"""
