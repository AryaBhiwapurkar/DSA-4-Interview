"""
0009. Palindrome Number  |  Easy  |  Math & Geometry
Link: https://leetcode.com/problems/palindrome-number/

Problem: Is the integer the same read forwards and backwards (base 10)?

Examples:
  121         -> True
  -121        -> False
  10          -> False
  0           -> True
  12321       -> True   (odd length)
  2147483647  -> False  (full reverse would overflow a 32-bit int)

Approaches:
  1. String compare           O(d) time, O(d) space
  2. Full reverse             O(d) time, O(1) space
  3. Reverse half  ⭐         O(d) time, O(1) space   <- go-to
"""


# ---------- Approach 1: String Compare ----------
def is_palindrome_string(x: int) -> bool:
    s = str(x)
    return s == s[::-1]


# ---------- Approach 2: Full Reverse ----------
def is_palindrome_full(x: int) -> bool:
    if x < 0:
        return False
    rev, t = 0, x
    while t:
        rev = rev * 10 + t % 10
        t //= 10
    return rev == x


# ---------- Approach 3: Reverse Half ⭐ ----------
def is_palindrome(x: int) -> bool:
    if x < 0 or (x % 10 == 0 and x != 0):  # trailing 0 can't be a leading 0
        return False
    rev = 0
    while x > rev:  # stop at the middle
        rev = rev * 10 + x % 10
        x //= 10
    return x == rev or x == rev // 10  # rev // 10 drops the middle digit


# ---------- Driver ----------
if __name__ == "__main__":
    for x in [121, -121, 10, 0, 12321, 2147483647]:
        print("string:", is_palindrome_string(x))
        print("full  :", is_palindrome_full(x))
        print("half  :", is_palindrome(x))
        print("---")

"""
Syntax notes (Python):
- s[::-1] reverses a string.
- divmod-style ops: // floors and % follows the divisor's sign (-121 % 10 == 9), so
  handle negatives before digit loops.
- Python ints never overflow; the 32-bit concern only matters in C++/Java.
"""
