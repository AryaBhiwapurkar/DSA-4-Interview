"""
0152. Maximum Product Subarray  |  Medium  |  1-D Dynamic Programming
Link: https://leetcode.com/problems/maximum-product-subarray/

Problem: Return the largest product of any non-empty contiguous subarray.

Examples:
  [2,3,-2,4]       -> 6
  [-2,0,-1]        -> 0
  [-2,3,-4]        -> 24
  [-2]             -> -2
  [2,-5,-2,-4,3]   -> 24

Approaches:
  1. Brute force (every start, running product)   O(n^2) time, O(1) space
  2. Track max and min ending here  ⭐              O(n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Brute Force ----------
def max_product_brute(nums: list[int]) -> int:
    best = nums[0]
    for i in range(len(nums)):
        prod = 1
        for j in range(i, len(nums)):
            prod *= nums[j]
            best = max(best, prod)
    return best


# ---------- Approach 2: Track Max and Min ⭐ ----------
def max_product(nums: list[int]) -> int:
    hi = lo = best = nums[0]  # max / min product ending here
    for x in nums[1:]:
        cands = (x, x * hi, x * lo)  # a negative x swaps the roles of hi and lo
        hi, lo = max(cands), min(cands)  # x alone restarts the subarray (e.g. after a 0)
        best = max(best, hi)
    return best


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[2, 3, -2, 4], [-2, 0, -1], [-2, 3, -4], [-2], [2, -5, -2, -4, 3]]:
        print("brute :", max_product_brute(t))
        print("minmax:", max_product(t))
        print("---")

"""
Syntax notes (Python):
- Build the candidate tuple once so hi and lo both use the old values.
- max()/min() accept any iterable, including a tuple.
- Python ints never overflow, so products are exact.
"""
