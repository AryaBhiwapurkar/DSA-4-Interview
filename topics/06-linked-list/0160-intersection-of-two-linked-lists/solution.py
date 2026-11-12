"""
0160. Intersection of Two Linked Lists  |  Easy  |  Linked List
Link: https://leetcode.com/problems/intersection-of-two-linked-lists/

Problem: Return the first node shared by two acyclic lists, or None.
         (skipA / skipB give where the shared tail starts; -1 = none.)

Examples:
  A = [4,1,8,4,5],  B = [5,6,1,8,4,5], skipA 2, skipB 3   -> 8
  A = [1,9,1,2,4],  B = [3,2,4],       skipA 3, skipB 1   -> 2
  A = [2,6,4],      B = [1,5],         no intersection    -> None
  A = [1],          B = [1],           skipA 0, skipB 0   -> 1   (same head)
  A = [7],          B = [7],           no intersection    -> None (equal values only)

Approaches:
  1. Hash set of A's nodes           O(m + n) time, O(m) space
  2. Length difference               O(m + n) time, O(1) space
  3. Head-switching two pointers ⭐  O(m + n) time, O(1) space   <- go-to
"""

from typing import Optional


class ListNode:
    def __init__(self, val: int = 0, next: Optional["ListNode"] = None):
        self.val = val
        self.next = next


# ---------- Approach 1: Hash Set of A's Nodes ----------
def get_intersection_node_set(a: Optional[ListNode], b: Optional[ListNode]) -> Optional[ListNode]:
    in_a = set()
    while a:
        in_a.add(a)
        a = a.next
    while b:
        if b in in_a:
            return b
        b = b.next
    return None


# ---------- Approach 2: Length Difference ----------
def length(p: Optional[ListNode]) -> int:
    n = 0
    while p:
        n, p = n + 1, p.next
    return n


def get_intersection_node_length(a: Optional[ListNode], b: Optional[ListNode]) -> Optional[ListNode]:
    la, lb = length(a), length(b)
    for _ in range(la - lb):  # align the longer list (empty range if negative)
        a = a.next
    for _ in range(lb - la):
        b = b.next
    while a is not b:
        a, b = a.next, b.next
    return a  # shared node or None


# ---------- Approach 3: Head-switching Two Pointers ⭐ ----------
def get_intersection_node(head_a: Optional[ListNode], head_b: Optional[ListNode]) -> Optional[ListNode]:
    pa, pb = head_a, head_b
    while pa is not pb:  # both None together if no intersection
        pa = pa.next if pa else head_b
        pb = pb.next if pb else head_a
    return pa


# ---------- Driver ----------
def build_pair(A: list[int], B: list[int], skip_a: int, skip_b: int):
    na = [ListNode(x) for x in A]
    for x, y in zip(na, na[1:]):
        x.next = y
    own_b = len(B) if skip_a < 0 else skip_b  # B's private nodes
    dummy = t = ListNode()
    for v in B[:own_b]:
        t.next = ListNode(v)
        t = t.next
    if skip_a >= 0:
        t.next = na[skip_a]  # join the shared tail
    return na[0], dummy.next


def show(p: Optional[ListNode]) -> str:
    return str(p.val) if p else "None"


if __name__ == "__main__":
    tests = [([4, 1, 8, 4, 5], [5, 6, 1, 8, 4, 5], 2, 3), ([1, 9, 1, 2, 4], [3, 2, 4], 3, 1),
             ([2, 6, 4], [1, 5], -1, -1), ([1], [1], 0, 0), ([7], [7], -1, -1)]
    for A, B, sa, sb in tests:
        a, b = build_pair(A, B, sa, sb)  # read-only: share the lists
        print("hashSet:", show(get_intersection_node_set(a, b)))
        print("length :", show(get_intersection_node_length(a, b)))
        print("switch :", show(get_intersection_node(a, b)))
        print("---")

"""
Syntax notes (Python):
- `pa.next if pa else head_b`: a None pointer takes one step before switching.
- range(negative) is empty, so both alignment loops can be written unconditionally.
- B[:own_b] slices the private prefix of B.
"""
