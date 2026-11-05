"""
0045. Jump Game II  |  Medium  |  Greedy
Link: https://leetcode.com/problems/jump-game-ii/

Problem: Minimum number of jumps from index 0 to the last index (always
         reachable), where nums[i] is the max jump from i.

Examples:
  [2,3,1,1,4]   -> 2
  [2,3,0,1,4]   -> 2
  [0]           -> 0
  [1,1,1,1]     -> 3
  [5,1,1,1,1]   -> 1

Approaches:
  1. DP: fewest jumps to each index    O(n^2) time, O(n) space
  2. BFS-style levels (greedy)  ⭐      O(n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: DP ----------
def jump_dp(nums: list[int]) -> int:
    n = len(nums)
    dp = [0] + [n] * (n - 1)  # n acts as infinity (never needs n jumps)
    for i in range(n):
        for j in range(i + 1, min(n, i + nums[i] + 1)):
            dp[j] = min(dp[j], dp[i] + 1)
    return dp[-1]


# ---------- Approach 2: BFS Levels ⭐ ----------
def jump(nums: list[int]) -> int:
    jumps, end, farthest = 0, 0, 0  # [.., end] = indices reachable with `jumps` jumps
    for i in range(len(nums) - 1):  # never jump from the last index
        farthest = max(farthest, i + nums[i])
        if i == end:  # finished this level: one more jump to reach the next
            jumps += 1
            end = farthest
    return jumps


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[2, 3, 1, 1, 4], [2, 3, 0, 1, 4], [0], [1, 1, 1, 1], [5, 1, 1, 1, 1]]:
        print("dp :", jump_dp(t))
        print("bfs:", jump(t))
        print("---")

"""
Syntax notes (Python):
- range(len(nums) - 1) stops before the last index, so reaching it never adds a jump.
- [0] + [n] * (n - 1) seeds dp[0] = 0 and "infinity" elsewhere.
- Multiple assignment `a, b, c = 0, 0, 0` initialises the window state.
"""
