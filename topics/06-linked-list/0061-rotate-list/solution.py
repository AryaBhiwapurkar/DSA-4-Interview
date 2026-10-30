"""
0061. Rotate List  |  Medium  |  Linked List
Link: https://leetcode.com/problems/rotate-list/

Problem: Rotate a linked list to the right by k places. k can be huge.

Examples:
  [1,2,3,4,5], k 2   -> [4,5,1,2,3]
  [0,1,2],     k 4   -> [2,0,1]
  [],          k 0   -> []
  [1],         k 99  -> [1]
  [1,2],       k 2   -> [1,2]

Approaches:
  1. Rotate one step, (k mod n) times   O(n * (k mod n)) time, O(1) space
  2. Ring and cut  ⭐                    O(n) time, O(1) space   <- go-to
"""

from typing import Optional


class ListNode:
    def __init__(self, val: int = 0, next: Optional["ListNode"] = None):
        self.val = val
        self.next = next


# ---------- Approach 1: Rotate One Step at a Time ----------
def rotate_right_steps(head: Optional[ListNode], k: int) -> Optional[ListNode]:
    if not head or not head.next:
        return head
    n, p = 0, head
    while p:
        n += 1
        p = p.next
    for _ in range(k % n):  # without % n, k = 2e9 never finishes
        prev = head
        while prev.next.next:  # second-to-last
            prev = prev.next
        last = prev.next
        prev.next = None
        last.next = head
        head = last
    return head


# ---------- Approach 2: Ring and Cut ⭐ ----------
def rotate_right(head: Optional[ListNode], k: int) -> Optional[ListNode]:
    if not head:
        return head
    n, tail = 1, head
    while tail.next:
        tail = tail.next
        n += 1
    k %= n  # n > 0 here: safe
    if k == 0:
        return head  # check BEFORE making the ring
    tail.next = head  # close the ring
    new_tail = head
    for _ in range(n - k - 1):
        new_tail = new_tail.next
    new_head, new_tail.next = new_tail.next, None  # cut the ring
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
    tests = [([1, 2, 3, 4, 5], 2), ([0, 1, 2], 4), ([], 0), ([1], 99), ([1, 2], 2)]
    for v, k in tests:
        print("steps:", to_list(rotate_right_steps(build(v), k)))
        print("ring :", to_list(rotate_right(build(v), k)))
        print("---")

"""
Syntax notes (Python):
- k %= n raises ZeroDivisionError if n == 0, so handle the empty list first.
- `new_head, new_tail.next = new_tail.next, None` reads before it cuts.
"""
