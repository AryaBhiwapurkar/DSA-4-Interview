"""
0172. Factorial Trailing Zeroes  |  Medium  |  Math & Geometry
Link: https://leetcode.com/problems/factorial-trailing-zeroes/

Problem: Count the trailing zeros of n! without computing n!.

Examples:
  3      -> 0
  5      -> 1
  0      -> 0
  25     -> 6
  100    -> 24
  10000  -> 2499

Approaches:
  1. Count 5s in each multiple of 5   O(n log n) time, O(1) space
  2. n/5 + n/25 + n/125 + ...  ⭐      O(log n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Count 5s in Each Number ----------
def trailing_zeroes_linear(n: int) -> int:
    count = 0
    for k in range(5, n + 1, 5):
        while k % 5 == 0:
            k //= 5
            count += 1
    return count


# ---------- Approach 2: Divide by Powers of 5 ⭐ ----------
def trailing_zeroes(n: int) -> int:
    count = 0
    while n:
        n //= 5  # numbers with at least one more factor of 5
        count += n
    return count


# ---------- Driver ----------
if __name__ == "__main__":
    for n in [3, 5, 0, 25, 100, 10000]:
        print("linear:", trailing_zeroes_linear(n))
        print("log   :", trailing_zeroes(n))
        print("---")

"""
Syntax notes (Python):
- range(5, n + 1, 5) steps through multiples of 5.
- Reassigning the loop variable k inside the body doesn't affect the next iteration.
- Brute check for small n: s = str(math.factorial(n)); len(s) - len(s.rstrip("0")).
  (str() of ints over 4300 digits raises ValueError unless sys.set_int_max_str_digits is raised.)
"""
