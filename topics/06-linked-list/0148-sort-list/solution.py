"""
0148. Sort List  |  Medium  |  Linked List
Link: https://leetcode.com/problems/sort-list/

Problem: Sort a linked list ascending in O(n log n) time.

Examples:
  [4,2,1,3]      -> [1,2,3,4]
  [-1,5,3,4,0]   -> [-1,0,3,4,5]
  []             -> []
  [1]            -> [1]
  [2,1,2,1]      -> [1,1,2,2]

Approaches:
  1. Copy values, sort, write back   O(n log n) time, O(n) space
  2. Top-down merge sort  ⭐          O(n log n) time, O(log n) stack   <- go-to
  3. Bottom-up merge sort            O(n log n) time, O(1) space
"""

from typing import Optional


class ListNode:
    def __init__(self, val: int = 0, next: Optional["ListNode"] = None):
        self.val = val
        self.next = next


def merge(a: Optional[ListNode], b: Optional[ListNode]) -> Optional[ListNode]:
    dummy = tail = ListNode()
    while a and b:
        if a.val <= b.val:  # <= keeps it stable
            tail.next, a = a, a.next
        else:
            tail.next, b = b, b.next
        tail = tail.next
    tail.next = a or b
    return dummy.next


# ---------- Approach 1: Copy Values, Sort, Write Back ----------
def sort_list_copy(head: Optional[ListNode]) -> Optional[ListNode]:
    vals, p = [], head
    while p:
        vals.append(p.val)
        p = p.next
    p = head
    for v in sorted(vals):
        p.val = v
        p = p.next
    return head


# ---------- Approach 2: Top-Down Merge Sort ⭐ ----------
def sort_list(head: Optional[ListNode]) -> Optional[ListNode]:
    if not head or not head.next:
        return head
    slow, fast = head, head.next  # head.next: 2 nodes split 1 + 1
    while fast and fast.next:
        slow, fast = slow.next, fast.next.next
    right, slow.next = slow.next, None  # cut before recursing
    return merge(sort_list(head), sort_list(right))


# ---------- Approach 3: Bottom-Up Merge Sort ----------
def split(head: Optional[ListNode], n: int) -> Optional[ListNode]:  # cut after n nodes, return the rest
    for _ in range(n - 1):
        if not head:
            break
        head = head.next
    if not head:
        return None
    rest, head.next = head.next, None
    return rest


def sort_list_bottom_up(head: Optional[ListNode]) -> Optional[ListNode]:
    n, p = 0, head
    while p:
        n += 1
        p = p.next
    dummy = ListNode(0, head)
    width = 1
    while width < n:
        tail, curr = dummy, dummy.next
        while curr:
            left = curr
            right = split(left, width)
            curr = split(right, width)
            tail.next = merge(left, right)
            while tail.next:  # advance to the end of the merged run
                tail = tail.next
        width *= 2
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
    for v in [[4, 2, 1, 3], [-1, 5, 3, 4, 0], [], [1], [2, 1, 2, 1]]:
        print("copy    :", to_list(sort_list_copy(build(v))))
        print("topDown :", to_list(sort_list(build(v))))
        print("bottomUp:", to_list(sort_list_bottom_up(build(v))))
        print("---")

"""
Syntax notes (Python):
- `right, slow.next = slow.next, None` saves the second half, then cuts.
- Recursion depth is only log2(n) here, far below Python's limit.
- `a or b` picks the non-empty leftover list in the merge.
"""
