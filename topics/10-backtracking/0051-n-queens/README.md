---
number: 51
title: N-Queens
difficulty: Hard
topic: Backtracking
pattern: Backtrack with col/diag sets
link: https://leetcode.com/problems/n-queens/
lists: [NeetCode 150]
followup_of: []
related: ["0052 N-Queens II", "0037 Sudoku Solver", "0036 Valid Sudoku"]
---

# 0051. N-Queens

## ⚡ 30-Second Summary
**Pattern:** Row-by-row backtracking with column and diagonal sets
**Key insight:** Exactly one queen per row, so recurse over rows and choose a column. Two queens share a "\" diagonal iff `r - c` is equal and a "/" diagonal iff `r + c` is equal, so three sets (cols, r-c, r+c) make each safety check O(1).
**Go-to:** Backtracking with 3 sets, O(n!) time, O(n) extra space (plus output)

## Problem
Place n queens on an n × n board so that no two attack each other (same row, column or diagonal). Return every such board, drawn as strings with 'Q' and '.'. Any order. [LeetCode](https://leetcode.com/problems/n-queens/)

**Examples:**
```
Input:  n = 4
Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
Why:    Only two placements survive on a 4×4 board, mirror images of each other.

Input:  n = 1
Output: [["Q"]]
Why:    A single queen on a single square.
```

**Constraints:**
- 1 ≤ n ≤ 9 (n = 9 has 352 solutions).

## Hints
<details><summary>Hint 1</summary>
Each row holds exactly one queen. What does that let you recurse over?
</details>
<details><summary>Hint 2</summary>
Checking a square by scanning the board is O(n). What single number identifies each diagonal?
</details>
<details><summary>Hint 3</summary>
`dfs(r)`: for each c, skip if c, r-c or r+c is taken; otherwise add all three, place 'Q', recurse to r+1, remove. At r == n, save the board.
</details>

## Clarifying Questions
- Output format? (List of boards, each a list of row strings.)
- n = 2 or 3? (No solutions: return [].)
- Order of solutions? (Any.)

## Example Walkthrough
n = 4: queen at (0,0) forces (1,2) or (1,3); both dead-end by row 3. Queen at (0,1) → (1,3) → (2,0) → (3,2) works: ".Q..", "...Q", "Q...", "..Q.". By symmetry (0,2) gives the mirror; (0,3) fails.

## Approaches

### 1. Backtracking + Board Scan: O(n! · n) time, O(n²) space
Place row by row; before placing, scan up the column and both diagonals on the board. Correct, slower check.

### 2. Backtracking + Column/Diagonal Sets ⭐ Go-to: O(n!) time, O(n) extra space
Three boolean arrays: `cols[c]`, `diag[r-c+n-1]`, `anti[r+c]`. Each check and update is O(1).
**Why it's the go-to:** it's what interviewers expect; the r-c / r+c identity is the key insight to say out loud.

## Dry Run (Approach 2)
n = 4 (columns tried left to right)

| row | tried | blocked by | placed | queens so far (col per row) |
|-----|-------|------------|--------|-----------------------------|
| 0 | 0 | | 0 | [0] |
| 1 | 0, 1, 2 | col 0; r-c 0 | 2 | [0,2] |
| 2 | 0..3 | col; r+c 3; col; r-c -1 | none → back | [0] |
| 1 | 3 | | 3 | [0,3] |
| 2 | 0, 1 | col 0 | 1 | [0,3,1] |
| 3 | 0..3 | cols 0, 3, 1; r-c 1 | none; row 2's cols 2, 3 also blocked (r-c 0; col) → back to row 0 | [] |
| 0 | 1 | | 1 | [1] |
| 1 | 0..3 | r+c 1; col; r-c -1 | 3 | [1,3] |
| 2 | 0 | | 0 | [1,3,0] |
| 3 | 0..2 | col 0; col 1 | 2 | **[1,3,0,2] saved** |

The search continues and finds the mirror [2,0,3,1].

## Edge Case Check
- n = 1: [["Q"]]. ✅
- n = 2, 3: no placement survives → []. ✅
- n = 8: 92 boards. ✅

## ⚠️ Pitfalls
- **Negative index for r - c**: offset by n - 1 in arrays (Python sets don't care).
- **Mixing up the two diagonals**: "\" is constant r - c, "/" is constant r + c.
- **Forgetting to reset the board cell** to '.' when backtracking.
- **Python: board as list of strings** is immutable per row; keep a list of lists (or column indices) and build strings when saving.

## 🎯 What the Interviewer Wants
- One queen per row → recursion over rows.
- O(1) conflict checks with the diagonal identities.
- Clean backtracking: add / recurse / remove in all three sets.

## Follow-ups
- **Count only:** [LC 0052 N-Queens II](../0052-n-queens-ii/), a bitmask version is the fastest.
- **Constraint-satisfaction on a grid:** LC 0037 Sudoku Solver (not added yet)
- **Validate an existing placement:** like [LC 0036 Valid Sudoku](../../01-arrays-hashing/0036-valid-sudoku/), sets per row/col/diagonal.
