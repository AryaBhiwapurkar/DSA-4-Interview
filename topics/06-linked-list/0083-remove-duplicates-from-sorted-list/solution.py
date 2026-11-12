"""
0083. Remove Duplicates from Sorted List  |  Easy  |  Linked List
Link: https://leetcode.com/problems/remove-duplicates-from-sorted-list/

Problem: Remove duplicates from a sorted list so each value appears once.

Examples:
  [1,1,2]         -> [1,2]
  [1,1,2,3,3]     -> [1,2,3]
  []              -> []
  [1,1,1]         -> [1]
  [1,2,3]         -> [1,2,3]
  [1,1,1,2]       -> [1,2]

Approaches:
  1. Recursion                O(n) time, O(n) stack
  2. Iterative skip  ⭐        O(n) time, O(1) space   <- go-to
"""

from typing import Optional


class ListNode:
    def __init__(self, val: int = 0, next: Optional["ListNode"] = None):
        self.val = val
        self.next = next


# ---------- Approach 1: Recursion ----------
def delete_duplicates_recursive(head: Optional[ListNode]) -> Optional[ListNode]:
    if not head or not head.next:
        return head
    head.next = delete_duplicates_recursive(head.next)  # rest is deduped
    if head.next.val == head.val:
        head.next = head.next.next
    return head


# ---------- Approach 2: Iterative Skip ⭐ ----------
def delete_duplicates(head: Optional[ListNode]) -> Optional[ListNode]:
    cur = head
    while cur and cur.next:
        if cur.next.val == cur.val:
            cur.next = cur.next.next  # unlink; stay on cur
        else:
            cur = cur.next
    return head


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
    for t in [[1, 1, 2], [1, 1, 2, 3, 3], [], [1, 1, 1], [1, 2, 3], [1, 1, 1, 2]]:
        print("recursive:", to_list(delete_duplicates_recursive(build(t))))
        print("iterative:", to_list(delete_duplicates(build(t))))
        print("---")

"""
Syntax notes (Python):
- Unlinked nodes are garbage-collected once nothing references them.
- `while cur and cur.next` short-circuits before touching cur.next.val.
- Return head unchanged: the first node is never a duplicate.
"""
