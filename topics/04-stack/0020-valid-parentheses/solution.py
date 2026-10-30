"""
0020. Valid Parentheses  |  Easy  |  Stack
Link: https://leetcode.com/problems/valid-parentheses/

Problem: A string of ()[]{} is valid if every closer matches the most
         recent unclosed opener of the same type and nothing is left open.

Examples:
  "()"      -> True
  "()[]{}"  -> True
  "(]"      -> False
  "([])"    -> True
  "([)]"    -> False
  "]"       -> False
  "(("      -> False

Approaches:
  1. Repeated removal   O(n^2) time, O(n) space
  2. Stack  ⭐           O(n) time, O(n) space   <- go-to
"""


# ---------- Approach 1: Repeated Removal ----------
def is_valid_brute(s: str) -> bool:
    prev = None
    while prev != s:
        prev = s
        s = s.replace("()", "").replace("[]", "").replace("{}", "")
    return s == ""


# ---------- Approach 2: Stack ⭐ ----------
def is_valid(s: str) -> bool:
    match = {")": "(", "]": "[", "}": "{"}
    st: list[str] = []
    for c in s:
        if c not in match:  # opener
            st.append(c)
        elif not st or st.pop() != match[c]:  # `not st` first: pop on empty raises
            return False
    return not st  # leftovers = unclosed openers


# ---------- Driver ----------
if __name__ == "__main__":
    tests = ["()", "()[]{}", "(]", "([])", "([)]", "]", "(("]
    for s in tests:
        print("brute:", is_valid_brute(s))
        print("stack:", is_valid(s))
        print("---")

"""
Syntax notes (Python):
- A list is the stack: append / pop / st[-1]; `not st` tests empty.
- Short-circuit `not st or st.pop() != x` makes the pop safe.
- str.replace returns a new string (strings are immutable).
"""
