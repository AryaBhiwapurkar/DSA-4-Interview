"""
0992. Subarrays with K Different Integers  |  Hard  |  Sliding Window
Link: https://leetcode.com/problems/subarrays-with-k-different-integers/

Problem: Count contiguous subarrays with exactly k distinct values.

Examples:
  [1,2,1,2,3], k = 2  -> 7
  [1,2,1,3,4], k = 3  -> 3
  [1,1,1],     k = 1  -> 6
  [1,2],       k = 3  -> 0

Approaches:
  1. All subarrays with a set                 O(n^2) time, O(n) space
  2. atMost(k) - atMost(k - 1)  ⭐            O(n) time, O(n) space   <- go-to
"""


# ---------- Approach 1: All Subarrays ----------
def subarrays_with_k_distinct_brute(nums: list[int], k: int) -> int:
    count = 0
    for i in range(len(nums)):
        seen: set[int] = set()
        for j in range(i, len(nums)):
            seen.add(nums[j])
            if len(seen) > k:
                break
            count += len(seen) == k
    return count


# ---------- Approach 2: atMost Difference ⭐ ----------
def at_most(nums: list[int], k: int) -> int:
    cnt = [0] * (len(nums) + 1)  # values are in 1..n
    l = distinct = total = 0
    for r, x in enumerate(nums):
        if cnt[x] == 0:
            distinct += 1
        cnt[x] += 1
        while distinct > k:
            cnt[nums[l]] -= 1
            if cnt[nums[l]] == 0:
                distinct -= 1
            l += 1
        total += r - l + 1  # subarrays ending at r with <= k distinct
    return total


def subarrays_with_k_distinct(nums: list[int], k: int) -> int:
    return at_most(nums, k) - at_most(nums, k - 1)


# ---------- Driver ----------
if __name__ == "__main__":
    for nums, k in [([1, 2, 1, 2, 3], 2), ([1, 2, 1, 3, 4], 3), ([1, 1, 1], 1), ([1, 2], 3)]:
        print("brute :", subarrays_with_k_distinct_brute(nums, k))
        print("atMost:", subarrays_with_k_distinct(nums, k))
        print("---")

"""
Syntax notes (Python):
- count += len(seen) == k adds 1 when the condition is True.
- A list indexed by value is faster than a dict when values are small and bounded.
- Helper functions at module level keep the go-to a one-liner.
"""
