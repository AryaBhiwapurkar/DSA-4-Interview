"""
0021. Merge Two Sorted Lists  |  Easy  |  Linked List
Link: https://leetcode.com/problems/merge-two-sorted-lists/

Problem: Splice two sorted linked lists into one sorted list.

Examples:
  [1,2,4], [1,3,4]  -> [1,1,2,3,4,4]
  [],      []       -> []
  [],      [0]      -> [0]
  [5],     [1,2,3]  -> [1,2,3,5]

Approaches:
  1. Collect, sort, rebuild      O((m+n) log(m+n)) time, O(m+n) space
  2. Recursive merge             O(m+n) time, O(m+n) stack
  3. Iterative with dummy  ⭐     O(m+n) time, O(1) space   <- go-to
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


# ---------- Approach 1: Collect, Sort, Rebuild ----------
def merge_two_lists_sort(l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
    return build(sorted(to_list(l1) + to_list(l2)))


# ---------- Approach 2: Recursive Merge ----------
def merge_two_lists_recursive(l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
    if not l1 or not l2:
        return l1 or l2
    if l1.val <= l2.val:
        l1.next = merge_two_lists_recursive(l1.next, l2)
        return l1
    l2.next = merge_two_lists_recursive(l1, l2.next)
    return l2


# ---------- Approach 3: Iterative With Dummy ⭐ ----------
def merge_two_lists(l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
    dummy = tail = ListNode()  # removes the "who is head?" case
    while l1 and l2:
        if l1.val <= l2.val:  # <= keeps it stable
            tail.next, l1 = l1, l1.next
        else:
            tail.next, l2 = l2, l2.next
        tail = tail.next
    tail.next = l1 or l2  # attach the leftover in one step
    return dummy.next


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([1, 2, 4], [1, 3, 4]), ([], []), ([], [0]), ([5], [1, 2, 3])]
    for a, b in tests:  # fresh lists per approach: merging splices nodes
        print("sort     :", to_list(merge_two_lists_sort(build(a), build(b))))
        print("recursive:", to_list(merge_two_lists_recursive(build(a), build(b))))
        print("iterative:", to_list(merge_two_lists(build(a), build(b))))
        print("---")

"""
Syntax notes (Python):
- `l1 or l2` returns the first truthy operand (the non-None list), or None.
- `tail.next, l1 = l1, l1.next` links and advances in one line.
- Node objects are truthy unless they define __bool__/__len__, so
  `while l1 and l2` works as a None check.
"""
