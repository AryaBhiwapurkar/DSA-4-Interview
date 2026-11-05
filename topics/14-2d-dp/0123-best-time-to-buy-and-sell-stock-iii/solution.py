"""
0123. Best Time to Buy and Sell Stock III  |  Hard  |  2-D Dynamic Programming
Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/

Problem: Max profit with at most two non-overlapping buy/sell transactions.

Examples:
  [3,3,5,0,0,3,1,4]   -> 6
  [1,2,3,4,5]         -> 4
  [7,6,4,3,1]         -> 0
  [1]                 -> 0
  [1,2,4,2,5,7,2,4,9,0] -> 13

Approaches:
  1. Brute split point                  O(n^2) time, O(1) space
  2. Prefix / suffix best single trade  O(n) time, O(n) space
  3. Four states b1, s1, b2, s2  ⭐      O(n) time, O(1) space   <- go-to
"""


def one_trade(prices: list[int], lo: int, hi: int) -> int:
    """Best single buy/sell within prices[lo:hi]."""
    best, low = 0, float("inf")
    for p in prices[lo:hi]:
        low = min(low, p)
        best = max(best, p - low)
    return int(best)


# ---------- Approach 1: Brute Split Point ----------
def max_profit_brute(prices: list[int]) -> int:
    n = len(prices)
    return max(one_trade(prices, 0, k) + one_trade(prices, k, n) for k in range(n + 1))


# ---------- Approach 2: Prefix / Suffix ----------
def max_profit_prefix(prices: list[int]) -> int:
    n = len(prices)
    left = [0] * n  # left[i]: best trade within days 0..i
    low = prices[0]
    for i in range(1, n):
        low = min(low, prices[i])
        left[i] = max(left[i - 1], prices[i] - low)
    best, high, right = left[-1], prices[-1], 0  # right: best trade within days i+1..n-1
    for i in range(n - 2, -1, -1):
        best = max(best, left[i] + right)
        high = max(high, prices[i])
        right = max(right, high - prices[i])
    return best


# ---------- Approach 3: Four States ⭐ ----------
def max_profit(prices: list[int]) -> int:
    b1 = b2 = float("-inf")  # best balance after 1st / 2nd buy
    s1 = s2 = 0  # best balance after 1st / 2nd sell
    for p in prices:
        b1 = max(b1, -p)
        s1 = max(s1, b1 + p)
        b2 = max(b2, s1 - p)  # 2nd buy is funded by the 1st sale
        s2 = max(s2, b2 + p)
    return int(s2)


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [[3, 3, 5, 0, 0, 3, 1, 4], [1, 2, 3, 4, 5], [7, 6, 4, 3, 1], [1], [1, 2, 4, 2, 5, 7, 2, 4, 9, 0]]
    for t in tests:
        print("brute :", max_profit_brute(t))
        print("prefix:", max_profit_prefix(t))
        print("states:", max_profit(t))
        print("---")

"""
Syntax notes (Python):
- float("-inf") marks "haven't bought yet"; int() converts the final answer back.
- Updating b1, s1, b2, s2 in order, in place, is fine: a same-day buy and sell nets 0.
- max(generator) over all split points keeps the brute force to one line.
"""
