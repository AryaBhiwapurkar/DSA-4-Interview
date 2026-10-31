"""
0070. Climbing Stairs  |  Easy  |  1-D Dynamic Programming
Link: https://leetcode.com/problems/climbing-stairs/

Problem: Climb n steps taking 1 or 2 at a time. Count the distinct ways.

Examples:
  n = 2   -> 2
  n = 3   -> 3
  n = 1   -> 1
  n = 5   -> 8
  n = 10  -> 89

Approaches:
  1. Plain recursion            O(2^n) time, O(n) space
  2. Memoized recursion         O(n) time, O(n) space
  3. Two variables (bottom-up)  ⭐  O(n) time, O(1) space   <- go-to
"""

from functools import cache


# ---------- Approach 1: Plain Recursion ----------
def climb_stairs_brute(n: int) -> int:
    if n <= 2:  # 1 way for 1 step, 2 ways for 2
        return n
    return climb_stairs_brute(n - 1) + climb_stairs_brute(n - 2)


# ---------- Approach 2: Memoized Recursion ----------
def climb_stairs_memo(n: int) -> int:
    @cache
    def ways(i: int) -> int:
        return i if i <= 2 else ways(i - 1) + ways(i - 2)

    return ways(n)


# ---------- Approach 3: Two Variables ⭐ ----------
def climb_stairs(n: int) -> int:
    prev, cur = 1, 1  # ways(0), ways(1)
    for _ in range(2, n + 1):
        prev, cur = cur, prev + cur  # last move was a 2-step or a 1-step
    return cur


# ---------- Driver ----------
if __name__ == "__main__":
    for n in [2, 3, 1, 5, 10]:
        print("brute:", climb_stairs_brute(n))
        print("memo :", climb_stairs_memo(n))
        print("dp   :", climb_stairs(n))
        print("---")

"""
Syntax notes (Python):
- functools.cache memoizes a function by its arguments (3.9+).
- `prev, cur = cur, prev + cur` evaluates the right side first: no temp variable.
- A nested @cache function gets a fresh cache per outer call.
"""
