"""
0328. Odd Even Linked List  |  Medium  |  Linked List
Link: https://leetcode.com/problems/odd-even-linked-list/

Problem: Put nodes at odd positions first, then even positions,
         preserving order within each group. O(1) extra space.

Examples:
  [1,2,3,4,5]       -> [1,3,5,2,4]
  [2,1,3,5,6,4,7]   -> [2,3,6,7,1,5,4]
  []                -> []
  [1]               -> [1]
  [1,2]             -> [1,2]
  [1,2,3,4]         -> [1,3,2,4]

Approaches:
  1. Collect nodes into two arrays   O(n) time, O(n) space
  2. In-place two chains  ⭐          O(n) time, O(1) space   <- go-to
"""

from typing import Optional


class ListNode:
    def __init__(self, val: int = 0, next: Optional["ListNode"] = None):
        self.val = val
        self.next = next


# ---------- Approach 1: Collect Nodes into Two Arrays ----------
def odd_even_list_arrays(head: Optional[ListNode]) -> Optional[ListNode]:
    nodes = []
    while head:
        nodes.append(head)
        head = head.next
    order = nodes[0::2] + nodes[1::2]  # odd positions are even indices
    for a, b in zip(order, order[1:] + [None]):
        a.next = b
    return order[0] if order else None


# ---------- Approach 2: In-place Two Chains ⭐ ----------
def odd_even_list(head: Optional[ListNode]) -> Optional[ListNode]:
    if not head:
        return head
    odd, even = head, head.next
    even_head = even
    while even and even.next:  # covers both odd and even lengths
        odd.next = even.next
        odd = odd.next
        even.next = odd.next
        even = even.next
    odd.next = even_head  # odd chain, then even chain
    return head


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
    for t in [[1, 2, 3, 4, 5], [2, 1, 3, 5, 6, 4, 7], [], [1], [1, 2], [1, 2, 3, 4]]:
        print("arrays :", to_list(odd_even_list_arrays(build(t))))
        print("inPlace:", to_list(odd_even_list(build(t))))
        print("---")

"""
Syntax notes (Python):
- nodes[0::2] / nodes[1::2]: slices with a step pick every other element.
- zip(order, order[1:] + [None]) pairs each node with its successor (last gets None).
- `x if cond else y` for the empty-list return.
"""
