"""
0215. Kth Largest Element in an Array  |  Medium  |  Heap / Priority Queue
Link: https://leetcode.com/problems/kth-largest-element-in-an-array/

Problem: Return the k-th largest element (duplicates count).

Examples:
  [3,2,1,5,6,4],         k 2  -> 5
  [3,2,3,1,2,4,5,5,6],   k 4  -> 4
  [1],                   k 1  -> 1
  [2,1],                 k 2  -> 1
  [7,7,7,7],             k 3  -> 7

Approaches:
  1. Sort                        O(n log n) time, O(1) extra
  2. Min-heap of size k  ⭐       O(n log k) time, O(k) space   <- go-to
  3. Quickselect (3-way)         O(n) average, O(n^2) worst, O(1) space
"""

import heapq


# ---------- Approach 1: Sort ----------
def find_kth_largest_sort(nums: list[int], k: int) -> int:
    return sorted(nums)[-k]


# ---------- Approach 2: Min-Heap of Size k ⭐ ----------
def find_kth_largest(nums: list[int], k: int) -> int:
    h: list[int] = []
    for x in nums:
        heapq.heappush(h, x)
        if len(h) > k:
            heapq.heappop(h)  # keep only the k largest
    return h[0]


# ---------- Approach 3: Quickselect (3-Way Partition) ----------
def find_kth_largest_select(nums: list[int], k: int) -> int:
    a = nums[:]
    lo, hi, target = 0, len(a) - 1, len(a) - k  # index in ascending order
    while True:
        pivot = a[(lo + hi) // 2]
        lt, i, gt = lo, lo, hi  # [lo,lt) < pivot, [lt,i) == pivot, (gt,hi] > pivot
        while i <= gt:
            if a[i] < pivot:
                a[lt], a[i] = a[i], a[lt]
                lt += 1
                i += 1
            elif a[i] > pivot:
                a[i], a[gt] = a[gt], a[i]
                gt -= 1
            else:
                i += 1
        if target < lt:
            hi = lt - 1
        elif target > gt:
            lo = gt + 1
        else:
            return pivot  # target inside the == block


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([3, 2, 1, 5, 6, 4], 2), ([3, 2, 3, 1, 2, 4, 5, 5, 6], 4), ([1], 1), ([2, 1], 2), ([7, 7, 7, 7], 3)]
    for nums, k in tests:
        print("sort  :", find_kth_largest_sort(nums, k))
        print("heap  :", find_kth_largest(nums, k))
        print("select:", find_kth_largest_select(nums, k))
        print("---")

"""
Syntax notes (Python):
- Library one-liner: heapq.nlargest(k, nums)[-1].
- sorted(nums)[-k] reads the k-th element from the end.
"""
