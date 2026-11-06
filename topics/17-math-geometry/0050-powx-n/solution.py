"""
0050. Pow(x, n)  |  Medium  |  Math & Geometry
Link: https://leetcode.com/problems/powx-n/

Problem: Compute x^n for a float x and an int n (possibly negative).

Examples:
  x = 2.0, n = 10           -> 1024.00000
  x = 2.1, n = 3            -> 9.26100
  x = 2.0, n = -2           -> 0.25000
  x = 5.0, n = 0            -> 1.00000
  x = -1.0, n = -2147483648 -> 1.00000   (INT_MIN)
  x = -2.0, n = 5           -> -32.00000

Approaches:
  1. Multiply |n| times        O(|n|) time, O(1) space      (too slow for big n; demoed on small n only)
  2. Recursive halving         O(log n) time, O(log n) space
  3. Iterative squaring  ⭐    O(log n) time, O(1) space    <- go-to
"""


# ---------- Approach 1: Multiply n Times ----------
def my_pow_linear(x: float, n: int) -> float:
    if n < 0:
        x, n = 1 / x, -n
    r = 1.0
    for _ in range(n):
        r *= x
    return r


# ---------- Approach 2: Recursive Halving ----------
def my_pow_recursive(x: float, n: int) -> float:
    def pos(x: float, n: int) -> float:
        if n == 0:
            return 1.0
        half = pos(x, n // 2)  # compute once, use twice
        return half * half * x if n % 2 else half * half

    return pos(1 / x, -n) if n < 0 else pos(x, n)


# ---------- Approach 3: Iterative Squaring ⭐ ----------
def my_pow(x: float, n: int) -> float:
    if n < 0:
        x, n = 1 / x, -n  # make n non-negative before halving
    result = 1.0
    while n:
        if n & 1:  # this bit of n is set
            result *= x
        x *= x  # x, x^2, x^4, x^8, ...
        n >>= 1
    return result


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [(2.0, 10), (2.1, 3), (2.0, -2), (5.0, 0), (-1.0, -(2**31)), (-2.0, 5)]
    for x, n in tests:
        if abs(n) <= 1000:
            print(f"linear   : {my_pow_linear(x, n):.5f}")
        else:
            print("linear   : skipped (|n| too big)")
        print(f"recursive: {my_pow_recursive(x, n):.5f}")
        print(f"squaring : {my_pow(x, n):.5f}")
        print("---")

"""
Syntax notes (Python):
- f"{v:.5f}" formats a float with 5 decimals.
- Python ints don't overflow, so -n is safe even for -2**31.
- Built-ins for reference: x ** n, pow(x, n), and pow(base, exp, mod) for modular powers.
"""
