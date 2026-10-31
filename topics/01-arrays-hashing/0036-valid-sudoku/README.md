---
number: 36
title: Valid Sudoku
difficulty: Medium
topic: Arrays & Hashing
pattern: Hash sets per row/col/box
link: https://leetcode.com/problems/valid-sudoku/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0037 Sudoku Solver", "0051 N-Queens"]
---

# 0036. Valid Sudoku

## ⚡ 30-Second Summary
**Pattern:** Seen-sets per row, column, and 3×3 box
**Key insight:** Each filled cell belongs to exactly one row, one column, and one box. The box index is `(r/3)*3 + c/3`. One pass, 27 "seen" sets, fail on the first repeat.
**Go-to:** Single pass with 27 seen-arrays, O(81) = O(1) time and space

## Problem
Given a partially filled 9×9 Sudoku board, return whether the filled cells are valid: no digit 1–9 repeats in any row, any column, or any of the nine 3×3 boxes. The board does not need to be solvable.

**Examples:**
```
Input:  board =
  5 3 . | . 7 . | . . .
  6 . . | 1 9 5 | . . .
  . 9 8 | . . . | . 6 .
  ------+-------+------
  8 . . | . 6 . | . . 3
  4 . . | 8 . 3 | . . 1
  7 . . | . 2 . | . . 6
  ------+-------+------
  . 6 . | . . . | 2 8 .
  . . . | 4 1 9 | . . 5
  . . . | . 8 . | . 7 9
Output: true
Why:    No row, column, or box has a repeated digit.

Input:  same board, but the top-left 5 is changed to 8
Output: false
Why:    The top-left box now has two 8s (and column 0 too).
```

**Constraints:**
- The board is always 9×9; cells are '1'–'9' or '.'.
- Only filled cells are checked; solvability is not required.

## Hints
<details><summary>Hint 1</summary>
Checking rows alone is easy with a set. Columns and boxes are the same check on a different grouping.
</details>
<details><summary>Hint 2</summary>
Can you do all three checks in a single pass over the board?
</details>
<details><summary>Hint 3</summary>
Number the boxes 0–8 with `(r/3)*3 + c/3`. Keep seen[row][d], seen[col][d], seen[box][d].
</details>

## Clarifying Questions
- Do I need to check solvability? (No.)
- Is the board always 9×9 with '.' for empty? (Yes.)
- Return on the first violation? (Yes, a boolean.)

## Example Walkthrough
Second example, top-left cell is now '8':
- Row 0 sees 8, 3, 7. Column 0 sees 8 (row 0), 6, then 8 again at row 3: violation.
- Box 0 also sees 8 at (0,0) and again at (2,2). Either way: false.

## Approaches

### 1. Three Separate Passes: O(81) time, O(9) space
Check all rows with a set, then all columns, then all boxes. Clear but three loops and more code.

### 2. Single Pass, 27 Seen-Arrays ⭐ Go-to: O(81) time, O(243) space (both O(1))
For each filled cell with digit d, check and mark `rows[r][d]`, `cols[c][d]`, `boxes[(r/3)*3 + c/3][d]`.
**Why it's the go-to:** one loop, early exit, and the box-index formula is the one thing they're looking for.

(Bitmask variant: three arrays of 9 ints, bit d marks "seen". Same complexity, smaller, a nice extra.)

## Dry Run (Approach 2)
Second example (top-left changed to 8), first few filled cells in row-major order:

| cell | d | box | row seen? | col seen? | box seen? |
|------|---|-----|-----------|-----------|-----------|
| (0,0) | 8 | 0 | no | no | no |
| (0,1) | 3 | 0 | no | no | no |
| (0,4) | 7 | 1 | no | no | no |
| ... | | | | | |
| (2,2) | 8 | 0 | no | no | **yes**: return false |

## Edge Case Check
- Empty board (all '.'): valid. ✅
- Repeat only inside a box (not in any row/col): caught by the box set. ✅
- Board that's valid but unsolvable: still true (only filled cells matter). ✅

## ⚠️ Pitfalls
- **Wrong box index:** `r/3 + c/3` collides (box (0,1) and (1,0)); it must be `(r/3)*3 + c/3`.
- **Digit to index:** `c - '1'` gives 0–8; `c - '0'` gives 1–9 (then arrays need size 10).
- **Checking '.' cells:** skip them before indexing.

## 🎯 What the Interviewer Wants
- One pass with the box formula.
- Clean data structure choice (bool arrays or bitmasks beat hash sets here).
- Clarify that solvability is not part of the task.

## Follow-ups
- **Actually solve the board:** backtracking with the same three seen-structures: LC 0037 Sudoku Solver (not added yet)
- **N×N Sudoku (N = k²):** box index `(r/k)*k + c/k`, same algorithm.
- **Similar constraint tracking:** [LC 0051 N-Queens](../../10-backtracking/0051-n-queens/)
