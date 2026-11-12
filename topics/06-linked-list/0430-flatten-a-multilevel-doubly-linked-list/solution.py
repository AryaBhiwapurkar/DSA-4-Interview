"""
0430. Flatten a Multilevel Doubly Linked List  |  Medium  |  Linked List
Link: https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/

Problem: Nodes have prev/next/child. Flatten so each child list sits between
         its parent and the parent's old next; clear all child pointers.
         (Input uses LeetCode's level format; N = null.)

Examples:
  [1,2,3,4,5,6,N,N,N,7,8,9,10,N,N,11,12]   -> [1,2,3,7,8,11,12,9,10,4,5,6]
  [1,2,N,3]                                -> [1,3,2]
  []                                       -> []
  [1,N,2,N,3]                              -> [1,2,3]      (child chain)
  [1,2,3,N,N,N,4]                          -> [1,2,3,4]    (child on the last node)

Approaches:
  1. Collect in pre-order, then relink   O(n) time, O(n) space
  2. Recursive DFS returning the tail    O(n) time, O(depth) stack
  3. Iterative splice  ⭐                 O(n) time, O(1) space   <- go-to
"""

from typing import Optional


class Node:
    def __init__(self, val: int):
        self.val = val
        self.prev: Optional["Node"] = None
        self.next: Optional["Node"] = None
        self.child: Optional["Node"] = None


# ---------- Approach 1: Collect in Pre-order, then Relink ----------
def flatten_collect(head: Optional[Node]) -> Optional[Node]:
    order, st = [], [head] if head else []
    while st:
        n = st.pop()
        order.append(n)
        if n.next:
            st.append(n.next)  # next is visited after the child
        if n.child:
            st.append(n.child)
    for i, n in enumerate(order):
        n.prev = order[i - 1] if i else None
        n.next = order[i + 1] if i + 1 < len(order) else None
        n.child = None
    return head


# ---------- Approach 2: Recursive DFS Returning the Tail ----------
def flatten_recursive(head: Optional[Node]) -> Optional[Node]:
    def flat(node: Node) -> Node:  # flattens from node; returns the last node
        last = node
        while node:
            nxt = node.next
            if node.child:
                child_tail = flat(node.child)
                node.next, node.child.prev = node.child, node
                node.child = None
                child_tail.next = nxt
                if nxt:
                    nxt.prev = child_tail
                last = child_tail
            else:
                last = node
            node = nxt
        return last

    if head:
        flat(head)
    return head


# ---------- Approach 3: Iterative Splice ⭐ ----------
def flatten(head: Optional[Node]) -> Optional[Node]:
    cur = head
    while cur:
        if cur.child:
            tail = cur.child
            while tail.next:  # each level's tail is searched once
                tail = tail.next
            tail.next = cur.next
            if cur.next:
                cur.next.prev = tail
            cur.next = cur.child
            cur.child.prev = cur
            cur.child = None
        cur = cur.next
    return head


# ---------- Driver ----------
N = None  # null in the level format


def build(tok: list) -> Optional[Node]:
    head, prev_level, i = None, [], 0
    while i < len(tok):
        skip = 0
        while i < len(tok) and tok[i] is None:
            skip, i = skip + 1, i + 1
        level = []
        while i < len(tok) and tok[i] is not None:
            n = Node(tok[i])
            if level:
                level[-1].next, n.prev = n, level[-1]
            level.append(n)
            i += 1
        if not prev_level:
            head = level[0]
        else:
            prev_level[skip - 1].child = level[0]  # first null closes the previous level
        prev_level = level
    return head


def show(head: Optional[Node]) -> str:  # also checks prev links and cleared children
    vals, ok, p = [], head is None or head.prev is None, head
    while p:
        vals.append(p.val)
        if p.child or (p.next and p.next.prev is not p):
            ok = False
        p = p.next
    return "[" + ",".join(map(str, vals)) + "]" + (" links ok" if ok else " LINKS BROKEN")


if __name__ == "__main__":
    tests = [[1, 2, 3, 4, 5, 6, N, N, N, 7, 8, 9, 10, N, N, 11, 12], [1, 2, N, 3], [], [1, N, 2, N, 3],
             [1, 2, 3, N, N, N, 4]]
    for t in tests:
        print("collect  :", show(flatten_collect(build(t))))
        print("recursive:", show(flatten_recursive(build(t))))
        print("splice   :", show(flatten(build(t))))
        print("---")

"""
Syntax notes (Python):
- `[head] if head else []` starts the stack empty for an empty list.
- level[-1].next, n.prev = n, level[-1] links both directions in one line.
- ",".join(map(str, vals)) formats like the C++ output (no spaces).
"""
