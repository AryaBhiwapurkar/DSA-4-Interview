"""
0112. Path Sum  |  Easy  |  Trees
Link: https://leetcode.com/problems/path-sum/

Problem: Is there a root-to-leaf path whose values sum to targetSum?

Examples (level order, None = missing):
  [5,4,8,11,null,13,4,7,2,null,null,null,1], 22  -> True
  [1,2,3], 5                                     -> False
  [], 0                                          -> False
  [1,2], 1                                       -> False  (root isn't a leaf)
  [-2,null,-3], -5                               -> True

Approaches:
  1. Recursive DFS  ⭐                 O(n) time, O(h) space   <- go-to
  2. Iterative stack (node, remaining) O(n) time, O(h) space
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: Recursive DFS ⭐ ----------
def has_path_sum(root: Optional[TreeNode], target: int) -> bool:
    if not root:
        return False
    if not root.left and not root.right:  # only leaves end paths
        return target == root.val
    rem = target - root.val
    return has_path_sum(root.left, rem) or has_path_sum(root.right, rem)


# ---------- Approach 2: Iterative Stack ----------
def has_path_sum_iter(root: Optional[TreeNode], target: int) -> bool:
    st = [(root, target)] if root else []
    while st:
        n, rem = st.pop()
        if not n.left and not n.right and rem == n.val:
            return True
        if n.left:
            st.append((n.left, rem - n.val))
        if n.right:
            st.append((n.right, rem - n.val))
    return False


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
    tests = [([5, 4, 8, 11, None, 13, 4, 7, 2, None, None, None, 1], 22), ([1, 2, 3], 5), ([], 0), ([1, 2], 1),
             ([-2, None, -3], -5)]
    for v, t in tests:
        root = build(v)
        print("dfs  :", has_path_sum(root, t))
        print("stack:", has_path_sum_iter(root, t))
        print("---")

"""
Syntax notes (Python):
- A list of tuples as a stack: append / pop from the end.
- `[x] if cond else []` seeds the stack only for a non-empty tree.
"""
