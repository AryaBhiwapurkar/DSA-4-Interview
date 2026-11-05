---
number: 64
title: Minimum Path Sum
difficulty: Medium
topic: 2-D Dynamic Programming
pattern: Grid DP
link: https://leetcode.com/problems/minimum-path-sum/
lists: [LC Top Interview 150]
followup_of: []
related: ["0062 Unique Paths", "0120 Triangle", "0174 Dungeon Game"]
---

# 0064. Minimum Path Sum

## ⚡ 30-Second Summary
**Pattern:** Grid DP, minimise the path cost
**Key insight:** The cheapest way into a cell comes from the cheaper of its top and left neighbours: `dp[r][c] = grid[r][c] + min(dp[r-1][c], dp[r][c-1])`. Values are non-negative, but you still can't go greedy cell by cell.
**Go-to:** 1-D rolling row, O(m·n) time, O(n) space

## Problem
Each cell of an m × n grid holds a non-negative cost. Moving only right or down from the top-left to the bottom-right, find the smallest possible sum of the cells on the path. [LeetCode](https://leetcode.com/problems/minimum-path-sum/)

**Examples:**
```
Input:  grid = [[1,3,1],[1,5,1],[4,2,1]]
Output: 7
Why:    Go right, right, down, down: 1+3+1+1+1. Every path through the 5 or the 4 costs more.

Input:  grid = [[1,2,3],[4,5,6]]
Output: 12
Why:    Along the top row then down: 1+2+3+6. Dropping down earlier pays 4 or 5.
```

**Constraints:**
- 1 ≤ m, n ≤ 200, 0 ≤ grid[i][j] ≤ 200, so sums stay ≤ 8·10⁴.

## Hints
<details><summary>Hint 1</summary>
Greedy (always step to the cheaper neighbour) fails. Think about the last step into the bottom-right cell instead.
</details>
<details><summary>Hint 2</summary>
If you knew the cheapest cost to reach the cell above and the cell to the left, what is the cheapest cost to reach this one?
</details>
<details><summary>Hint 3</summary>
dp = cell + min(top, left). First row only has a left neighbour, first column only a top. Keep one row: row[c] = grid[r][c] + min(row[c], row[c-1]) sweeping left to right.
</details>

## Clarifying Questions
- Only right/down? (Yes.)
- Negative costs? (No, all ≥ 0.)
- Return the sum or the path? (Sum. For the path, keep parent pointers or backtrack through dp.)
- Can I overwrite the grid? (Ask; it gives O(1) extra space.)

## Example Walkthrough
`[[1,2,3],[4,5,6]]`: top row prefix sums [1,3,6]. Row 2: col 0 = 1+4 = 5; col 1 = 5 + min(3, 5) = 8; col 2 = 6 + min(6, 8) = 12.

## Approaches

### 1. Memoized Recursion: O(m·n) time, O(m·n) space
cost(r, c) = grid[r][c] + min(cost(r-1, c), cost(r, c-1)), with out-of-bounds = infinity.

### 2. 2-D Table (or in place): O(m·n) time, O(m·n) space
Fill a dp grid row by row, or overwrite the input for O(1) extra space.

### 3. 1-D Rolling Row ⭐ Go-to: O(m·n) time, O(n) space
row[c] holds "best cost to the cell above" until it's overwritten with the new value.
**Why it's the go-to:** clean, O(n) space, and it doesn't mutate the input.

## Dry Run (Approach 3)
`[[1,3,1],[1,5,1],[4,2,1]]`

| r | row after the sweep | how |
|---|---------------------|-----|
| 0 | [1, 4, 5] | prefix sums |
| 1 | [2, 7, 6] | 1+2; 5+min(4,2)=7; 1+min(5,7)=6 |
| 2 | [6, 8, **7**] | 4+2; 2+min(7,6)=8; 1+min(6,8)=7 |

## Edge Case Check
- Single cell `[[5]]` → 5. ✅
- Single row `[[1,2,3]]` → 6 (prefix sum). ✅
- All zeros → 0. ✅

## ⚠️ Pitfalls
- **Greedy neighbour choice** misses cheaper detours.
- **Mishandling the first row/column:** only one neighbour exists there; using a sentinel like INT_MAX in C++ then adding a cell overflows.
- **Python `[[0]*n]*m`** aliases rows if you build a 2-D table.
- **In-place edits** destroy the input; mention it before doing it.

## 🎯 What the Interviewer Wants
- The recurrence from the last move, and a correct first row/column.
- Space down to O(n) (or O(1) in place, with the trade-off stated).
- Optional: reconstruct the path from the table.

## Follow-ups
- **Count the paths instead:** [LC 0062 Unique Paths](../0062-unique-paths/)
- **Triangle-shaped grid:** [LC 0120 Triangle](../0120-triangle/)
- **Minimum starting health, solved right-to-left:** LC 0174 Dungeon Game (not added yet)
- **Any direction allowed:** DP no longer works (cycles); use Dijkstra on the grid.
