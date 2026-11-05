"""
0312. Burst Balloons  |  Hard  |  2-D Dynamic Programming
Link: https://leetcode.com/problems/burst-balloons/

Problem: Bursting balloon i earns left * nums[i] * right, where left/right are
         its current neighbours (1 past either end). Maximise the total.

Examples:
  [3,1,5,8]      -> 167
  [1,5]          -> 10
  [7]            -> 7
  [9,76,64,21]   -> 116718

Approaches:
  1. Brute force over burst orders              O(n!) time, O(n) space
  2. Interval memo, k = LAST balloon burst  ⭐   O(n^3) time, O(n^2) space   <- go-to
  3. Bottom-up by interval length               O(n^3) time, O(n^2) space
"""

from functools import cache


# ---------- Approach 1: Brute Force ----------
def max_coins_brute(nums: list[int]) -> int:
    def go(arr: tuple[int, ...]) -> int:
        best = 0
        for i in range(len(arr)):
            left = arr[i - 1] if i > 0 else 1
            right = arr[i + 1] if i + 1 < len(arr) else 1
            best = max(best, left * arr[i] * right + go(arr[:i] + arr[i + 1 :]))
        return best

    return go(tuple(nums))


# ---------- Approach 2: Interval Memo ⭐ ----------
def max_coins(nums: list[int]) -> int:
    a = [1] + nums + [1]  # padded: a[0] and a[-1] are the virtual 1s

    @cache
    def best(l: int, r: int) -> int:  # max coins bursting everything strictly between l and r
        return max(
            (a[l] * a[k] * a[r] + best(l, k) + best(k, r) for k in range(l + 1, r)),  # k goes last
            default=0,
        )

    return best(0, len(a) - 1)


# ---------- Approach 3: Bottom-up ----------
def max_coins_table(nums: list[int]) -> int:
    a = [1] + nums + [1]
    n = len(a)
    dp = [[0] * n for _ in range(n)]  # dp[l][r]: open interval (l, r)
    for length in range(2, n):  # r - l
        for l in range(n - length):
            r = l + length
            for k in range(l + 1, r):
                dp[l][r] = max(dp[l][r], a[l] * a[k] * a[r] + dp[l][k] + dp[k][r])
    return dp[0][n - 1]


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[3, 1, 5, 8], [1, 5], [7], [9, 76, 64, 21]]:
        print("brute:", max_coins_brute(t))
        print("memo :", max_coins(t))
        print("table:", max_coins_table(t))
        print("---")

"""
Syntax notes (Python):
- max(generator, default=0) handles the empty interval (no k between l and r).
- arr[:i] + arr[i + 1:] on a tuple builds the remaining balloons (hashable if cached).
- [1] + nums + [1] pads both ends so neighbours always exist.
"""
