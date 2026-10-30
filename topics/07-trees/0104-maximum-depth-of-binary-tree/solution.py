"""
0104. Maximum Depth of Binary Tree  |  Easy  |  Trees
Link: https://leetcode.com/problems/maximum-depth-of-binary-tree/

Problem: Number of nodes on the longest root-to-leaf path.

Examples (level order, None = missing):
  [3,9,20,null,null,15,7]  -> 3
  [1,null,2]               -> 2
  []                       -> 0
  [1]                      -> 1

Approaches:
  1. Recursive DFS  ⭐   O(n) time, O(h) space   <- go-to
  2. BFS level count    O(n) time, O(w) space
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: Recursive DFS ⭐ ----------
def max_depth(root: Optional[TreeNode]) -> int:
    if not root:
        return 0
    return 1 + max(max_depth(root.left), max_depth(root.right))


# ---------- Approach 2: BFS Level Count ----------
def max_depth_bfs(root: Optional[TreeNode]) -> int:
    if not root:
        return 0
    q, depth = deque([root]), 0
    while q:
        depth += 1
        for _ in range(len(q)):  # exactly one level per iteration
            n = q.popleft()
            if n.left:
                q.append(n.left)
            if n.right:
                q.append(n.right)
    return depth


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
    for v in [[3, 9, 20, None, None, 15, 7], [1, None, 2], [], [1]]:
        root = build(v)
        print("dfs:", max_depth(root))
        print("bfs:", max_depth_bfs(root))
        print("---")

"""
Syntax notes (Python):
- range(len(q)) is evaluated once, so appends during the loop don't
  extend the current level.
- For very deep trees: sys.setrecursionlimit(10**5) or use the BFS.
"""
