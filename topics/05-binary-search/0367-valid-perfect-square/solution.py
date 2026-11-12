"""
0367. Valid Perfect Square  |  Easy  |  Binary Search
Link: https://leetcode.com/problems/valid-perfect-square/

Problem: Return whether a positive integer is a perfect square,
         without a built-in sqrt.

Examples:
  16          -> True
  14          -> False
  1           -> True
  808201      -> True    (899^2)
  2147395600  -> True    (46340^2, largest square in int)
  2147483647  -> False

Approaches:
  1. Linear root scan               O(sqrt n) time, O(1) space
  2. Binary search on the root ⭐   O(log n) time, O(1) space   <- go-to
  3. Newton's method                O(log n) time, O(1) space
"""


# ---------- Approach 1: Linear Root Scan ----------
def is_perfect_square_linear(num: int) -> bool:
    r = 1
    while r * r < num:
        r += 1
    return r * r == num


# ---------- Approach 2: Binary Search on the Root ⭐ ----------
def is_perfect_square(num: int) -> bool:
    lo, hi = 1, num
    while lo <= hi:
        mid = (lo + hi) // 2
        sq = mid * mid
        if sq == num:
            return True
        if sq < num:
            lo = mid + 1
        else:
            hi = mid - 1
    return False


# ---------- Approach 3: Newton's Method ----------
def is_perfect_square_newton(num: int) -> bool:
    x = num
    while x * x > num:
        x = (x + num // x) // 2  # decreases to floor(sqrt(num))
    return x * x == num


# ---------- Driver ----------
if __name__ == "__main__":
    for num in [16, 14, 1, 808201, 2147395600, 2147483647]:
        print("linear:", is_perfect_square_linear(num))
        print("binary:", is_perfect_square(num))
        print("newton:", is_perfect_square_newton(num))
        print("---")

"""
Syntax notes (Python):
- Integer // keeps Newton's iteration exact (no float rounding).
- No overflow: mid * mid is an arbitrary-precision int.
- math.isqrt(num) ** 2 == num is the one-liner outside interviews.
"""
