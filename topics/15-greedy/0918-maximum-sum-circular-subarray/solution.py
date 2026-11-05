"""
0918. Maximum Sum Circular Subarray  |  Medium  |  Greedy
Link: https://leetcode.com/problems/maximum-sum-circular-subarray/

Problem: Largest sum of a non-empty subarray of a circular array (a subarray
         may wrap past the end, but uses each element at most once).

Examples:
  [1,-2,3,-2]   -> 3
  [5,-3,5]      -> 10
  [-3,-2,-3]    -> -2
  [3,-1,2,-1]   -> 4
  [-2]          -> -2

Approaches:
  1. Brute force, every start and length   O(n^2) time, O(1) space
  2. Kadane on max and min  ⭐              O(n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Brute Force ----------
def max_subarray_sum_circular_brute(nums: list[int]) -> int:
    n, best = len(nums), nums[0]
    for i in range(n):
        s = 0
        for k in range(n):  # lengths 1..n starting at i, wrapping
            s += nums[(i + k) % n]
            best = max(best, s)
    return best


# ---------- Approach 2: Kadane on Max and Min ⭐ ----------
def max_subarray_sum_circular(nums: list[int]) -> int:
    total = 0
    cur_max = cur_min = 0
    best_max, best_min = nums[0], nums[0]
    for x in nums:
        cur_max = max(x, cur_max + x)
        best_max = max(best_max, cur_max)  # best non-wrapping subarray
        cur_min = min(x, cur_min + x)
        best_min = min(best_min, cur_min)  # worst subarray: removing it gives the wrap
        total += x
    if best_max < 0:  # all negative: the wrap would be empty
        return best_max
    return max(best_max, total - best_min)


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[1, -2, 3, -2], [5, -3, 5], [-3, -2, -3], [3, -1, 2, -1], [-2]]:
        print("brute :", max_subarray_sum_circular_brute(t))
        print("kadane:", max_subarray_sum_circular(t))
        print("---")

"""
Syntax notes (Python):
- (i + k) % n wraps the index around the end of the list.
- Running max and min Kadane share one loop.
- best_max < 0 means every element is negative.
"""
