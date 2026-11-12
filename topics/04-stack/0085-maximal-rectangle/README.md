---
number: 85
title: Maximal Rectangle
difficulty: Hard
topic: Stack
pattern: Row-by-row histogram + largest rectangle in histogram
link: https://leetcode.com/problems/maximal-rectangle/
lists: [Interview Extras]
followup_of: ["0084 Largest Rectangle in Histogram"]
related: ["0084 Largest Rectangle in Histogram", "0221 Maximal Square", "1277 Count Square Submatrices with All Ones"]
---

# 0085. Maximal Rectangle

## ⚡ 30-Second Summary
**Pattern:** Turn each row into a histogram, then run LC 84 on it
**Key insight:** For each row, `h[c]` is the number of consecutive '1's ending at that row in column c. It resets to 0 on a '0'. Any all-ones rectangle has a bottom row, and in that row's histogram it fits under the bars. So the answer is the best "largest rectangle in histogram" over all rows. Each row costs O(cols) with a monotonic stack.
**Go-to:** Histogram per row + monotonic stack, O(rows · cols) time, O(cols) space

## Problem
Given a binary matrix of '0' and '1' characters, return the area of the largest rectangle that contains only '1's. [LeetCode](https://leetcode.com/problems/maximal-rectangle/)

**Examples:**
```
Input:  matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 6
Why:    Rows 1-2, columns 2-4 are all ones: 2 × 3.

Input:  matrix = [["0"]]
Output: 0
Why:    No ones.

Input:  matrix = [["1"]]
Output: 1
Why:    A single cell.
```

**Constraints:**
- 1 ≤ rows, cols ≤ 200; cells are the characters '0' and '1'.

## Hints
<details><summary>Hint 1</summary>
Fix the bottom row of the rectangle. What does each column look like above it?
</details>
<details><summary>Hint 2</summary>
Heights of consecutive ones above the bottom row form a histogram. Which problem finds the largest rectangle in a histogram?
</details>
<details><summary>Hint 3</summary>
h[c] = h[c] + 1 if cell is '1' else 0, row by row. After each row, run the LC 84 monotonic stack on h and keep the best area.
</details>

## Clarifying Questions
- Cells are characters, not ints? (Yes, '0' / '1'.)
- Rectangles must be axis-aligned and solid? (Yes.)
- Squares only? (No, any rectangle; squares are 0221.)

## Example Walkthrough
Example 1 histograms by row: [1,0,1,0,0] → [2,0,2,1,1] → [3,1,3,2,2] → [4,0,0,3,0]. Row 2's histogram [3,1,3,2,2] contains the rectangle of height 2 across columns 2..4 → area 6, and nothing beats it.

## Approaches

### 1. Every Top-left and Bottom-right: O(r²·c²) time
Check every rectangle (with 2-D prefix sums for the all-ones test). Far too slow beyond tiny grids.

### 2. Row Widths, Extend Upwards: O(r² · c) time, O(r · c) space
`w[r][c]` = run of ones ending at (r, c) going left. For each cell, walk upwards, keeping the minimum width, and maximise width × height. Simpler than the stack, but cubic in the worst case.

### 3. Histogram + Monotonic Stack ⭐ Go-to: O(r · c) time, O(c) space
**Why it's the go-to:** reuses LC 84 directly; the reduction is the interview insight.

## Dry Run (Approach 3)
Row 2 histogram h = [3,1,3,2,2], plus a sentinel 0 at the end.

| i | h[i] | pops (height × width) | stack (indices) | best |
|---|------|-----------------------|-----------------|------|
| 0 | 3 | – | [0] | 0 |
| 1 | 1 | 3 × 1 = 3 | [1] | 3 |
| 2 | 3 | – | [1,2] | 3 |
| 3 | 2 | 3 × 1 = 3 | [1,3] | 3 |
| 4 | 2 | – (equal kept) | [1,3,4] | 3 |
| 5 | 0 | 2 × 1 = 2, 2 × 3 = **6**, 1 × 5 = 5 | [5] | **6** |

## Edge Case Check
- All zeros → 0. ✅
- All ones r × c → r · c. ✅
- A single row → LC 84 on that row. ✅

## ⚠️ Pitfalls
- **Not resetting the height to 0** on a '0' cell.
- **Comparing chars with ints:** `cell == 1` is always false for '1'.
- **Forgetting the end-of-row flush:** add a sentinel 0 or empty the stack after each row.

## 🎯 What the Interviewer Wants
- The reduction to LC 84.
- A correct monotonic stack with widths.
- O(r · c) overall.

## Follow-ups
- **The histogram subproblem:** [LC 0084 Largest Rectangle in Histogram](../0084-largest-rectangle-in-histogram/)
- **Largest square of ones:** [LC 0221 Maximal Square](../../14-2d-dp/0221-maximal-square/)
- **Count all square submatrices:** LC 1277 Count Square Submatrices with All Ones (not added yet)
