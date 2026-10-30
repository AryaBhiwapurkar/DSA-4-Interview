"""
0427. Construct Quad Tree  |  Medium  |  Trees
Link: https://leetcode.com/problems/construct-quad-tree/

Problem: Build the quad tree of an n x n 0/1 grid (n a power of 2).
         Output: level order of [isLeaf, val] with null for missing children.

Examples:
  [[0,1],[1,0]]       -> [[0,1],[1,0],[1,1],[1,1],[1,0]]
  8x8 (see README)    -> [[0,1],[1,1],[0,1],[1,1],[1,0],null,null,null,null,[1,0],[1,0],[1,1],[1,1]]
  [[1]]               -> [[1,1]]
  [[0,0],[0,0]]       -> [[1,0]]

Approaches:
  1. Check then split  ⭐          O(n^2 log n) time, O(log n) stack   <- go-to
  2. Split then merge (bottom-up)  O(n^2) time, O(log n) stack
"""

from collections import deque
from typing import Optional


class Node:
    def __init__(self, val: bool, isLeaf: bool, topLeft: Optional["Node"] = None, topRight: Optional["Node"] = None,
                 bottomLeft: Optional["Node"] = None, bottomRight: Optional["Node"] = None):
        self.val, self.isLeaf = val, isLeaf
        self.topLeft, self.topRight, self.bottomLeft, self.bottomRight = topLeft, topRight, bottomLeft, bottomRight


# ---------- Approach 1: Check Then Split ⭐ ----------
def construct(grid: list[list[int]]) -> Node:
    def go(r: int, c: int, size: int) -> Node:
        first = grid[r][c]
        if all(grid[i][j] == first for i in range(r, r + size) for j in range(c, c + size)):
            return Node(bool(first), True)
        h = size // 2  # TL, TR, BL, BR: rows first, then columns
        return Node(True, False, go(r, c, h), go(r, c + h, h), go(r + h, c, h), go(r + h, c + h, h))

    return go(0, 0, len(grid))


# ---------- Approach 2: Split Then Merge ----------
def construct_merge(grid: list[list[int]]) -> Node:
    def go(r: int, c: int, size: int) -> Node:
        if size == 1:
            return Node(bool(grid[r][c]), True)
        h = size // 2
        kids = [go(r, c, h), go(r, c + h, h), go(r + h, c, h), go(r + h, c + h, h)]
        if all(k.isLeaf for k in kids) and len({k.val for k in kids}) == 1:
            return Node(kids[0].val, True)  # four equal leaves collapse into one
        return Node(True, False, *kids)

    return go(0, 0, len(grid))


# ---------- Driver ----------
def serialize(root: Optional[Node]) -> str:  # LeetCode format: level order of [isLeaf,val]
    out, q = [], deque([root])
    while q:
        n = q.popleft()
        if not n:
            out.append("null")
            continue
        out.append(f"[{int(n.isLeaf)},{int(n.val)}]")
        q.extend([n.topLeft, n.topRight, n.bottomLeft, n.bottomRight])
    while out and out[-1] == "null":
        out.pop()
    return "[" + ",".join(out) + "]"


if __name__ == "__main__":
    tests = [
        [[0, 1], [1, 0]],
        [[1, 1, 1, 1, 0, 0, 0, 0], [1, 1, 1, 1, 0, 0, 0, 0], [1, 1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1, 1, 1],
         [1, 1, 1, 1, 0, 0, 0, 0], [1, 1, 1, 1, 0, 0, 0, 0], [1, 1, 1, 1, 0, 0, 0, 0], [1, 1, 1, 1, 0, 0, 0, 0]],
        [[1]],
        [[0, 0], [0, 0]],
    ]
    for g in tests:
        print("split:", serialize(construct(g)))
        print("merge:", serialize(construct_merge(g)))
        print("---")

"""
Syntax notes (Python):
- all(generator) short-circuits on the first mismatch.
- len({set comprehension}) == 1 checks that all values are equal.
- Node(..., *kids) unpacks a list into positional arguments.
"""
