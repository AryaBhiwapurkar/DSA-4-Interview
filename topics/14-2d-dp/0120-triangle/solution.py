"""
0120. Triangle  |  Medium  |  2-D Dynamic Programming
Link: https://leetcode.com/problems/triangle/

Problem: Minimum top-to-bottom path sum in a number triangle, stepping to
         index i or i+1 of the next row.

Examples:
  [[2],[3,4],[6,5,7],[4,1,8,3]]   -> 11
  [[-10]]                         -> -10
  [[1],[2,3],[100,100,1]]         -> 5   (greedy gives 103)
  [[-1],[2,3],[1,-1,-3]]          -> -1

Approaches:
  1. Top-down memo              O(n^2) time, O(n^2) space
  2. Bottom-up, O(n) space  ⭐   O(n^2) time, O(n) space    <- go-to
  3. Top-down table             O(n^2) time, O(n) space
"""

from functools import cache


# ---------- Approach 1: Top-down Memo ----------
def minimum_total_memo(triangle: list[list[int]]) -> int:
    last = len(triangle) - 1

    @cache
    def best(r: int, i: int) -> int:
        if r == last:
            return triangle[r][i]
        return triangle[r][i] + min(best(r + 1, i), best(r + 1, i + 1))

    return best(0, 0)


# ---------- Approach 2: Bottom-up, O(n) Space ⭐ ----------
def minimum_total(triangle: list[list[int]]) -> int:
    dp = triangle[-1][:]  # copy: don't mutate the input
    for r in range(len(triangle) - 2, -1, -1):
        for i in range(r + 1):
            dp[i] = triangle[r][i] + min(dp[i], dp[i + 1])  # dp[i+1] not overwritten yet
    return dp[0]


# ---------- Approach 3: Top-down Table ----------
def minimum_total_top_down(triangle: list[list[int]]) -> int:
    dp = [triangle[0][0]]
    for r in range(1, len(triangle)):
        row = triangle[r]
        nxt = [0] * (r + 1)
        nxt[0] = dp[0] + row[0]  # left edge: one parent
        nxt[r] = dp[r - 1] + row[r]  # right edge: one parent
        for i in range(1, r):
            nxt[i] = row[i] + min(dp[i - 1], dp[i])
        dp = nxt
    return min(dp)


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        [[2], [3, 4], [6, 5, 7], [4, 1, 8, 3]],
        [[-10]],
        [[1], [2, 3], [100, 100, 1]],
        [[-1], [2, 3], [1, -1, -3]],
    ]
    for t in tests:
        print("memo    :", minimum_total_memo(t))
        print("bottomup:", minimum_total(t))
        print("topdown :", minimum_total_top_down(t))
        print("---")

"""
Syntax notes (Python):
- lst[:] makes a shallow copy; without it dp would alias the input row.
- range(n - 2, -1, -1) walks rows from second-last up to 0.
- @cache needs no sentinel, so negative answers are fine.
"""
