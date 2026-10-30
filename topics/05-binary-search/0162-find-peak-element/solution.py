"""
0162. Find Peak Element  |  Medium  |  Binary Search
Link: https://leetcode.com/problems/find-peak-element/

Problem: Return the index of any element strictly greater than its
         neighbours (outside the array counts as -inf). O(log n).

Examples (any peak is accepted; each approach's answer is checked):
  [1,2,3,1]        -> 2
  [1,2,1,3,5,6,4]  -> 1 or 5   (linear finds 1, binary finds 5)
  [1]              -> 0
  [3,2,1]          -> 0
  [1,2,3]          -> 2

Approaches:
  1. Linear scan                 O(n) time, O(1) space
  2. Binary search on slope  ⭐   O(log n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Linear Scan ----------
def find_peak_element_linear(nums: list[int]) -> int:
    for i in range(len(nums) - 1):
        if nums[i] > nums[i + 1]:  # first downhill step: everything before rose
            return i
    return len(nums) - 1


# ---------- Approach 2: Binary Search on Slope ⭐ ----------
def find_peak_element(nums: list[int]) -> int:
    lo, hi = 0, len(nums) - 1
    while lo < hi:  # lo < hi guarantees mid + 1 <= hi
        mid = (lo + hi) // 2
        if nums[mid] > nums[mid + 1]:
            hi = mid  # downhill: peak at mid or left
        else:
            lo = mid + 1  # uphill: peak strictly right
    return lo


# ---------- Driver ----------
def is_peak(a: list[int], i: int) -> bool:
    return (i == 0 or a[i] > a[i - 1]) and (i == len(a) - 1 or a[i] > a[i + 1])


if __name__ == "__main__":
    tests = [[1, 2, 3, 1], [1, 2, 1, 3, 5, 6, 4], [1], [3, 2, 1], [1, 2, 3]]
    for nums in tests:
        a, b = find_peak_element_linear(nums), find_peak_element(nums)
        print(f"linear: {a} peak={is_peak(nums, a)}")
        print(f"binary: {b} peak={is_peak(nums, b)}")
        print("---")

"""
Syntax notes (Python):
- a[i - 1] with i == 0 would silently read a[-1] (the LAST element), so the
  `i == 0 or ...` guard matters in Python too.
- f-strings: f"{x} peak={flag}" formats values inline.
"""
