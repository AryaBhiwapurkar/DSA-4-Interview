"""
0086. Partition List  |  Medium  |  Linked List
Link: https://leetcode.com/problems/partition-list/

Problem: Move nodes with value < x before nodes with value >= x, keeping
         the original order within each group.

Examples:
  [1,4,3,2,5,2], x 3  -> [1,2,2,4,3,5]
  [2,1],         x 2  -> [1,2]
  [],            x 0  -> []
  [3,1,2],       x 4  -> [3,1,2]
  [3,1,2],       x 0  -> [3,1,2]

Approaches:
  1. Two value arrays, rebuild   O(n) time, O(n) space
  2. Two dummy lists  ⭐          O(n) time, O(1) extra space   <- go-to
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


# ---------- Approach 1: Two Value Arrays, Rebuild ----------
def partition_array(head: Optional[ListNode], x: int) -> Optional[ListNode]:
    vals = to_list(head)
    return build([v for v in vals if v < x] + [v for v in vals if v >= x])


# ---------- Approach 2: Two Dummy Lists ⭐ ----------
def partition(head: Optional[ListNode], x: int) -> Optional[ListNode]:
    less_dummy, ge_dummy = ListNode(), ListNode()
    less, ge = less_dummy, ge_dummy
    while head:
        if head.val < x:  # appending keeps the order (stable)
            less.next = head
            less = head
        else:
            ge.next = head
            ge = head
        head = head.next
    ge.next = None  # or the old link may form a cycle
    less.next = ge_dummy.next
    return less_dummy.next


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([1, 4, 3, 2, 5, 2], 3), ([2, 1], 2), ([], 0), ([3, 1, 2], 4), ([3, 1, 2], 0)]
    for v, x in tests:
        print("arrays :", to_list(partition_array(build(v), x)))
        print("dummies:", to_list(partition(build(v), x)))
        print("---")

"""
Syntax notes (Python):
- Two list comprehensions with complementary conditions give a stable split.
- `a, b = ListNode(), ListNode()` creates two separate objects
  (unlike `a = b = ListNode()`, which aliases one).
"""
