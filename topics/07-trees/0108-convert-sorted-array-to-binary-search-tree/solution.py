"""
0108. Convert Sorted Array to Binary Search Tree  |  Easy  |  Trees
Link: https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/

Problem: Build a height-balanced BST from a sorted array of distinct ints.
         Any balanced BST is accepted.

Examples (output in level order; left-middle choice, so it differs from
LeetCode's printed answer but is equally valid):
  [-10,-3,0,5,9]  -> [0,-10,5,null,-3,null,9]   (LC shows [0,-3,9,-10,null,5])
  [1,3]           -> [1,null,3]                 (LC shows [3,1])
  [1]             -> [1]

Approaches:
  1. Recursive middle split  ⭐        O(n) time, O(log n) stack   <- go-to
  2. Iterative stack of (node, lo, hi) O(n) time, O(log n) space
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: Recursive Middle Split ⭐ ----------
def sorted_array_to_bst(nums: list[int]) -> Optional[TreeNode]:
    def go(lo: int, hi: int) -> Optional[TreeNode]:
        if lo > hi:
            return None
        mid = (lo + hi) // 2  # middle -> halves differ by at most 1
        return TreeNode(nums[mid], go(lo, mid - 1), go(mid + 1, hi))

    return go(0, len(nums) - 1)


# ---------- Approach 2: Iterative Stack of (node, lo, hi) ----------
def sorted_array_to_bst_iter(a: list[int]) -> Optional[TreeNode]:
    if not a:
        return None
    root = TreeNode(a[(len(a) - 1) // 2])
    st = [(root, 0, len(a) - 1)]
    while st:
        node, lo, hi = st.pop()
        m = (lo + hi) // 2
        if lo <= m - 1:  # left range non-empty
            node.left = TreeNode(a[(lo + m - 1) // 2])
            st.append((node.left, lo, m - 1))
        if m + 1 <= hi:
            node.right = TreeNode(a[(m + 1 + hi) // 2])
            st.append((node.right, m + 1, hi))
    return root


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
    for v in [[-10, -3, 0, 5, 9], [1, 3], [1]]:
        print("recursive:", serialize(sorted_array_to_bst(v)))
        print("iterative:", serialize(sorted_array_to_bst_iter(v)))
        print("---")

"""
Syntax notes (Python):
- TreeNode(val, left, right) builds a subtree in one expression.
- Index-based recursion avoids the O(n log n) cost of slicing.
"""
