"""
0039. Combination Sum  |  Medium  |  Backtracking
Link: https://leetcode.com/problems/combination-sum/

Problem: Distinct positive candidates, a target. Return every unique
         multiset of candidates (unlimited reuse) summing to target.

Examples:
  [2,3,6,7], 7  -> [[2,2,3],[7]]
  [2,3,5],   8  -> [[2,2,2,2],[2,3,3],[3,5]]
  [2],       1  -> []
  [7,3,2],  18  -> 7 combinations (unsorted input)

Approaches:
  1. Include / exclude                O(2^(n+T/m)) time, O(n+T/m) space
  2. Sorted loop from start  ⭐        O(n^(T/m+1)) time, O(T/m) space   <- go-to
"""


# ---------- Approach 1: Include / Exclude ----------
def combination_sum_binary(candidates: list[int], target: int) -> list[list[int]]:
    res: list[list[int]] = []
    path: list[int] = []

    def go(i: int, rem: int) -> None:
        if rem == 0:
            res.append(path[:])
            return
        if i == len(candidates) or rem < 0:
            return
        path.append(candidates[i])
        go(i, rem - candidates[i])  # use it again
        path.pop()
        go(i + 1, rem)  # never use it again

    go(0, target)
    return res


# ---------- Approach 2: Sorted Loop from Start Index ⭐ ----------
def combination_sum(candidates: list[int], target: int) -> list[list[int]]:
    c = sorted(candidates)
    res: list[list[int]] = []
    path: list[int] = []

    def dfs(start: int, rem: int) -> None:
        if rem == 0:
            res.append(path[:])  # copy: path keeps changing
            return
        for i in range(start, len(c)):
            if c[i] > rem:
                break  # sorted: everything after is bigger too
            path.append(c[i])
            dfs(i, rem - c[i])  # i, not i + 1: reuse allowed
            path.pop()

    dfs(0, target)
    return res


# ---------- Driver ----------
def norm(v: list[list[int]]) -> list[list[int]]:
    return sorted(sorted(x) for x in v)  # any order is accepted


if __name__ == "__main__":
    tests = [([2, 3, 6, 7], 7), ([2, 3, 5], 8), ([2], 1), ([7, 3, 2], 18)]
    for c, t in tests:
        print("binary:", norm(combination_sum_binary(c, t)))
        print("loop  :", norm(combination_sum(c, t)))
        print("---")

"""
Syntax notes (Python):
- path[:] (or list(path)) snapshots the current path; appending `path` itself
  would leave every result pointing at the same, eventually empty, list.
- sorted() on a list of lists compares lexicographically.
"""
