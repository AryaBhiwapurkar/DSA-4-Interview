"""
0445. Add Two Numbers II  |  Medium  |  Linked List
Link: https://leetcode.com/problems/add-two-numbers-ii/

Problem: Add two numbers stored most-significant-digit first;
         return the sum in the same format.

Examples:
  [7,2,4,3] + [5,6,4]   -> [7,8,0,7]
  [2,4,3]   + [5,6,4]   -> [8,0,7]
  [0]       + [0]       -> [0]
  [9,9]     + [1]       -> [1,0,0]
  [5]       + [5]       -> [1,0]

Approaches:
  1. Reverse, add (LC 2), reverse   O(m + n) time, O(1) extra (mutates input)
  2. Two stacks + prepend  ⭐        O(m + n) time, O(m + n) space   <- go-to
  3. Pad + recursion                O(m + n) time, O(m + n) stack
"""

from typing import Optional


class ListNode:
    def __init__(self, val: int = 0, next: Optional["ListNode"] = None):
        self.val = val
        self.next = next


# ---------- Approach 1: Reverse, Add, Reverse ----------
def reverse_list(h: Optional[ListNode]) -> Optional[ListNode]:
    prev = None
    while h:
        h.next, prev, h = prev, h, h.next
    return prev


def add_two_numbers_reverse(l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
    a, b = reverse_list(l1), reverse_list(l2)  # note: mutates the input
    dummy = t = ListNode()
    carry = 0
    while a or b or carry:
        s = carry + (a.val if a else 0) + (b.val if b else 0)
        t.next = ListNode(s % 10)
        t = t.next
        carry = s // 10
        a = a.next if a else None
        b = b.next if b else None
    return reverse_list(dummy.next)


# ---------- Approach 2: Two Stacks + Prepend ⭐ ----------
def add_two_numbers(l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
    s1, s2 = [], []
    while l1:
        s1.append(l1.val)
        l1 = l1.next
    while l2:
        s2.append(l2.val)
        l2 = l2.next
    head, carry = None, 0
    while s1 or s2 or carry:  # carry may add a leading 1
        s = carry + (s1.pop() if s1 else 0) + (s2.pop() if s2 else 0)
        head = ListNode(s % 10, head)  # prepend: no final reverse
        carry = s // 10
    return head


# ---------- Approach 3: Pad + Recursion ----------
def add_two_numbers_recursive(l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
    def length(p):
        n = 0
        while p:
            n, p = n + 1, p.next
        return n

    n1, n2 = length(l1), length(l2)
    for _ in range(n2 - n1):  # pad with leading zeros
        l1 = ListNode(0, l1)
    for _ in range(n1 - n2):
        l2 = ListNode(0, l2)
    head = None

    def add_same(a, b) -> int:  # returns the carry out of this position
        nonlocal head
        if a is None:
            return 0
        s = a.val + b.val + add_same(a.next, b.next)
        head = ListNode(s % 10, head)
        return s // 10

    carry = add_same(l1, l2)
    return ListNode(carry, head) if carry else head


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
    tests = [([7, 2, 4, 3], [5, 6, 4]), ([2, 4, 3], [5, 6, 4]), ([0], [0]), ([9, 9], [1]), ([5], [5])]
    for a, b in tests:
        print("reverse  :", to_list(add_two_numbers_reverse(build(a), build(b))))
        print("stacks   :", to_list(add_two_numbers(build(a), build(b))))
        print("recursive:", to_list(add_two_numbers_recursive(build(a), build(b))))
        print("---")

"""
Syntax notes (Python):
- A list is the stack: append to push, pop() to pop from the end.
- `s1.pop() if s1 else 0` treats an exhausted number as 0.
- nonlocal head lets the nested function prepend into the outer variable.
"""
