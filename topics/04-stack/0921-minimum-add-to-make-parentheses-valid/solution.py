"""
0921. Minimum Add to Make Parentheses Valid  |  Medium  |  Stack
Link: https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/

Problem: Fewest '(' or ')' insertions that make the string valid.

Examples:
  "())"   -> 1
  "((("   -> 3
  ")("    -> 2
  "()"    -> 0
  ")))"   -> 3

Approaches:
  1. Remove "()" pairs repeatedly     O(n^2) time
  2. Stack                            O(n) time, O(n) space
  3. Two counters  ⭐                 O(n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Remove Pairs ----------
def min_add_to_make_valid_pairs(s: str) -> int:
    while "()" in s:
        s = s.replace("()", "")
    return len(s)  # everything left is unmatched


# ---------- Approach 2: Stack ----------
def min_add_to_make_valid_stack(s: str) -> int:
    st: list[str] = []
    unmatched_close = 0
    for c in s:
        if c == "(":
            st.append(c)
        elif st:
            st.pop()
        else:
            unmatched_close += 1
    return len(st) + unmatched_close


# ---------- Approach 3: Two Counters ⭐ ----------
def min_add_to_make_valid(s: str) -> int:
    open_ = add = 0
    for c in s:
        if c == "(":
            open_ += 1
        elif open_:
            open_ -= 1  # matched
        else:
            add += 1  # needs an inserted '('
    return add + open_  # leftover '(' each need a ')'


# ---------- Driver ----------
if __name__ == "__main__":
    for s in ["())", "(((", ")(", "()", ")))"]:
        print("pairs   :", min_add_to_make_valid_pairs(s))
        print("stack   :", min_add_to_make_valid_stack(s))
        print("counters:", min_add_to_make_valid(s))
        print("---")

"""
Syntax notes (Python):
- open_ avoids shadowing the built-in open().
- s.replace("()", "") removes every non-overlapping "()" in one pass.
- `elif open_:` treats any non-zero count as True.
"""
