"""
0036. Valid Sudoku  |  Medium  |  Arrays & Hashing
Link: https://leetcode.com/problems/valid-sudoku/

Problem: Return true if the filled cells of a 9x9 board have no repeated
         digit in any row, column, or 3x3 box ('.' = empty).

Examples (rows written as strings):
  LeetCode example 1                               -> True
  example 1 with top-left 5 changed to 8           -> False
  empty board                                      -> True

Approaches:
  1. Three separate passes        O(81) time, O(9) space
  2. Single pass, 27 seen  ⭐      O(81) time, O(243) space   <- go-to
"""


def no_repeats(cells: list[str]) -> bool:
    digits = [c for c in cells if c != "."]
    return len(digits) == len(set(digits))


# ---------- Approach 1: Three Separate Passes ----------
def is_valid_sudoku_three_pass(board: list[str]) -> bool:
    for i in range(9):
        row = list(board[i])
        col = [board[j][i] for j in range(9)]
        box = [board[(i // 3) * 3 + j // 3][(i % 3) * 3 + j % 3] for j in range(9)]  # j-th cell of box i
        if not (no_repeats(row) and no_repeats(col) and no_repeats(box)):
            return False
    return True


# ---------- Approach 2: Single Pass, 27 Seen-Sets ⭐ ----------
def is_valid_sudoku(board: list[str]) -> bool:
    rows = [set() for _ in range(9)]
    cols = [set() for _ in range(9)]
    boxes = [set() for _ in range(9)]
    for r in range(9):
        for c in range(9):
            d = board[r][c]
            if d == ".":
                continue
            k = (r // 3) * 3 + c // 3  # box index 0..8
            if d in rows[r] or d in cols[c] or d in boxes[k]:
                return False
            rows[r].add(d)
            cols[c].add(d)
            boxes[k].add(d)
    return True


# ---------- Driver ----------
if __name__ == "__main__":
    valid = [
        "53..7....", "6..195...", ".98....6.",
        "8...6...3", "4..8.3..1", "7...2...6",
        ".6....28.", "...419..5", "....8..79",
    ]
    invalid = ["8" + valid[0][1:]] + valid[1:]
    empty = ["." * 9] * 9
    for b in (valid, invalid, empty):
        print("three pass :", is_valid_sudoku_three_pass(b))
        print("single pass:", is_valid_sudoku(b))
        print("---")

"""
Syntax notes (Python):
- // is floor division: (r // 3) * 3 + c // 3 gives the box index.
- [set() for _ in range(9)] makes 9 separate sets ([set()] * 9 would share one).
- Strings are immutable: build a modified row with slicing ("8" + s[1:]).
"""
