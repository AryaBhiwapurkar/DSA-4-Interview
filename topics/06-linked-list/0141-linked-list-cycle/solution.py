"""
0141. Linked List Cycle  |  Easy  |  Linked List
Link: https://leetcode.com/problems/linked-list-cycle/

Problem: Return whether a linked list contains a cycle. (pos below only
         says where the tail links back; it isn't an input.)

Examples:
  [3,2,0,-4], pos 1   -> True
  [1,2],      pos 0   -> True
  [1],        pos -1  -> False
  [],         pos -1  -> False
  [1],        pos 0   -> True   (self-loop)
  [1,2,3],    pos -1  -> False

Approaches:
  1. Hash set of visited nodes   O(n) time, O(n) space
  2. Floyd fast/slow  ⭐          O(n) time, O(1) space   <- go-to
"""

from typing import Optional


class ListNode:
    def __init__(self, val: int = 0, next: Optional["ListNode"] = None):
        self.val = val
        self.next = next


# ---------- Approach 1: Hash Set of Visited Nodes ----------
def has_cycle_set(head: Optional[ListNode]) -> bool:
    seen: set[int] = set()  # node identity, not values
    while head:
        if id(head) in seen:
            return True
        seen.add(id(head))
        head = head.next
    return False


# ---------- Approach 2: Floyd Fast/Slow ⭐ ----------
def has_cycle(head: Optional[ListNode]) -> bool:
    slow = fast = head
    while fast and fast.next:  # both needed before fast.next.next
        slow = slow.next
        fast = fast.next.next
        if slow is fast:  # check AFTER moving: they start equal
            return True
    return False


# ---------- Driver ----------
def build_cycle(vals: list[int], pos: int) -> Optional[ListNode]:
    dummy = tail = ListNode()
    entry = None
    for i, v in enumerate(vals):
        tail.next = ListNode(v)
        tail = tail.next
        if i == pos:
            entry = tail
    if entry:
        tail.next = entry  # close the loop
    return dummy.next


if __name__ == "__main__":
    tests = [([3, 2, 0, -4], 1), ([1, 2], 0), ([1], -1), ([], -1), ([1], 0), ([1, 2, 3], -1)]
    for vals, pos in tests:
        head = build_cycle(vals, pos)  # read-only approaches: one list is enough
        print("hashSet:", has_cycle_set(head))
        print("floyd  :", has_cycle(head))
        print("---")

"""
Syntax notes (Python):
- `is` compares object identity; == on plain classes falls back to identity
  too, but `is` states the intent.
- id(obj) gives a unique int for a live object; a set of ids tracks nodes.
  (Nodes are hashable by identity, so `set[ListNode]` also works.)
"""
