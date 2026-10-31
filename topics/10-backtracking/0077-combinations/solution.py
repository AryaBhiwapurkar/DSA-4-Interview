"""
0077. Combinations  |  Medium  |  Backtracking
Link: https://leetcode.com/problems/combinations/

Problem: Return all ways to choose k numbers from 1..n.

Examples:
  n 4, k 2  -> [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
  n 1, k 1  -> [[1]]
  n 3, k 3  -> [[1,2,3]]
  n 5, k 3  -> 10 combinations

Approaches:
  1. Include / exclude                 O(2^n) time, O(n) space
  2. Start-index loop + prune  ⭐       O(k * C(n,k)) time, O(k) space   <- go-to
"""


# ---------- Approach 1: Include / Exclude ----------
def combine_binary(n: int, k: int) -> list[list[int]]:
    res: list[list[int]] = []
    path: list[int] = []

    def go(x: int) -> None:
        if len(path) == k:
            res.append(path[:])
            return
        if x > n:
            return
        path.append(x)
        go(x + 1)
        path.pop()
        go(x + 1)

    go(1)
    return res


# ---------- Approach 2: Start-Index Loop + Prune ⭐ ----------
def combine(n: int, k: int) -> list[list[int]]:
    res: list[list[int]] = []
    path: list[int] = []

    def dfs(start: int) -> None:
        if len(path) == k:
            res.append(path[:])
            return
        need = k - len(path)
        for i in range(start, n - need + 2):  # enough numbers must remain
            path.append(i)
            dfs(i + 1)
            path.pop()

    dfs(1)
    return res


# ---------- Driver ----------
if __name__ == "__main__":
    for n, k in [(4, 2), (1, 1), (3, 3), (5, 3)]:
        print("binary:", sorted(combine_binary(n, k)))  # any order is accepted
        print("prune :", sorted(combine(n, k)))
        print("---")

"""
Syntax notes (Python):
- range(start, n - need + 2) includes n - need + 1 (range end is exclusive).
- Library one-liner: [list(c) for c in itertools.combinations(range(1, n + 1), k)].
"""
