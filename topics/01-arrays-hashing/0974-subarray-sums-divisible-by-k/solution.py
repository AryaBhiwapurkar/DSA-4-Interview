"""
0974. Subarray Sums Divisible by K  |  Medium  |  Arrays & Hashing
Link: https://leetcode.com/problems/subarray-sums-divisible-by-k/

Problem: Count non-empty subarrays whose sum is divisible by k (values may be negative).

Examples:
  [4,5,0,-2,-3,1], k = 5  -> 7
  [5],             k = 9  -> 0
  [0,0],           k = 3  -> 3
  [-5],            k = 5  -> 1
  [-1,2,9],        k = 2  -> 2

Approaches:
  1. All subarrays             O(n^2) time, O(1) space
  2. Remainder counts  ⭐      O(n) time, O(k) space   <- go-to
"""


# ---------- Approach 1: All Subarrays ----------
def subarrays_div_by_k_brute(nums: list[int], k: int) -> int:
    count = 0
    for i in range(len(nums)):
        s = 0
        for j in range(i, len(nums)):
            s += nums[j]
            count += s % k == 0
    return count


# ---------- Approach 2: Remainder Counts ⭐ ----------
def subarrays_div_by_k(nums: list[int], k: int) -> int:
    cnt = [0] * k
    cnt[0] = 1  # empty prefix
    r = count = 0
    for x in nums:
        r = (r + x) % k  # Python % is already in 0..k-1 for k > 0
        count += cnt[r]  # pair with every earlier equal remainder
        cnt[r] += 1
    return count


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([4, 5, 0, -2, -3, 1], 5), ([5], 9), ([0, 0], 3), ([-5], 5), ([-1, 2, 9], 2)]
    for nums, k in tests:
        print("brute    :", subarrays_div_by_k_brute(nums, k))
        print("remainder:", subarrays_div_by_k(nums, k))
        print("---")

"""
Syntax notes (Python):
- Python's % follows the divisor's sign: -2 % 5 == 3, so no normalising step is needed.
- count += (s % k == 0) adds 1 for True, 0 for False.
- Alternative: Counter of all prefix remainders, then sum c * (c - 1) // 2 pairs per remainder.
"""
