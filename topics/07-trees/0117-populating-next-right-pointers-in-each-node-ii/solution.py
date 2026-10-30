"""
0117. Populating Next Right Pointers in Each Node II  |  Medium  |  Trees
Link: https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/

Problem: Point each node's next to its right neighbour on the same level
         (None at the end). Any binary tree.

Examples (output: each level via next pointers, # ends a level):
  [1,2,3,4,5,null,7]     -> [1,#,2,3,#,4,5,7,#]
  []                     -> []
  [1,2,3,4,null,null,5]  -> [1,#,2,3,#,4,5,#]

Approaches:
  1. BFS queue                  O(n) time, O(w) space
  2. Dummy-node level linking ⭐ O(n) time, O(1) space   <- go-to
"""

from collections import deque
from typing import Optional


class Node:
    def __init__(self, val: int = 0, left: Optional["Node"] = None, right: Optional["Node"] = None,
                 next: Optional["Node"] = None):
        self.val, self.left, self.right, self.next = val, left, right, next


TreeNode = Node  # lets the shared level-order builder create Nodes


# ---------- Approach 1: BFS Queue ----------
def connect_bfs(root: Optional[Node]) -> Optional[Node]:
    q = deque([root] if root else [])
    while q:
        sz = len(q)
        for i in range(sz):
            n = q.popleft()
            if i < sz - 1:  # not across levels
                n.next = q[0]
            if n.left:
                q.append(n.left)
            if n.right:
                q.append(n.right)
    return root


# ---------- Approach 2: Dummy-Node Level Linking ⭐ ----------
def connect(root: Optional[Node]) -> Optional[Node]:
    cur = root  # walks the current (already linked) level
    while cur:
        dummy = tail = Node(0)  # builds the next level's chain
        while cur:
            if cur.left:
                tail.next = cur.left
                tail = tail.next
            if cur.right:
                tail.next = cur.right
                tail = tail.next
            cur = cur.next
        cur = dummy.next  # first node of the next level
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


def levels(root: Optional[Node]) -> str:  # follow next pointers level by level
    out, start = [], root
    while start:
        nxt, p = None, start
        while p:
            out.append(str(p.val))
            nxt = nxt or p.left or p.right
            p = p.next
        out.append("#")
        start = nxt
    return "[" + ",".join(out) + "]"


if __name__ == "__main__":
    for v in [[1, 2, 3, 4, 5, None, 7], [], [1, 2, 3, 4, None, None, 5]]:
        print("bfs  :", levels(connect_bfs(build(v))))
        print("dummy:", levels(connect(build(v))))
        print("---")

"""
Syntax notes (Python):
- `TreeNode = Node` binds a second name to the same class.
- `nxt = nxt or p.left or p.right` keeps the first non-None child seen.
- q[0] peeks at the front of a deque.
"""
