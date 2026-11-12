"""
0862. Shortest Subarray with Sum at Least K  |  Hard  |  Sliding Window
Link: https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/

Problem: Length of the shortest subarray with sum >= k (negatives allowed), or -1.

Examples:
  [1],          k = 1   -> 1
  [1,2],        k = 4   -> -1
  [2,-1,2],     k = 3   -> 3
  [84,-37,32,40,95], k = 167 -> 3
  [-28,81,-20,28,-29], k = 89 -> 3

Approaches:
  1. All pairs of prefixes             O(n^2) time, O(n) space
  2. Monotonic deque on prefixes  ⭐   O(n) time, O(n) space   <- go-to
"""

from collections import deque
from itertools import accumulate


# ---------- Approach 1: All Pairs ----------
def shortest_subarray_brute(nums: list[int], k: int) -> int:
    best = float("inf")
    for i in range(len(nums)):
        s = 0
        for j in range(i, len(nums)):
            s += nums[j]
            if s >= k:
                best = min(best, j - i + 1)
                break
    return -1 if best == float("inf") else int(best)


# ---------- Approach 2: Monotonic Deque ⭐ ----------
def shortest_subarray(nums: list[int], k: int) -> int:
    P = list(accumulate(nums, initial=0))
    best = len(nums) + 1
    dq: deque[int] = deque()  # start indices, P increasing
    for j, pj in enumerate(P):
        while dq and pj - P[dq[0]] >= k:
            best = min(best, j - dq.popleft())  # later j can't beat this start
        while dq and P[dq[-1]] >= pj:
            dq.pop()  # j dominates
        dq.append(j)
    return best if best <= len(nums) else -1


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([1], 1), ([1, 2], 4), ([2, -1, 2], 3), ([84, -37, 32, 40, 95], 167), ([-28, 81, -20, 28, -29], 89)]
    for nums, k in tests:
        print("brute:", shortest_subarray_brute(nums, k))
        print("deque:", shortest_subarray(nums, k))
        print("---")

"""
Syntax notes (Python):
- deque.popleft() / pop() are O(1) at both ends; dq[0] and dq[-1] peek.
- accumulate(nums, initial=0) builds the n + 1 prefix sums.
- n + 1 works as an "impossible" length sentinel, avoiding float('inf').
"""
