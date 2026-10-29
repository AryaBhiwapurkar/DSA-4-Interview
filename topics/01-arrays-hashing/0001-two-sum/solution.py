"""
0001. Two Sum  |  Easy  |  Arrays & Hashing
Link: https://leetcode.com/problems/two-sum/

Problem: Given an array and a target, return indices of the two
         numbers that add up to target. Exactly one answer exists;
         the same element can't be used twice.

Examples:
  [2,7,11,15], target 9  -> [0,1]
  [3,2,4],     target 6  -> [1,2]
  [3,3],       target 6  -> [0,1]
  [-3,4,3,90], target 0  -> [0,2]

Approaches:
  1. Brute force        O(n^2) time, O(1) space
  2. Sort + two ptrs    O(n log n) time, O(n) space
  3. Hashmap  ⭐         O(n) time, O(n) space   <- go-to
"""


# ---------- Approach 1: Brute Force ----------
def two_sum_brute(nums: list[int], target: int) -> list[int]:
    n = len(nums)
    for i in range(n):
        for j in range(i + 1, n):  # j > i: never pair an element with itself
            if nums[i] + nums[j] == target:
                return [i, j]
    return []


# ---------- Approach 2: Sort + Two Pointers ----------
def two_sum_sorted(nums: list[int], target: int) -> list[int]:
    arr = sorted((v, i) for i, v in enumerate(nums))  # keep original indices
    l, r = 0, len(arr) - 1
    while l < r:
        s = arr[l][0] + arr[r][0]
        if s == target:
            return sorted([arr[l][1], arr[r][1]])
        if s < target:
            l += 1
        else:
            r -= 1
    return []


# ---------- Approach 3: One-Pass Hashmap ⭐ ----------
def two_sum(nums: list[int], target: int) -> list[int]:
    seen: dict[int, int] = {}  # value -> index
    for i, num in enumerate(nums):
        need = target - num
        if need in seen:
            return [seen[need], i]
        seen[num] = i  # insert AFTER checking: avoids self-match
    return []


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([2, 7, 11, 15], 9), ([3, 2, 4], 6), ([3, 3], 6), ([-3, 4, 3, 90], 0)]
    for nums, target in tests:
        print("brute :", two_sum_brute(nums, target))
        print("sorted:", two_sum_sorted(nums, target))
        print("hash  :", two_sum(nums, target))
        print("---")

"""
Syntax notes (Python):
- enumerate(nums) gives (index, value) pairs.
- `key in dict` is an O(1) average lookup; dict.get(key) returns None if missing.
- Tuples sort lexicographically: sorted((v, i) ...) sorts by value, then index.
- Python ints don't overflow, so no overflow worries in Python.
"""
