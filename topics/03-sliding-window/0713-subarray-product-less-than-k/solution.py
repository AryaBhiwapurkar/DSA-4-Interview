"""
0713. Subarray Product Less Than K  |  Medium  |  Sliding Window
Link: https://leetcode.com/problems/subarray-product-less-than-k/

Problem: Count contiguous subarrays (positive values) with product strictly below k.

Examples:
  [10,5,2,6], k = 100  -> 8
  [1,2,3],    k = 0    -> 0
  [1,1,1],    k = 2    -> 6
  [5],        k = 5    -> 0
  [1,2,3],    k = 1    -> 0

Approaches:
  1. All start/end pairs           O(n^2) time, O(1) space
  2. Sliding window + count  ⭐    O(n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: All Pairs ----------
def num_subarray_product_less_than_k_brute(nums: list[int], k: int) -> int:
    count = 0
    for i in range(len(nums)):
        prod = 1
        for j in range(i, len(nums)):
            prod *= nums[j]
            if prod >= k:  # positive values: only grows from here
                break
            count += 1
    return count


# ---------- Approach 2: Sliding Window ⭐ ----------
def num_subarray_product_less_than_k(nums: list[int], k: int) -> int:
    if k <= 1:
        return 0  # no positive product is < 1
    prod, l, count = 1, 0, 0
    for r, x in enumerate(nums):
        prod *= x
        while prod >= k:
            prod //= nums[l]
            l += 1
        count += r - l + 1  # subarrays ending at r: starts l..r
    return count


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([10, 5, 2, 6], 100), ([1, 2, 3], 0), ([1, 1, 1], 2), ([5], 5), ([1, 2, 3], 1)]
    for nums, k in tests:
        print("brute :", num_subarray_product_less_than_k_brute(nums, k))
        print("window:", num_subarray_product_less_than_k(nums, k))
        print("---")

"""
Syntax notes (Python):
- //= keeps the product an exact int (the divisor always divides it).
- prod, l, count = 1, 0, 0 sets three variables at once.
- Guard clauses (if k <= 1: return 0) keep the main loop simple.
"""
