"""
0105. Construct Binary Tree from Preorder and Inorder Traversal  |  Medium  |  Trees
Link: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

Problem: Rebuild a tree (unique values) from its preorder and inorder.

Examples (output in level order):
  pre [3,9,20,15,7], in [9,3,15,20,7]  -> [3,9,20,null,null,15,7]
  pre [-1],          in [-1]           -> [-1]
  pre [1,2,3],       in [3,2,1]        -> [1,2,null,3]   (left-skewed)

Approaches:
  1. Slice + linear search         O(n^2) time, O(n^2) space
  2. Index ranges + hashmap  ⭐     O(n) time, O(n) space   <- go-to
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: Slice + Linear Search ----------
def build_tree_slice(pre: list[int], ino: list[int]) -> Optional[TreeNode]:
    if not pre:
        return None
    mid = ino.index(pre[0])  # O(n) search
    root = TreeNode(pre[0])
    root.left = build_tree_slice(pre[1 : 1 + mid], ino[:mid])
    root.right = build_tree_slice(pre[1 + mid :], ino[mid + 1 :])
    return root


# ---------- Approach 2: Index Ranges + Hashmap ⭐ ----------
def build_tree(preorder: list[int], inorder: list[int]) -> Optional[TreeNode]:
    pos = {v: i for i, v in enumerate(inorder)}  # value -> inorder index
    idx = 0

    def go(lo: int, hi: int) -> Optional[TreeNode]:
        nonlocal idx
        if lo > hi:
            return None
        val = preorder[idx]  # next preorder value is this subtree's root
        idx += 1
        root = TreeNode(val)
        mid = pos[val]
        root.left = go(lo, mid - 1)  # LEFT first: preorder order
        root.right = go(mid + 1, hi)
        return root

    return go(0, len(inorder) - 1)


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
    for pre, ino in [([3, 9, 20, 15, 7], [9, 3, 15, 20, 7]), ([-1], [-1]), ([1, 2, 3], [3, 2, 1])]:
        print("slice:", serialize(build_tree_slice(pre, ino)))
        print("map  :", serialize(build_tree(pre, ino)))
        print("---")

"""
Syntax notes (Python):
- {v: i for i, v in enumerate(a)} builds a value -> index map.
- `nonlocal idx` lets the nested builder advance the shared preorder pointer.
- Slices copy, which is why approach 1 is O(n^2).
"""
