"""
0300. Longest Increasing Subsequence  |  Medium  |  1-D Dynamic Programming
Link: https://leetcode.com/problems/longest-increasing-subsequence/

Problem: Length of the longest strictly increasing subsequence (elements in
         order, not necessarily adjacent).

Examples:
  [10,9,2,5,3,7,101,18]  -> 4
  [0,1,0,3,2,3]          -> 4
  [7,7,7,7,7,7,7]        -> 1
  [5]                    -> 1
  [4,10,4,3,8,9]         -> 3

Approaches:
  1. DP: longest ending at i                 O(n^2) time, O(n) space
  2. Tails array + binary search  ⭐          O(n log n) time, O(n) space   <- go-to
"""

from bisect import bisect_left


# ---------- Approach 1: O(n^2) DP ----------
def length_of_lis_dp(nums: list[int]) -> int:
    dp = [1] * len(nums)  # dp[i]: LIS that ends exactly at i
    for i in range(1, len(nums)):
        for j in range(i):
            if nums[j] < nums[i]:
                dp[i] = max(dp[i], dp[j] + 1)
    return max(dp)


# ---------- Approach 2: Tails + Binary Search ⭐ ----------
def length_of_lis(nums: list[int]) -> int:
    tails: list[int] = []  # tails[k]: smallest tail of any increasing run of length k+1
    for x in nums:
        k = bisect_left(tails, x)  # first tail >= x (strict increase)
        if k == len(tails):
            tails.append(x)  # x extends the longest run
        else:
            tails[k] = x  # x is a smaller tail for that length
    return len(tails)


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[10, 9, 2, 5, 3, 7, 101, 18], [0, 1, 0, 3, 2, 3], [7, 7, 7, 7, 7, 7, 7], [5], [4, 10, 4, 3, 8, 9]]:
        print("dp    :", length_of_lis_dp(t))
        print("tails :", length_of_lis(t))
        print("---")

"""
Syntax notes (Python):
- bisect_left(a, x): first index with a[i] >= x; bisect_right: first index with a[i] > x.
- [1] * n is fine for immutable ints (each slot is independent).
- max(list) on a non-empty list returns the largest value.
"""
