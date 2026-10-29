"""
0006. Zigzag Conversion  |  Medium  |  Arrays & Hashing
Link: https://leetcode.com/problems/zigzag-conversion/

Problem: Write s in a zigzag over numRows rows (down, then diagonally
         up, repeat) and return the rows read left to right.

Examples:
  "PAYPALISHIRING", 3  -> "PAHNAPLSIIGYIR"
  "PAYPALISHIRING", 4  -> "PINALSIGYAHRPI"
  "A", 1               -> "A"
  "AB", 5              -> "AB"

Approaches:
  1. Direct index math     O(n) time, O(n) output
  2. Row buckets  ⭐        O(n) time, O(n) space   <- go-to
"""


# ---------- Approach 1: Direct Index Math ----------
def convert_math(s: str, num_rows: int) -> str:
    n = len(s)
    if num_rows == 1 or num_rows >= n:
        return s
    cycle = 2 * (num_rows - 1)
    out: list[str] = []
    for r in range(num_rows):
        for k in range(r, n, cycle):
            out.append(s[k])  # vertical column char
            diag = k + cycle - 2 * r  # diagonal char between columns
            if 0 < r < num_rows - 1 and diag < n:
                out.append(s[diag])
    return "".join(out)


# ---------- Approach 2: Row Buckets ⭐ ----------
def convert(s: str, num_rows: int) -> str:
    if num_rows == 1:
        return s  # otherwise the bounce never moves
    rows: list[list[str]] = [[] for _ in range(min(num_rows, len(s)))]
    r, step = 0, 1
    for c in s:
        rows[r].append(c)
        if r == 0:
            step = 1
        elif r == len(rows) - 1:
            step = -1  # bounce at top and bottom
        r += step
    return "".join("".join(row) for row in rows)


# ---------- Driver ----------
if __name__ == "__main__":
    for s, k in [("PAYPALISHIRING", 3), ("PAYPALISHIRING", 4), ("A", 1), ("AB", 5)]:
        print("math   :", convert_math(s, k))
        print("buckets:", convert(s, k))
        print("---")

"""
Syntax notes (Python):
- range(start, stop, step) handles the cycle stride directly.
- Chained comparison: 0 < r < n - 1.
- Nested join: "".join("".join(row) for row in rows).
"""
