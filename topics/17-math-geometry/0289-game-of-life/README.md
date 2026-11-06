---
number: 289
title: Game of Life
difficulty: Medium
topic: Math & Geometry
pattern: In-place state encoding
link: https://leetcode.com/problems/game-of-life/
lists: [LC Top Interview 150]
followup_of: []
related: ["0073 Set Matrix Zeroes", "0200 Number of Islands"]
---

# 0289. Game of Life

## ⚡ 30-Second Summary
**Pattern:** Two bits per cell: bit 0 = current state, bit 1 = next state
**Key insight:** Every cell must update from the *old* board at the same instant. Overwriting cells as you go corrupts the counts for neighbours you haven't processed. A copy fixes that, but so does stashing the next state in bit 1. Neighbour counts read only `cell & 1`, and a final pass does `cell >>= 1`.
**Go-to:** Bit encoding, O(m·n) time, O(1) extra space

## Problem
Cells of an m × n grid are live (1) or dead (0), and each has up to 8 neighbours. Advance the board one generation in place:
- A live cell with 2 or 3 live neighbours survives; otherwise it dies.
- A dead cell with exactly 3 live neighbours becomes live.

[LeetCode](https://leetcode.com/problems/game-of-life/)

**Examples:**
```
Input:  board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
Output: [[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
Why:    The glider shape shifts down one step: some cells starve, some get born.

Input:  board = [[1,1],[1,0]]
Output: [[1,1],[1,1]]
Why:    Each live cell has 2 live neighbours and survives; the dead corner has 3 and is born.
```

**Constraints:**
- 1 ≤ m, n ≤ 25; cells are 0 or 1, so the upper bits are free to use.
- Follow-ups: do it in place; how would you handle an infinite board?

## Hints
<details><summary>Hint 1</summary>
What goes wrong if you update cell (0,0) and then count neighbours for cell (0,1)?
</details>
<details><summary>Hint 2</summary>
Cells only hold 0 or 1. Could one int hold both the old and the new state?
</details>
<details><summary>Hint 3</summary>
For each cell, count live neighbours with (board[nr][nc] &amp; 1). If the cell should be live next, set bit 1 (board[r][c] |= 2). Afterwards shift every cell right by one.
</details>

## Clarifying Questions
- Do cells outside the grid count as dead? (Yes.)
- Are diagonals neighbours? (Yes, all 8.)
- In place, or return a new board? (In place.)

## Example Walkthrough
`[[1,1],[1,0]]`. Cell (1,1) is dead with 3 live neighbours, so it becomes born: 0 | 2 = 2. Every live cell has 2 neighbours and survives: 1 | 2 = 3. The board is now `[[3,3],[3,2]]`. Shifting right by one gives `[[1,1],[1,1]]`.

## Approaches

### 1. Copy the Board: O(m·n) time, O(m·n) space
Count neighbours on the copy and write to the original. Clear, but extra memory.

### 2. Bit Encoding ⭐ Go-to: O(m·n) time, O(1) extra
**Why it's the go-to:** same code as the copy version, with `& 1` reads, `|= 2` writes and one shift pass. It's the in-place answer interviewers ask for.

(The common variant uses sentinel values, e.g. −1 = "was live, now dead" and 2 = "was dead, now live". It's equivalent but harder to keep straight.)

## Dry Run (Approach 2)
First example, interesting cells only. "n" is the live-neighbour count on the old board.

| cell | old | n | next | stored |
|------|-----|---|------|--------|
| (0,1) | 1 | 1 | dies | 1 |
| (1,0) | 0 | 3 | born | 2 |
| (1,2) | 1 | 3 | lives | 3 |
| (2,0) | 1 | 1 | dies | 1 |
| (2,1) | 1 | 3 | lives | 3 |
| (2,2) | 1 | 2 | lives | 3 |
| (3,1) | 0 | 3 | born | 2 |

After `>>= 1`: **[[0,0,0],[1,0,1],[0,1,1],[0,1,0]]**.

## Edge Case Check
- 1×1 board → it has no neighbours, so it dies or stays dead. ✅
- All dead → stays all dead. ✅
- Edges/corners → bounds checks skip off-grid neighbours. ✅

## ⚠️ Pitfalls
- **Updating in place without encoding** reads already-updated neighbours.
- **Counting `board[nr][nc]` instead of `& 1`** treats the stored value 2 or 3 as "live" wrongly.
- **Counting the cell itself** as its own neighbour: skip (dr, dc) = (0, 0).
- **Python `[[0] * n] * m`** for the copy shares one row. Use `[row[:] for row in board]`.

## 🎯 What the Interviewer Wants
- See the simultaneous-update problem.
- The O(1) encoding trick and a clean neighbour loop.
- Infinite-board follow-up: store only live cells in a set and count neighbours from them.

## Follow-ups
- **Another flag-in-the-matrix trick:** [LC 0073 Set Matrix Zeroes](../0073-set-matrix-zeroes/)
- **8-direction grid traversal:** [LC 0200 Number of Islands](../../11-graphs/0200-number-of-islands/)
- **Infinite or sparse board:** keep a hash set of live coordinates; count neighbours with a Counter over each live cell's 8 neighbours.
