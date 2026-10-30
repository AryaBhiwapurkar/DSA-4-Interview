"""
0106. Construct Binary Tree from Inorder and Postorder Traversal  |  Medium  |  Trees
Link: https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/

Problem: Rebuild a tree (unique values) from its inorder and postorder.

Examples (output in level order):
  in [9,3,15,20,7], post [9,15,7,20,3]  -> [3,9,20,null,null,15,7]
  in [-1],          post [-1]           -> [-1]
  in [1,2,3],       post [3,2,1]        -> [1,null,2,null,3]   (right-skewed)

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
def build_tree_slice(ino: list[int], post: list[int]) -> Optional[TreeNode]:
    if not post:
        return None
    mid = ino.index(post[-1])  # O(n) search
    root = TreeNode(post[-1])
    root.left = build_tree_slice(ino[:mid], post[:mid])
    root.right = build_tree_slice(ino[mid + 1 :], post[mid:-1])
    return root


# ---------- Approach 2: Index Ranges + Hashmap ⭐ ----------
def build_tree(inorder: list[int], postorder: list[int]) -> Optional[TreeNode]:
    pos = {v: i for i, v in enumerate(inorder)}
    idx = len(postorder) - 1

    def go(lo: int, hi: int) -> Optional[TreeNode]:
        nonlocal idx
        if lo > hi:
            return None
        val = postorder[idx]  # postorder read backwards: root, right..., left...
        idx -= 1
        root = TreeNode(val)
        mid = pos[val]
        root.right = go(mid + 1, hi)  # RIGHT first
        root.left = go(lo, mid - 1)
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
    for ino, post in [([9, 3, 15, 20, 7], [9, 15, 7, 20, 3]), ([-1], [-1]), ([1, 2, 3], [3, 2, 1])]:
        print("slice:", serialize(build_tree_slice(ino, post)))
        print("map  :", serialize(build_tree(ino, post)))
        print("---")

"""
Syntax notes (Python):
- post[mid:-1] slices up to (not including) the last element.
- Assigning root.right before root.left matters here: it controls
  which values the shared idx hands out.
"""
