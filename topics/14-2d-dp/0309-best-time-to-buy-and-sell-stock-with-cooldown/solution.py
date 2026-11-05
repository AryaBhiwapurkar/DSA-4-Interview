"""
0309. Best Time to Buy and Sell Stock with Cooldown  |  Medium  |  2-D Dynamic Programming
Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/

Problem: Max profit with unlimited transactions, one share at a time, and a
         one-day cooldown after every sale.

Examples:
  [1,2,3,0,2]     -> 3
  [1]             -> 0
  [2,1]           -> 0
  [1,2,4]         -> 3
  [6,1,3,2,4,7]   -> 6

Approaches:
  1. Memoized recursion (day, holding)       O(n) time, O(n) space
  2. State machine: hold / sold / rest  ⭐    O(n) time, O(1) space   <- go-to
"""

from functools import cache


# ---------- Approach 1: Memoized Recursion ----------
def max_profit_memo(prices: list[int]) -> int:
    n = len(prices)

    @cache
    def f(i: int, holding: bool) -> int:
        if i >= n:
            return 0
        if holding:  # keep, or sell and skip tomorrow (cooldown)
            return max(f(i + 1, True), prices[i] + f(i + 2, False))
        return max(f(i + 1, False), -prices[i] + f(i + 1, True))  # wait, or buy

    return f(0, False)


# ---------- Approach 2: State Machine ⭐ ----------
def max_profit(prices: list[int]) -> int:
    hold, sold, rest = -prices[0], 0, 0  # best profit ending today in each state
    for p in prices[1:]:
        hold, sold, rest = (
            max(hold, rest - p),  # keep holding, or buy from rest (not right after a sale)
            hold + p,  # sell today
            max(rest, sold),  # idle; yesterday's sale finishes its cooldown
        )
    return max(sold, rest)


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[1, 2, 3, 0, 2], [1], [2, 1], [1, 2, 4], [6, 1, 3, 2, 4, 7]]:
        print("memo :", max_profit_memo(t))
        print("state:", max_profit(t))
        print("---")

"""
Syntax notes (Python):
- Tuple assignment evaluates every right-hand side with the OLD values first.
- f(i + 2, False) jumps over the cooldown day; i >= n covers running past the end.
- @cache on (i, holding) gives 2n states.
"""
