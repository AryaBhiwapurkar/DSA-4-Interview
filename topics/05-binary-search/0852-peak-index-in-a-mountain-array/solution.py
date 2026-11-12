"""
0852. Peak Index in a Mountain Array  |  Medium  |  Binary Search
Link: https://leetcode.com/problems/peak-index-in-a-mountain-array/

Problem: The array strictly rises to one peak then strictly falls.
         Return the peak's index in O(log n).

Examples:
  [0,1,0]                              -> 1
  [0,2,1,0]                            -> 1
  [0,10,5,2]                           -> 1
  [3,4,5,1]                            -> 2
  [24,69,100,99,79,78,67,36,26,19]     -> 2

Approaches:
  1. Linear scan                    O(n) time, O(1) space
  2. Binary search on the slope ⭐  O(log n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Linear Scan ----------
def peak_index_in_mountain_array_linear(arr: list[int]) -> int:
    return next(i for i in range(len(arr) - 1) if arr[i] > arr[i + 1])


# ---------- Approach 2: Binary Search on the Slope ⭐ ----------
def peak_index_in_mountain_array(arr: list[int]) -> int:
    lo, hi = 0, len(arr) - 1
    while lo < hi:
        mid = (lo + hi) // 2  # mid < hi, so mid + 1 is in bounds
        if arr[mid] < arr[mid + 1]:
            lo = mid + 1  # still climbing
        else:
            hi = mid  # at or past the peak
    return lo


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [[0, 1, 0], [0, 2, 1, 0], [0, 10, 5, 2], [3, 4, 5, 1], [24, 69, 100, 99, 79, 78, 67, 36, 26, 19]]
    for t in tests:
        print("linear:", peak_index_in_mountain_array_linear(t))
        print("binary:", peak_index_in_mountain_array(t))
        print("---")

"""
Syntax notes (Python):
- next(generator) returns the first matching item (raises StopIteration if none).
- (lo + hi) // 2 is floor division: mid < hi whenever lo < hi.
- range(len(arr) - 1) stops before the last index so arr[i + 1] is valid.
"""
