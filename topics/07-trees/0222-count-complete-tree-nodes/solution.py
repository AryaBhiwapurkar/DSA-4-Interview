"""
0222. Count Complete Tree Nodes  |  Easy  |  Trees
Link: https://leetcode.com/problems/count-complete-tree-nodes/

Problem: Count the nodes of a complete binary tree in less than O(n).

Examples (level order, None = missing):
  [1,2,3,4,5,6]    -> 6
  []               -> 0
  [1]              -> 1
  [1,2,3,4,5,6,7]  -> 7   (perfect: answered at the root)
  [1,2,3,4]        -> 4

Approaches:
  1. Plain DFS count               O(n) time, O(h) space
  2. Spine heights + recursion  ⭐  O(log^2 n) time, O(log n) space   <- go-to
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: Plain DFS Count ----------
def count_nodes_dfs(root: Optional[TreeNode]) -> int:
    return 1 + count_nodes_dfs(root.left) + count_nodes_dfs(root.right) if root else 0


# ---------- Approach 2: Spine Heights + Recursion ⭐ ----------
def count_nodes(root: Optional[TreeNode]) -> int:
    if not root:
        return 0
    lh, rh, n = 0, 0, root
    while n:  # walk spines only: O(log n)
        lh += 1
        n = n.left
    n = root
    while n:
        rh += 1
        n = n.right
    if lh == rh:
        return (1 << lh) - 1  # perfect tree
    return 1 + count_nodes(root.left) + count_nodes(root.right)  # one side is perfect


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
    for v in [[1, 2, 3, 4, 5, 6], [], [1], [1, 2, 3, 4, 5, 6, 7], [1, 2, 3, 4]]:
        root = build(v)
        print("dfs   :", count_nodes_dfs(root))
        print("spines:", count_nodes(root))
        print("---")

"""
Syntax notes (Python):
- (1 << h) - 1 equals 2**h - 1.
- A conditional expression as the whole return keeps the base case on one line.
"""
