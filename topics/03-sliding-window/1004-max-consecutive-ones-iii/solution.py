"""
1004. Max Consecutive Ones III  |  Medium  |  Sliding Window
Link: https://leetcode.com/problems/max-consecutive-ones-iii/

Problem: Longest run of 1s after flipping at most k zeros.

Examples:
  [1,1,1,0,0,0,1,1,1,1,0], k = 2                      -> 6
  [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3      -> 10
  [1,0,1,0,1], k = 1                                  -> 3
  [0,0,0], k = 0                                      -> 0
  [0,0,1], k = 5                                      -> 3

Approaches:
  1. Every start, extend          O(n^2) time, O(1) space
  2. Shrinking window  ⭐         O(n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Every Start ----------
def longest_ones_brute(nums: list[int], k: int) -> int:
    best = 0
    for l in range(len(nums)):
        zeros = 0
        for r in range(l, len(nums)):
            zeros += nums[r] == 0
            if zeros > k:
                break
            best = max(best, r - l + 1)
    return best


# ---------- Approach 2: Shrinking Window ⭐ ----------
def longest_ones(nums: list[int], k: int) -> int:
    l = zeros = best = 0
    for r, x in enumerate(nums):
        zeros += x == 0
        while zeros > k:  # shrink until back within budget
            zeros -= nums[l] == 0
            l += 1
        best = max(best, r - l + 1)
    return best


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0], 2),
             ([0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1], 3),
             ([1, 0, 1, 0, 1], 1), ([0, 0, 0], 0), ([0, 0, 1], 5)]
    for nums, k in tests:
        print("brute :", longest_ones_brute(nums, k))
        print("window:", longest_ones(nums, k))
        print("---")

"""
Syntax notes (Python):
- zeros += x == 0 adds True/False as 1/0.
- l = zeros = best = 0 initialises several ints at once.
- enumerate gives index and value together.
"""
