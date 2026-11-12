"""
0977. Squares of a Sorted Array  |  Easy  |  Two Pointers
Link: https://leetcode.com/problems/squares-of-a-sorted-array/

Problem: Sorted array (may include negatives) -> sorted array of squares.

Examples:
  [-4,-1,0,3,10]  -> [0,1,9,16,100]
  [-7,-3,2,3,11]  -> [4,9,9,49,121]
  [-5,-3,-1]      -> [1,9,25]
  [2]             -> [4]

Approaches:
  1. Square and sort                   O(n log n) time, O(n) space
  2. Two pointers, fill from back  ⭐  O(n) time, O(n) output   <- go-to
"""


# ---------- Approach 1: Square and Sort ----------
def sorted_squares_sort(nums: list[int]) -> list[int]:
    return sorted(x * x for x in nums)


# ---------- Approach 2: Two Pointers ⭐ ----------
def sorted_squares(nums: list[int]) -> list[int]:
    n = len(nums)
    lo, hi = 0, n - 1
    res = [0] * n
    for k in range(n - 1, -1, -1):  # largest square is at an end
        if abs(nums[lo]) > abs(nums[hi]):
            res[k] = nums[lo] * nums[lo]
            lo += 1
        else:
            res[k] = nums[hi] * nums[hi]
            hi -= 1
    return res


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[-4, -1, 0, 3, 10], [-7, -3, 2, 3, 11], [-5, -3, -1], [2]]:
        print("sort    :", sorted_squares_sort(t))
        print("pointers:", sorted_squares(t))
        print("---")

"""
Syntax notes (Python):
- sorted(generator) accepts any iterable and returns a new list.
- range(n - 1, -1, -1) fills the result from the back.
- [0] * n preallocates a list you then assign by index.
"""
