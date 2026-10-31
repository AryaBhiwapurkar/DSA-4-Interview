"""
0322. Coin Change  |  Medium  |  1-D Dynamic Programming
Link: https://leetcode.com/problems/coin-change/

Problem: Fewest coins (unlimited supply of each denomination) that sum to
         amount, or -1 if impossible.

Examples:
  [1,2,5], 11              -> 3
  [2], 3                   -> -1
  [1], 0                   -> 0
  [1,3,4], 6               -> 2 (greedy picks 4+1+1 = 3 coins)
  [186,419,83,408], 6249   -> 20

Approaches:
  1. Memoized recursion        O(amount * coins) time, O(amount) space
  2. BFS over amounts          O(amount * coins) time, O(amount) space
  3. Bottom-up DP  ⭐           O(amount * coins) time, O(amount) space   <- go-to
"""

from collections import deque
from functools import cache

INF = float("inf")


# ---------- Approach 1: Memoized Recursion ----------
def coin_change_memo(coins: list[int], amount: int) -> int:
    @cache
    def fewest(a: int) -> float:  # inf = impossible
        if a == 0:
            return 0
        return min((fewest(a - c) + 1 for c in coins if c <= a), default=INF)

    r = fewest(amount)
    return -1 if r == INF else int(r)


# ---------- Approach 2: BFS over Amounts ----------
def coin_change_bfs(coins: list[int], amount: int) -> int:
    seen = [False] * (amount + 1)
    seen[0] = True
    q = deque([0])
    steps = 0
    while q:  # level = number of coins used
        for _ in range(len(q)):
            a = q.popleft()
            if a == amount:
                return steps
            for c in coins:
                if a + c <= amount and not seen[a + c]:
                    seen[a + c] = True
                    q.append(a + c)
        steps += 1
    return -1


# ---------- Approach 3: Bottom-up DP ⭐ ----------
def coin_change(coins: list[int], amount: int) -> int:
    dp = [0] + [amount + 1] * amount  # amount+1 acts as infinity
    for a in range(1, amount + 1):
        for c in coins:
            if c <= a:
                dp[a] = min(dp[a], dp[a - c] + 1)  # last coin is c
    return -1 if dp[amount] > amount else dp[amount]


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([1, 2, 5], 11), ([2], 3), ([1], 0), ([1, 3, 4], 6), ([186, 419, 83, 408], 6249)]
    for coins, amount in tests:
        print("memo:", coin_change_memo(coins, amount))
        print("bfs :", coin_change_bfs(coins, amount))
        print("dp  :", coin_change(coins, amount))
        print("---")

"""
Syntax notes (Python):
- min(generator, default=INF) handles the "no coin fits" case without a special branch.
- [0] + [x] * amount builds the dp list with dp[0] = 0.
- Memo recursion depth is about amount / smallest coin; amount 10^4 with coin 1 would
  pass the default recursion limit (1000), another reason to prefer bottom-up.
"""
