"""
0543. Diameter of Binary Tree  |  Easy  |  Trees
Link: https://leetcode.com/problems/diameter-of-binary-tree/

Problem: Number of edges on the longest path between any two nodes.

Examples (level order, None = missing):
  [1,2,3,4,5]                     -> 3
  [1,2]                           -> 1
  [1]                             -> 0
  [1,2,null,3,4,5,null,null,6]    -> 4   (longest path avoids the root)

Approaches:
  1. Height per node                O(n^2) time, O(h) space
  2. Single DFS, global max  ⭐      O(n) time, O(h) space   <- go-to
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: Height Per Node ----------
def height(n: Optional[TreeNode]) -> int:
    return 1 + max(height(n.left), height(n.right)) if n else 0


def diameter_of_binary_tree_brute(root: Optional[TreeNode]) -> int:
    if not root:
        return 0
    through = height(root.left) + height(root.right)
    return max(through, diameter_of_binary_tree_brute(root.left), diameter_of_binary_tree_brute(root.right))


# ---------- Approach 2: Single DFS, Global Max ⭐ ----------
def diameter_of_binary_tree(root: Optional[TreeNode]) -> int:
    best = 0

    def dfs(n: Optional[TreeNode]) -> int:  # returns height in nodes
        nonlocal best
        if not n:
            return 0
        L, R = dfs(n.left), dfs(n.right)
        best = max(best, L + R)  # path bending here, in edges
        return 1 + max(L, R)  # parent can only use one branch

    dfs(root)
    return best


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
    for v in [[1, 2, 3, 4, 5], [1, 2], [1], [1, 2, None, 3, 4, 5, None, None, 6]]:
        root = build(v)
        print("brute :", diameter_of_binary_tree_brute(root))
        print("global:", diameter_of_binary_tree(root))
        print("---")

"""
Syntax notes (Python):
- `nonlocal best` lets the nested dfs rebind the outer variable.
- `A if cond else B` binds looser than +, so `1 + max(...) if n else 0`
  reads as `(1 + max(...)) if n else 0`.
"""
