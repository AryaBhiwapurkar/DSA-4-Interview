"""
0043. Multiply Strings  |  Medium  |  Math & Geometry
Link: https://leetcode.com/problems/multiply-strings/

Problem: Multiply two non-negative decimal strings without converting them
         to integers. Return the product as a string.

Examples:
  "2"   * "3"    -> "6"
  "123" * "456"  -> "56088"
  "0"   * "52"   -> "0"
  "9"   * "9"    -> "81"
  "999" * "999"  -> "998001"
  "123456789" * "987654321" -> "121932631112635269"

Approaches:
  1. Multiply by each digit + add strings   O(m*n) time, O(m+n) space
  2. Position array  ⭐                     O(m*n) time, O(m+n) space   <- go-to
"""


# ---------- Approach 1: Multiply by Each Digit + Add Strings ----------
def add_strings(a: str, b: str) -> str:
    out: list[str] = []
    i, j, carry = len(a) - 1, len(b) - 1, 0
    while i >= 0 or j >= 0 or carry:
        s = carry
        if i >= 0:
            s += ord(a[i]) - ord("0")
            i -= 1
        if j >= 0:
            s += ord(b[j]) - ord("0")
            j -= 1
        carry, d = divmod(s, 10)
        out.append(str(d))
    return "".join(reversed(out))


def multiply_rows(num1: str, num2: str) -> str:
    if num1 == "0" or num2 == "0":
        return "0"
    total = "0"
    n = len(num2)
    for j in range(n - 1, -1, -1):
        d, carry = int(num2[j]), 0
        row = ["0"] * (n - 1 - j)  # shift: trailing zeros (built reversed)
        for i in range(len(num1) - 1, -1, -1):
            carry, digit = divmod(int(num1[i]) * d + carry, 10)
            row.append(str(digit))
        if carry:
            row.append(str(carry))
        total = add_strings(total, "".join(reversed(row)))
    return total


# ---------- Approach 2: Position Array ⭐ ----------
def multiply(num1: str, num2: str) -> str:
    m, n = len(num1), len(num2)
    res = [0] * (m + n)  # product has at most m + n digits
    for i in range(m - 1, -1, -1):
        for j in range(n - 1, -1, -1):
            s = int(num1[i]) * int(num2[j]) + res[i + j + 1]
            res[i + j + 1] = s % 10
            res[i + j] += s // 10  # may exceed 9 briefly; fixed by a later pair
    out = "".join(map(str, res)).lstrip("0")
    return out or "0"


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [("2", "3"), ("123", "456"), ("0", "52"), ("9", "9"), ("999", "999"),
             ("123456789", "987654321")]
    for a, b in tests:
        print("rows    :", multiply_rows(a, b))
        print("position:", multiply(a, b))
        print("---")

"""
Syntax notes (Python):
- int(c) on a single character is fine; only whole-string conversion is off limits.
- s.lstrip("0") strips leading zeros; `out or "0"` handles the all-zero case.
- "".join(reversed(lst)) builds a string from digits collected backwards.
"""
