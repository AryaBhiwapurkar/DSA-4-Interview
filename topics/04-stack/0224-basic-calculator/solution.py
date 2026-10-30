"""
0224. Basic Calculator  |  Hard  |  Stack
Link: https://leetcode.com/problems/basic-calculator/

Problem: Evaluate a valid expression with non-negative integers, + - ( )
         and spaces. '-' may be unary. No eval.

Examples:
  "1 + 1"                -> 2
  " 2-1 + 2 "            -> 3
  "(1+(4+5+2)-3)+(6+8)"  -> 23
  "-(2+3)"               -> -5
  "1-(     -2)"          -> 3
  "2147483647"           -> 2147483647

Approaches:
  1. Recursive descent       O(n) time, O(depth) space
  2. Stack of (result, sign) ⭐ O(n) time, O(depth) space   <- go-to
"""


# ---------- Approach 1: Recursive Descent ----------
def calculate_recursive(s: str) -> int:
    i = 0

    def parse() -> int:
        nonlocal i
        res, sign = 0, 1
        while i < len(s):
            c = s[i]
            i += 1
            if c.isdigit():
                num = int(c)
                while i < len(s) and s[i].isdigit():
                    num = num * 10 + int(s[i])
                    i += 1
                res += sign * num
            elif c == "+":
                sign = 1
            elif c == "-":
                sign = -1
            elif c == "(":
                res += sign * parse()  # a group is just a number
            elif c == ")":
                return res
        return res

    return parse()


# ---------- Approach 2: Stack of (result, sign) ⭐ ----------
def calculate(s: str) -> int:
    res, num, sign = 0, 0, 1
    st: list[tuple[int, int]] = []  # saved (result, sign) per open paren
    for c in s:
        if c.isdigit():
            num = num * 10 + int(c)
        elif c in "+-":
            res += sign * num  # flush the pending number
            num = 0
            sign = 1 if c == "+" else -1
        elif c == "(":
            st.append((res, sign))
            res, sign = 0, 1
        elif c == ")":
            res += sign * num
            num = 0
            outer_res, outer_sign = st.pop()
            res = outer_res + outer_sign * res
        # spaces fall through
    return res + sign * num  # flush the final number


# ---------- Driver ----------
if __name__ == "__main__":
    tests = ["1 + 1", " 2-1 + 2 ", "(1+(4+5+2)-3)+(6+8)", "-(2+3)", "1-(     -2)", "2147483647"]
    for s in tests:
        print("recursive:", calculate_recursive(s))
        print("stack    :", calculate(s))
        print("---")

"""
Syntax notes (Python):
- `nonlocal i` lets a nested function rebind a variable of the outer one.
- `c in "+-"` checks membership in a string of chars.
- Stack of tuples: st.append((a, b)); a, b = st.pop() unpacks in one line.
- Default recursion limit is ~1000: deep nesting needs the iterative version.
"""
