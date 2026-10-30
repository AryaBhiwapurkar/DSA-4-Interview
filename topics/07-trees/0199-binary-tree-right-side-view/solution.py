"""
0199. Binary Tree Right Side View  |  Medium  |  Trees
Link: https://leetcode.com/problems/binary-tree-right-side-view/

Problem: Values visible from the right side, top to bottom.

Examples (level order, None = missing):
  [1,2,3,null,5,null,4]        -> [1,3,4]
  [1,2,3,4,null,null,null,5]   -> [1,3,4,5]
  [1,null,3]                   -> [1,3]
  []                           -> []

Approaches:
  1. BFS, last per level  ⭐   O(n) time, O(w) space   <- go-to
  2. DFS right-first          O(n) time, O(h) space
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: BFS, Last per Level ⭐ ----------
def right_side_view(root: Optional[TreeNode]) -> list[int]:
    res: list[int] = []
    q = deque([root] if root else [])
    while q:
        res.append(q[-1].val)  # queue holds exactly one level: last = rightmost
        for _ in range(len(q)):
            n = q.popleft()
            if n.left:
                q.append(n.left)
            if n.right:
                q.append(n.right)
    return res


# ---------- Approach 2: DFS Right-First ----------
def right_side_view_dfs(root: Optional[TreeNode]) -> list[int]:
    res: list[int] = []

    def dfs(n: Optional[TreeNode], depth: int) -> None:
        if not n:
            return
        if depth == len(res):  # first node seen at this depth
            res.append(n.val)
        dfs(n.right, depth + 1)  # right first
        dfs(n.left, depth + 1)

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
    for v in [[1, 2, 3, None, 5, None, 4], [1, 2, 3, 4, None, None, None, 5], [1, None, 3], []]:
        root = build(v)
        print("bfs:", right_side_view(root))
        print("dfs:", right_side_view_dfs(root))
        print("---")

"""
Syntax notes (Python):
- q[-1] peeks at the back of a deque (the rightmost node of the level).
- Right-first DFS + "depth == len(res)" records one node per depth.
"""
