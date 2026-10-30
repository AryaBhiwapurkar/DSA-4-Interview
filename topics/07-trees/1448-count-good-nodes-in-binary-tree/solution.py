"""
1448. Count Good Nodes in Binary Tree  |  Medium  |  Trees
Link: https://leetcode.com/problems/count-good-nodes-in-binary-tree/

Problem: A node is good if no node on its root path is greater. Count them.

Examples (level order, None = missing):
  [3,1,4,3,null,1,5]  -> 4
  [3,3,null,4,2]      -> 3
  [1]                 -> 1
  [-1,-2,-3]          -> 1   (negatives: don't start max at 0)

Approaches:
  1. DFS with path max  ⭐     O(n) time, O(h) space   <- go-to
  2. BFS with (node, max)     O(n) time, O(w) space
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: DFS With Path Max ⭐ ----------
def good_nodes(root: Optional[TreeNode]) -> int:
    def dfs(n: Optional[TreeNode], mx: float) -> int:
        if not n:
            return 0
        good = 1 if n.val >= mx else 0  # >= : equal values are good
        mx = max(mx, n.val)
        return good + dfs(n.left, mx) + dfs(n.right, mx)

    return dfs(root, float("-inf"))


# ---------- Approach 2: BFS With (node, max) ----------
def good_nodes_bfs(root: Optional[TreeNode]) -> int:
    count = 0
    q = deque([(root, float("-inf"))] if root else [])
    while q:
        n, mx = q.popleft()
        if n.val >= mx:
            count += 1
        nm = max(mx, n.val)
        if n.left:
            q.append((n.left, nm))
        if n.right:
            q.append((n.right, nm))
    return count


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
    for v in [[3, 1, 4, 3, None, 1, 5], [3, 3, None, 4, 2], [1], [-1, -2, -3]]:
        root = build(v)
        print("dfs:", good_nodes(root))
        print("bfs:", good_nodes_bfs(root))
        print("---")

"""
Syntax notes (Python):
- float("-inf") compares below every int: a clean starting max.
- Deep skewed trees (1e5 nodes) exceed the recursion limit: prefer the BFS.
"""
