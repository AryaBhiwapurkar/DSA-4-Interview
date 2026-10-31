"""
0040. Combination Sum II  |  Medium  |  Backtracking
Link: https://leetcode.com/problems/combination-sum-ii/

Problem: Positive candidates (with duplicates), a target. Return every
         unique combination summing to target, each element used once.

Examples:
  [10,1,2,7,6,1,5], 8  -> [[1,1,6],[1,2,5],[1,7],[2,6]]
  [2,5,2,1,2],      5  -> [[1,2,2],[5]]
  [2,2,2],          4  -> [[2,2]]
  [3],              1  -> []

Approaches:
  1. All subsets + set           O(2^n * n log n) time, O(2^n * n) space
  2. Sort + skip duplicates  ⭐   O(2^n * n) time, O(n) space   <- go-to
"""


# ---------- Approach 1: All Subsets + Set ----------
def combination_sum2_set(candidates: list[int], target: int) -> list[list[int]]:
    c = sorted(candidates)
    seen: set[tuple[int, ...]] = set()
    path: list[int] = []

    def go(i: int, rem: int) -> None:
        if rem == 0:
            seen.add(tuple(path))  # path built in sorted order
            return
        if i == len(c) or rem < 0:
            return
        path.append(c[i])
        go(i + 1, rem - c[i])
        path.pop()
        go(i + 1, rem)

    go(0, target)
    return [list(t) for t in seen]


# ---------- Approach 2: Sort + Skip Duplicates ⭐ ----------
def combination_sum2(candidates: list[int], target: int) -> list[list[int]]:
    c = sorted(candidates)
    res: list[list[int]] = []
    path: list[int] = []

    def dfs(start: int, rem: int) -> None:
        if rem == 0:
            res.append(path[:])
            return
        for i in range(start, len(c)):
            if i > start and c[i] == c[i - 1]:
                continue  # same value, same depth: already explored
            if c[i] > rem:
                break
            path.append(c[i])
            dfs(i + 1, rem - c[i])  # i + 1: each element once
            path.pop()

    dfs(0, target)
    return res


# ---------- Driver ----------
def norm(v: list[list[int]]) -> list[list[int]]:
    return sorted(sorted(x) for x in v)  # any order is accepted


if __name__ == "__main__":
    tests = [([10, 1, 2, 7, 6, 1, 5], 8), ([2, 5, 2, 1, 2], 5), ([2, 2, 2], 4), ([3], 1)]
    for c, t in tests:
        print("set :", norm(combination_sum2_set(c, t)))
        print("skip:", norm(combination_sum2(c, t)))
        print("---")

"""
Syntax notes (Python):
- Lists aren't hashable; convert to tuple(path) to put them in a set.
- tuple[int, ...] is the type hint for a variable-length tuple.
"""
