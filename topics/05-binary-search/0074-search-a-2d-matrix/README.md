---
number: 74
title: Search a 2D Matrix
difficulty: Medium
topic: Binary Search
pattern: Treat as flat sorted array
link: https://leetcode.com/problems/search-a-2d-matrix/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: ["0704 Binary Search"]
related: ["0240 Search a 2D Matrix II", "0704 Binary Search", "0378 Kth Smallest Element in a Sorted Matrix"]
---

# 0074. Search a 2D Matrix

## ⚡ 30-Second Summary
**Pattern:** Treat the matrix as one flat sorted array
**Key insight:** Rows are sorted and each row starts after the previous one ends, so reading row by row gives one sorted list of m·n numbers. Flat index k maps to `matrix[k / n][k % n]`.
**Go-to:** One binary search over [0, m·n), O(log(m·n)) time, O(1) space

## Problem
Each row of an m × n matrix is sorted, and each row's first value is greater than the previous row's last value. Return whether the target is in the matrix, in O(log(m·n)).

**Examples:**
```
Input:  matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
Output: true
Why:    3 is in the first row.

Input:  matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
Output: false
Why:    13 would sit between 11 and 16 but isn't there.
```

**Constraints:**
- 1 ≤ m, n ≤ 100; values and target in ±10⁴.
- The rows chain into one sorted sequence (stronger than LC 0240).

## Hints
<details><summary>Hint 1</summary>
If you concatenated the rows, what would the resulting list look like?
</details>
<details><summary>Hint 2</summary>
You don't have to build that list. Given a flat index k, which row and column is it?
</details>
<details><summary>Hint 3</summary>
Binary search k in [0, m·n - 1] and read matrix[k / n][k % n] (n = number of columns).
</details>

## Clarifying Questions
- Does each row start above the previous row's end? (Yes, so it's fully sorted.)
- Can the matrix be empty? (No, m, n ≥ 1.)
- Duplicates? (Doesn't matter for "exists".)

## Example Walkthrough
`target = 13`, m = 3, n = 4, flat range [0, 11].
- mid 5 → (1,1) = 11 < 13, lo = 6.
- mid 8 → (2,0) = 23 > 13, hi = 7.
- mid 6 → (1,2) = 16 > 13, hi = 5. lo > hi → false.

## Approaches

### 1. Scan Everything: O(m·n) time, O(1) space
Ignores all the ordering.

### 2. Staircase From the Top-Right: O(m + n) time, O(1) space
At (r, c): too big → move left; too small → move down. Works even for the weaker LC 0240 ordering; worth mentioning.

### 3. Flat Binary Search ⭐ Go-to: O(log(m·n)) time, O(1) space
One search with index mapping. (Two searches, first the row and then the column, have the same complexity but more code.)
**Why it's the go-to:** meets the required complexity with the plain 0704 template plus one line of mapping.

## Dry Run (Approach 3)
`target = 3`, n = 4

| lo | hi | mid | (r, c) | value | action |
|----|----|-----|--------|-------|--------|
| 0 | 11 | 5 | (1, 1) | 11 | 11 > 3, hi = 4 |
| 0 | 4 | 2 | (0, 2) | 5 | 5 > 3, hi = 1 |
| 0 | 1 | 0 | (0, 0) | 1 | 1 < 3, lo = 1 |
| 1 | 1 | 1 | (0, 1) | 3 | found → **true** |

## Edge Case Check
- 1 × 1 matrix: one comparison. ✅
- Single row or single column: mapping still works (n = 1 makes k / 1 = k). ✅
- Target below the first or above the last element: false. ✅

## ⚠️ Pitfalls
- **Dividing by the wrong dimension**: row = k / **cols**, col = k % **cols**.
- **hi = m·n instead of m·n - 1** with an inclusive loop reads out of bounds.
- **Staircase from the top-left**: both moves increase the value, so it doesn't work. Start top-right or bottom-left.

## 🎯 What the Interviewer Wants
- See the flattening and do the index arithmetic correctly.
- Contrast with 0240, where only the staircase works.
- O(log(m·n)) = O(log m + log n), the same as the two-search version.

## Follow-ups
- **Rows and columns sorted independently:** staircase O(m + n): LC 0240 Search a 2D Matrix II (not added yet)
- **Kth smallest in a row/col-sorted matrix:** heap or binary search on value: LC 0378 Kth Smallest Element in a Sorted Matrix (not added yet)
- **1-D version:** [LC 0704 Binary Search](../0704-binary-search/)
