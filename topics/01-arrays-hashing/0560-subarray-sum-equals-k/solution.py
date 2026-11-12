"""
0560. Subarray Sum Equals K  |  Medium  |  Arrays & Hashing
Link: https://leetcode.com/problems/subarray-sum-equals-k/

Problem: Count contiguous subarrays whose sum is exactly k (values may be negative).

Examples:
  [1,1,1],     k = 2  -> 2
  [1,2,3],     k = 3  -> 2
  [3,4,-7,3],  k = 3  -> 3
  [0,0,0],     k = 0  -> 6
  [1,-1,0],    k = 0  -> 3

Approaches:
  1. All start/end pairs           O(n^2) time, O(1) space
  2. Prefix sum + count map  ⭐    O(n) time, O(n) space   <- go-to
"""

from collections import defaultdict


# ---------- Approach 1: All Pairs ----------
def subarray_sum_brute(nums: list[int], k: int) -> int:
    count = 0
    for i in range(len(nums)):
        s = 0
        for j in range(i, len(nums)):
            s += nums[j]
            count += s == k
    return count


# ---------- Approach 2: Prefix Sum + Count Map ⭐ ----------
def subarray_sum(nums: list[int], k: int) -> int:
    seen: defaultdict[int, int] = defaultdict(int)
    seen[0] = 1  # empty prefix: subarrays starting at 0
    prefix = count = 0
    for x in nums:
        prefix += x
        count += seen.get(prefix - k, 0)  # earlier prefix P with prefix - P == k
        seen[prefix] += 1  # add after lookup
    return count


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([1, 1, 1], 2), ([1, 2, 3], 3), ([3, 4, -7, 3], 3), ([0, 0, 0], 0), ([1, -1, 0], 0)]
    for nums, k in tests:
        print("brute :", subarray_sum_brute(nums, k))
        print("prefix:", subarray_sum(nums, k))
        print("---")

"""
Syntax notes (Python):
- count += (s == k) works because bool is a subclass of int.
- d.get(key, 0) reads without inserting, even on a defaultdict.
- itertools.accumulate(nums, initial=0) yields all prefix sums if you want them as a list.
"""
