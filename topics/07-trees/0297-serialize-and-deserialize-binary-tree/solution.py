"""
0297. Serialize and Deserialize Binary Tree  |  Hard  |  Trees
Link: https://leetcode.com/problems/serialize-and-deserialize-binary-tree/

Problem: Encode a binary tree to a string and decode it back exactly.

Examples (round trip shown in level order, plus each codec's encoding):
  [1,2,3,null,null,4,5]  -> [1,2,3,null,null,4,5]
  []                     -> []
  [1]                    -> [1]
  [1,-2,3,null,40]       -> [1,-2,3,null,40]   (negative, multi-digit)

Approaches:
  1. Preorder with null markers  ⭐   O(n) time, O(n) space   <- go-to
  2. BFS level order with markers    O(n) time, O(n) space
"""

from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val: int = 0, left: Optional["TreeNode"] = None, right: Optional["TreeNode"] = None):
        self.val, self.left, self.right = val, left, right


# ---------- Approach 1: Preorder With Null Markers ⭐ ----------
class Codec:
    def serialize(self, root: Optional[TreeNode]) -> str:
        out: list[str] = []

        def enc(n: Optional[TreeNode]) -> None:
            if not n:
                out.append("#")  # null marker fixes the shape
                return
            out.append(str(n.val))
            enc(n.left)
            enc(n.right)

        enc(root)
        return ",".join(out)  # delimiter: "12" vs "1","2"

    def deserialize(self, data: str) -> Optional[TreeNode]:
        tokens = iter(data.split(","))  # local iterator: codec stays stateless

        def dec() -> Optional[TreeNode]:
            tok = next(tokens)
            if tok == "#":
                return None
            n = TreeNode(int(tok))
            n.left = dec()  # same order as encoding: left, then right
            n.right = dec()
            return n

        return dec()


# ---------- Approach 2: BFS Level Order With Markers ----------
class CodecBFS:
    def serialize(self, root: Optional[TreeNode]) -> str:
        out, q = [], deque([root])
        while q:
            n = q.popleft()
            if not n:
                out.append("#")
                continue
            out.append(str(n.val))
            q.append(n.left)
            q.append(n.right)
        return ",".join(out)

    def deserialize(self, data: str) -> Optional[TreeNode]:
        t = data.split(",")
        if t[0] == "#":
            return None
        root = TreeNode(int(t[0]))
        q = deque([root])
        for i in range(1, len(t), 2):  # each queued node owns the next two tokens
            n = q.popleft()
            if t[i] != "#":
                n.left = TreeNode(int(t[i]))
                q.append(n.left)
            if t[i + 1] != "#":
                n.right = TreeNode(int(t[i + 1]))
                q.append(n.right)
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
    for v in [[1, 2, 3, None, None, 4, 5], [], [1], [1, -2, 3, None, 40]]:
        root = build(v)
        a, b = Codec(), CodecBFS()
        ea, eb = a.serialize(root), b.serialize(root)
        print(f"preorder: {ea} -> {serialize(a.deserialize(ea))}")
        print(f"bfs     : {eb} -> {serialize(b.deserialize(eb))}")
        print("---")

"""
Syntax notes (Python):
- iter(list) + next(it) consumes tokens one at a time across recursive calls.
- ",".join(parts) is linear; += on strings in a loop can be quadratic.
"""
