"""
0173. Binary Search Tree Iterator  |  Medium  |  Trees
Link: https://leetcode.com/problems/binary-search-tree-iterator/

Problem: Iterator over a BST in ascending order: next() and hasNext(),
         O(1) average time and O(h) memory.

Examples:
  [7,3,15,null,null,9,20]: next, next, hasNext, next, hasNext, next, hasNext, next, hasNext
    -> [null,3,7,true,9,true,15,true,20,false]
  [1]: hasNext, next, hasNext
    -> [null,true,1,false]

Approaches:
  1. Flatten to an array      O(n) init, O(1) next, O(n) space
  2. Controlled stack  ⭐      O(1) amortized next, O(h) space   <- go-to
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: Flatten to an Array ----------
class BSTIteratorArray:
    def __init__(self, root: Optional[TreeNode]) -> None:
        self.vals: list[int] = []
        self._inorder(root)
        self.i = 0

    def _inorder(self, n: Optional[TreeNode]) -> None:
        if n:
            self._inorder(n.left)
            self.vals.append(n.val)
            self._inorder(n.right)

    def next(self) -> int:
        self.i += 1
        return self.vals[self.i - 1]

    def hasNext(self) -> bool:
        return self.i < len(self.vals)


# ---------- Approach 2: Controlled Stack ⭐ ----------
class BSTIterator:
    def __init__(self, root: Optional[TreeNode]) -> None:
        self.st: list[TreeNode] = []  # pending left spine: at most h nodes
        self._push_left(root)

    def _push_left(self, n: Optional[TreeNode]) -> None:
        while n:
            self.st.append(n)
            n = n.left

    def next(self) -> int:
        n = self.st.pop()
        self._push_left(n.right)  # successor lives in the right subtree's left spine
        return n.val

    def hasNext(self) -> bool:
        return bool(self.st)


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


def run(cls: type, tree: list, ops: list[str]) -> str:
    it = cls(build(tree))
    out = ["null"]
    for op in ops[1:]:
        out.append(str(it.next()) if op == "next" else str(it.hasNext()).lower())
    return "[" + ",".join(out) + "]"


if __name__ == "__main__":
    tests = [
        ([7, 3, 15, None, None, 9, 20],
         ["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"]),
        ([1], ["BSTIterator", "hasNext", "next", "hasNext"]),
    ]
    for tree, ops in tests:
        print("array:", run(BSTIteratorArray, tree, ops))
        print("stack:", run(BSTIterator, tree, ops))
        print("---")

"""
Syntax notes (Python):
- Method names follow LeetCode (hasNext), even though PEP 8 prefers snake_case.
- bool(list) is False for an empty list.
"""
