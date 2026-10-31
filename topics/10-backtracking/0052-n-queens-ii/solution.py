"""
0052. N-Queens II  |  Hard  |  Backtracking
Link: https://leetcode.com/problems/n-queens-ii/

Problem: Count the placements of n non-attacking queens on an n x n board.

Examples:
  n 4  -> 2
  n 1  -> 1
  n 2  -> 0
  n 3  -> 0
  n 8  -> 92
  n 9  -> 352

Approaches:
  1. Backtracking + col/diag sets  ⭐   O(n!) time, O(n) space   <- go-to
  2. Bitmask backtracking              O(n!) time, O(n) space
"""


# ---------- Approach 1: Backtracking + Column/Diagonal Sets ⭐ ----------
def total_n_queens(n: int) -> int:
    cols: set[int] = set()
    diag: set[int] = set()
    anti: set[int] = set()

    def count(r: int) -> int:
        if r == n:
            return 1
        total = 0
        for c in range(n):
            if c in cols or r - c in diag or r + c in anti:
                continue
            cols.add(c), diag.add(r - c), anti.add(r + c)
            total += count(r + 1)
            cols.remove(c), diag.remove(r - c), anti.remove(r + c)
        return total

    return count(0)


# ---------- Approach 2: Bitmask Backtracking ----------
def total_n_queens_bitmask(n: int) -> int:
    full = (1 << n) - 1

    def go(cols: int, d1: int, d2: int) -> int:
        if cols == full:
            return 1
        total = 0
        avail = full & ~(cols | d1 | d2)  # mask: ~ makes a negative int in Python
        while avail:
            bit = avail & -avail  # lowest free column
            avail -= bit
            total += go(cols | bit, ((d1 | bit) << 1) & full, (d2 | bit) >> 1)
        return total

    return go(0, 0, 0)


# ---------- Driver ----------
if __name__ == "__main__":
    for n in [4, 1, 2, 3, 8, 9]:
        print("sets   :", total_n_queens(n))
        print("bitmask:", total_n_queens_bitmask(n))
        print("---")

"""
Syntax notes (Python):
- ~x is -(x + 1) on unbounded ints; AND with `full` to keep n bits.
- x & -x still isolates the lowest set bit.
"""
