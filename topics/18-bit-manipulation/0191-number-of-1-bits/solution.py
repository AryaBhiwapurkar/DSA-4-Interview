"""
0191. Number of 1 Bits  |  Easy  |  Bit Manipulation
Link: https://leetcode.com/problems/number-of-1-bits/

Problem: Count the set bits (Hamming weight) of a positive integer.

Examples:
  11           -> 3   (1011)
  128          -> 1   (10000000)
  2147483645   -> 30  (thirty 1s and one 0)
  1            -> 1
  2147483647   -> 31

Approaches:
  1. Check every bit with a shift      O(32) time, O(1) space
  2. n & (n - 1) drops the lowest 1  ⭐  O(#set bits) time, O(1) space   <- go-to
  3. Built-in popcount                 O(1) time, O(1) space
"""


# ---------- Approach 1: Shift and Check ----------
def hamming_weight_shift(n: int) -> int:
    count = 0
    while n:
        count += n & 1  # lowest bit
        n >>= 1
    return count


# ---------- Approach 2: n & (n - 1) ⭐ ----------
def hamming_weight(n: int) -> int:
    count = 0
    while n:
        n &= n - 1  # clears the lowest set bit
        count += 1
    return count


# ---------- Approach 3: Built-in ----------
def hamming_weight_builtin(n: int) -> int:
    return n.bit_count()  # Python 3.10+; bin(n).count("1") on older versions


# ---------- Driver ----------
if __name__ == "__main__":
    for n in [11, 128, 2147483645, 1, 2147483647]:
        print("shift  :", hamming_weight_shift(n))
        print("n&(n-1):", hamming_weight(n))
        print("builtin:", hamming_weight_builtin(n))
        print("---")

"""
Syntax notes (Python):
- int.bit_count() counts 1 bits (3.10+).
- n & 1 reads the lowest bit; n >>= 1 drops it.
- For negative ints Python's >> never reaches 0 (infinite sign bits): mask with & 0xFFFFFFFF first.
"""
