"""
0002. Add Two Numbers  |  Medium  |  Linked List
Link: https://leetcode.com/problems/add-two-numbers/

Problem: Two numbers stored as digit lists, ones digit first. Return
         their sum in the same format.

Examples:
  [2,4,3],         [5,6,4]    -> [7,0,8]
  [0],             [0]        -> [0]
  [9,9,9,9,9,9,9], [9,9,9,9]  -> [8,9,9,9,0,0,0,1]
  [5],             [5]        -> [0,1]
  [1,8],           [0]        -> [1,8]

Approaches:
  1. Iterative with carry  ⭐   O(max(m,n)) time, O(1) extra space   <- go-to
  2. Recursive                 O(max(m,n)) time, O(max(m,n)) stack
"""

from typing import Optional


class ListNode:
    def __init__(self, val: int = 0, next: Optional["ListNode"] = None):
        self.val = val
        self.next = next


# ---------- Approach 1: Iterative With Carry ⭐ ----------
def add_two_numbers(l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
    dummy = tail = ListNode()
    carry = 0
    while l1 or l2 or carry:  # carry keeps the loop alive for the last digit
        s = carry
        if l1:
            s += l1.val
            l1 = l1.next
        if l2:
            s += l2.val
            l2 = l2.next
        carry, digit = divmod(s, 10)
        tail.next = ListNode(digit)
        tail = tail.next
    return dummy.next


# ---------- Approach 2: Recursive ----------
def add_two_numbers_recursive(l1: Optional[ListNode], l2: Optional[ListNode], carry: int = 0) -> Optional[ListNode]:
    if not l1 and not l2 and not carry:
        return None
    s = carry + (l1.val if l1 else 0) + (l2.val if l2 else 0)
    return ListNode(s % 10, add_two_numbers_recursive(l1 and l1.next, l2 and l2.next, s // 10))


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
    tests = [([2, 4, 3], [5, 6, 4]), ([0], [0]), ([9, 9, 9, 9, 9, 9, 9], [9, 9, 9, 9]), ([5], [5]), ([1, 8], [0])]
    for a, b in tests:
        print("iterative:", to_list(add_two_numbers(build(a), build(b))))
        print("recursive:", to_list(add_two_numbers_recursive(build(a), build(b))))
        print("---")

"""
Syntax notes (Python):
- divmod(s, 10) returns (quotient, remainder) = (carry, digit).
- `l1 and l1.next` is None when l1 is None, else l1.next: a null-safe step.
- A default parameter (carry: int = 0) is safe because ints are immutable.
"""
