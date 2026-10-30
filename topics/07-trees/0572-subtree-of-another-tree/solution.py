"""
0572. Subtree of Another Tree  |  Easy  |  Trees
Link: https://leetcode.com/problems/subtree-of-another-tree/

Problem: Does subRoot appear in root as a complete subtree?

Examples (level order, None = missing):
  [3,4,5,1,2],                         [4,1,2]  -> True
  [3,4,5,1,2,null,null,null,null,0],   [4,1,2]  -> False
  [12],                                [2]      -> False  (delimiter check)
  [1,1],                               [1]      -> True

Approaches:
  1. DFS + same tree  ⭐          O(m*n) time, O(h) space   <- go-to
  2. Serialize + substring        O(m+n) with KMP, O(m+n) space
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: DFS + Same Tree ⭐ ----------
def same(a: Optional[TreeNode], b: Optional[TreeNode]) -> bool:
    if not a or not b:
        return a is b
    return a.val == b.val and same(a.left, b.left) and same(a.right, b.right)


def is_subtree(root: Optional[TreeNode], sub_root: Optional[TreeNode]) -> bool:
    if not root:
        return False
    return same(root, sub_root) or is_subtree(root.left, sub_root) or is_subtree(root.right, sub_root)


# ---------- Approach 2: Serialize + Substring ----------
def pre(n: Optional[TreeNode], out: list[str]) -> None:
    if not n:
        out.append(",#")  # null marker keeps shapes distinct
        return
    out.append("," + str(n.val))  # leading comma: "2" can't match inside "12"
    pre(n.left, out)
    pre(n.right, out)


def is_subtree_serialize(root: Optional[TreeNode], sub_root: Optional[TreeNode]) -> bool:
    a: list[str] = []
    b: list[str] = []
    pre(root, a)
    pre(sub_root, b)
    return "".join(b) in "".join(a)


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
    tests = [([3, 4, 5, 1, 2], [4, 1, 2]), ([3, 4, 5, 1, 2, None, None, None, None, 0], [4, 1, 2]),
             ([12], [2]), ([1, 1], [1])]
    for a, b in tests:
        r, s = build(a), build(b)
        print("dfs      :", is_subtree(r, s))
        print("serialize:", is_subtree_serialize(r, s))
        print("---")

"""
Syntax notes (Python):
- `a is b` with at least one None is True only when both are None.
- `sub in s` is substring search on strings.
- Collect parts in a list and "".join once: avoids quadratic concatenation.
"""
