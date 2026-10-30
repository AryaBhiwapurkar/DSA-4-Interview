"""
0155. Min Stack  |  Medium  |  Stack
Link: https://leetcode.com/problems/min-stack/

Problem: Design a stack with push, pop, top and getMin, all O(1).
         pop/top/getMin are only called on a non-empty stack.

Examples:
  push -2, push 0, push -3, getMin, pop, top, getMin
    -> [null,null,null,null,-3,null,0,-2]
  push 0, push 1, push 0, getMin, pop, getMin          (duplicate min)
    -> [null,null,null,null,0,null,0]

Approaches:
  1. Plain stack, scan on getMin   O(n) getMin, O(n) space
  2. Stack of (val, min)  ⭐        O(1) all ops, O(n) space   <- go-to
  3. Two stacks                    O(1) all ops, O(n) space worst case
"""


# ---------- Approach 1: Plain Stack, Scan for Min ----------
class MinStackBrute:
    def __init__(self) -> None:
        self.st: list[int] = []

    def push(self, val: int) -> None:
        self.st.append(val)

    def pop(self) -> None:
        self.st.pop()

    def top(self) -> int:
        return self.st[-1]

    def getMin(self) -> int:
        return min(self.st)


# ---------- Approach 2: Stack of (val, min) ⭐ ----------
class MinStack:
    def __init__(self) -> None:
        self.st: list[tuple[int, int]] = []  # (value, min of this and everything below)

    def push(self, val: int) -> None:
        m = min(val, self.st[-1][1]) if self.st else val
        self.st.append((val, m))

    def pop(self) -> None:
        self.st.pop()

    def top(self) -> int:
        return self.st[-1][0]

    def getMin(self) -> int:
        return self.st[-1][1]


# ---------- Approach 3: Two Stacks ----------
class MinStackTwoStacks:
    def __init__(self) -> None:
        self.st: list[int] = []
        self.mins: list[int] = []

    def push(self, val: int) -> None:
        self.st.append(val)
        if not self.mins or val <= self.mins[-1]:  # <= keeps duplicate mins
            self.mins.append(val)

    def pop(self) -> None:
        if self.st.pop() == self.mins[-1]:
            self.mins.pop()

    def top(self) -> int:
        return self.st[-1]

    def getMin(self) -> int:
        return self.mins[-1]


# ---------- Driver ----------
def run(cls: type, ops: list[str], args: list[int]) -> str:
    st = cls()  # ops[0] is the constructor
    out = ["null"]
    for op, a in zip(ops[1:], args[1:]):
        if op == "push":
            st.push(a)
            out.append("null")
        elif op == "pop":
            st.pop()
            out.append("null")
        elif op == "top":
            out.append(str(st.top()))
        else:
            out.append(str(st.getMin()))
    return "[" + ",".join(out) + "]"


if __name__ == "__main__":
    tests = [
        (["MinStack", "push", "push", "push", "getMin", "pop", "top", "getMin"],
         [0, -2, 0, -3, 0, 0, 0, 0]),
        (["MinStack", "push", "push", "push", "getMin", "pop", "getMin"],
         [0, 0, 1, 0, 0, 0, 0]),
    ]
    for ops, args in tests:
        print("brute    :", run(MinStackBrute, ops, args))
        print("pairs    :", run(MinStack, ops, args))
        print("twoStacks:", run(MinStackTwoStacks, ops, args))
        print("---")

"""
Syntax notes (Python):
- Classes are first-class: pass `cls` and call cls() to construct.
- st[-1][1] reads the second field of the top tuple.
- `x if cond else y` is the conditional expression.
- zip(ops[1:], args[1:]) walks two lists in lockstep, skipping index 0.
"""
