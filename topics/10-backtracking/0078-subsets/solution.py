"""
0078. Subsets  |  Medium  |  Backtracking
Link: https://leetcode.com/problems/subsets/

Problem: Return the power set of an array of distinct integers.

Examples:
  [1,2,3]  -> [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
  [0]      -> [[],[0]]
  [5,-1]   -> [[],[5],[-1],[5,-1]]

Approaches:
  1. Iterative doubling    O(n * 2^n) time, O(n * 2^n) space
  2. Bitmask               O(n * 2^n) time, O(n) extra
  3. Backtracking  ⭐       O(n * 2^n) time, O(n) extra   <- go-to
"""


# ---------- Approach 1: Iterative Doubling ----------
def subsets_iter(nums: list[int]) -> list[list[int]]:
    res: list[list[int]] = [[]]
    for x in nums:
        res += [s + [x] for s in res]  # comprehension reads the old res first
    return res


# ---------- Approach 2: Bitmask ----------
def subsets_bitmask(nums: list[int]) -> list[list[int]]:
    n = len(nums)
    return [[nums[j] for j in range(n) if mask >> j & 1] for mask in range(1 << n)]


# ---------- Approach 3: Backtracking ⭐ ----------
def subsets(nums: list[int]) -> list[list[int]]:
    res: list[list[int]] = []
    path: list[int] = []

    def dfs(start: int) -> None:
        res.append(path[:])  # every node is a subset
        for i in range(start, len(nums)):
            path.append(nums[i])
            dfs(i + 1)
            path.pop()

    dfs(0)
    return res


# ---------- Driver ----------
if __name__ == "__main__":
    for nums in [[1, 2, 3], [0], [5, -1]]:
        print("iter     :", sorted(subsets_iter(nums)))  # any order is accepted
        print("bitmask  :", sorted(subsets_bitmask(nums)))
        print("backtrack:", sorted(subsets(nums)))
        print("---")

"""
Syntax notes (Python):
- `res += [s + [x] for s in res]` is safe: the right side is built before extending.
- `mask >> j & 1` tests bit j; Python ints never overflow.
- s + [x] creates a new list, leaving s unchanged.
"""
