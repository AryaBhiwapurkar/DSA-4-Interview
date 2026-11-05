"""
0201. Bitwise AND of Numbers Range  |  Medium  |  Bit Manipulation
Link: https://leetcode.com/problems/bitwise-and-of-numbers-range/

Problem: Return left & (left+1) & ... & right.

Examples:
  5, 7              -> 4
  0, 0              -> 0
  1, 2147483647     -> 0
  12, 15            -> 12
  6, 6              -> 6

Approaches:
  1. AND every number (stop early at 0)       O(right - left) time, O(1) space
  2. Shift both down to the common prefix  ⭐  O(32) time, O(1) space   <- go-to
  3. Clear right's low bits: right &= right - 1 while right > left   O(32) time, O(1) space
"""


# ---------- Approach 1: Brute Force ----------
def range_bitwise_and_brute(left: int, right: int) -> int:
    res = left
    for x in range(left + 1, right + 1):
        res &= x
        if res == 0:  # can't come back from 0
            break
    return res


# ---------- Approach 2: Common Prefix ⭐ ----------
def range_bitwise_and(left: int, right: int) -> int:
    shift = 0
    while left != right:  # differing low bits all become 0 somewhere in the range
        left >>= 1
        right >>= 1
        shift += 1
    return left << shift


# ---------- Approach 3: Clear Lowest Bits ----------
def range_bitwise_and_kernighan(left: int, right: int) -> int:
    while right > left:
        right &= right - 1  # drop right's lowest 1 bit
    return right


# ---------- Driver ----------
if __name__ == "__main__":
    for left, right in [(5, 7), (0, 0), (1, 2147483647), (12, 15), (6, 6)]:
        print("brute    :", range_bitwise_and_brute(left, right))
        print("prefix   :", range_bitwise_and(left, right))
        print("kernighan:", range_bitwise_and_kernighan(left, right))
        print("---")

"""
Syntax notes (Python):
- range(left + 1, right + 1) is lazy, so a huge range costs nothing until iterated.
- left << shift puts the common prefix back in place, with zeros below.
- right &= right - 1 is the same lowest-bit trick as LC 191.
"""
