---
number: 62
title: Unique Paths
difficulty: Medium
topic: 2-D Dynamic Programming
pattern: Grid DP
link: https://leetcode.com/problems/unique-paths/
lists: [NeetCode 150]
followup_of: []
related: ["0063 Unique Paths II", "0064 Minimum Path Sum", "0070 Climbing Stairs"]
---

# 0062. Unique Paths

## ⚡ 30-Second Summary
**Pattern:** Grid DP, count paths
**Key insight:** You can only enter a cell from above or from the left, so `paths[r][c] = paths[r-1][c] + paths[r][c-1]`, and the first row and column are all 1. One row is enough: `row[c] += row[c-1]`.
**Go-to:** 1-D rolling row, O(m·n) time, O(n) space (mention the C(m+n-2, m-1) formula)

## Problem
A robot starts in the top-left cell of an m × n grid and can only move right or down. Count the distinct paths to the bottom-right cell. [LeetCode](https://leetcode.com/problems/unique-paths/)

**Examples:**
```
Input:  m = 3, n = 7
Output: 28
Why:    Every path is 2 downs and 6 rights in some order: C(8, 2) = 28.

Input:  m = 3, n = 2
Output: 3
Why:    The single right move can happen before, between, or after the two downs.
```

**Constraints:**
- 1 ≤ m, n ≤ 100.
- The answer is guaranteed ≤ 2·10⁹, so it fits in an int (intermediate DP values never exceed the answer).

## Hints
<details><summary>Hint 1</summary>
Look at the last move into the target cell. Where could the robot have been just before?
</details>
<details><summary>Hint 2</summary>
The number of paths to a cell is the sum of the paths to the cell above and the cell to the left. What are the values along the top row and left column?
</details>
<details><summary>Hint 3</summary>
Keep one row initialised to all 1s. For each of the remaining m-1 rows, sweep left to right doing row[c] += row[c-1]: row[c] still holds "above", row[c-1] already holds "left". Return row[n-1].
</details>

## Clarifying Questions
- Only right and down moves? (Yes, so paths never revisit a cell.)
- Any obstacles? (No. That's LC 63.)
- 1 × 1 grid? (One path: stay put.)
- Overflow? (Answer ≤ 2·10⁹ by guarantee; the formula needs care with intermediate products.)

## Example Walkthrough
`m = 3, n = 2`: top row [1,1]. Row 2: [1, 1+1=2]. Row 3: [1, 1+2=3]. Answer 3. Each value is "ways from above" plus "ways from the left".

## Approaches

### 1. Memoized Recursion: O(m·n) time, O(m·n) space
paths(r, c) = paths(r-1, c) + paths(r, c-1), with paths = 1 on the first row/column. Without the memo it's exponential.

### 2. 2-D Table: O(m·n) time, O(m·n) space
Fill dp row by row with the same recurrence. The easiest version to explain.

### 3. 1-D Rolling Row ⭐ Go-to: O(m·n) time, O(n) space
Each row only needs the row above, and the update reads "above" before overwriting it.
**Why it's the go-to:** same idea as the table in three lines, and it shows you know the space trick.

### 4. Combinatorics: O(min(m, n)) time, O(1) space
Choose which m-1 of the m+n-2 moves are downs: C(m+n-2, m-1). Compute it incrementally, `res = res * (n-1+i) / i`, which stays an integer at every step. Great to mention; interviewers usually still want the DP.

## Dry Run (Approach 3)
`m = 3, n = 7`

| after row | row |
|-----------|-----|
| 1 | [1, 1, 1, 1, 1, 1, 1] |
| 2 | [1, 2, 3, 4, 5, 6, 7] |
| 3 | [1, 3, 6, 10, 15, 21, **28**] |

Row 3, c = 2: old row[2] = 3 (above) + new row[1] = 3 (left) = 6.

## Edge Case Check
- `m = 1` or `n = 1`: no extra rows (or a single column), the answer stays 1. ✅
- `m = n = 1`: 1. ✅
- Large `m = 100, n = 7` stays within the guarantee (1,609,344,100). ✅

## ⚠️ Pitfalls
- **Sweeping right to left** in the 1-D version reads a stale "left" value.
- **Formula overflow in C++:** `res * (n-1+i)` can exceed 32 bits before the division; use `long long`.
- **Factorials directly** (`(m+n-2)! / ...`) overflow for small inputs; compute incrementally.
- **Python recursion** is fine here (depth ≤ m+n), but bottom-up is still cleaner.

## 🎯 What the Interviewer Wants
- The recurrence from "the last move" and correct base cases.
- Space optimisation from O(m·n) to O(n).
- Bonus: recognise the binomial coefficient.

## Follow-ups
- **Obstacles in the grid:** [LC 0063 Unique Paths II](../0063-unique-paths-ii/)
- **Minimise a cost instead of counting:** [LC 0064 Minimum Path Sum](../0064-minimum-path-sum/)
- **One dimension instead of two:** [LC 0070 Climbing Stairs](../../13-1d-dp/0070-climbing-stairs/)
- **Must visit every empty cell:** LC 0980 Unique Paths III (not added yet). Backtracking, not DP.
