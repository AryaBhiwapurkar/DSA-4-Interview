"""
0371. Sum of Two Integers  |  Medium  |  Bit Manipulation
Link: https://leetcode.com/problems/sum-of-two-integers/

Problem: Return a + b without using the + or - operators.

Examples:
  1, 2        -> 3
  2, 3        -> 5
  -1, 1       -> 0
  -12, -8     -> -20
  1000, -1000 -> 0

Approaches:
  1. Bit-by-bit full adder (32 positions)   O(32) time, O(1) space
  2. XOR for sum, AND << 1 for carry  ⭐     O(32) time, O(1) space   <- go-to
"""

MASK = 0xFFFFFFFF  # emulate 32-bit wraparound
INT_MAX = 0x7FFFFFFF


def to_signed(x: int) -> int:
    return x if x <= INT_MAX else ~(x ^ MASK)  # reinterpret bit 31 as the sign


# ---------- Approach 1: Full Adder ----------
def get_sum_adder(a: int, b: int) -> int:
    res, carry = 0, 0
    for i in range(32):
        x, y = (a >> i) & 1, (b >> i) & 1
        res |= (x ^ y ^ carry) << i  # sum bit
        carry = (x & y) | (carry & (x ^ y))  # carry out
    return to_signed(res)


# ---------- Approach 2: XOR + Carry ⭐ ----------
def get_sum(a: int, b: int) -> int:
    a, b = a & MASK, b & MASK
    while b:
        a, b = (a ^ b) & MASK, ((a & b) << 1) & MASK  # sum without carry, carry moved left
    return to_signed(a)


# ---------- Driver ----------
if __name__ == "__main__":
    for a, b in [(1, 2), (2, 3), (-1, 1), (-12, -8), (1000, -1000)]:
        print("adder:", get_sum_adder(a, b))
        print("xor  :", get_sum(a, b))
        print("---")

"""
Syntax notes (Python):
- Python ints are unbounded: without & MASK the carry loop never ends for negatives.
- ~(x ^ MASK) turns a 32-bit pattern with bit 31 set into the matching negative int.
- (a >> i) & 1 reads bit i (works on negatives too: infinite sign bits).
"""
