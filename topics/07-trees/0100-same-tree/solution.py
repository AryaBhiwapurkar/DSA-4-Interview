"""
0100. Same Tree  |  Easy  |  Trees
Link: https://leetcode.com/problems/same-tree/

Problem: Are two binary trees identical in structure and values?

Examples (level order, None = missing):
  [1,2,3], [1,2,3]        -> True
  [1,2],   [1,null,2]     -> False
  [1,2,1], [1,1,2]        -> False
  [],      []             -> True
  [1],     []             -> False

Approaches:
  1. Recursive parallel DFS  ⭐   O(n) time, O(h) space   <- go-to
  2. Queue of pairs              O(n) time, O(w) space
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: Recursive Parallel DFS ⭐ ----------
def is_same_tree(p: Optional[TreeNode], q: Optional[TreeNode]) -> bool:
    if not p and not q:
        return True
    if not p or not q:  # exactly one is None
        return False
    return p.val == q.val and is_same_tree(p.left, q.left) and is_same_tree(p.right, q.right)


# ---------- Approach 2: Queue of Pairs ----------
def is_same_tree_bfs(p: Optional[TreeNode], q: Optional[TreeNode]) -> bool:
    qu = deque([(p, q)])
    while qu:
        a, b = qu.popleft()
        if not a and not b:
            continue
        if not a or not b or a.val != b.val:
            return False
        qu.append((a.left, b.left))
        qu.append((a.right, b.right))
    return True


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
    tests = [([1, 2, 3], [1, 2, 3]), ([1, 2], [1, None, 2]), ([1, 2, 1], [1, 1, 2]), ([], []), ([1], [])]
    for a, b in tests:
        p, q = build(a), build(b)
        print("dfs:", is_same_tree(p, q))
        print("bfs:", is_same_tree_bfs(p, q))
        print("---")

"""
Syntax notes (Python):
- `and` short-circuits: later recursive calls are skipped after a False.
- A deque of tuples walks two trees in lockstep.
"""
