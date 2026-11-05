"""
0122. Best Time to Buy and Sell Stock II  |  Medium  |  Greedy
Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/

Problem: Max profit with unlimited transactions, holding at most one share
         (selling and rebuying on the same day is allowed).

Examples:
  [7,1,5,3,6,4]   -> 7
  [1,2,3,4,5]     -> 4
  [7,6,4,3,1]     -> 0
  [5]             -> 0
  [2,1,2,0,1]     -> 2

Approaches:
  1. State machine DP (hold / free)   O(n) time, O(1) space
  2. Sum of positive day-to-day gains  ⭐   O(n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: State Machine DP ----------
def max_profit_dp(prices: list[int]) -> int:
    hold, free = -prices[0], 0  # best balance holding a share / not holding
    for p in prices[1:]:
        hold, free = max(hold, free - p), max(free, hold + p)
    return free


# ---------- Approach 2: Sum of Gains ⭐ ----------
def max_profit(prices: list[int]) -> int:
    return sum(max(0, b - a) for a, b in zip(prices, prices[1:]))  # take every rise


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[7, 1, 5, 3, 6, 4], [1, 2, 3, 4, 5], [7, 6, 4, 3, 1], [5], [2, 1, 2, 0, 1]]:
        print("dp   :", max_profit_dp(t))
        print("gains:", max_profit(t))
        print("---")

"""
Syntax notes (Python):
- zip(prices, prices[1:]) pairs each day with the next one.
- Tuple assignment updates hold and free from yesterday's values together.
- sum() over a generator never builds the list of gains.
"""
