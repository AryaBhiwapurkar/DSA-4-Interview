"""
0092. Reverse Linked List II  |  Medium  |  Linked List
Link: https://leetcode.com/problems/reverse-linked-list-ii/

Problem: Reverse the nodes from position left to right (1-indexed).

Examples:
  [1,2,3,4,5], left 2, right 4  -> [1,4,3,2,5]
  [5],         left 1, right 1  -> [5]
  [3,5],       left 1, right 2  -> [5,3]
  [1,2,3],     left 1, right 3  -> [3,2,1]
  [1,2,3],     left 2, right 2  -> [1,2,3]

Approaches:
  1. Values array, reverse segment   O(n) time, O(n) space
  2. Head insertion with dummy  ⭐    O(n) time, O(1) space   <- go-to
"""

from typing import Optional


class ListNode:
    def __init__(self, val: int = 0, next: Optional["ListNode"] = None):
        self.val = val
        self.next = next


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


# ---------- Approach 1: Values Array, Reverse Segment ----------
def reverse_between_array(head: Optional[ListNode], left: int, right: int) -> Optional[ListNode]:
    vals = to_list(head)
    vals[left - 1 : right] = vals[left - 1 : right][::-1]  # 1-indexed, inclusive
    return build(vals)


# ---------- Approach 2: Head Insertion With Dummy ⭐ ----------
def reverse_between(head: Optional[ListNode], left: int, right: int) -> Optional[ListNode]:
    dummy = ListNode(0, head)  # left = 1 becomes a normal case
    prev = dummy
    for _ in range(left - 1):  # node before position left
        prev = prev.next
    curr = prev.next  # stays fixed; ends as the range's tail
    for _ in range(right - left):
        nxt = curr.next  # move nxt to right after prev
        curr.next = nxt.next
        nxt.next = prev.next
        prev.next = nxt
    return dummy.next


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([1, 2, 3, 4, 5], 2, 4), ([5], 1, 1), ([3, 5], 1, 2), ([1, 2, 3], 1, 3), ([1, 2, 3], 2, 2)]
    for v, l, r in tests:
        print("array    :", to_list(reverse_between_array(build(v), l, r)))
        print("headInsert:", to_list(reverse_between(build(v), l, r)))
        print("---")

"""
Syntax notes (Python):
- vals[a:b] = vals[a:b][::-1] reverses a slice in place.
- Convert 1-indexed [left, right] to the slice [left-1 : right].
- Three separate assignments (not one tuple) keep the head-insertion order obvious.
"""
