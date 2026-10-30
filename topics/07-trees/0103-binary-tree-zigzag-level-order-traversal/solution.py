"""
0103. Binary Tree Zigzag Level Order Traversal  |  Medium  |  Trees
Link: https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/

Problem: Level order, alternating left-to-right and right-to-left.

Examples (level order, None = missing):
  [3,9,20,null,null,15,7]  -> [[3],[20,9],[15,7]]
  [1]                      -> [[1]]
  []                       -> []
  [1,2,3,4,null,null,5]    -> [[1],[3,2],[4,5]]

Approaches:
  1. BFS + index by direction  ⭐   O(n) time, O(w) space   <- go-to
  2. BFS + reverse odd levels       O(n) time, O(w) space
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: BFS + Index by Direction ⭐ ----------
def zigzag_level_order(root: Optional[TreeNode]) -> list[list[int]]:
    res: list[list[int]] = []
    q = deque([root] if root else [])
    left_to_right = True
    while q:
        sz = len(q)
        level = [0] * sz
        for i in range(sz):
            n = q.popleft()
            level[i if left_to_right else sz - 1 - i] = n.val  # BFS order stays normal
            if n.left:
                q.append(n.left)
            if n.right:
                q.append(n.right)
        res.append(level)
        left_to_right = not left_to_right
    return res


# ---------- Approach 2: BFS + Reverse Odd Levels ----------
def zigzag_level_order_reverse(root: Optional[TreeNode]) -> list[list[int]]:
    res: list[list[int]] = []
    q = deque([root] if root else [])
    while q:
        level = []
        for _ in range(len(q)):
            n = q.popleft()
            level.append(n.val)
            if n.left:
                q.append(n.left)
            if n.right:
                q.append(n.right)
        res.append(level[::-1] if len(res) % 2 else level)
    return res


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


if __name__ == "__main__":
    for v in [[3, 9, 20, None, None, 15, 7], [1], [], [1, 2, 3, 4, None, None, 5]]:
        root = build(v)
        print("index  :", zigzag_level_order(root))
        print("reverse:", zigzag_level_order_reverse(root))
        print("---")

"""
Syntax notes (Python):
- level[::-1] returns a reversed copy.
- `[0] * sz` pre-sizes a list for index writes.
"""
