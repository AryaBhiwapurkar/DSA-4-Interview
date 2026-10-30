"""
0206. Reverse Linked List  |  Easy  |  Linked List
Link: https://leetcode.com/problems/reverse-linked-list/

Problem: Reverse a singly linked list and return the new head.

Examples:
  [1,2,3,4,5]  -> [5,4,3,2,1]
  [1,2]        -> [2,1]
  []           -> []
  [1]          -> [1]

Approaches:
  1. Copy values, rebuild     O(n) time, O(n) space
  2. Iterative  ⭐             O(n) time, O(1) space   <- go-to
  3. Recursive                O(n) time, O(n) stack
"""

from typing import Optional


class ListNode:
    def __init__(self, val: int = 0, next: Optional["ListNode"] = None):
        self.val = val
        self.next = next


# ---------- Approach 1: Copy Values, Rebuild ----------
def reverse_list_copy(head: Optional[ListNode]) -> Optional[ListNode]:
    res = None
    while head:
        res = ListNode(head.val, res)  # prepend each value
        head = head.next
    return res


# ---------- Approach 2: Iterative ⭐ ----------
def reverse_list(head: Optional[ListNode]) -> Optional[ListNode]:
    prev, curr = None, head
    while curr:
        curr.next, prev, curr = prev, curr, curr.next  # RHS evaluated first: safe
    return prev  # old tail


# ---------- Approach 3: Recursive ----------
def reverse_list_recursive(head: Optional[ListNode]) -> Optional[ListNode]:
    if not head or not head.next:
        return head
    new_head = reverse_list_recursive(head.next)
    head.next.next = head  # the node after me now points back to me
    head.next = None  # otherwise a 2-node cycle remains
    return new_head


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
    for v in [[1, 2, 3, 4, 5], [1, 2], [], [1]]:  # fresh list per approach: reversal mutates
        print("copy     :", to_list(reverse_list_copy(build(v))))
        print("iterative:", to_list(reverse_list(build(v))))
        print("recursive:", to_list(reverse_list_recursive(build(v))))
        print("---")

"""
Syntax notes (Python):
- Tuple assignment evaluates the whole right side first, so
  `curr.next, prev, curr = prev, curr, curr.next` needs no temp variable.
  (Order on the left still matters: curr.next is assigned before curr moves.)
- Optional["ListNode"] is a forward reference to the class being defined.
- `dummy = tail = ListNode()` binds two names to the same node.
"""
