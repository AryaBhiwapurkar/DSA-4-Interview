---
number: 73
title: Set Matrix Zeroes
difficulty: Medium
topic: Math & Geometry
pattern: First row/col as markers
link: https://leetcode.com/problems/set-matrix-zeroes/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0289 Game of Life", "0048 Rotate Image"]
---

# 0073. Set Matrix Zeroes

## ⚡ 30-Second Summary
**Pattern:** Store the "this row/column must be zeroed" flags inside the matrix itself
**Key insight:** Zeroing as soon as you see a 0 spreads fake zeros. Record first, write second. Row 0 and column 0 can hold the flags for every other row and column. Cell (0,0) can't flag both row 0 and column 0, so keep one extra boolean for column 0. Then zero the inner cells, and finally row 0 and column 0.
**Go-to:** First row/col markers + one flag, O(m·n) time, O(1) extra space

## Problem
Whenever a cell of an m × n matrix is 0, set its entire row and column to 0. Do it in place. [LeetCode](https://leetcode.com/problems/set-matrix-zeroes/)

**Examples:**
```
Input:  matrix = [[1,1,1],[1,0,1],[1,1,1]]
Output: [[1,0,1],[0,0,0],[1,0,1]]
Why:    The single 0 in the centre wipes the middle row and middle column.

Input:  matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
Why:    Zeros at (0,0) and (0,3) wipe row 0 and columns 0 and 3.
```

**Constraints:**
- 1 ≤ m, n ≤ 200; values are any 32-bit int, so no spare "sentinel" value is safe.
- Follow-up: O(m·n) extra is easy, O(m + n) is better, O(1) is the goal.

## Hints
<details><summary>Hint 1</summary>
Why does zeroing a row the moment you find a 0 give the wrong answer?
</details>
<details><summary>Hint 2</summary>
You only need to know which rows and which columns contain a 0. Is there spare space in the matrix to store that?
</details>
<details><summary>Hint 3</summary>
Use matrix[i][0] and matrix[0][j] as flags, plus a boolean col0 for column 0. Pass 1: for each 0 at (i, j), set matrix[i][0] = matrix[0][j] = 0 (or col0 = true when j = 0). Pass 2: zero inner cells whose row or column flag is 0. Last: zero row 0 if matrix[0][0] == 0, and column 0 if col0.
</details>

## Clarifying Questions
- In place? (Yes.)
- Can values be anything, including negatives? (Yes, so no sentinel like −1.)
- Does a zero created by the process trigger more zeroing? (No, only original zeros count.)

## Example Walkthrough
`[[1,0],[1,1]]`: the 0 at (0,1) sets flags matrix[0][0] = 0 (row 0) and matrix[0][1] = 0 (col 1). Inner cell (1,1): column flag matrix[0][1] = 0 → zero it. matrix[0][0] = 0 → zero row 0. col0 is false → column 0 is untouched. Result `[[0,0],[1,0]]`.

## Approaches

### 1. Copy the Matrix: O(m·n) time, O(m·n) space
Scan the original copy, write zeros into the real one. Correct, wasteful.

### 2. Row and Column Sets: O(m·n) time, O(m + n) space
Collect zero rows and zero columns in one pass, then zero them in a second pass. The natural first answer.

### 3. First Row/Col Markers ⭐ Go-to: O(m·n) time, O(1) space
**Why it's the go-to:** it's what the follow-up asks for, and it's Approach 2 with the sets moved into row 0 and column 0.

## Dry Run (Approach 3)
`[[0,1,2,0],[3,4,5,2],[1,3,1,5]]`

| step | matrix | col0 |
|------|--------|------|
| mark (0,0): j = 0 → col0; also row flag m[0][0] = 0 | unchanged | true |
| mark (0,3): m[0][0] = 0, m[0][3] = 0 | unchanged | true |
| inner (i ≥ 1, j ≥ 1): zero if m[i][0] or m[0][j] is 0 | [[0,1,2,0],[3,4,5,0],[1,3,1,0]] | |
| m[0][0] == 0 → zero row 0 | [[0,0,0,0],[3,4,5,0],[1,3,1,0]] | |
| col0 → zero column 0 | **[[0,0,0,0],[0,4,5,0],[0,3,1,0]]** | |

## Edge Case Check
- No zeros → unchanged. ✅
- 1×1 `[[0]]` → `[[0]]`. ✅
- Zero only in column 0 (`[[1],[0]]`) → col0 zeroes the column; m[0][0] stays 1, so row 0 isn't wiped. Result `[[0],[0]]`. ✅
- All zeros → all zeros. ✅

## ⚠️ Pitfalls
- **Zeroing during the scan** cascades and wipes everything.
- **Zeroing row 0 / column 0 before the inner cells** destroys the flags you still need.
- **Using m[0][0] for both** row 0 and column 0 conflates them. Keep the separate `col0` flag.
- **Sentinel tricks (mark with −1 or None)** break when those values appear in the input.

## 🎯 What the Interviewer Wants
- Spot the cascade bug, then give O(m + n) with sets.
- Upgrade to O(1) using the first row and column.
- Get the order of the final passes right.

## Follow-ups
- **Another in-place state-encoding problem:** [LC 0289 Game of Life](../0289-game-of-life/)
- **Other in-place matrix transforms:** [LC 0048 Rotate Image](../0048-rotate-image/)
