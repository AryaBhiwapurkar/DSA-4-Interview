"""
0051. N-Queens  |  Hard  |  Backtracking
Link: https://leetcode.com/problems/n-queens/

Problem: Return every placement of n non-attacking queens on an n x n
         board, as row strings of 'Q' and '.'.

Examples:
  n 4  -> [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
  n 1  -> [["Q"]]
  n 2  -> []
  n 3  -> []
  n 8  -> 92 solutions (count printed)

Approaches:
  1. Backtracking + board scan      O(n! * n) time, O(n^2) space
  2. Backtracking + col/diag sets ⭐ O(n!) time, O(n) extra   <- go-to
"""


# ---------- Approach 1: Backtracking + Board Scan ----------
def solve_n_queens_scan(n: int) -> list[list[str]]:
    b = [["."] * n for _ in range(n)]
    res: list[list[str]] = []

    def safe(r: int, c: int) -> bool:
        for i in range(r):
            if b[i][c] == "Q":
                return False
            dc = r - i  # same row distance -> diagonal offsets
            if c - dc >= 0 and b[i][c - dc] == "Q":
                return False
            if c + dc < n and b[i][c + dc] == "Q":
                return False
        return True

    def go(r: int) -> None:
        if r == n:
            res.append(["".join(row) for row in b])
            return
        for c in range(n):
            if safe(r, c):
                b[r][c] = "Q"
                go(r + 1)
                b[r][c] = "."

    go(0)
    return res


# ---------- Approach 2: Backtracking + Column/Diagonal Sets ⭐ ----------
def solve_n_queens(n: int) -> list[list[str]]:
    cols: set[int] = set()
    diag: set[int] = set()  # r - c, constant along "\"
    anti: set[int] = set()  # r + c, constant along "/"
    queen_col = [0] * n
    res: list[list[str]] = []

    def place(r: int) -> None:
        if r == n:
            res.append(["." * c + "Q" + "." * (n - c - 1) for c in queen_col])
            return
        for c in range(n):
            if c in cols or r - c in diag or r + c in anti:
                continue
            cols.add(c), diag.add(r - c), anti.add(r + c)
            queen_col[r] = c
            place(r + 1)
            cols.remove(c), diag.remove(r - c), anti.remove(r + c)

    place(0)
    return res


# ---------- Driver ----------
if __name__ == "__main__":
    for n in [4, 1, 2, 3]:
        print("scan:", sorted(solve_n_queens_scan(n)))  # any order is accepted
        print("sets:", sorted(solve_n_queens(n)))
        print("---")
    print("scan n=8 count:", len(solve_n_queens_scan(8)))
    print("sets n=8 count:", len(solve_n_queens(8)))

"""
Syntax notes (Python):
- Python sets accept negative keys, so r - c needs no offset.
- "." * c + "Q" + ... builds a row string directly from the queen's column.
- `a.add(x), b.add(y)` is a tuple expression: a compact way to run several calls.
"""
