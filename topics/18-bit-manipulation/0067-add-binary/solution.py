"""
0067. Add Binary  |  Easy  |  Bit Manipulation
Link: https://leetcode.com/problems/add-binary/

Problem: Add two binary strings and return the sum as a binary string.

Examples:
  "11", "1"         -> "100"
  "1010", "1011"    -> "10101"
  "0", "0"          -> "0"
  "1111", "1"       -> "10000"
  "1", "111"        -> "1000"

Approaches:
  1. Pad to equal length, add column by column  O(max(m, n)) time, O(max(m, n)) space
  2. Two pointers from the right with carry  ⭐  O(max(m, n)) time, O(max(m, n)) space   <- go-to
"""


# ---------- Approach 1: Pad + Column Add ----------
def add_binary_pad(a: str, b: str) -> str:
    n = max(len(a), len(b))
    a, b = a.zfill(n), b.zfill(n)  # left-pad with zeros
    out, carry = [], 0
    for k in range(n - 1, -1, -1):
        s = int(a[k]) + int(b[k]) + carry
        out.append(str(s % 2))
        carry = s // 2
    if carry:
        out.append("1")
    return "".join(reversed(out))


# ---------- Approach 2: Two Pointers + Carry ⭐ ----------
def add_binary(a: str, b: str) -> str:
    i, j, carry = len(a) - 1, len(b) - 1, 0
    out = []
    while i >= 0 or j >= 0 or carry:
        s = carry
        if i >= 0:
            s += int(a[i])
            i -= 1
        if j >= 0:
            s += int(b[j])
            j -= 1
        out.append(str(s & 1))  # sum bit
        carry = s >> 1  # 0 or 1
    return "".join(reversed(out))


# ---------- Driver ----------
if __name__ == "__main__":
    for a, b in [("11", "1"), ("1010", "1011"), ("0", "0"), ("1111", "1"), ("1", "111")]:
        print("pad  :", add_binary_pad(a, b))
        print("carry:", add_binary(a, b))
        print("---")

"""
Syntax notes (Python):
- s.zfill(n) left-pads with zeros; int(a, 2) / bin(x)[2:] would also work (big ints).
- Build the answer in a list and join once: repeated str + str is O(n^2).
- `while i >= 0 or j >= 0 or carry` keeps going for a final carry.
"""
