"""
0137. Single Number II  |  Medium  |  Bit Manipulation
Link: https://leetcode.com/problems/single-number-ii/

Problem: Every number appears three times except one, which appears once.
         Find it in O(n) time and O(1) extra space.

Examples:
  [2,2,3,2]                       -> 3
  [0,1,0,1,0,1,99]                -> 99
  [-2,-2,1,1,4,1,4,4,-4,-2]       -> -4
  [7]                             -> 7

Approaches:
  1. Hash map of counts                     O(n) time, O(n) space
  2. Count each bit position mod 3  ⭐       O(32n) time, O(1) space   <- go-to
  3. ones / twos state machine              O(n) time, O(1) space
"""

from collections import Counter


# ---------- Approach 1: Counts ----------
def single_number_count(nums: list[int]) -> int:
    return next(x for x, c in Counter(nums).items() if c == 1)


# ---------- Approach 2: Bit Counting ⭐ ----------
def single_number(nums: list[int]) -> int:
    res = 0
    for b in range(32):
        total = sum((x >> b) & 1 for x in nums)  # triples contribute multiples of 3
        if total % 3:
            res |= 1 << b
    return res - (1 << 32) if res >= 1 << 31 else res  # bit 31 set: negative in 32-bit


# ---------- Approach 3: ones / twos ----------
def single_number_states(nums: list[int]) -> int:
    ones = twos = 0  # bits seen once / twice (mod 3)
    for x in nums:
        ones = (ones ^ x) & ~twos
        twos = (twos ^ x) & ~ones
    return ones


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[2, 2, 3, 2], [0, 1, 0, 1, 0, 1, 99], [-2, -2, 1, 1, 4, 1, 4, 4, -4, -2], [7]]:
        print("count :", single_number_count(t))
        print("bits  :", single_number(t))
        print("states:", single_number_states(t))
        print("---")

"""
Syntax notes (Python):
- (x >> b) & 1 reads bit b, also for negatives (Python uses infinite sign bits).
- Python ints are unbounded, so a 32-bit result with bit 31 set must be shifted down by 2^32.
- The ones/twos version needs no fix-up: & ~twos keeps negatives consistent.
"""
