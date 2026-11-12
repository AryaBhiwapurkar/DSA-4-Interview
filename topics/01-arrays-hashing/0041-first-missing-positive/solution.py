"""
0041. First Missing Positive  |  Hard  |  Arrays & Hashing
Link: https://leetcode.com/problems/first-missing-positive/

Problem: Smallest positive integer missing from an unsorted array,
         in O(n) time and O(1) extra space.

Examples:
  [1,2,0]         -> 3
  [3,4,-1,1]      -> 2
  [7,8,9,11,12]   -> 1
  [1]             -> 2
  [1,1]           -> 2
  [2,1]           -> 3

Approaches:
  1. Sort and scan             O(n log n) time, O(1) extra
  2. Hash set                  O(n) time, O(n) space
  3. Cyclic placement  ⭐      O(n) time, O(1) extra   <- go-to
"""


# ---------- Approach 1: Sort and Scan ----------
def first_missing_positive_sort(nums: list[int]) -> int:
    want = 1
    for x in sorted(nums):
        if x == want:  # duplicates and junk just don't match
            want += 1
    return want


# ---------- Approach 2: Hash Set ----------
def first_missing_positive_set(nums: list[int]) -> int:
    s = set(nums)
    want = 1
    while want in s:
        want += 1
    return want


# ---------- Approach 3: Cyclic Placement ⭐ ----------
def first_missing_positive(nums: list[int]) -> int:
    nums = nums[:]
    n = len(nums)
    for i in range(n):
        while 1 <= nums[i] <= n and nums[nums[i] - 1] != nums[i]:  # stops on duplicates
            v = nums[i]  # save first: nums[i] changes during the swap
            nums[i], nums[v - 1] = nums[v - 1], v  # value v goes home to index v - 1
    for i, x in enumerate(nums):
        if x != i + 1:
            return i + 1
    return n + 1


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[1, 2, 0], [3, 4, -1, 1], [7, 8, 9, 11, 12], [1], [1, 1], [2, 1]]:
        print("sort  :", first_missing_positive_sort(t))
        print("set   :", first_missing_positive_set(t))
        print("cyclic:", first_missing_positive(t))
        print("---")

"""
Syntax notes (Python):
- In a, b = b, a the right side is evaluated first, but targets are assigned left to right,
  so nums[i], nums[nums[i]-1] = ... reads the NEW nums[i] for the second target. Cache v.
- 1 <= x <= n chains comparisons.
- nums[:] copies so the caller's list isn't rearranged.
"""
