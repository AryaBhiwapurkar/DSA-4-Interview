"""
0053. Maximum Subarray  |  Medium  |  Greedy
Link: https://leetcode.com/problems/maximum-subarray/

Problem: Largest sum of a non-empty contiguous subarray.

Examples:
  [-2,1,-3,4,-1,2,1,-5,4]   -> 6
  [1]                       -> 1
  [5,4,-1,7,8]              -> 23
  [-3,-1,-2]                -> -1  (all negative: best single element)

Approaches:
  1. Brute force, all subarrays   O(n^2) time, O(1) space
  2. Divide and conquer           O(n log n) time, O(log n) space
  3. Kadane  ⭐                    O(n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Brute Force ----------
def max_sub_array_brute(nums: list[int]) -> int:
    best = nums[0]
    for i in range(len(nums)):
        s = 0
        for j in range(i, len(nums)):  # extend the subarray starting at i
            s += nums[j]
            best = max(best, s)
    return best


# ---------- Approach 2: Divide and Conquer ----------
def max_sub_array_dc(nums: list[int]) -> int:
    def solve(lo: int, hi: int) -> int:  # inclusive range
        if lo == hi:
            return nums[lo]
        mid = (lo + hi) // 2
        left_best, s = float("-inf"), 0
        for i in range(mid, lo - 1, -1):  # best sum ending at mid
            s += nums[i]
            left_best = max(left_best, s)
        right_best, s = float("-inf"), 0
        for i in range(mid + 1, hi + 1):  # best sum starting at mid+1
            s += nums[i]
            right_best = max(right_best, s)
        cross = int(left_best + right_best)
        return max(solve(lo, mid), solve(mid + 1, hi), cross)

    return solve(0, len(nums) - 1)


# ---------- Approach 3: Kadane ⭐ ----------
def max_sub_array(nums: list[int]) -> int:
    best = cur = nums[0]
    for x in nums[1:]:
        cur = max(x, cur + x)  # a negative running sum only hurts: restart at x
        best = max(best, cur)
    return best


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[-2, 1, -3, 4, -1, 2, 1, -5, 4], [1], [5, 4, -1, 7, 8], [-3, -1, -2]]:
        print("brute :", max_sub_array_brute(t))
        print("divide:", max_sub_array_dc(t))
        print("kadane:", max_sub_array(t))
        print("---")

"""
Syntax notes (Python):
- best = cur = nums[0] seeds both from the first element (handles all-negative input).
- range(mid, lo - 1, -1) walks left from mid down to lo inclusive.
- float("-inf") seeds a running max; int() converts the finite result back.
"""
