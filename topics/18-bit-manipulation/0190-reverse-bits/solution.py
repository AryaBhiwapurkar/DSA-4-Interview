"""
0190. Reverse Bits  |  Easy  |  Bit Manipulation
Link: https://leetcode.com/problems/reverse-bits/

Problem: Reverse the 32 bits of an integer (bit 0 swaps with bit 31, and so
         on) and return the resulting unsigned value.

Examples:
  43261596     -> 964176192
  2147483644   -> 1073741822
  0            -> 0
  1            -> 2147483648
  4294967293   -> 3221225471   (0xFFFFFFFD)

Approaches:
  1. Bit by bit: shift out of n, into result  ⭐   O(32) time, O(1) space   <- go-to
  2. Divide and conquer swaps (masks)            O(log 32) = O(5) time, O(1) space
"""

MASK = 0xFFFFFFFF


# ---------- Approach 1: Bit by Bit ⭐ ----------
def reverse_bits(n: int) -> int:
    res = 0
    for _ in range(32):  # exactly 32: leading zeros of n become trailing zeros
        res = (res << 1) | (n & 1)
        n >>= 1
    return res


# ---------- Approach 2: Divide and Conquer ----------
def reverse_bits_swap(n: int) -> int:
    n = ((n >> 16) | (n << 16)) & MASK  # swap 16-bit halves
    n = ((n & 0xFF00FF00) >> 8) | ((n & 0x00FF00FF) << 8)  # swap bytes
    n = ((n & 0xF0F0F0F0) >> 4) | ((n & 0x0F0F0F0F) << 4)  # swap nibbles
    n = ((n & 0xCCCCCCCC) >> 2) | ((n & 0x33333333) << 2)  # swap bit pairs
    n = ((n & 0xAAAAAAAA) >> 1) | ((n & 0x55555555) << 1)  # swap single bits
    return n & MASK


# ---------- Driver ----------
if __name__ == "__main__":
    for n in [43261596, 2147483644, 0, 1, 4294967293]:
        print("loop:", reverse_bits(n))
        print("swap:", reverse_bits_swap(n))
        print("---")

"""
Syntax notes (Python):
- Python ints are unbounded, so mask with 0xFFFFFFFF wherever a left shift could pass bit 31.
- (res << 1) | (n & 1) appends n's lowest bit to res.
- Hex masks: 0x55555555 = 0101..., 0x33333333 = 0011..., 0x0F0F0F0F = 00001111...
"""
