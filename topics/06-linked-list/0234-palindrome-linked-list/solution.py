"""
0234. Palindrome Linked List  |  Easy  |  Linked List
Link: https://leetcode.com/problems/palindrome-linked-list/

Problem: Return whether a singly linked list's values form a palindrome.

Examples:
  [1,2,2,1]     -> True
  [1,2]         -> False
  [1]           -> True
  [1,2,3,2,1]   -> True
  [1,2,3,1]     -> False
  [1,1,2,1]     -> False

Approaches:
  1. Copy to an array                 O(n) time, O(n) space
  2. Recursion with a front pointer   O(n) time, O(n) stack
  3. Reverse the second half  ⭐      O(n) time, O(1) space   <- go-to
"""

from typing import Optional


class ListNode:
    def __init__(self, val: int = 0, next: Optional["ListNode"] = None):
        self.val = val
        self.next = next


# ---------- Approach 1: Copy to an Array ----------
def is_palindrome_array(head: Optional[ListNode]) -> bool:
    v = []
    while head:
        v.append(head.val)
        head = head.next
    return v == v[::-1]


# ---------- Approach 2: Recursion with a Front Pointer ----------
def is_palindrome_recursive(head: Optional[ListNode]) -> bool:
    front = head

    def check(node: Optional[ListNode]) -> bool:
        nonlocal front
        if node is None:
            return True
        if not check(node.next):  # compare deepest first
            return False
        ok = node.val == front.val
        front = front.next
        return ok

    return check(head)


# ---------- Approach 3: Reverse the Second Half ⭐ ----------
def reverse_list(head: Optional[ListNode]) -> Optional[ListNode]:
    prev = None
    while head:
        head.next, prev, head = prev, head, head.next
    return prev


def is_palindrome(head: ListNode) -> bool:
    slow = fast = head
    while fast.next and fast.next.next:  # slow stops at the end of the first half
        slow, fast = slow.next, fast.next.next
    second = reverse_list(slow.next)
    p, q, ok = head, second, True
    while q:
        if p.val != q.val:
            ok = False
            break
        p, q = p.next, q.next
    slow.next = reverse_list(second)  # restore the input
    return ok


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
    for t in [[1, 2, 2, 1], [1, 2], [1], [1, 2, 3, 2, 1], [1, 2, 3, 1], [1, 1, 2, 1]]:
        head = build(t)
        print("array    :", is_palindrome_array(head))
        print("recursive:", is_palindrome_recursive(head))
        print("reverse  :", is_palindrome(head), " list after:", to_list(head))
        print("---")

"""
Syntax notes (Python):
- nonlocal lets the inner function reassign `front` from the enclosing scope.
- head.next, prev, head = prev, head, head.next reverses one link in a line:
  the right side is evaluated first, then assigned left to right.
- v == v[::-1] compares a list with its reversed copy.
"""
