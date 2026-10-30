"""
0023. Merge k Sorted Lists  |  Hard  |  Linked List
Link: https://leetcode.com/problems/merge-k-sorted-lists/

Problem: Merge k sorted linked lists into one sorted list.

Examples:
  [[1,4,5],[1,3,4],[2,6]]  -> [1,1,2,3,4,4,5,6]
  []                       -> []
  [[]]                     -> []
  [[2],[],[1]]             -> [1,2]

Approaches:
  1. Collect, sort, rebuild        O(N log N) time, O(N) space
  2. Min-heap of heads  ⭐          O(N log k) time, O(k) space   <- go-to
  3. Divide & conquer merging      O(N log k) time, O(1) extra space
"""

import heapq
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
def merge_k_lists_sort(lists: list[Optional[ListNode]]) -> Optional[ListNode]:
    return build(sorted(v for l in lists for v in to_list(l)))


# ---------- Approach 2: Min-Heap of Heads ⭐ ----------
def merge_k_lists(lists: list[Optional[ListNode]]) -> Optional[ListNode]:
    heap = [(l.val, i, l) for i, l in enumerate(lists) if l]  # skip empty lists
    heapq.heapify(heap)  # (val, index, node): index breaks ties, nodes never compared
    dummy = tail = ListNode()
    while heap:
        _, i, node = heapq.heappop(heap)
        tail.next = node
        tail = node
        if node.next:
            heapq.heappush(heap, (node.next.val, i, node.next))
    return dummy.next


# ---------- Approach 3: Divide & Conquer Merging ----------
def merge_two(a: Optional[ListNode], b: Optional[ListNode]) -> Optional[ListNode]:
    dummy = tail = ListNode()
    while a and b:
        if a.val <= b.val:
            tail.next, a = a, a.next
        else:
            tail.next, b = b, b.next
        tail = tail.next
    tail.next = a or b
    return dummy.next


def merge_k_lists_divide(lists: list[Optional[ListNode]]) -> Optional[ListNode]:
    if not lists:
        return None
    step = 1
    while step < len(lists):  # log k rounds
        for i in range(0, len(lists) - step, 2 * step):
            lists[i] = merge_two(lists[i], lists[i + step])
        step *= 2
    return lists[0]


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [[[1, 4, 5], [1, 3, 4], [2, 6]], [], [[]], [[2], [], [1]]]
    for t in tests:  # fresh lists per approach: merging splices nodes
        print("sort  :", to_list(merge_k_lists_sort([build(v) for v in t])))
        print("heap  :", to_list(merge_k_lists([build(v) for v in t])))
        print("divide:", to_list(merge_k_lists_divide([build(v) for v in t])))
        print("---")

"""
Syntax notes (Python):
- heapq is a min-heap on a plain list: heapify, heappush, heappop.
- Tuples compare element by element; the unique index i stops comparison
  before it reaches ListNode (which has no ordering).
- Nested generator `v for l in lists for v in to_list(l)` flattens.
"""
