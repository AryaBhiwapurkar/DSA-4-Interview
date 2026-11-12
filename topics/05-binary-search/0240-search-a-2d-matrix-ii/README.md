---
number: 240
title: Search a 2D Matrix II
difficulty: Medium
topic: Binary Search
pattern: Staircase search from the top-right corner
link: https://leetcode.com/problems/search-a-2d-matrix-ii/
lists: [Interview Extras]
followup_of: ["0074 Search a 2D Matrix"]
related: ["0074 Search a 2D Matrix", "0378 Kth Smallest Element in a Sorted Matrix", "1351 Count Negative Numbers in a Sorted Matrix"]
---

# 0240. Search a 2D Matrix II

## ⚡ 30-Second Summary
**Pattern:** Staircase walk from a corner where one move goes up in value and the other goes down
**Key insight:** At the top-right cell, everything to the left is smaller and everything below is bigger. If the cell is bigger than the target, the whole column is too big: move left. If it's smaller, the whole row is too small: move down. Each step drops a row or a column.
**Go-to:** Staircase from top-right, O(m + n) time, O(1) space

## Problem
Each row of an m × n matrix is sorted left to right, and each column is sorted top to bottom (rows don't continue into each other). Return whether a target value is present. [LeetCode](https://leetcode.com/problems/search-a-2d-matrix-ii/)

**Examples:**
```
Input:  matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
Output: true
Why:    5 sits at row 1, column 1.

Input:  same matrix, target = 20
Output: false
Why:    The nearby values are 19, 21 and 22; no cell holds 20.
```

**Constraints:**
- 1 ≤ m, n ≤ 300; rows and columns sorted ascending; values in [−10⁹, 10⁹].

## Hints
<details><summary>Hint 1</summary>
Unlike LC 74, you can't flatten the matrix into one sorted list. Which corner gives you a useful decision?
</details>
<details><summary>Hint 2</summary>
At the top-left both moves increase the value, so you can't decide. At the top-right, left decreases and down increases.
</details>
<details><summary>Hint 3</summary>
Start at (0, n − 1). Greater than the target → col−−. Smaller → row++. Equal → true. Falling off the grid → false.
</details>

## Clarifying Questions
- Is the matrix sorted only within rows and within columns? (Yes; the last value of a row can be bigger than the first of the next row.)
- Can it contain duplicates? (Yes; it doesn't matter for "exists?".)
- Can the matrix be empty? (No, m, n ≥ 1.)

## Example Walkthrough
target = 5. Start at 15 (top-right). 15 > 5 → left to 11 → left to 7 → left to 4. 4 < 5 → down to 5. Found.

## Approaches

### 1. Scan Everything: O(m · n) time, O(1) space
Check every cell. Ignores the ordering.

### 2. Binary Search Each Row: O(m log n) time, O(1) space
Rows are sorted, so binary search each one. Better, and fine when m is small.

### 3. Staircase from Top-right ⭐ Go-to: O(m + n) time, O(1) space
Each comparison eliminates one row or one column.
**Why it's the go-to:** linear in the perimeter, five lines, and the corner argument is easy to explain.

## Dry Run (Approach 3)
target = 20.

| row | col | value | vs 20 | move |
|-----|-----|-------|-------|------|
| 0 | 4 | 15 | < | row++ |
| 1 | 4 | 19 | < | row++ |
| 2 | 4 | 22 | > | col−− |
| 2 | 3 | 16 | < | row++ |
| 3 | 3 | 17 | < | row++ |
| 4 | 3 | 26 | > | col−− |
| 4 | 2 | 23 | > | col−− |
| 4 | 1 | 21 | > | col−− |
| 4 | 0 | 18 | < | row++ → 5, off the grid → **false** |

## Edge Case Check
- 1 × 1 matrix → one comparison. ✅
- Target smaller than matrix[0][0] → walks left along row 0 and exits. ✅
- Target larger than the bottom-right → walks down the last column and exits. ✅

## ⚠️ Pitfalls
- **Starting at the top-left (or bottom-right):** both neighbours move the same way, so no decision is possible.
- **Treating it like LC 74** (flattened binary search): wrong, since rows don't continue into each other.
- **Loop bounds:** check `row < m && col >= 0` before reading the cell.

## 🎯 What the Interviewer Wants
- See why the top-right (or bottom-left) corner works.
- O(m + n) with a clean argument that each step drops a row or a column.
- Contrast with LC 74, where a single binary search works.

## Follow-ups
- **Rows chain into each other:** [LC 0074 Search a 2D Matrix](../0074-search-a-2d-matrix/)
- **k-th smallest in this kind of matrix:** binary search on value plus a staircase count: LC 0378 Kth Smallest Element in a Sorted Matrix (not added yet)
- **Count cells below a value with the same walk:** LC 1351 Count Negative Numbers in a Sorted Matrix (not added yet)
