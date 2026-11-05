---
number: 221
title: Maximal Square
difficulty: Medium
topic: 2-D Dynamic Programming
pattern: Grid DP, min of 3 neighbors
link: https://leetcode.com/problems/maximal-square/
lists: [LC Top Interview 150]
followup_of: []
related: ["0085 Maximal Rectangle", "1277 Count Square Submatrices with All Ones"]
---

# 0221. Maximal Square

## ⚡ 30-Second Summary
**Pattern:** Grid DP where each cell is the bottom-right corner of a square
**Key insight:** `dp[r][c]` = side of the largest all-'1' square ending at (r, c). It's limited by the squares ending above, left and diagonally up-left: `dp = 1 + min(top, left, diag)` for a '1', else 0. Return side².
**Go-to:** 2-D DP with a padded table, O(m·n) time, O(m·n) space (1-D row as the follow-up)

## Problem
Given a grid of '0'/'1' characters, return the area of the largest square that contains only '1's. [LeetCode](https://leetcode.com/problems/maximal-square/)

**Examples:**
```
Input:  matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 4
Why:    Rows 1-2, columns 2-3 (also 3-4) form a 2×2 block of 1s; nothing 3×3 exists.

Input:  matrix = [["0","1"],["1","0"]]
Output: 1
Why:    The 1s only touch diagonally, so the best is a single cell.

Input:  matrix = [["0"]]
Output: 0
Why:    No 1 anywhere.
```

**Constraints:**
- 1 ≤ m, n ≤ 300, so O(m·n) is easy and O((m·n)²) brute force is too slow.
- Cells are characters '0'/'1', not ints.
- Return the **area**, not the side.

## Hints
<details><summary>Hint 1</summary>
Fix a cell as the bottom-right corner of a square. What would you like to know about the cells next to it?
</details>
<details><summary>Hint 2</summary>
A k×k square ending at (r, c) needs (k-1)×(k-1) squares ending at the top, left and top-left neighbours.
</details>
<details><summary>Hint 3</summary>
dp[r][c] = 0 if the cell is '0', else 1 + min(dp[r-1][c], dp[r][c-1], dp[r-1][c-1]). Pad the table with an extra row and column of zeros so edges need no checks. Track the max side, return side * side.
</details>

## Clarifying Questions
- Square only, or any rectangle? (Square. Rectangles are LC 85.)
- Area or side? (Area.)
- Chars or ints? (Chars '0'/'1'.)
- Empty matrix? (m, n ≥ 1.)

## Example Walkthrough
A 3×3 block of 1s: the first row and column all get 1. (1,1): 1 + min(1,1,1) = 2. (2,2): 1 + min(dp(1,2)=2, dp(2,1)=2, dp(1,1)=2) = 3. Area 9. If any of the three neighbours were smaller, the square would be capped by it.

## Approaches

### 1. Brute Force Expansion: O((m·n)·min(m,n)²) time, O(1) space
From each '1', grow the square one layer at a time, checking the new row and column, until a '0' appears.

### 2. 2-D DP ⭐ Go-to: O(m·n) time, O(m·n) space
The min-of-three recurrence on a (m+1)×(n+1) table.
**Why it's the go-to:** one-line recurrence, and the padding removes edge cases. Easy to justify with a picture.

### 3. 1-D Rolling Row: O(m·n) time, O(n) space
Keep one row plus a `prev` variable holding the old diagonal value before it's overwritten.

## Dry Run (Approach 2)
Example 1 (unpadded view of dp):

| r \ c | 0 | 1 | 2 | 3 | 4 |
|-------|---|---|---|---|---|
| 0 | 1 | 0 | 1 | 0 | 0 |
| 1 | 1 | 0 | 1 | 1 | 1 |
| 2 | 1 | 1 | 1 | **2** | **2** |
| 3 | 1 | 0 | 0 | 1 | 0 |

(2,3): 1 + min(top 1, left 1, diag 1) = 2. (2,4): 1 + min(1, 2, 1) = 2. Max side 2 → area **4**.

## Edge Case Check
- All zeros → 0. ✅
- Single '1' → 1. ✅
- Diagonal-only 1s (example 2) → each dp is 1 since a neighbour is 0. ✅

## ⚠️ Pitfalls
- **Returning the side** instead of the area.
- **Comparing with 1 instead of '1'** in C++ (`matrix[r][c] == 1` is always false for chars).
- **1-D version:** forgetting to save the diagonal before overwriting `row[c]`.
- **Not padding:** index -1 checks on the first row/column.

## 🎯 What the Interviewer Wants
- The "bottom-right corner" state and why the min of three is correct.
- O(m·n) with padding, then O(n) space if asked.
- Contrast with the rectangle version (histogram + stack).

## Follow-ups
- **Largest rectangle of 1s:** LC 0085 Maximal Rectangle (not added yet). Histogram per row + monotonic stack.
- **Count all-1 squares:** LC 1277 Count Square Submatrices with All Ones (not added yet). Sum of all dp values.
- **Histogram building block:** [LC 0084 Largest Rectangle in Histogram](../../04-stack/0084-largest-rectangle-in-histogram/)
