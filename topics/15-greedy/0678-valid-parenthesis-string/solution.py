"""
0678. Valid Parenthesis String  |  Medium  |  Greedy
Link: https://leetcode.com/problems/valid-parenthesis-string/

Problem: '*' can be '(', ')' or empty. Can s be a valid parentheses string?

Examples:
  "()"       -> true
  "(*)"      -> true
  "(*))"     -> true
  "(((*)"    -> false
  "*("       -> false
  ")*"       -> false
  ""         -> true

Approaches:
  1. Memo on (index, open count)       O(n^2) time, O(n^2) space
  2. Two stacks of indices             O(n) time, O(n) space
  3. Range of open counts [lo, hi]  ⭐  O(n) time, O(1) space   <- go-to
"""

from functools import cache


# ---------- Approach 1: Memo ----------
def check_valid_string_memo(s: str) -> bool:
    @cache
    def ok(i: int, opened: int) -> bool:
        if opened < 0:  # more ')' than '(' so far
            return False
        if i == len(s):
            return opened == 0
        if s[i] == "(":
            return ok(i + 1, opened + 1)
        if s[i] == ")":
            return ok(i + 1, opened - 1)
        return ok(i + 1, opened + 1) or ok(i + 1, opened - 1) or ok(i + 1, opened)  # '*' as ( ) or empty

    return ok(0, 0)


# ---------- Approach 2: Two Stacks ----------
def check_valid_string_stacks(s: str) -> bool:
    opens: list[int] = []
    stars: list[int] = []
    for i, ch in enumerate(s):
        if ch == "(":
            opens.append(i)
        elif ch == "*":
            stars.append(i)
        elif opens:  # prefer a real '(' to close ')'
            opens.pop()
        elif stars:
            stars.pop()
        else:
            return False
    while opens and stars:  # leftover '(' each needs a '*' AFTER it
        if opens.pop() > stars.pop():
            return False
    return not opens


# ---------- Approach 3: Open-count Range ⭐ ----------
def check_valid_string(s: str) -> bool:
    lo = hi = 0  # min / max possible number of unmatched '('
    for ch in s:
        if ch == "(":
            lo, hi = lo + 1, hi + 1
        elif ch == ")":
            lo, hi = lo - 1, hi - 1
        else:  # '*': could close one, or open one
            lo, hi = lo - 1, hi + 1
        if hi < 0:  # too many ')' even if every '*' is '('
            return False
        lo = max(lo, 0)  # a negative count is never a valid choice
    return lo == 0


# ---------- Driver ----------
if __name__ == "__main__":
    for s in ["()", "(*)", "(*))", "(((*)", "*(", ")*", ""]:
        print("memo  :", str(check_valid_string_memo(s)).lower())
        print("stacks:", str(check_valid_string_stacks(s)).lower())
        print("range :", str(check_valid_string(s)).lower())
        print("---")

"""
Syntax notes (Python):
- `or` short-circuits across the three '*' choices.
- `elif opens:` treats an empty list as False.
- lo, hi = lo - 1, hi + 1 updates both from the old values.
"""
