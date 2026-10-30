"""
0101. Symmetric Tree  |  Easy  |  Trees
Link: https://leetcode.com/problems/symmetric-tree/

Problem: Is the tree a mirror image of itself?

Examples (level order, None = missing):
  [1,2,2,3,4,4,3]          -> True
  [1,2,2,null,3,null,3]    -> False
  [1]                      -> True
  [1,2,3]                  -> False

Approaches:
  1. Recursive mirror check  ⭐   O(n) time, O(h) space   <- go-to
  2. Queue of pairs              O(n) time, O(w) space
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: Recursive Mirror Check ⭐ ----------
def is_symmetric(root: Optional[TreeNode]) -> bool:
    def mirror(a: Optional[TreeNode], b: Optional[TreeNode]) -> bool:
        if not a and not b:
            return True
        if not a or not b:
            return False
        return a.val == b.val and mirror(a.left, b.right) and mirror(a.right, b.left)  # crossed

    return not root or mirror(root.left, root.right)


# ---------- Approach 2: Queue of Pairs ----------
def is_symmetric_bfs(root: Optional[TreeNode]) -> bool:
    if not root:
        return True
    q = deque([(root.left, root.right)])
    while q:
        a, b = q.popleft()
        if not a and not b:
            continue
        if not a or not b or a.val != b.val:
            return False
        q.append((a.left, b.right))  # outer pair
        q.append((a.right, b.left))  # inner pair
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
    for v in [[1, 2, 2, 3, 4, 4, 3], [1, 2, 2, None, 3, None, 3], [1], [1, 2, 3]]:
        root = build(v)
        print("dfs:", is_symmetric(root))
        print("bfs:", is_symmetric_bfs(root))
        print("---")

"""
Syntax notes (Python):
- A nested helper (mirror) keeps the public signature LeetCode-shaped.
- `not root or ...` returns True for an empty tree without a branch.
"""
