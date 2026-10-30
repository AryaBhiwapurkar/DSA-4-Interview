"""
0110. Balanced Binary Tree  |  Easy  |  Trees
Link: https://leetcode.com/problems/balanced-binary-tree/

Problem: Is every node's left/right subtree height difference <= 1?

Examples (level order, None = missing):
  [3,9,20,null,null,15,7]                -> True
  [1,2,2,3,3,null,null,4,4]              -> False
  []                                     -> True
  [1,2,2,3,null,null,3,4,null,null,4]    -> False  (root looks balanced, subtrees aren't)

Approaches:
  1. Top-down heights              O(n^2) time, O(h) space
  2. Bottom-up with -1 sentinel ⭐  O(n) time, O(h) space   <- go-to
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: Top-Down Heights ----------
def height(n: Optional[TreeNode]) -> int:
    return 1 + max(height(n.left), height(n.right)) if n else 0


def is_balanced_top_down(root: Optional[TreeNode]) -> bool:
    if not root:
        return True
    return (abs(height(root.left) - height(root.right)) <= 1
            and is_balanced_top_down(root.left) and is_balanced_top_down(root.right))


# ---------- Approach 2: Bottom-Up With -1 Sentinel ⭐ ----------
def is_balanced(root: Optional[TreeNode]) -> bool:
    def check(n: Optional[TreeNode]) -> int:  # height, or -1 if unbalanced
        if not n:
            return 0
        L = check(n.left)
        if L == -1:
            return -1  # propagate failure immediately
        R = check(n.right)
        if R == -1 or abs(L - R) > 1:
            return -1
        return 1 + max(L, R)

    return check(root) != -1


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
    tests = [[3, 9, 20, None, None, 15, 7], [1, 2, 2, 3, 3, None, None, 4, 4], [],
             [1, 2, 2, 3, None, None, 3, 4, None, None, 4]]
    for v in tests:
        root = build(v)
        print("topDown :", is_balanced_top_down(root))
        print("bottomUp:", is_balanced(root))
        print("---")

"""
Syntax notes (Python):
- Parentheses let a long boolean expression span lines without backslashes.
- A sentinel (-1) avoids returning a (balanced, height) tuple.
"""
