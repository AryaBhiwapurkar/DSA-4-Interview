"""
0098. Validate Binary Search Tree  |  Medium  |  Trees
Link: https://leetcode.com/problems/validate-binary-search-tree/

Problem: Is the tree a BST (left subtree strictly less, right strictly
         greater, at every node)?

Examples (level order, None = missing):
  [2,1,3]                   -> True
  [5,1,4,null,null,3,6]     -> False
  [5,4,6,null,null,3,7]     -> False  (3 violates the grandparent 5)
  [2,2,2]                   -> False  (duplicates)
  [2147483647]              -> True   (no INT_MAX sentinels)

Approaches:
  1. Inorder strictly increasing   O(n) time, O(h) space
  2. DFS with bounds  ⭐            O(n) time, O(h) space   <- go-to
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: Inorder Strictly Increasing ----------
def is_valid_bst_inorder(root: Optional[TreeNode]) -> bool:
    prev = float("-inf")

    def inorder(n: Optional[TreeNode]) -> bool:
        nonlocal prev
        if not n:
            return True
        if not inorder(n.left):
            return False
        if n.val <= prev:  # must strictly increase
            return False
        prev = n.val
        return inorder(n.right)

    return inorder(root)


# ---------- Approach 2: DFS With Bounds ⭐ ----------
def is_valid_bst(root: Optional[TreeNode]) -> bool:
    def valid(n: Optional[TreeNode], lo: float, hi: float) -> bool:  # open interval (lo, hi)
        if not n:
            return True
        if not lo < n.val < hi:
            return False
        return valid(n.left, lo, n.val) and valid(n.right, n.val, hi)

    return valid(root, float("-inf"), float("inf"))


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
    tests = [[2, 1, 3], [5, 1, 4, None, None, 3, 6], [5, 4, 6, None, None, 3, 7], [2, 2, 2], [2147483647]]
    for v in tests:
        root = build(v)
        print("inorder:", is_valid_bst_inorder(root))
        print("bounds :", is_valid_bst(root))
        print("---")

"""
Syntax notes (Python):
- Chained comparison `lo < x < hi` checks both bounds at once.
- float("inf") bounds avoid any sentinel clash with real values.
"""
