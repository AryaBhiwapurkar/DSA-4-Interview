"""
0448. Find All Numbers Disappeared in an Array  |  Easy  |  Arrays & Hashing
Link: https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/

Problem: Values are in 1..n (some repeated). Return every number in 1..n that's absent.

Examples:
  [4,3,2,7,8,2,3,1]  -> [5,6]
  [1,1]              -> [2]
  [1,2,3]            -> []
  [1,1,1]            -> [2,3]
  [2,2]              -> [1]

Approaches:
  1. Set difference             O(n) time, O(n) space
  2. Negation marking  ⭐       O(n) time, O(1) extra   <- go-to
"""


# ---------- Approach 1: Set Difference ----------
def find_disappeared_numbers_set(nums: list[int]) -> list[int]:
    present = set(nums)
    return [v for v in range(1, len(nums) + 1) if v not in present]


# ---------- Approach 2: Negation Marking ⭐ ----------
def find_disappeared_numbers(nums: list[int]) -> list[int]:
    nums = nums[:]
    for x in nums:
        j = abs(x) - 1  # x may already be negated
        if nums[j] > 0:
            nums[j] = -nums[j]  # mark "j + 1 seen"
    return [i + 1 for i, x in enumerate(nums) if x > 0]


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[4, 3, 2, 7, 8, 2, 3, 1], [1, 1], [1, 2, 3], [1, 1, 1], [2, 2]]:
        print("seen  :", find_disappeared_numbers_set(t))
        print("negate:", find_disappeared_numbers(t))
        print("---")

"""
Syntax notes (Python):
- Iterating `for x in nums` while assigning nums[j] is fine: the list size doesn't change,
  and each x is read when the loop reaches it (possibly already negated).
- set(range(1, n + 1)) - set(nums) is the one-liner version (unordered result).
- List comprehension with enumerate collects indices that pass a test.
"""
