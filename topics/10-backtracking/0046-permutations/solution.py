"""
0046. Permutations  |  Medium  |  Backtracking
Link: https://leetcode.com/problems/permutations/

Problem: Return all orderings of an array of distinct integers.

Examples:
  [1,2,3]  -> [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
  [0,1]    -> [[0,1],[1,0]]
  [1]      -> [[1]]
  [-1,5]   -> [[-1,5],[5,-1]]

Approaches:
  1. Backtracking with used[]  ⭐  O(n * n!) time, O(n) extra space   <- go-to
  2. In-place swapping            O(n * n!) time, O(n) recursion
"""


# ---------- Approach 1: Backtracking with used[] ⭐ ----------
def permute(nums: list[int]) -> list[list[int]]:
    res: list[list[int]] = []
    path: list[int] = []
    used = [False] * len(nums)

    def dfs() -> None:
        if len(path) == len(nums):
            res.append(path[:])
            return
        for i in range(len(nums)):  # from 0: order matters
            if used[i]:
                continue
            used[i] = True
            path.append(nums[i])
            dfs()
            path.pop()
            used[i] = False

    dfs()
    return res


# ---------- Approach 2: In-Place Swapping ----------
def permute_swap(nums: list[int]) -> list[list[int]]:
    a = nums[:]
    res: list[list[int]] = []

    def go(i: int) -> None:
        if i == len(a):
            res.append(a[:])
            return
        for j in range(i, len(a)):
            a[i], a[j] = a[j], a[i]  # put a[j] in slot i
            go(i + 1)
            a[i], a[j] = a[j], a[i]  # restore for the next j

    go(0)
    return res


# ---------- Driver ----------
if __name__ == "__main__":
    for nums in [[1, 2, 3], [0, 1], [1], [-1, 5]]:
        print("used:", sorted(permute(nums)))  # any order of permutations is accepted
        print("swap:", sorted(permute_swap(nums)))
        print("---")

"""
Syntax notes (Python):
- a[i], a[j] = a[j], a[i] swaps without a temp.
- Library one-liner: [list(p) for p in itertools.permutations(nums)].
"""
