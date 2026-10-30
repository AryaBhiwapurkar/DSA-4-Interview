"""
0637. Average of Levels in Binary Tree  |  Easy  |  Trees
Link: https://leetcode.com/problems/average-of-levels-in-binary-tree/

Problem: Average value of the nodes on each level, top to bottom.

Examples (level order, None = missing):
  [3,9,20,null,null,15,7]                  -> [3.00000,14.50000,11.00000]
  [3,9,20,15,7]                            -> [3.00000,14.50000,11.00000]
  [2147483647,2147483647,2147483647]       -> [2147483647.00000,2147483647.00000]

Approaches:
  1. BFS with level sum  ⭐          O(n) time, O(w) space   <- go-to
  2. DFS (sum, count) per depth      O(n) time, O(h) space
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: BFS With Level Sum ⭐ ----------
def average_of_levels(root: Optional[TreeNode]) -> list[float]:
    res: list[float] = []
    q = deque([root] if root else [])
    while q:
        sz, total = len(q), 0
        for _ in range(sz):
            n = q.popleft()
            total += n.val
            if n.left:
                q.append(n.left)
            if n.right:
                q.append(n.right)
        res.append(total / sz)
    return res


# ---------- Approach 2: DFS (sum, count) per Depth ----------
def average_of_levels_dfs(root: Optional[TreeNode]) -> list[float]:
    sums: list[int] = []
    cnts: list[int] = []

    def dfs(n: Optional[TreeNode], d: int) -> None:
        if not n:
            return
        if d == len(sums):
            sums.append(0)
            cnts.append(0)
        sums[d] += n.val
        cnts[d] += 1
        dfs(n.left, d + 1)
        dfs(n.right, d + 1)

    dfs(root, 0)
    return [s / c for s, c in zip(sums, cnts)]


# ---------- Driver ----------
def build(vals: list[Optional[int]]) -> Optional[TreeNode]:  # LeetCode level order
    if not vals or vals[0] is None:
        return None
    root = TreeNode(vals[0])
    q = deque([root])
    for i in range(1, len(vals), 2):
        n = q.popleft()
        if vals[i] is not None:
            n.left = TreeNode(vals[i])
            q.append(n.left)
        if i + 1 < len(vals) and vals[i + 1] is not None:
            n.right = TreeNode(vals[i + 1])
            q.append(n.right)
    return root


def serialize(root: Optional[TreeNode]) -> str:  # level order, trailing nulls trimmed
    out, q = [], deque([root])
    while q:
        n = q.popleft()
        out.append(str(n.val) if n else "null")
        if n:
            q.extend([n.left, n.right])
    while out and out[-1] == "null":
        out.pop()
    return "[" + ",".join(out) + "]"


def show(v: list[float]) -> str:
    return "[" + ",".join(f"{x:.5f}" for x in v) + "]"


if __name__ == "__main__":
    for v in [[3, 9, 20, None, None, 15, 7], [3, 9, 20, 15, 7], [2147483647, 2147483647, 2147483647]]:
        root = build(v)
        print("bfs:", show(average_of_levels(root)))
        print("dfs:", show(average_of_levels_dfs(root)))
        print("---")

"""
Syntax notes (Python):
- Python ints don't overflow, and / always returns a float.
- f"{x:.5f}" formats with five decimals.
"""
