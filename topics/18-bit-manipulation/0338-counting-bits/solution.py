"""
0338. Counting Bits  |  Easy  |  Bit Manipulation
Link: https://leetcode.com/problems/counting-bits/

Problem: Return ans where ans[i] is the number of 1 bits in i, for 0 <= i <= n.

Examples:
  2   -> [0,1,1]
  5   -> [0,1,1,2,1,2]
  0   -> [0]
  8   -> [0,1,1,2,1,2,2,3,1]

Approaches:
  1. Popcount every number              O(n log n) time, O(1) extra
  2. DP: bits(i) = bits(i >> 1) + (i & 1)  ⭐   O(n) time, O(1) extra   <- go-to
  3. DP: bits(i) = bits(i & (i - 1)) + 1        O(n) time, O(1) extra
"""


# ---------- Approach 1: Popcount Each ----------
def count_bits_naive(n: int) -> list[int]:
    res = []
    for i in range(n + 1):
        c, x = 0, i
        while x:
            x &= x - 1
            c += 1
        res.append(c)
    return res


# ---------- Approach 2: DP on i >> 1 ⭐ ----------
def count_bits(n: int) -> list[int]:
    ans = [0] * (n + 1)
    for i in range(1, n + 1):
        ans[i] = ans[i >> 1] + (i & 1)  # i without its last bit, plus that bit
    return ans


# ---------- Approach 3: DP on i & (i - 1) ----------
def count_bits_lowbit(n: int) -> list[int]:
    ans = [0] * (n + 1)
    for i in range(1, n + 1):
        ans[i] = ans[i & (i - 1)] + 1  # i with its lowest 1 removed, plus one
    return ans


# ---------- Driver ----------
if __name__ == "__main__":
    for n in [2, 5, 0, 8]:
        print("naive :", count_bits_naive(n))
        print("shift :", count_bits(n))
        print("lowbit:", count_bits_lowbit(n))
        print("---")

"""
Syntax notes (Python):
- i >> 1 is i // 2 for non-negative ints; i & 1 is i % 2.
- Parenthesise (i & 1): + binds tighter than &.
- [0] * (n + 1) sizes the table to include n.
"""
