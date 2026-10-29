"""
0121. Best Time to Buy and Sell Stock  |  Easy  |  Sliding Window
Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

Problem: Buy on one day and sell on a later day; return the max profit
         (0 if no profit is possible).

Examples:
  [7,1,5,3,6,4]  -> 5
  [7,6,4,3,1]    -> 0
  [2,4,1]        -> 2
  [5]            -> 0

Approaches:
  1. Brute force        O(n^2) time, O(1) space
  2. Running min  ⭐     O(n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Brute Force ----------
def max_profit_brute(prices: list[int]) -> int:
    n = len(prices)
    return max([prices[j] - prices[i] for i in range(n) for j in range(i + 1, n)] + [0])


# ---------- Approach 2: Running Min ⭐ ----------
def max_profit(prices: list[int]) -> int:
    min_price, best = float("inf"), 0
    for p in prices:
        best = max(best, p - min_price)  # sell today, bought at the cheapest earlier day
        min_price = min(min_price, p)
    return int(best)


# ---------- Driver ----------
if __name__ == "__main__":
    for p in [[7, 1, 5, 3, 6, 4], [7, 6, 4, 3, 1], [2, 4, 1], [5]]:
        print("brute  :", max_profit_brute(p))
        print("run min:", max_profit(p))
        print("---")

"""
Syntax notes (Python):
- float("inf") is a safe "infinity"; p - inf is -inf, so max() ignores it.
- `+ [0]` gives max() a floor and avoids an empty-sequence error.
- int(best) converts back in case best was compared with floats.
"""
