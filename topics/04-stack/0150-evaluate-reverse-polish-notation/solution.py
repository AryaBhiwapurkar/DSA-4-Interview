"""
0150. Evaluate Reverse Polish Notation  |  Medium  |  Stack
Link: https://leetcode.com/problems/evaluate-reverse-polish-notation/

Problem: Evaluate a postfix expression of integers and + - * /.
         Division truncates toward zero. Input is always valid.

Examples:
  ["2","1","+","3","*"]                                        -> 9
  ["4","13","5","/","+"]                                       -> 6
  ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]    -> 22
  ["18"]                                                       -> 18
  ["4","-3","/"]                                               -> -1

Approaches:
  1. Repeated collapse   O(n^2) time, O(n) space
  2. Stack  ⭐            O(n) time, O(n) space   <- go-to
"""

OPS = {
    "+": lambda a, b: a + b,
    "-": lambda a, b: a - b,
    "*": lambda a, b: a * b,
    "/": lambda a, b: int(a / b),  # truncate toward zero; // would floor
}


# ---------- Approach 1: Repeated Collapse ----------
def eval_rpn_brute(tokens: list[str]) -> int:
    t = tokens[:]
    while len(t) > 1:
        i = next(k for k, tok in enumerate(t) if tok in OPS)  # first operator
        t[i - 2 : i + 1] = [str(OPS[t[i]](int(t[i - 2]), int(t[i - 1])))]
    return int(t[0])


# ---------- Approach 2: Stack ⭐ ----------
def eval_rpn(tokens: list[str]) -> int:
    st: list[int] = []
    for tok in tokens:
        if tok in OPS:  # "-11" is not a key, so it's treated as a number
            b = st.pop()  # first pop = RIGHT operand
            a = st.pop()
            st.append(OPS[tok](a, b))
        else:
            st.append(int(tok))
    return st[-1]


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        ["2", "1", "+", "3", "*"],
        ["4", "13", "5", "/", "+"],
        ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"],
        ["18"],
        ["4", "-3", "/"],
    ]
    for t in tests:
        print("brute:", eval_rpn_brute(t))
        print("stack:", eval_rpn(t))
        print("---")

"""
Syntax notes (Python):
- A dict of lambdas replaces an if/elif chain for operators.
- int(a / b) truncates toward zero; a // b floors (-4 // 3 == -2).
- Slice assignment t[i-2:i+1] = [x] replaces three items with one.
- next(gen) returns the first item a generator yields.
"""
