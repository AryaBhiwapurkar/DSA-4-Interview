"""
0129. Sum Root to Leaf Numbers  |  Medium  |  Trees
Link: https://leetcode.com/problems/sum-root-to-leaf-numbers/

Problem: Each root-to-leaf path of digits spells a number; sum them all.

Examples (level order, None = missing):
  [1,2,3]        -> 25
  [4,9,0,5,1]    -> 1026
  [0]            -> 0
  [1,0]          -> 10   (one-child node: null side adds nothing)

Approaches:
  1. Recursive DFS  ⭐        O(n) time, O(h) space   <- go-to
  2. BFS (node, number)      O(n) time, O(w) space
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: Recursive DFS ⭐ ----------
def sum_numbers(root: Optional[TreeNode]) -> int:
    def dfs(n: Optional[TreeNode], cur: int) -> int:
        if not n:
            return 0  # null contributes nothing
        cur = cur * 10 + n.val  # append this digit
        if not n.left and not n.right:
            return cur
        return dfs(n.left, cur) + dfs(n.right, cur)

    return dfs(root, 0)


# ---------- Approach 2: BFS (node, number) ----------
def sum_numbers_bfs(root: Optional[TreeNode]) -> int:
    total = 0
    q = deque([(root, root.val)] if root else [])
    while q:
        n, cur = q.popleft()
        if not n.left and not n.right:
            total += cur
        for c in (n.left, n.right):
            if c:
                q.append((c, cur * 10 + c.val))
    return total


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
    for v in [[1, 2, 3], [4, 9, 0, 5, 1], [0], [1, 0]]:
        root = build(v)
        print("dfs:", sum_numbers(root))
        print("bfs:", sum_numbers_bfs(root))
        print("---")

"""
Syntax notes (Python):
- `for c in (n.left, n.right):` loops over both children without duplication.
- Root value 0 is falsy, but the node object itself is truthy: test nodes, not values.
"""
