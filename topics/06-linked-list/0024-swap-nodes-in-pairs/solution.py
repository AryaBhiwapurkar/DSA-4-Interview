"""
0024. Swap Nodes in Pairs  |  Medium  |  Linked List
Link: https://leetcode.com/problems/swap-nodes-in-pairs/

Problem: Swap every two adjacent nodes (links, not values).

Examples:
  [1,2,3,4]     -> [2,1,4,3]
  []            -> []
  [1]           -> [1]
  [1,2,3]       -> [2,1,3]
  [1,2,3,4,5]   -> [2,1,4,3,5]

Approaches:
  1. Recursion                     O(n) time, O(n) stack
  2. Iterative with a dummy  ⭐     O(n) time, O(1) space   <- go-to
"""

from typing import Optional


class ListNode:
    def __init__(self, val: int = 0, next: Optional["ListNode"] = None):
        self.val = val
        self.next = next


# ---------- Approach 1: Recursion ----------
def swap_pairs_recursive(head: Optional[ListNode]) -> Optional[ListNode]:
    if not head or not head.next:
        return head
    second = head.next
    head.next = swap_pairs_recursive(second.next)  # rest is already swapped
    second.next = head
    return second


# ---------- Approach 2: Iterative with a Dummy ⭐ ----------
def swap_pairs(head: Optional[ListNode]) -> Optional[ListNode]:
    dummy = prev = ListNode(0, head)
    while prev.next and prev.next.next:
        a, b = prev.next, prev.next.next
        a.next = b.next  # keep the rest before b.next changes
        b.next = a
        prev.next = b
        prev = a  # a now ends this pair
    return dummy.next


# ---------- Driver ----------
def build(vals: list[int]) -> Optional[ListNode]:
    dummy = tail = ListNode()
    for v in vals:
        tail.next = ListNode(v)
        tail = tail.next
    return dummy.next


def to_list(head: Optional[ListNode]) -> list[int]:
    out = []
    while head:
        out.append(head.val)
        head = head.next
    return out


if __name__ == "__main__":
    for t in [[1, 2, 3, 4], [], [1], [1, 2, 3], [1, 2, 3, 4, 5]]:  # fresh list per approach
        print("recursive:", to_list(swap_pairs_recursive(build(t))))
        print("iterative:", to_list(swap_pairs(build(t))))
        print("---")

"""
Syntax notes (Python):
- dummy = prev = ListNode(0, head): two names for one sentinel; prev moves, dummy stays.
- Separate assignment lines make the rewiring order explicit; a tuple swap
  here is easy to get wrong because targets are assigned left to right.
- `not head or not head.next` guards both None cases before touching .next.
"""
