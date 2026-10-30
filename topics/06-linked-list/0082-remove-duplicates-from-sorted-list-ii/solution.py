"""
0082. Remove Duplicates from Sorted List II  |  Medium  |  Linked List
Link: https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/

Problem: In a sorted list, delete every node whose value is duplicated,
         keeping only values that appear exactly once.

Examples:
  [1,2,3,3,4,4,5]  -> [1,2,5]
  [1,1,1,2,3]      -> [2,3]
  []               -> []
  [1,1]            -> []
  [1,2,2]          -> [1]

Approaches:
  1. Count values, then relink   O(n) time, O(n) space
  2. Dummy + skip runs  ⭐        O(n) time, O(1) space   <- go-to
"""

from collections import Counter
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


# ---------- Approach 1: Count Values, Then Relink ----------
def delete_duplicates_count(head: Optional[ListNode]) -> Optional[ListNode]:
    cnt = Counter(to_list(head))
    dummy = tail = ListNode()
    while head:
        if cnt[head.val] == 1:  # keep unique values only
            tail.next = head
            tail = head
        head = head.next
    tail.next = None  # cut whatever followed the last kept node
    return dummy.next


# ---------- Approach 2: Dummy + Skip Runs ⭐ ----------
def delete_duplicates(head: Optional[ListNode]) -> Optional[ListNode]:
    dummy = ListNode(0, head)  # a run at the head becomes a normal case
    prev, curr = dummy, head
    while curr:
        if curr.next and curr.val == curr.next.val:
            v = curr.val
            while curr and curr.val == v:  # skip the whole run
                curr = curr.next
            prev.next = curr  # prev stays: curr may start another run
        else:
            prev, curr = curr, curr.next  # curr is unique
    return dummy.next


# ---------- Driver ----------
if __name__ == "__main__":
    for v in [[1, 2, 3, 3, 4, 4, 5], [1, 1, 1, 2, 3], [], [1, 1], [1, 2, 2]]:
        print("count:", to_list(delete_duplicates_count(build(v))))
        print("skip :", to_list(delete_duplicates(build(v))))
        print("---")

"""
Syntax notes (Python):
- Counter(iterable) counts occurrences; a missing key reads as 0.
- `while curr and curr.val == v` short-circuits on None.
- prev, curr = curr, curr.next advances both in one line.
"""
