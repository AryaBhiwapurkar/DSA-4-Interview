"""
0128. Longest Consecutive Sequence  |  Medium  |  Arrays & Hashing
Link: https://leetcode.com/problems/longest-consecutive-sequence/

Problem: Return the length of the longest run of consecutive integers
         that can be formed from the array's values. O(n) required.

Examples:
  [100,4,200,1,3,2]        -> 4
  [0,3,7,2,5,8,4,6,0,1]    -> 9
  [1,0,1,2]                -> 3
  []                       -> 0

Approaches:
  1. Sort + scan                 O(n log n) time, O(n) space (sorted copy)
  2. Hash set, start-of-run  ⭐   O(n) time, O(n) space   <- go-to
"""


# ---------- Approach 1: Sort + Scan ----------
def longest_consecutive_sorted(nums: list[int]) -> int:
    if not nums:
        return 0
    s = sorted(nums)
    best = cur = 1
    for prev, x in zip(s, s[1:]):
        if x == prev:  # duplicate: neither breaks nor extends
            continue
        cur = cur + 1 if x == prev + 1 else 1
        best = max(best, cur)
    return best


# ---------- Approach 2: Hash Set, Start-of-Run ⭐ ----------
def longest_consecutive(nums: list[int]) -> int:
    s = set(nums)
    best = 0
    for x in s:  # iterate the set: each value once
        if x - 1 in s:  # not a run start
            continue
        length = 1
        while x + length in s:
            length += 1
        best = max(best, length)
    return best


# ---------- Driver ----------
if __name__ == "__main__":
    for nums in [[100, 4, 200, 1, 3, 2], [0, 3, 7, 2, 5, 8, 4, 6, 0, 1], [1, 0, 1, 2], []]:
        print("sorted:", longest_consecutive_sorted(nums))
        print("set   :", longest_consecutive(nums))
        print("---")

"""
Syntax notes (Python):
- zip(s, s[1:]) walks adjacent pairs (prev, cur).
- best = cur = 1 chains assignment to the same value.
- `x - 1 in s` parses as `(x - 1) in s`.
"""
