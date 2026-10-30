"""
0069. Sqrt(x)  |  Easy  |  Binary Search
Link: https://leetcode.com/problems/sqrtx/

Problem: Return floor(sqrt(x)) for 0 <= x <= 2^31 - 1 without sqrt/pow.

Examples:
  4           -> 2
  8           -> 2
  0           -> 0
  1           -> 1
  2147395599  -> 46339
  2147483647  -> 46340

Approaches:
  1. Linear scan                O(sqrt x) time, O(1) space
  2. Binary search on answer ⭐  O(log x) time, O(1) space   <- go-to
  3. Newton's method            O(log x) iterations, O(1) space
"""


# ---------- Approach 1: Linear Scan ----------
def my_sqrt_linear(x: int) -> int:
    k = 0
    while (k + 1) * (k + 1) <= x:
        k += 1
    return k


# ---------- Approach 2: Binary Search on Answer ⭐ ----------
def my_sqrt(x: int) -> int:
    lo, hi, ans = 0, x, 0
    while lo <= hi:
        mid = (lo + hi) // 2
        if mid * mid <= x:
            ans = mid  # mid works; try bigger
            lo = mid + 1
        else:
            hi = mid - 1
    return ans


# ---------- Approach 3: Newton's Method ----------
def my_sqrt_newton(x: int) -> int:
    r = x
    while r * r > x:
        r = (r + x // r) // 2  # integer Newton step, decreases to the floor
    return r


# ---------- Driver ----------
if __name__ == "__main__":
    for x in [4, 8, 0, 1, 2147395599, 2147483647]:
        print("linear:", my_sqrt_linear(x))
        print("binary:", my_sqrt(x))
        print("newton:", my_sqrt_newton(x))
        print("---")

"""
Syntax notes (Python):
- Python ints are arbitrary precision, so mid * mid never overflows.
- Use // for integer division; / would return a float and lose exactness.
- math.isqrt(x) is the built-in exact integer sqrt (not allowed here).
"""
