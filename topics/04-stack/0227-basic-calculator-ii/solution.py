"""
0227. Basic Calculator II  |  Medium  |  Stack
Link: https://leetcode.com/problems/basic-calculator-ii/

Problem: Evaluate a string with non-negative ints, + - * /, spaces; no parentheses.
         Division truncates toward zero.

Examples:
  "3+2*2"      -> 7
  " 3/2 "      -> 1
  " 3+5 / 2 "  -> 5
  "14-3/2"     -> 13
  "42"         -> 42

Approaches:
  1. Two passes (tokens, then precedence)       O(n) time, O(n) space
  2. Stack with previous operator  ⭐           O(n) time, O(n) space   <- go-to
"""

import re


def trunc_div(a: int, b: int) -> int:
    return int(a / b)  # truncate toward zero (// would floor)


# ---------- Approach 1: Two Passes ----------
def calculate_two_pass(s: str) -> int:
    tokens = re.findall(r"\d+|[-+*/]", s)
    terms, add_ops = [int(tokens[0])], []
    for op, val in zip(tokens[1::2], map(int, tokens[2::2])):  # collapse * and / first
        if op == "*":
            terms[-1] *= val
        elif op == "/":
            terms[-1] = trunc_div(terms[-1], val)
        else:
            add_ops.append(op)
            terms.append(val)
    return terms[0] + sum(t if op == "+" else -t for op, t in zip(add_ops, terms[1:]))


# ---------- Approach 2: Previous-operator Stack ⭐ ----------
def calculate(s: str) -> int:
    st: list[int] = []
    num, op = 0, "+"  # op: operator before the current number
    for c in s + "\0":  # "\0" = end: flush the last number
        if c.isdigit():
            num = num * 10 + int(c)
        elif c != " ":
            if op == "+":
                st.append(num)
            elif op == "-":
                st.append(-num)
            elif op == "*":
                st[-1] *= num
            else:
                st[-1] = trunc_div(st[-1], num)
            op, num = c, 0
    return sum(st)


# ---------- Driver ----------
if __name__ == "__main__":
    for s in ["3+2*2", " 3/2 ", " 3+5 / 2 ", "14-3/2", "42"]:
        print("two-pass:", calculate_two_pass(s))
        print("stack   :", calculate(s))
        print("---")

"""
Syntax notes (Python):
- int(a / b) truncates toward zero; a // b floors (-3 // 2 == -2). Fine here: |values| < 2^31.
- re.findall(r"\\d+|[-+*/]", s) tokenises numbers and operators, skipping spaces.
- tokens[1::2] / tokens[2::2] take every other element (operators / following numbers).
"""
