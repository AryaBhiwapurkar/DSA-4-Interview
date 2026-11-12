"""
0147. Insertion Sort List  |  Medium  |  Linked List
Link: https://leetcode.com/problems/insertion-sort-list/

Problem: Sort a singly linked list with insertion sort (relink nodes).

Examples:
  [4,2,1,3]       -> [1,2,3,4]
  [-1,5,3,4,0]    -> [-1,0,3,4,5]
  [1]             -> [1]
  [3,3,1]         -> [1,3,3]
  [1,2,3]         -> [1,2,3]
  [5,4,3,2,1]     -> [1,2,3,4,5]

Approaches:
  1. Copy values, sort, write back           O(n log n) time, O(n) space
  2. Insertion into a dummy-headed list ⭐   O(n^2) time, O(1) space   <- go-to
  3. With a sorted-tail shortcut             O(n^2) worst, O(n) if sorted, O(1) space
"""

from typing import Optional


class ListNode:
    def __init__(self, val: int = 0, next: Optional["ListNode"] = None):
        self.val = val
        self.next = next


# ---------- Approach 1: Copy Values, Sort, Write Back ----------
def insertion_sort_list_values(head: Optional[ListNode]) -> Optional[ListNode]:
    vals, p = [], head
    while p:
        vals.append(p.val)
        p = p.next
    p = head
    for v in sorted(vals):
        p.val, p = v, p.next
    return head


# ---------- Approach 2: Insertion into a Dummy-headed List ⭐ ----------
def insertion_sort_list(head: Optional[ListNode]) -> Optional[ListNode]:
    dummy = ListNode()  # dummy.next is the sorted list
    while head:
        cur, head = head, head.next  # save the rest of the input first
        prev = dummy
        while prev.next and prev.next.val <= cur.val:  # <= keeps it stable
            prev = prev.next
        cur.next = prev.next
        prev.next = cur
    return dummy.next


# ---------- Approach 3: With a Sorted-tail Shortcut ----------
def insertion_sort_list_tail(head: Optional[ListNode]) -> Optional[ListNode]:
    if not head:
        return head
    dummy = ListNode(0, head)
    last = head  # end of the sorted prefix
    while last.next:
        cur = last.next
        if last.val <= cur.val:  # already in place
            last = cur
            continue
        last.next = cur.next  # unlink cur
        prev = dummy
        while prev.next.val <= cur.val:  # stops before last
            prev = prev.next
        cur.next = prev.next
        prev.next = cur
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
    for t in [[4, 2, 1, 3], [-1, 5, 3, 4, 0], [1], [3, 3, 1], [1, 2, 3], [5, 4, 3, 2, 1]]:
        print("values   :", to_list(insertion_sort_list_values(build(t))))
        print("insertion:", to_list(insertion_sort_list(build(t))))
        print("tailCheck:", to_list(insertion_sort_list_tail(build(t))))
        print("---")

"""
Syntax notes (Python):
- cur, head = head, head.next detaches the front node and advances in one line.
- p.val, p = v, p.next: the right side is evaluated before either assignment.
- `continue` jumps to the next loop iteration.
"""
