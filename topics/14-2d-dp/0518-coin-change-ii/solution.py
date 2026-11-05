"""
0518. Coin Change II  |  Medium  |  2-D Dynamic Programming
Link: https://leetcode.com/problems/coin-change-ii/

Problem: Count the combinations (order doesn't matter) of coins, unlimited
         supply each, that sum to amount.

Examples:
  5, [1,2,5]   -> 4
  3, [2]       -> 0
  10, [10]     -> 1
  0, [7]       -> 1  (the empty combination)
  4, [1,2,3]   -> 4

Approaches:
  1. Memoized recursion (coin index, amount)   O(n * amount) time, O(n * amount) space
  2. 2-D table                                O(n * amount) time, O(n * amount) space
  3. 1-D, coins outer / amounts inner  ⭐      O(n * amount) time, O(amount) space   <- go-to
"""

from functools import cache


# ---------- Approach 1: Memoized Recursion ----------
def change_memo(amount: int, coins: list[int]) -> int:
    @cache
    def ways(i: int, a: int) -> int:
        if a == 0:
            return 1
        if i == len(coins) or a < 0:
            return 0
        return ways(i, a - coins[i]) + ways(i + 1, a)  # use coin i again, or move past it

    return ways(0, amount)


# ---------- Approach 2: 2-D Table ----------
def change_table(amount: int, coins: list[int]) -> int:
    n = len(coins)
    dp = [[0] * (amount + 1) for _ in range(n + 1)]  # dp[i][a]: ways using the first i coins
    for i in range(n + 1):
        dp[i][0] = 1
    for i in range(1, n + 1):
        c = coins[i - 1]
        for a in range(1, amount + 1):
            dp[i][a] = dp[i - 1][a] + (dp[i][a - c] if a >= c else 0)  # skip c / use c again
    return dp[n][amount]


# ---------- Approach 3: 1-D ⭐ ----------
def change(amount: int, coins: list[int]) -> int:
    dp = [1] + [0] * amount  # dp[a]: ways to make a with the coins seen so far
    for c in coins:  # coins outside: each combination counted once, in coin order
        for a in range(c, amount + 1):  # ascending: coin c reusable
            dp[a] += dp[a - c]
    return dp[amount]


# ---------- Driver ----------
if __name__ == "__main__":
    for amount, coins in [(5, [1, 2, 5]), (3, [2]), (10, [10]), (0, [7]), (4, [1, 2, 3])]:
        print("memo :", change_memo(amount, coins))
        print("table:", change_table(amount, coins))
        print("1-D  :", change(amount, coins))
        print("---")

"""
Syntax notes (Python):
- range(c, amount + 1) starts at c, so dp[a - c] never goes negative.
- Python ints don't overflow, so intermediate counts can exceed 2^31 safely.
- (x if cond else 0) adds a term only when it exists.
"""
