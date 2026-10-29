"""
0238. Product of Array Except Self  |  Medium  |  Arrays & Hashing
Link: https://leetcode.com/problems/product-of-array-except-self/

Problem: Return ans where ans[i] is the product of all elements except
         nums[i]. No division, O(n) time.

Examples:
  [1,2,3,4]        -> [24,12,8,6]
  [-1,1,0,-3,3]    -> [0,0,9,0,0]
  [0,0,5]          -> [0,0,0]

Approaches:
  1. Brute force                    O(n^2) time, O(1) extra space
  2. Prefix + suffix arrays         O(n) time, O(n) extra space
  3. Output + running suffix  ⭐     O(n) time, O(1) extra space   <- go-to
"""


# ---------- Approach 1: Brute Force ----------
def product_except_self_brute(nums: list[int]) -> list[int]:
    n = len(nums)
    ans = [1] * n
    for i in range(n):
        for j in range(n):
            if j != i:
                ans[i] *= nums[j]
    return ans


# ---------- Approach 2: Prefix + Suffix Arrays ----------
def product_except_self_arrays(nums: list[int]) -> list[int]:
    n = len(nums)
    prefix, suffix = [1] * n, [1] * n
    for i in range(1, n):
        prefix[i] = prefix[i - 1] * nums[i - 1]  # product left of i
    for i in range(n - 2, -1, -1):
        suffix[i] = suffix[i + 1] * nums[i + 1]  # product right of i
    return [p * s for p, s in zip(prefix, suffix)]


# ---------- Approach 3: Output Array + Running Suffix ⭐ ----------
def product_except_self(nums: list[int]) -> list[int]:
    n = len(nums)
    ans = [1] * n
    for i in range(1, n):
        ans[i] = ans[i - 1] * nums[i - 1]  # ans holds left products
    suffix = 1
    for i in range(n - 1, -1, -1):
        ans[i] *= suffix  # left * right
        suffix *= nums[i]
    return ans


# ---------- Driver ----------
if __name__ == "__main__":
    for nums in [[1, 2, 3, 4], [-1, 1, 0, -3, 3], [0, 0, 5]]:
        print("brute :", product_except_self_brute(nums))
        print("arrays:", product_except_self_arrays(nums))
        print("suffix:", product_except_self(nums))
        print("---")

"""
Syntax notes (Python):
- range(n - 1, -1, -1) iterates n-1 down to 0 (stop is exclusive).
- [1] * n is safe for immutable values like ints (not for nested lists).
- zip(a, b) pairs elements position-wise.
"""
