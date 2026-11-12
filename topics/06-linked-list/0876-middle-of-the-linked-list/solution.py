"""
0876. Middle of the Linked List  |  Easy  |  Linked List
Link: https://leetcode.com/problems/middle-of-the-linked-list/

Problem: Return the middle node; for even length, the second middle.

Examples:
  [1,2,3,4,5]     -> [3,4,5]
  [1,2,3,4,5,6]   -> [4,5,6]
  [1]             -> [1]
  [1,2]           -> [2]

Approaches:
  1. Count, then walk n/2      O(n) time, O(1) space
  2. Fast/slow pointers  ⭐     O(n) time, O(1) space   <- go-to
"""

from typing import Optional


class ListNode:
    def __init__(self, val: int = 0, next: Optional["ListNode"] = None):
        self.val = val
        self.next = next


# ---------- Approach 1: Count, then Walk ----------
def middle_node_count(head: ListNode) -> ListNode:
    n, p = 0, head
    while p:
        n, p = n + 1, p.next
    for _ in range(n // 2):  # n // 2 -> second middle
        head = head.next
    return head


# ---------- Approach 2: Fast/Slow Pointers ⭐ ----------
def middle_node(head: ListNode) -> ListNode:
    slow = fast = head
    while fast and fast.next:  # this condition -> second middle
        slow, fast = slow.next, fast.next.next
    return slow


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
    for t in [[1, 2, 3, 4, 5], [1, 2, 3, 4, 5, 6], [1], [1, 2]]:
        head = build(t)
        print("count   :", to_list(middle_node_count(head)))
        print("fastSlow:", to_list(middle_node(head)))
        print("---")

"""
Syntax notes (Python):
- slow, fast = slow.next, fast.next.next advances both from their old values.
- `for _ in range(k)` repeats k times when the index isn't needed.
- dummy = tail = ListNode() binds both names to the same sentinel node.
"""
