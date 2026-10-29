"""
0239. Sliding Window Maximum  |  Hard  |  Sliding Window
Link: https://leetcode.com/problems/sliding-window-maximum/

Problem: Return the maximum of every window of size k as it slides
         from left to right.

Examples:
  [1,3,-1,-3,5,3,6,7], k=3   -> [3,3,5,5,6,7]
  [1], k=1                   -> [1]
  [9,8,7,6], k=2             -> [9,8,7]
  [4,4,4], k=2               -> [4,4]

Approaches:
  1. Brute force                   O(n*k) time, O(1) space
  2. Max-heap with lazy deletion   O(n log n) time, O(n) space
  3. Monotonic deque  ⭐            O(n) time, O(k) space   <- go-to
"""

import heapq
from collections import deque


# ---------- Approach 1: Brute Force ----------
def max_sliding_window_brute(nums: list[int], k: int) -> list[int]:
    return [max(nums[i : i + k]) for i in range(len(nums) - k + 1)]


# ---------- Approach 2: Max-Heap With Lazy Deletion ----------
def max_sliding_window_heap(nums: list[int], k: int) -> list[int]:
    heap: list[tuple[int, int]] = []  # (-value, index): heapq is a min-heap
    res: list[int] = []
    for i, x in enumerate(nums):
        heapq.heappush(heap, (-x, i))
        if i >= k - 1:
            while heap[0][1] <= i - k:  # discard maxes that left the window
                heapq.heappop(heap)
            res.append(-heap[0][0])
    return res


# ---------- Approach 3: Monotonic Deque ⭐ ----------
def max_sliding_window(nums: list[int], k: int) -> list[int]:
    dq: deque[int] = deque()  # indices; values strictly decreasing
    res: list[int] = []
    for i, x in enumerate(nums):
        if dq and dq[0] <= i - k:  # front left the window
            dq.popleft()
        while dq and nums[dq[-1]] <= x:  # dominated: never a max again
            dq.pop()
        dq.append(i)
        if i >= k - 1:
            res.append(nums[dq[0]])
    return res


# ---------- Driver ----------
if __name__ == "__main__":
    for nums, k in [([1, 3, -1, -3, 5, 3, 6, 7], 3), ([1], 1), ([9, 8, 7, 6], 2), ([4, 4, 4], 2)]:
        print("brute:", max_sliding_window_brute(nums, k))
        print("heap :", max_sliding_window_heap(nums, k))
        print("deque:", max_sliding_window(nums, k))
        print("---")

"""
Syntax notes (Python):
- collections.deque: append/pop at the right, appendleft/popleft at the left, all O(1).
- dq[0] / dq[-1] peek the front / back.
- heapq is a min-heap; push negated values to simulate a max-heap.
"""
