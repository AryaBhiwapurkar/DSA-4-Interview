"""
0188. Best Time to Buy and Sell Stock IV  |  Hard  |  2-D Dynamic Programming
Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/

Problem: Max profit with at most k non-overlapping buy/sell transactions.

Examples:
  k=2, [2,4,1]          -> 2
  k=2, [3,2,6,5,0,3]    -> 7
  k=1, [7,1,5,3,6,4]    -> 5
  k=100, [1,2,3,4,5]    -> 4   (k >= n/2: unlimited)
  k=3, [1,3,2,5,4,8,0,1] -> 9    (4 rises, keep the best 3)

Approaches:
  1. Memoized recursion (day, trades left, holding)   O(n*k) time, O(n*k) space
  2. buy[j] / sell[j] state arrays  ⭐                 O(n*k) time, O(k) space   <- go-to
"""

import sys
from functools import cache

sys.setrecursionlimit(10_000)  # depth reaches n


# ---------- Approach 1: Memoized Recursion ----------
def max_profit_memo(k: int, prices: list[int]) -> int:
    n = len(prices)

    @cache
    def f(i: int, left: int, holding: bool) -> int:
        if i == n or left == 0:
            return 0
        if holding:  # keep, or sell (completes a transaction)
            return max(f(i + 1, left, True), prices[i] + f(i + 1, left - 1, False))
        return max(f(i + 1, left, False), -prices[i] + f(i + 1, left, True))  # wait, or buy

    return f(0, k, False)


# ---------- Approach 2: State Arrays ⭐ ----------
def max_profit(k: int, prices: list[int]) -> int:
    if 2 * k >= len(prices):  # enough trades to take every rise
        return sum(max(0, b - a) for a, b in zip(prices, prices[1:]))
    buy = [float("-inf")] * (k + 1)  # buy[j]: best balance holding the j-th share
    sell = [0] * (k + 1)  # sell[j]: best balance after j completed trades
    for p in prices:
        for j in range(1, k + 1):
            buy[j] = max(buy[j], sell[j - 1] - p)  # j-th buy uses the (j-1)-th sale's money
            sell[j] = max(sell[j], buy[j] + p)
    return int(sell[k])


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [(2, [2, 4, 1]), (2, [3, 2, 6, 5, 0, 3]), (1, [7, 1, 5, 3, 6, 4]), (100, [1, 2, 3, 4, 5]), (3, [1, 3, 2, 5, 4, 8, 0, 1])]
    for k, t in tests:
        print("memo  :", max_profit_memo(k, t))
        print("states:", max_profit(k, t))
        print("---")

"""
Syntax notes (Python):
- zip(prices, prices[1:]) yields consecutive (yesterday, today) pairs.
- buy[0] is never read as a buy; sell[0] = 0 is the "no trades yet" base.
- @cache on (i, left, holding) gives at most n * (k+1) * 2 states.
"""
