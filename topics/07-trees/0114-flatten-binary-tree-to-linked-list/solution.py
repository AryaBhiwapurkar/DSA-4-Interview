"""
0114. Flatten Binary Tree to Linked List  |  Medium  |  Trees
Link: https://leetcode.com/problems/flatten-binary-tree-to-linked-list/

Problem: Flatten in place into a right-pointer chain in preorder;
         every left pointer becomes None.

Examples (level order, None = missing):
  [1,2,5,3,4,null,6]  -> [1,null,2,null,3,null,4,null,5,null,6]
  []                  -> []
  [0]                 -> [0]
  [1,2,null,3]        -> [1,null,2,null,3]   (left chain)

Approaches:
  1. Preorder list, relink         O(n) time, O(n) space
  2. Reverse preorder with prev    O(n) time, O(h) stack
  3. In-place splicing  ⭐          O(n) time, O(1) space   <- go-to
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: Preorder List, Relink ----------
def flatten_list(root: Optional[TreeNode]) -> None:
    nodes: list[TreeNode] = []

    def pre(n: Optional[TreeNode]) -> None:
        if n:
            nodes.append(n)
            pre(n.left)
            pre(n.right)

    pre(root)
    for i, n in enumerate(nodes):
        n.left = None
        n.right = nodes[i + 1] if i + 1 < len(nodes) else None


# ---------- Approach 2: Reverse Preorder With prev ----------
def flatten_reverse(root: Optional[TreeNode]) -> None:
    prev: Optional[TreeNode] = None

    def rev(n: Optional[TreeNode]) -> None:
        nonlocal prev
        if not n:
            return
        rev(n.right)  # right, left, node = reverse preorder
        rev(n.left)
        n.right, n.left = prev, None
        prev = n

    rev(root)


# ---------- Approach 3: In-Place Splicing ⭐ ----------
def flatten(root: Optional[TreeNode]) -> None:
    cur = root
    while cur:
        if cur.left:
            pred = cur.left  # rightmost of the left subtree precedes cur.right
            while pred.right:
                pred = pred.right
            pred.right = cur.right
            cur.right, cur.left = cur.left, None
        cur = cur.right


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
    for v in [[1, 2, 5, 3, 4, None, 6], [], [0], [1, 2, None, 3]]:  # fresh tree per approach
        a, b, c = build(v), build(v), build(v)
        flatten_list(a)
        flatten_reverse(b)
        flatten(c)
        print("list   :", serialize(a))
        print("reverse:", serialize(b))
        print("splice :", serialize(c))
        print("---")

"""
Syntax notes (Python):
- `cur.right, cur.left = cur.left, None` reads the old left before clearing it.
- Functions that mutate in place return None by convention (like list.sort).
"""
