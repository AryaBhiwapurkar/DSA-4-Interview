"""
0007. Reverse Integer  |  Medium  |  Bit Manipulation
Link: https://leetcode.com/problems/reverse-integer/

Problem: Reverse the decimal digits of a 32-bit signed int. Return 0 if the
         result doesn't fit in 32 bits. Assume no 64-bit integers are available.

Examples:
  123           -> 321
  -123          -> -321
  120           -> 21
  1534236469    -> 0   (9646324351 overflows)
  -2147483648   -> 0
  -2147483412   -> -2143847412

Approaches:
  1. String reverse + range check           O(d) time, O(d) space
  2. Pop digits, check before pushing  ⭐    O(d) time, O(1) space   <- go-to
"""

INT_MAX, INT_MIN = 2**31 - 1, -(2**31)


# ---------- Approach 1: String Reverse ----------
def reverse_str(x: int) -> int:
    sign = -1 if x < 0 else 1
    r = sign * int(str(abs(x))[::-1])
    return r if INT_MIN <= r <= INT_MAX else 0


# ---------- Approach 2: Pop and Check ⭐ ----------
def reverse(x: int) -> int:
    sign = -1 if x < 0 else 1
    x = abs(x)  # Python's % floors toward -inf, so work on the magnitude
    limit = INT_MAX if sign > 0 else -INT_MIN  # 2147483647 or 2147483648
    r = 0
    while x:
        d = x % 10
        x //= 10
        if r > (limit - d) // 10:  # r * 10 + d would exceed the limit
            return 0
        r = r * 10 + d
    return sign * r


# ---------- Driver ----------
if __name__ == "__main__":
    for x in [123, -123, 120, 1534236469, -2147483648, -2147483412]:
        print("string:", reverse_str(x))
        print("pop   :", reverse(x))
        print("---")

"""
Syntax notes (Python):
- -7 % 10 == 3 in Python (floor), unlike C++ (-7); take abs() first.
- s[::-1] reverses a string; int("021") == 21 drops leading zeros.
- Python ints never overflow, so the range check is explicit.
"""
