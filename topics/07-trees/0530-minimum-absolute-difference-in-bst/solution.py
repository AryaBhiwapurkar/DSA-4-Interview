"""
0530. Minimum Absolute Difference in BST  |  Easy  |  Trees
Link: https://leetcode.com/problems/minimum-absolute-difference-in-bst/

Problem: Minimum absolute difference between values of any two nodes.

Examples (level order, None = missing):
  [4,2,6,1,3]               -> 1
  [1,0,48,null,null,12,49]  -> 1
  [236,104,701,null,227,null,911]  -> 9   (closest pair 227, 236 isn't parent-child)

Approaches:
  1. Inorder list + adjacent gaps   O(n) time, O(n) space
  2. Inorder with prev  ⭐           O(n) time, O(h) space   <- go-to
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: Inorder List + Adjacent Gaps ----------
def get_minimum_difference_list(root: Optional[TreeNode]) -> int:
    vals: list[int] = []

    def collect(n: Optional[TreeNode]) -> None:
        if n:
            collect(n.left)
            vals.append(n.val)
            collect(n.right)

    collect(root)
    return min(b - a for a, b in zip(vals, vals[1:]))


# ---------- Approach 2: Inorder With prev ⭐ ----------
def get_minimum_difference(root: Optional[TreeNode]) -> int:
    prev: Optional[int] = None
    best = float("inf")

    def inorder(n: Optional[TreeNode]) -> None:
        nonlocal prev, best
        if not n:
            return
        inorder(n.left)
        if prev is not None:  # None = nothing seen yet
            best = min(best, n.val - prev)
        prev = n.val
        inorder(n.right)

    inorder(root)
    return int(best)


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
    for v in [[4, 2, 6, 1, 3], [1, 0, 48, None, None, 12, 49], [236, 104, 701, None, 227, None, 911]]:
        root = build(v)
        print("list:", get_minimum_difference_list(root))
        print("prev:", get_minimum_difference(root))
        print("---")

"""
Syntax notes (Python):
- zip(vals, vals[1:]) pairs each element with its successor.
- `nonlocal a, b` declares several outer variables at once.
"""
