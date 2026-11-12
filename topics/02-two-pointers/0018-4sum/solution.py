"""
0018. 4Sum  |  Medium  |  Two Pointers
Link: https://leetcode.com/problems/4sum/

Problem: All unique quadruplets (by value, distinct indices) summing to target.

Examples:
  [1,0,-1,0,-2,2],  target = 0   -> [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
  [2,2,2,2,2],      target = 8   -> [[2,2,2,2]]
  [1000000000,1000000000,1000000000,1000000000], target = -294967296 -> []   (int overflow trap in C++)
  [1,2,3],          target = 6   -> []   (fewer than 4 numbers)

Approaches:
  1. Four loops + set                          O(n^4) time
  2. Sort + two loops + two pointers  ⭐       O(n^3) time, O(1) extra   <- go-to
"""

from itertools import combinations


# ---------- Approach 1: Four Loops + Set ----------
def four_sum_brute(nums: list[int], target: int) -> list[list[int]]:
    found = {q for q in combinations(sorted(nums), 4) if sum(q) == target}  # sorted -> canonical tuples
    return [list(q) for q in found]


# ---------- Approach 2: Sort + Two Pointers ⭐ ----------
def four_sum(nums: list[int], target: int) -> list[list[int]]:
    nums = sorted(nums)
    n = len(nums)
    res: list[list[int]] = []
    for i in range(n - 3):
        if i > 0 and nums[i] == nums[i - 1]:
            continue
        for j in range(i + 1, n - 2):
            if j > i + 1 and nums[j] == nums[j - 1]:  # dedupe j relative to its own start
                continue
            lo, hi = j + 1, n - 1
            while lo < hi:
                s = nums[i] + nums[j] + nums[lo] + nums[hi]
                if s < target:
                    lo += 1
                elif s > target:
                    hi -= 1
                else:
                    res.append([nums[i], nums[j], nums[lo], nums[hi]])
                    while lo < hi and nums[lo] == nums[lo + 1]:
                        lo += 1
                    while lo < hi and nums[hi] == nums[hi - 1]:
                        hi -= 1
                    lo, hi = lo + 1, hi - 1
    return res


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([1, 0, -1, 0, -2, 2], 0), ([2, 2, 2, 2, 2], 8),
             ([1000000000] * 4, -294967296), ([1, 2, 3], 6)]
    for nums, t in tests:
        print("brute   :", sorted(four_sum_brute(nums, t)))
        print("pointers:", sorted(four_sum(nums, t)))
        print("---")

"""
Syntax notes (Python):
- itertools.combinations(sorted(nums), 4) yields index-distinct quadruples in sorted order.
- A set comprehension of tuples removes duplicate quadruplets.
- Python ints don't overflow, but the 64-bit concern is real in C++/Java.
"""
