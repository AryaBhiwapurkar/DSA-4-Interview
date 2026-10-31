"""
0017. Letter Combinations of a Phone Number  |  Medium  |  Backtracking
Link: https://leetcode.com/problems/letter-combinations-of-a-phone-number/

Problem: Return every letter string that a string of digits 2-9 could
         spell on a phone keypad. Any order.

Examples:
  "23"  -> ["ad","ae","af","bd","be","bf","cd","ce","cf"]
  ""    -> []
  "2"   -> ["a","b","c"]
  "79"  -> 16 strings, "pw" .. "sz"

Approaches:
  1. Iterative expansion       O(4^n * n) time, O(4^n * n) space
  2. Backtracking  ⭐           O(4^n * n) time, O(n) extra space   <- go-to
"""

KEYS = {"2": "abc", "3": "def", "4": "ghi", "5": "jkl", "6": "mno", "7": "pqrs", "8": "tuv", "9": "wxyz"}


# ---------- Approach 1: Iterative Expansion ----------
def letter_combinations_iter(digits: str) -> list[str]:
    if not digits:
        return []
    res = [""]
    for d in digits:
        res = [s + c for s in res for c in KEYS[d]]
    return res


# ---------- Approach 2: Backtracking ⭐ ----------
def letter_combinations(digits: str) -> list[str]:
    if not digits:
        return []  # otherwise dfs would save ""
    res: list[str] = []
    path: list[str] = []

    def dfs(i: int) -> None:
        if i == len(digits):
            res.append("".join(path))
            return
        for c in KEYS[digits[i]]:
            path.append(c)
            dfs(i + 1)
            path.pop()  # unchoose

    dfs(0)
    return res


# ---------- Driver ----------
if __name__ == "__main__":
    for d in ["23", "", "2", "79"]:
        print("iter     :", sorted(letter_combinations_iter(d)))  # any order is accepted
        print("backtrack:", sorted(letter_combinations(d)))
        print("---")

"""
Syntax notes (Python):
- A nested comprehension `[s + c for s in res for c in ...]` reads left to right
  like nested loops.
- A list of chars + "".join(path) avoids O(n) string concatenation per step.
- Nested def sees res/path from the enclosing scope (mutation needs no nonlocal).
"""
