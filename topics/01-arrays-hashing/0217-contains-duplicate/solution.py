"""
0217. Contains Duplicate  |  Easy  |  Arrays & Hashing
Link: https://leetcode.com/problems/contains-duplicate/

Problem: Return true if any value appears at least twice in the
         array, false if all elements are distinct.

Examples:
  [1,2,3,1]               -> True
  [1,2,3,4]               -> False
  [1,1,1,3,3,4,3,2,4,2]   -> True
  [7]                     -> False

Approaches:
  1. Brute force        O(n^2) time, O(1) space
  2. Sort + adjacent    O(n log n) time, O(n) space (sorted copy)
  3. Hash set  ⭐        O(n) time, O(n) space   <- go-to
"""


# ---------- Approach 1: Brute Force ----------
def contains_duplicate_brute(nums: list[int]) -> bool:
    n = len(nums)
    for i in range(n):
        for j in range(i + 1, n):
            if nums[i] == nums[j]:
                return True
    return False


# ---------- Approach 2: Sort + Adjacent Check ----------
def contains_duplicate_sorted(nums: list[int]) -> bool:
    s = sorted(nums)  # copy; nums.sort() would mutate the caller's list
    return any(s[i] == s[i - 1] for i in range(1, len(s)))


# ---------- Approach 3: Hash Set ⭐ ----------
def contains_duplicate(nums: list[int]) -> bool:
    seen: set[int] = set()
    for x in nums:
        if x in seen:
            return True
        seen.add(x)
    return False


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [[1, 2, 3, 1], [1, 2, 3, 4], [1, 1, 1, 3, 3, 4, 3, 2, 4, 2], [7]]
    for nums in tests:
        print("brute :", contains_duplicate_brute(nums))
        print("sorted:", contains_duplicate_sorted(nums))
        print("hash  :", contains_duplicate(nums))
        print("---")

"""
Syntax notes (Python):
- sorted(x) returns a new list; x.sort() sorts in place and returns None.
- any(generator) short-circuits on the first True.
- One-liner alternative: len(set(nums)) != len(nums) (no early exit).
- set[int] type hint works on Python 3.9+.
"""
