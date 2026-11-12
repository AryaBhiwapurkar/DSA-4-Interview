"""
0142. Linked List Cycle II  |  Medium  |  Linked List
Link: https://leetcode.com/problems/linked-list-cycle-ii/

Problem: Return the node where the cycle begins, or None. (pos below only
         says where the tail links back; output shows the node's index.)

Examples:
  [3,2,0,-4],    pos 1   -> 1
  [1,2],         pos 0   -> 0
  [1],           pos -1  -> None
  [],            pos -1  -> None
  [1],           pos 0   -> 0     (self-loop)
  [1,2,3,4,5,6], pos 2   -> 2

Approaches:
  1. Hash set of visited nodes   O(n) time, O(n) space
  2. Floyd's two phases  ⭐       O(n) time, O(1) space   <- go-to
"""

from typing import Optional


class ListNode:
    def __init__(self, val: int = 0, next: Optional["ListNode"] = None):
        self.val = val
        self.next = next


# ---------- Approach 1: Hash Set of Visited Nodes ----------
def detect_cycle_set(head: Optional[ListNode]) -> Optional[ListNode]:
    seen: set[ListNode] = set()  # hashed by identity
    while head:
        if head in seen:  # first node seen twice
            return head
        seen.add(head)
        head = head.next
    return None


# ---------- Approach 2: Floyd's Two Phases ⭐ ----------
def detect_cycle(head: Optional[ListNode]) -> Optional[ListNode]:
    slow = fast = head
    while fast and fast.next:
        slow, fast = slow.next, fast.next.next
        if slow is fast:  # phase 1 done: inside the cycle
            p = head  # a = k*c - b: walk both at speed 1
            while p is not slow:
                p, slow = p.next, slow.next
            return p
    return None


# ---------- Driver ----------
def build_cycle(vals: list[int], pos: int) -> list[ListNode]:
    nodes = [ListNode(v) for v in vals]
    for a, b in zip(nodes, nodes[1:]):
        a.next = b
    if pos >= 0:
        nodes[-1].next = nodes[pos]  # close the loop
    return nodes


def index_of(nodes: list[ListNode], p: Optional[ListNode]) -> str:
    return "None" if p is None else str(next(i for i, n in enumerate(nodes) if n is p))


if __name__ == "__main__":
    tests = [([3, 2, 0, -4], 1), ([1, 2], 0), ([1], -1), ([], -1), ([1], 0), ([1, 2, 3, 4, 5, 6], 2)]
    for vals, pos in tests:
        nodes = build_cycle(vals, pos)
        head = nodes[0] if nodes else None  # read-only: share one list
        print("hashSet:", index_of(nodes, detect_cycle_set(head)))
        print("floyd  :", index_of(nodes, detect_cycle(head)))
        print("---")

"""
Syntax notes (Python):
- Plain class instances hash by identity, so set[ListNode] tracks nodes, not values.
- `is` / `is not` compare identity: the right test for "same node".
- zip(nodes, nodes[1:]) walks consecutive pairs to link them.
"""
