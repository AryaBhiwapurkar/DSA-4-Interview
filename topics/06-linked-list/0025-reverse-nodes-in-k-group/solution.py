"""
0025. Reverse Nodes in k-Group  |  Hard  |  Linked List
Link: https://leetcode.com/problems/reverse-nodes-in-k-group/

Problem: Reverse the list k nodes at a time; a final group shorter than
         k stays as is. Relink nodes, don't change values.

Examples:
  [1,2,3,4,5], k 2  -> [2,1,4,3,5]
  [1,2,3,4,5], k 3  -> [3,2,1,4,5]
  [1,2,3,4],   k 4  -> [4,3,2,1]
  [1,2],       k 1  -> [1,2]
  [1],         k 1  -> [1]

Approaches:
  1. Values array, reverse chunks   O(n) time, O(n) space
  2. Iterative group reversal  ⭐    O(n) time, O(1) space   <- go-to
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


# ---------- Approach 1: Values Array, Reverse Chunks ----------
def reverse_k_group_array(head: Optional[ListNode], k: int) -> Optional[ListNode]:
    vals = to_list(head)
    for i in range(0, len(vals) - k + 1, k):  # full chunks only
        vals[i : i + k] = vals[i : i + k][::-1]
    return build(vals)


# ---------- Approach 2: Iterative Group Reversal ⭐ ----------
def reverse_k_group(head: Optional[ListNode], k: int) -> Optional[ListNode]:
    dummy = ListNode(0, head)
    group_prev = dummy
    while True:
        kth = group_prev
        for _ in range(k):
            kth = kth.next
            if not kth:
                return dummy.next  # fewer than k left: keep as is
        group_next = kth.next

        prev, curr = group_next, group_prev.next  # prev = group_next, NOT None
        while curr is not group_next:
            curr.next, prev, curr = prev, curr, curr.next

        old_first = group_prev.next  # now the group's last node
        group_prev.next = kth
        group_prev = old_first


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([1, 2, 3, 4, 5], 2), ([1, 2, 3, 4, 5], 3), ([1, 2, 3, 4], 4), ([1, 2], 1), ([1], 1)]
    for v, k in tests:
        print("array    :", to_list(reverse_k_group_array(build(v), k)))
        print("iterative:", to_list(reverse_k_group(build(v), k)))
        print("---")

"""
Syntax notes (Python):
- Slice assignment vals[i:i+k] = vals[i:i+k][::-1] reverses a chunk.
- `is not` compares identity: the right test for "reached group_next"
  (which may be None).
- range(0, n - k + 1, k) yields the start of every full chunk.
"""
