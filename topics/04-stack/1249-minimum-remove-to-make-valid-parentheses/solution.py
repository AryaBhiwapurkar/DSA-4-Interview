"""
1249. Minimum Remove to Make Valid Parentheses  |  Medium  |  Stack
Link: https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/

Problem: Remove the fewest parentheses so the string is valid; return any valid result.

Examples:
  "lee(t(c)o)de)"  -> "lee(t(c)o)de"
  "a)b(c)d"        -> "ab(c)d"
  "))(("           -> ""
  "(a(b)"          -> "a(b)"   (two-pass gives "(ab)": also valid)
  "abc"            -> "abc"

Approaches:
  1. Two passes with a counter         O(n) time, O(n) space
  2. Index stack + removal set  ⭐     O(n) time, O(n) space   <- go-to
  (Any valid minimal answer is accepted; the two approaches may pick different brackets.)
"""


# ---------- Approach 1: Two Passes ----------
def min_remove_to_make_valid_two_pass(s: str) -> str:
    a, bal = [], 0
    for c in s:  # drop ')' that would go negative
        if c == ")" and bal == 0:
            continue
        bal += 1 if c == "(" else -1 if c == ")" else 0
        a.append(c)
    b = []
    for c in reversed(a):  # drop the last `bal` extra '('
        if c == "(" and bal > 0:
            bal -= 1
            continue
        b.append(c)
    return "".join(reversed(b))


# ---------- Approach 2: Index Stack ⭐ ----------
def min_remove_to_make_valid(s: str) -> str:
    st: list[int] = []  # indices of unmatched '('
    drop: set[int] = set()
    for i, c in enumerate(s):
        if c == "(":
            st.append(i)
        elif c == ")":
            if st:
                st.pop()
            else:
                drop.add(i)  # nothing to match
    drop.update(st)  # leftover '(' are unmatched
    return "".join(c for i, c in enumerate(s) if i not in drop)


# ---------- Driver ----------
if __name__ == "__main__":
    for s in ["lee(t(c)o)de)", "a)b(c)d", "))((", "(a(b)", "abc"]:
        print(f'two-pass: "{min_remove_to_make_valid_two_pass(s)}"')
        print(f'stack   : "{min_remove_to_make_valid(s)}"')
        print("---")

"""
Syntax notes (Python):
- set.update(iterable) adds many items at once.
- Chained conditional expression: 1 if a else -1 if b else 0.
- "".join(generator) builds the result without repeated string concatenation.
"""
