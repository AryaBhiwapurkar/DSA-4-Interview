"""
0226. Invert Binary Tree  |  Easy  |  Trees
Link: https://leetcode.com/problems/invert-binary-tree/

Problem: Mirror a binary tree (swap left/right at every node).

Examples (level order, None = missing):
  [4,2,7,1,3,6,9]  -> [4,7,2,9,6,3,1]
  [2,1,3]          -> [2,3,1]
  []               -> []
  [1,2]            -> [1,null,2]

Approaches:
  1. Recursive DFS  ⭐   O(n) time, O(h) space   <- go-to
  2. Iterative BFS      O(n) time, O(w) space
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: Recursive DFS ⭐ ----------
def invert_tree(root: Optional[TreeNode]) -> Optional[TreeNode]:
    if not root:
        return None
    root.left, root.right = invert_tree(root.right), invert_tree(root.left)  # RHS first: safe
    return root


# ---------- Approach 2: Iterative BFS ----------
def invert_tree_bfs(root: Optional[TreeNode]) -> Optional[TreeNode]:
    q = deque([root] if root else [])
    while q:
        n = q.popleft()
        n.left, n.right = n.right, n.left
        if n.left:
            q.append(n.left)
        if n.right:
            q.append(n.right)
    return root


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
    for v in [[4, 2, 7, 1, 3, 6, 9], [2, 1, 3], [], [1, 2]]:  # fresh tree per approach
        print("dfs:", serialize(invert_tree(build(v))))
        print("bfs:", serialize(invert_tree_bfs(build(v))))
        print("---")

"""
Syntax notes (Python):
- Tuple assignment evaluates both recursive calls before assigning, so
  `root.left, root.right = f(root.right), f(root.left)` is safe.
- collections.deque gives O(1) popleft for BFS; list.pop(0) is O(n).
- q.extend([a, b]) appends several items at once.
"""
