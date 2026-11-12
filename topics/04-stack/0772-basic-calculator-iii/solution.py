"""
0772. Basic Calculator III  |  Hard  |  Stack  |  LC Premium
Link: https://leetcode.com/problems/basic-calculator-iii/

Problem: Evaluate non-negative ints with + - * /, parentheses and spaces;
         division truncates toward zero.

Examples:
  "1+1"                    -> 2
  "6-4/2"                  -> 4
  "2*(5+5*2)/3+(6/2+8)"    -> 21
  "((2))"                  -> 2
  "(0-3)/2"                -> -1

Approaches:
  1. Two stacks (shunting-yard)               O(n) time, O(n) space
  2. Recursive previous-operator stack  ⭐    O(n) time, O(n) space   <- go-to
"""

PREC = {"+": 1, "-": 1, "*": 2, "/": 2, "(": 0}


def apply(op: str, a: int, b: int) -> int:
    if op == "+":
        return a + b
    if op == "-":
        return a - b
    if op == "*":
        return a * b
    return int(a / b)  # truncate toward zero


# ---------- Approach 1: Two Stacks ----------
def calculate_two_stacks(s: str) -> int:
    vals: list[int] = []
    ops: list[str] = []

    def reduce_top() -> None:
        b, a = vals.pop(), vals.pop()
        vals.append(apply(ops.pop(), a, b))

    i = 0
    while i < len(s):
        c = s[i]
        if c.isdigit():
            j = i
            while j < len(s) and s[j].isdigit():
                j += 1
            vals.append(int(s[i:j]))
            i = j
            continue
        if c == "(":
            ops.append(c)
        elif c == ")":
            while ops[-1] != "(":
                reduce_top()
            ops.pop()  # drop '('
        elif c != " ":
            while ops and PREC[ops[-1]] >= PREC[c]:  # left-assoc
                reduce_top()
            ops.append(c)
        i += 1
    while ops:
        reduce_top()
    return vals[-1]


# ---------- Approach 2: Recursive Stack ⭐ ----------
def calculate(s: str) -> int:
    def eval_from(i: int) -> tuple[int, int]:
        st: list[int] = []
        num, op = 0, "+"
        while i <= len(s):
            c = s[i] if i < len(s) else "\0"
            if c.isdigit():
                num = num * 10 + int(c)
            elif c == "(":
                num, i = eval_from(i + 1)  # group = one operand; i lands on ')'
            elif c != " ":
                if op == "+":
                    st.append(num)
                elif op == "-":
                    st.append(-num)
                else:
                    st[-1] = apply(op, st[-1], num)
                if c in ")\0":
                    return sum(st), i  # caller resumes after ')'
                op, num = c, 0
            i += 1
        return sum(st), i

    return eval_from(0)[0]


# ---------- Driver ----------
if __name__ == "__main__":
    for s in ["1+1", "6-4/2", "2*(5+5*2)/3+(6/2+8)", "((2))", "(0-3)/2"]:
        print("two stacks:", calculate_two_stacks(s))
        print("recursive :", calculate(s))
        print("---")

"""
Syntax notes (Python):
- A nested function returning (value, index) replaces C++'s pass-by-reference index.
- `c in ")\\0"` checks membership in a short string of characters.
- int(a / b) truncates toward zero; // would floor (-3 // 2 == -2).
"""
