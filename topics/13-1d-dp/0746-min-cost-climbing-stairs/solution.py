"""
0746. Min Cost Climbing Stairs  |  Easy  |  1-D Dynamic Programming
Link: https://leetcode.com/problems/min-cost-climbing-stairs/

Problem: cost[i] is paid when you step on stair i; then you climb 1 or 2.
         Start at index 0 or 1. Min cost to get past the last stair.

Examples:
  [10,15,20]                       -> 15
  [1,100,1,1,1,100,1,1,100,1]      -> 6
  [0,0]                            -> 0
  [5,3]                            -> 3

Approaches:
  1. Memoized recursion            O(n) time, O(n) space
  2. Two variables (bottom-up)  ⭐  O(n) time, O(1) space   <- go-to
"""

from functools import cache


# ---------- Approach 1: Memoized Recursion ----------
def min_cost_climbing_stairs_memo(cost: list[int]) -> int:
    @cache
    def reach(i: int) -> int:  # min cost to stand on i (before paying cost[i])
        if i <= 1:  # starting on 0 or 1 is free
            return 0
        return min(reach(i - 1) + cost[i - 1], reach(i - 2) + cost[i - 2])

    return reach(len(cost))  # the top is index n


# ---------- Approach 2: Two Variables ⭐ ----------
def min_cost_climbing_stairs(cost: list[int]) -> int:
    a = b = 0  # reach(i-2), reach(i-1)
    for i in range(2, len(cost) + 1):
        a, b = b, min(b + cost[i - 1], a + cost[i - 2])
    return b


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [[10, 15, 20], [1, 100, 1, 1, 1, 100, 1, 1, 100, 1], [0, 0], [5, 3]]
    for c in tests:
        print("memo:", min_cost_climbing_stairs_memo(c))
        print("dp  :", min_cost_climbing_stairs(c))
        print("---")

"""
Syntax notes (Python):
- A nested @cache function can read `cost` from the enclosing scope.
- `a = b = 0` is safe for ints (immutable); never do it with lists.
- Tuple assignment updates both rolling values at once.
"""
