"""
0090. Subsets II  |  Medium  |  Backtracking
Link: https://leetcode.com/problems/subsets-ii/

Problem: Return all distinct subsets of an array that may contain duplicates.

Examples:
  [1,2,2]      -> [[],[1],[1,2],[1,2,2],[2],[2,2]]
  [0]          -> [[],[0]]
  [4,4,4,1,4]  -> 10 subsets

Approaches:
  1. Power set + set             O(n^2 * 2^n) time, O(n * 2^n) space
  2. Sort + skip duplicates  ⭐   O(n * 2^n) time, O(n) extra   <- go-to
"""


# ---------- Approach 1: Power Set + Set ----------
def subsets_with_dup_set(nums: list[int]) -> list[list[int]]:
    a = sorted(nums)  # equal subsets then look identical
    n = len(a)
    seen = {tuple(a[j] for j in range(n) if mask >> j & 1) for mask in range(1 << n)}
    return [list(t) for t in seen]


# ---------- Approach 2: Sort + Skip Duplicates ⭐ ----------
def subsets_with_dup(nums: list[int]) -> list[list[int]]:
    a = sorted(nums)
    res: list[list[int]] = []
    path: list[int] = []

    def dfs(start: int) -> None:
        res.append(path[:])
        for i in range(start, len(a)):
            if i > start and a[i] == a[i - 1]:
                continue  # same value at the same depth
            path.append(a[i])
            dfs(i + 1)
            path.pop()

    dfs(0)
    return res


# ---------- Driver ----------
if __name__ == "__main__":
    for nums in [[1, 2, 2], [0], [4, 4, 4, 1, 4]]:
        print("set :", sorted(subsets_with_dup_set(nums)))  # any order is accepted
        print("skip:", sorted(subsets_with_dup(nums)))
        print("---")

"""
Syntax notes (Python):
- A set comprehension {tuple(...) for ...} dedupes in one expression.
- tuple(generator) builds a hashable key from a filtered sequence.
"""
