"""
0102. Binary Tree Level Order Traversal  |  Medium  |  Trees
Link: https://leetcode.com/problems/binary-tree-level-order-traversal/

Problem: Return node values level by level, left to right.

Examples (level order, None = missing):
  [3,9,20,null,null,15,7]  -> [[3],[9,20],[15,7]]
  [1]                      -> [[1]]
  []                       -> []
  [1,2,null,3]             -> [[1],[2],[3]]

Approaches:
  1. BFS with level size  ⭐   O(n) time, O(w) space   <- go-to
  2. DFS with depth           O(n) time, O(h) space
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: BFS With Level Size ⭐ ----------
def level_order(root: Optional[TreeNode]) -> list[list[int]]:
    res: list[list[int]] = []
    q = deque([root] if root else [])
    while q:
        level = []
        for _ in range(len(q)):  # snapshot: exactly this level
            n = q.popleft()
            level.append(n.val)
            if n.left:
                q.append(n.left)
            if n.right:
                q.append(n.right)
        res.append(level)
    return res


# ---------- Approach 2: DFS With Depth ----------
def level_order_dfs(root: Optional[TreeNode]) -> list[list[int]]:
    res: list[list[int]] = []

    def dfs(n: Optional[TreeNode], depth: int) -> None:
        if not n:
            return
        if depth == len(res):  # first visit to this depth
            res.append([])
        res[depth].append(n.val)
        dfs(n.left, depth + 1)  # left first keeps left-to-right order
        dfs(n.right, depth + 1)

    dfs(root, 0)
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
    for v in [[3, 9, 20, None, None, 15, 7], [1], [], [1, 2, None, 3]]:
        root = build(v)
        print("bfs:", level_order(root))
        print("dfs:", level_order_dfs(root))
        print("---")

"""
Syntax notes (Python):
- deque([root] if root else []) avoids queueing None for an empty tree.
- range(len(q)) is evaluated once, so it's the level-size snapshot.
"""
