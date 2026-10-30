"""
0019. Remove Nth Node From End of List  |  Medium  |  Linked List
Link: https://leetcode.com/problems/remove-nth-node-from-end-of-list/

Problem: Remove the n-th node from the end and return the head.
         n is always valid.

Examples:
  [1,2,3,4,5], n 2  -> [1,2,3,5]
  [1],         n 1  -> []
  [1,2],       n 1  -> [1]
  [1,2],       n 2  -> [2]

Approaches:
  1. Two passes (count length)   O(L) time, O(1) space
  2. One pass with n-gap  ⭐      O(L) time, O(1) space   <- go-to
"""

from typing import Optional


class ListNode:
    def __init__(self, val: int = 0, next: Optional["ListNode"] = None):
        self.val = val
        self.next = next


# ---------- Approach 1: Two Passes ----------
def remove_nth_from_end_two_pass(head: Optional[ListNode], n: int) -> Optional[ListNode]:
    length, p = 0, head
    while p:
        length += 1
        p = p.next
    dummy = ListNode(0, head)
    prev = dummy
    for _ in range(length - n):  # predecessor of the target
        prev = prev.next
    prev.next = prev.next.next
    return dummy.next


# ---------- Approach 2: One Pass With n-Gap ⭐ ----------
def remove_nth_from_end(head: Optional[ListNode], n: int) -> Optional[ListNode]:
    dummy = ListNode(0, head)  # makes removing the head a normal case
    slow = fast = dummy
    for _ in range(n):  # fast leads by n
        fast = fast.next
    while fast.next:  # stop with fast on the LAST node
        slow, fast = slow.next, fast.next
    slow.next = slow.next.next  # slow is the predecessor
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
    tests = [([1, 2, 3, 4, 5], 2), ([1], 1), ([1, 2], 1), ([1, 2], 2)]
    for v, n in tests:  # fresh list per approach: removal mutates
        print("twoPass:", to_list(remove_nth_from_end_two_pass(build(v), n)))
        print("onePass:", to_list(remove_nth_from_end(build(v), n)))
        print("---")

"""
Syntax notes (Python):
- `for _ in range(k)` repeats k times without using the index.
- ListNode(0, head) builds a dummy already pointing at head.
- Python frees the unlinked node automatically (garbage collection).
"""
