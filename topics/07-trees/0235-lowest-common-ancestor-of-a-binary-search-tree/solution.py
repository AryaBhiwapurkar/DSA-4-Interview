"""
0235. Lowest Common Ancestor of a Binary Search Tree  |  Medium  |  Trees
Link: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/

Problem: In a BST, return the deepest node that has both p and q as
         descendants (a node is its own descendant).

Examples (level order, None = missing; answer printed as a value):
  [6,2,8,0,4,7,9,null,null,3,5], p 2, q 8  -> 6
  [6,2,8,0,4,7,9,null,null,3,5], p 2, q 4  -> 2
  [2,1],                         p 2, q 1  -> 2
  [6,2,8,0,4,7,9,null,null,3,5], p 3, q 5  -> 4

Approaches:
  1. Recursive descent        O(h) time, O(h) stack
  2. Iterative descent  ⭐     O(h) time, O(1) space   <- go-to
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: Recursive Descent ----------
def lca_recursive(root: TreeNode, p: TreeNode, q: TreeNode) -> TreeNode:
    if p.val < root.val and q.val < root.val:
        return lca_recursive(root.left, p, q)
    if p.val > root.val and q.val > root.val:
        return lca_recursive(root.right, p, q)
    return root  # split point (or root is p or q)


# ---------- Approach 2: Iterative Descent ⭐ ----------
def lowest_common_ancestor(root: TreeNode, p: TreeNode, q: TreeNode) -> TreeNode:
    lo, hi = min(p.val, q.val), max(p.val, q.val)
    while root:
        if hi < root.val:  # both smaller (strict: stop on equality)
            root = root.left
        elif lo > root.val:  # both larger
            root = root.right
        else:
            return root
    raise ValueError("p and q must exist in the tree")


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


def find(root: Optional[TreeNode], v: int) -> Optional[TreeNode]:  # BST lookup to get the node
    while root and root.val != v:
        root = root.left if v < root.val else root.right
    return root


if __name__ == "__main__":
    big = [6, 2, 8, 0, 4, 7, 9, None, None, 3, 5]
    for v, a, b in [(big, 2, 8), (big, 2, 4), ([2, 1], 2, 1), (big, 3, 5)]:
        root = build(v)
        p, q = find(root, a), find(root, b)
        print("recursive:", lca_recursive(root, p, q).val)
        print("iterative:", lowest_common_ancestor(root, p, q).val)
        print("---")

"""
Syntax notes (Python):
- Normalising to (lo, hi) turns "both smaller" into one comparison: hi < val.
- The driver's find() turns test values into the node objects LeetCode passes.
"""
