"""
0230. Kth Smallest Element in a BST  |  Medium  |  Trees
Link: https://leetcode.com/problems/kth-smallest-element-in-a-bst/

Problem: Return the k-th smallest value (1-indexed) in a BST.

Examples (level order, None = missing):
  [3,1,4,null,2],            k 1  -> 1
  [5,3,6,2,4,null,null,1],   k 3  -> 3
  [5,3,6,2,4,null,null,1],   k 6  -> 6
  [1],                       k 1  -> 1

Approaches:
  1. Full inorder into a list       O(n) time, O(n) space
  2. Iterative inorder, stop at k ⭐ O(h + k) time, O(h) space   <- go-to
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: Full Inorder Into a List ----------
def kth_smallest_list(root: Optional[TreeNode], k: int) -> int:
    def inorder(n: Optional[TreeNode]) -> list[int]:
        return inorder(n.left) + [n.val] + inorder(n.right) if n else []

    return inorder(root)[k - 1]


# ---------- Approach 2: Iterative Inorder, Stop at k ⭐ ----------
def kth_smallest(root: Optional[TreeNode], k: int) -> int:
    st: list[TreeNode] = []
    cur = root
    while cur or st:
        while cur:  # go as far left as possible
            st.append(cur)
            cur = cur.left
        cur = st.pop()
        k -= 1
        if k == 0:  # k-th node in sorted order
            return cur.val
        cur = cur.right
    return -1  # unreachable for valid k


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
    t2 = [5, 3, 6, 2, 4, None, None, 1]
    for v, k in [([3, 1, 4, None, 2], 1), (t2, 3), (t2, 6), ([1], 1)]:
        root = build(v)
        print("list :", kth_smallest_list(root, k))
        print("stack:", kth_smallest(root, k))
        print("---")

"""
Syntax notes (Python):
- List concatenation in the recursive inorder is O(n^2) in the worst case;
  appending to a shared list is linear. Fine for a baseline.
- `while cur or st:` runs while there's a node to descend or one to pop.
"""
