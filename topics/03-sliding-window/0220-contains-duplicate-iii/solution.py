"""
0220. Contains Duplicate III  |  Hard  |  Sliding Window
Link: https://leetcode.com/problems/contains-duplicate-iii/

Problem: Is there i != j with |i - j| <= indexDiff and |nums[i] - nums[j]| <= valueDiff?

Examples:
  [1,2,3,1],     indexDiff = 3, valueDiff = 0  -> True
  [1,5,9,1,5,9], indexDiff = 2, valueDiff = 3  -> False
  [-3,3],        indexDiff = 1, valueDiff = 2  -> False   (truncating buckets would say True)
  [2147483647,-2147483648], indexDiff = 1, valueDiff = 1 -> False   (overflow trap in C++)
  [1,5,9,1],     indexDiff = 3, valueDiff = 3  -> True

Approaches:
  1. Check each pair in range      O(n * indexDiff) time, O(1) space
  2. Ordered window (bisect)       O(n * k) worst here (list insert), O(n log k) with a real BST
  3. Buckets  ⭐                   O(n) time, O(k) space   <- go-to
"""

from bisect import bisect_left, insort


# ---------- Approach 1: Pairs in Range ----------
def contains_nearby_almost_duplicate_brute(nums: list[int], index_diff: int, value_diff: int) -> bool:
    n = len(nums)
    return any(abs(nums[i] - nums[j]) <= value_diff
               for i in range(n) for j in range(i + 1, min(n, i + index_diff + 1)))


# ---------- Approach 2: Ordered Window ----------
def contains_nearby_almost_duplicate_sorted(nums: list[int], index_diff: int, value_diff: int) -> bool:
    win: list[int] = []  # sorted values in the window (stdlib has no balanced BST)
    for i, x in enumerate(nums):
        k = bisect_left(win, x - value_diff)  # smallest >= x - value_diff
        if k < len(win) and win[k] <= x + value_diff:
            return True
        insort(win, x)
        if i >= index_diff:
            win.pop(bisect_left(win, nums[i - index_diff]))
    return False


# ---------- Approach 3: Buckets ⭐ ----------
def contains_nearby_almost_duplicate(nums: list[int], index_diff: int, value_diff: int) -> bool:
    w = value_diff + 1
    bucket: dict[int, int] = {}  # bucket id -> the one value in it
    for i, x in enumerate(nums):
        b = x // w  # Python // already floors negatives
        if b in bucket:
            return True  # same bucket: within value_diff
        if (b - 1 in bucket and x - bucket[b - 1] <= value_diff) or \
           (b + 1 in bucket and bucket[b + 1] - x <= value_diff):
            return True
        bucket[b] = x
        if i >= index_diff:
            del bucket[nums[i - index_diff] // w]  # keep the last index_diff values
    return False


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([1, 2, 3, 1], 3, 0), ([1, 5, 9, 1, 5, 9], 2, 3), ([-3, 3], 1, 2),
             ([2147483647, -2147483648], 1, 1), ([1, 5, 9, 1], 3, 3)]
    for nums, k, t in tests:
        print("pairs  :", contains_nearby_almost_duplicate_brute(nums, k, t))
        print("set    :", contains_nearby_almost_duplicate_sorted(nums, k, t))
        print("buckets:", contains_nearby_almost_duplicate(nums, k, t))
        print("---")

"""
Syntax notes (Python):
- // is floor division, so -3 // 4 == -1 (C++ gives 0).
- bisect.insort keeps a list sorted (O(k) insert); sortedcontainers.SortedList is O(log k) but not stdlib.
- A trailing backslash continues a long boolean expression onto the next line.
"""
