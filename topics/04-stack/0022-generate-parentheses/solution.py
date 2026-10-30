"""
0022. Generate Parentheses  |  Medium  |  Stack
Link: https://leetcode.com/problems/generate-parentheses/

Problem: Return every well-formed string of n pairs of parentheses.

Examples (printed sorted):
  n = 3  -> ["((()))","(()())","(())()","()(())","()()()"]
  n = 1  -> ["()"]
  n = 2  -> ["(())","()()"]

Approaches:
  1. Generate all, filter      O(2^(2n) * n) time, O(n) depth
  2. Backtracking  ⭐           O(4^n / sqrt(n)) time, O(n) depth   <- go-to
"""

from itertools import product


# ---------- Approach 1: Generate All, Then Filter ----------
def balanced(s: str) -> bool:
    bal = 0
    for c in s:
        bal += 1 if c == "(" else -1
        if bal < 0:  # a ')' with nothing to close
            return False
    return bal == 0


def generate_parenthesis_brute(n: int) -> list[str]:
    return [s for s in map("".join, product("()", repeat=2 * n)) if balanced(s)]


# ---------- Approach 2: Backtracking With Counts ⭐ ----------
def generate_parenthesis(n: int) -> list[str]:
    res: list[str] = []
    path: list[str] = []

    def backtrack(open_: int, close: int) -> None:
        if len(path) == 2 * n:
            res.append("".join(path))  # every leaf is valid by construction
            return
        if open_ < n:
            path.append("(")
            backtrack(open_ + 1, close)
            path.pop()
        if close < open_:  # NOT close < n
            path.append(")")
            backtrack(open_, close + 1)
            path.pop()

    backtrack(0, 0)
    return res


# ---------- Driver ----------
if __name__ == "__main__":
    for n in [3, 1, 2]:
        print("brute    :", sorted(generate_parenthesis_brute(n)))  # any order is accepted
        print("backtrack:", sorted(generate_parenthesis(n)))
        print("---")

"""
Syntax notes (Python):
- itertools.product("()", repeat=k) yields every length-k tuple of chars.
- map("".join, ...) turns each tuple into a string.
- A nested def closes over res/path; no nonlocal needed since we only
  mutate them (append/pop), never rebind.
- `open` is a builtin; `open_` avoids shadowing it.
"""
