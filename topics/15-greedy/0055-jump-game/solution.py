"""
0055. Jump Game  |  Medium  |  Greedy
Link: https://leetcode.com/problems/jump-game/

Problem: nums[i] is the max jump length from i. Starting at index 0, can you
         reach the last index?

Examples:
  [2,3,1,1,4]   -> true
  [3,2,1,0,4]   -> false
  [0]           -> true
  [2,0,0]       -> true
  [1,0,1]       -> false

Approaches:
  1. DP from the right (can reach end?)   O(n^2) time, O(n) space
  2. Farthest reach, forward  ⭐           O(n) time, O(1) space   <- go-to
  3. Shrinking goal, backward             O(n) time, O(1) space
"""


# ---------- Approach 1: DP from the Right ----------
def can_jump_dp(nums: list[int]) -> bool:
    n = len(nums)
    good = [False] * n
    good[-1] = True
    for i in range(n - 2, -1, -1):
        good[i] = any(good[j] for j in range(i + 1, min(n, i + nums[i] + 1)))
    return good[0]


# ---------- Approach 2: Farthest Reach ⭐ ----------
def can_jump(nums: list[int]) -> bool:
    reach = 0  # farthest index reachable so far
    for i, x in enumerate(nums):
        if i > reach:  # stuck: this index can't be reached
            return False
        reach = max(reach, i + x)
    return True


# ---------- Approach 3: Shrinking Goal ----------
def can_jump_goal(nums: list[int]) -> bool:
    goal = len(nums) - 1
    for i in range(len(nums) - 2, -1, -1):
        if i + nums[i] >= goal:  # i can reach the goal, so reaching i is enough
            goal = i
    return goal == 0


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[2, 3, 1, 1, 4], [3, 2, 1, 0, 4], [0], [2, 0, 0], [1, 0, 1]]:
        print("dp   :", str(can_jump_dp(t)).lower())
        print("reach:", str(can_jump(t)).lower())
        print("goal :", str(can_jump_goal(t)).lower())
        print("---")

"""
Syntax notes (Python):
- any(generator) stops at the first True.
- enumerate(nums) gives (index, value) pairs.
- min(n, i + nums[i] + 1) clips the jump window at the array end.
"""
