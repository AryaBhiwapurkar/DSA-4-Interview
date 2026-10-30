"""
0143. Reorder List  |  Medium  |  Linked List
Link: https://leetcode.com/problems/reorder-list/

Problem: Relink L0->L1->...->Ln into L0->Ln->L1->Ln-1->... in place.

Examples:
  [1,2,3,4]    -> [1,4,2,3]
  [1,2,3,4,5]  -> [1,5,2,4,3]
  [1]          -> [1]
  [1,2]        -> [1,2]

Approaches:
  1. Array of nodes + two pointers   O(n) time, O(n) space
  2. Mid + reverse + merge  ⭐        O(n) time, O(1) space   <- go-to
"""

from typing import Optional


class ListNode:
    def __init__(self, val: int = 0, next: Optional["ListNode"] = None):
        self.val = val
        self.next = next


# ---------- Approach 1: Array of Nodes + Two Pointers ----------
def reorder_list_array(head: ListNode) -> None:
    nodes = []
    while head:
        nodes.append(head)
        head = head.next
    i, j = 0, len(nodes) - 1
    while i < j:
        nodes[i].next = nodes[j]
        i += 1
        if i == j:
            break
        nodes[j].next = nodes[i]
        j -= 1
    nodes[i].next = None  # new tail: cut the old links


# ---------- Approach 2: Mid + Reverse + Merge ⭐ ----------
def reorder_list(head: ListNode) -> None:
    slow = fast = head  # find the end of the first half
    while fast.next and fast.next.next:
        slow, fast = slow.next, fast.next.next
    second, slow.next = slow.next, None  # cut, or the weave makes a cycle

    prev = None  # reverse the second half
    while second:
        second.next, prev, second = prev, second, second.next

    first, back = head, prev  # weave: first is never shorter
    while back:
        n1, n2 = first.next, back.next  # save both before relinking
        first.next, back.next = back, n1
        first, back = n1, n2


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
    for v in [[1, 2, 3, 4], [1, 2, 3, 4, 5], [1], [1, 2]]:  # fresh list per approach
        a = build(v)
        reorder_list_array(a)
        print("array  :", to_list(a))
        b = build(v)
        reorder_list(b)
        print("inPlace:", to_list(b))
        print("---")

"""
Syntax notes (Python):
- `second, slow.next = slow.next, None` reads slow.next before clearing it.
- Functions returning None that mutate their argument: call, then inspect.
- Multiple assignment targets are assigned left to right after the RHS
  is fully evaluated.
"""
