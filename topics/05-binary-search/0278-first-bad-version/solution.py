"""
0278. First Bad Version  |  Easy  |  Binary Search
Link: https://leetcode.com/problems/first-bad-version/

Problem: Versions 1..n; from some version on all are bad. Using
         isBadVersion(v), return the first bad version.

Examples:
  n = 5,          bad = 4           -> 4
  n = 1,          bad = 1           -> 1
  n = 10,         bad = 7           -> 7
  n = 10,         bad = 1           -> 1
  n = 2126753390, bad = 1702766719  -> 1702766719   (lo + hi overflows int in C++)

Approaches:
  1. Linear scan                 O(n) calls
  2. Lower-bound binary search ⭐ O(log n) calls, O(1) space   <- go-to
"""

BAD = 1  # the hidden first bad version


def isBadVersion(v: int) -> bool:  # stand-in for the LeetCode API
    return v >= BAD


# ---------- Approach 1: Linear Scan ----------
def first_bad_version_linear(n: int) -> int:
    for v in range(1, n):
        if isBadVersion(v):
            return v
    return n  # at least version n is bad


# ---------- Approach 2: Lower-bound Binary Search ⭐ ----------
def first_bad_version(n: int) -> int:
    lo, hi = 1, n
    while lo < hi:
        mid = (lo + hi) // 2  # no overflow in Python
        if isBadVersion(mid):
            hi = mid  # mid might be the first bad one
        else:
            lo = mid + 1
    return lo


# ---------- Driver ----------
if __name__ == "__main__":
    for n, bad in [(5, 4), (1, 1), (10, 7), (10, 1), (2126753390, 1702766719)]:
        BAD = bad
        if n <= 1_000_000:
            print("linear:", first_bad_version_linear(n))
        else:
            print("linear: skipped (n too large)")
        print("binary:", first_bad_version(n))
        print("---")

"""
Syntax notes (Python):
- Assigning BAD inside `if __name__ == "__main__":` rebinds the module global,
  so isBadVersion sees it (no `global` needed at module level).
- Python ints are arbitrary precision: (lo + hi) // 2 can't overflow.
- 1_000_000: underscores in numeric literals for readability.
"""
