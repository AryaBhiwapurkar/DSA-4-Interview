"""
0124. Binary Tree Maximum Path Sum  |  Hard  |  Trees
Link: https://leetcode.com/problems/binary-tree-maximum-path-sum/

Problem: Maximum sum of any non-empty path (connected nodes, each used
         once, not necessarily through the root).

Examples (level order, None = missing):
  [1,2,3]                    -> 6
  [-10,9,20,null,null,15,7]  -> 42
  [-3]                       -> -3   (all negative)
  [2,-1]                     -> 2

Approaches:
  1. Every node as top, recomputing gains   O(n^2) time, O(h) space
  2. Single DFS, global max  ⭐              O(n) time, O(h) space   <- go-to
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: Every Node as Top ----------
def down(n: Optional[TreeNode]) -> int:  # best path starting at n going down
    return n.val + max(0, down(n.left), down(n.right)) if n else 0


def max_path_sum_brute(root: Optional[TreeNode]) -> float:
    if not root:
        return float("-inf")
    here = root.val + max(0, down(root.left)) + max(0, down(root.right))
    return max(here, max_path_sum_brute(root.left), max_path_sum_brute(root.right))


# ---------- Approach 2: Single DFS, Global Max ⭐ ----------
def max_path_sum(root: Optional[TreeNode]) -> int:
    best = float("-inf")  # not 0: all-negative trees

    def gain(n: Optional[TreeNode]) -> int:
        nonlocal best
        if not n:
            return 0
        L = max(0, gain(n.left))  # a negative branch is never worth taking
        R = max(0, gain(n.right))
        best = max(best, n.val + L + R)  # path bending at n
        return n.val + max(L, R)  # parent can extend only one side

    gain(root)
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
    for v in [[1, 2, 3], [-10, 9, 20, None, None, 15, 7], [-3], [2, -1]]:
        root = build(v)
        print("brute :", int(max_path_sum_brute(root)))
        print("global:", max_path_sum(root))
        print("---")

"""
Syntax notes (Python):
- float("-inf") as the starting best; convert back with int() at the end.
- max() takes any number of arguments: max(0, a, b).
"""
