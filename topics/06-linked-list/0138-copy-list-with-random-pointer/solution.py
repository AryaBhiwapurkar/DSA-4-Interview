"""
0138. Copy List with Random Pointer  |  Medium  |  Linked List
Link: https://leetcode.com/problems/copy-list-with-random-pointer/

Problem: Deep-copy a list whose nodes have next and random pointers.
         Shown as [val, index of random or null].

Examples (printed as the copy, then whether it shares no nodes with the input):
  [[7,null],[13,0],[11,4],[10,2],[1,0]]  -> same, deep
  [[1,1],[2,1]]                          -> same, deep
  [[3,null],[3,0],[3,null]]              -> same, deep
  []                                     -> [], deep

Approaches:
  1. Two-pass hashmap  ⭐     O(n) time, O(n) space   <- go-to
  2. Interleave copies       O(n) time, O(1) extra space
"""

from typing import Optional


class Node:
    def __init__(self, x: int, next: Optional["Node"] = None, random: Optional["Node"] = None):
        self.val = x
        self.next = next
        self.random = random


# ---------- Approach 1: Two-Pass Hashmap ⭐ ----------
def copy_random_list(head: Optional[Node]) -> Optional[Node]:
    copy: dict[Optional[Node], Optional[Node]] = {None: None}  # null maps to null
    p = head
    while p:
        copy[p] = Node(p.val)
        p = p.next
    p = head
    while p:  # all copies exist: forward randoms are safe
        copy[p].next = copy[p.next]
        copy[p].random = copy[p.random]
        p = p.next
    return copy[head]


# ---------- Approach 2: Interleave Copies ----------
def copy_random_list_interleave(head: Optional[Node]) -> Optional[Node]:
    p = head
    while p:  # A -> A' -> B -> B' ...
        p.next = Node(p.val, p.next)
        p = p.next.next
    p = head
    while p:
        if p.random:
            p.next.random = p.random.next  # copy of random = random's next
        p = p.next.next
    dummy = tail = Node(0)
    p = head
    while p:  # split, restoring the original
        tail.next = p.next
        tail = tail.next
        p.next = p.next.next
        p = p.next
    return dummy.next


# ---------- Driver ----------
def build(spec: list[list]) -> Optional[Node]:  # [val, random index or None]
    nodes = [Node(v) for v, _ in spec]
    for i, (_, r) in enumerate(spec):
        if i + 1 < len(nodes):
            nodes[i].next = nodes[i + 1]
        if r is not None:
            nodes[i].random = nodes[r]
    return nodes[0] if nodes else None


def show(orig: Optional[Node], cp: Optional[Node]) -> str:
    orig_ids = set()
    p = orig
    while p:
        orig_ids.add(id(p))
        p = p.next
    idx, p, i = {}, cp, 0
    while p:
        idx[id(p)] = i
        p, i = p.next, i + 1
    parts, deep, p = [], True, cp
    while p:
        if id(p) in orig_ids or (p.random and id(p.random) in orig_ids):
            deep = False
        r = "null" if p.random is None else str(idx[id(p.random)])
        parts.append(f"[{p.val},{r}]")
        p = p.next
    return "[" + ",".join(parts) + f"] deep={str(deep).lower()}"


if __name__ == "__main__":
    tests = [[[7, None], [13, 0], [11, 4], [10, 2], [1, 0]], [[1, 1], [2, 1]], [[3, None], [3, 0], [3, None]], []]
    for spec in tests:
        a = build(spec)
        print("hashmap   :", show(a, copy_random_list(a)))
        b = build(spec)
        print("interleave:", show(b, copy_random_list_interleave(b)))  # show also checks b was restored
        print("---")

"""
Syntax notes (Python):
- Objects hash by identity by default, so a dict can map node -> copy.
- Seeding {None: None} makes copy[p.random] safe when random is None.
- id(obj) is a stable identity for the object's lifetime.
- Node(p.val, p.next) inserts a copy right after p in one expression.
"""
