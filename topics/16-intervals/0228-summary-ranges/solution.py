"""
0228. Summary Ranges  |  Easy  |  Intervals
Link: https://leetcode.com/problems/summary-ranges/

Problem: Given a sorted array of distinct ints, describe it as the fewest
         ranges of consecutive numbers ("a->b", or "a" for a single number).

Examples:
  [0,1,2,4,5,7]       -> ["0->2","4->5","7"]
  [0,2,3,4,6,8,9]     -> ["0","2->4","6","8->9"]
  []                  -> []
  [-1]                -> ["-1"]
  [-2147483648,2147483647] -> ["-2147483648","2147483647"]

Approaches:
  1. Group by (value - index)          O(n) time, O(n) space
  2. One scan with a run start  ⭐      O(n) time, O(1) extra   <- go-to
"""

from itertools import groupby


def fmt(a: int, b: int) -> str:
    return str(a) if a == b else f"{a}->{b}"


# ---------- Approach 1: Group by value - index ----------
def summary_ranges_group(nums: list[int]) -> list[str]:
    res = []
    for _, grp in groupby(enumerate(nums), key=lambda p: p[1] - p[0]):  # constant within a run
        run = [v for _, v in grp]
        res.append(fmt(run[0], run[-1]))
    return res


# ---------- Approach 2: One Scan ⭐ ----------
def summary_ranges(nums: list[int]) -> list[str]:
    res = []
    i = 0
    while i < len(nums):
        start = nums[i]
        while i + 1 < len(nums) and nums[i + 1] == nums[i] + 1:  # extend the run
            i += 1
        res.append(fmt(start, nums[i]))
        i += 1
    return res


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[0, 1, 2, 4, 5, 7], [0, 2, 3, 4, 6, 8, 9], [], [-1], [-2147483648, 2147483647]]:
        print("group:", summary_ranges_group(t))
        print("scan :", summary_ranges(t))
        print("---")

"""
Syntax notes (Python):
- itertools.groupby groups CONSECUTIVE items with the same key.
- In a run of consecutive numbers, value - index stays constant.
- f"{a}->{b}" builds the range string.
"""
