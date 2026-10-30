"""
0236. Lowest Common Ancestor of a Binary Tree  |  Medium  |  Trees
Link: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/

Problem: LCA of two distinct nodes p, q in a general binary tree.

Examples (level order, None = missing; answer printed as a value):
  [3,5,1,6,2,0,8,null,null,7,4], p 5, q 1  -> 3
  [3,5,1,6,2,0,8,null,null,7,4], p 5, q 4  -> 5
  [1,2],                         p 1, q 2  -> 1
  [3,5,1,6,2,0,8,null,null,7,4], p 7, q 8  -> 3

Approaches:
  1. Parent pointers + ancestor set   O(n) time, O(n) space
  2. Recursive postorder  ⭐           O(n) time, O(h) space   <- go-to
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: Parent Pointers + Ancestor Set ----------
def lca_parents(root: TreeNode, p: TreeNode, q: TreeNode) -> TreeNode:
    parent: dict[TreeNode, Optional[TreeNode]] = {root: None}
    st = [root]
    while p not in parent or q not in parent:  # stop once both are mapped
        n = st.pop()
        for c in (n.left, n.right):
            if c:
                parent[c] = n
                st.append(c)
    anc = set()
    a: Optional[TreeNode] = p
    while a:
        anc.add(a)
        a = parent[a]
    b = q
    while b not in anc:
        b = parent[b]
    return b


# ---------- Approach 2: Recursive Postorder ⭐ ----------
def lowest_common_ancestor(root: Optional[TreeNode], p: TreeNode, q: TreeNode) -> Optional[TreeNode]:
    if not root or root is p or root is q:  # found one (or nothing)
        return root
    L = lowest_common_ancestor(root.left, p, q)
    R = lowest_common_ancestor(root.right, p, q)
    if L and R:  # p and q on different sides
        return root
    return L or R  # pass up whichever side found something


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


def find_val(n: Optional[TreeNode], v: int) -> Optional[TreeNode]:  # locate the node LeetCode would pass
    if not n or n.val == v:
        return n
    return find_val(n.left, v) or find_val(n.right, v)


if __name__ == "__main__":
    big = [3, 5, 1, 6, 2, 0, 8, None, None, 7, 4]
    for v, a, b in [(big, 5, 1), (big, 5, 4), ([1, 2], 1, 2), (big, 7, 8)]:
        root = build(v)
        p, q = find_val(root, a), find_val(root, b)
        print("parents  :", lca_parents(root, p, q).val)
        print("postorder:", lowest_common_ancestor(root, p, q).val)
        print("---")

"""
Syntax notes (Python):
- `is` compares node identity.
- `L or R` returns the first truthy one (a node), or None.
- Plain objects are hashable by identity, so they work as dict keys.
"""
