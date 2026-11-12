---
number: 304
title: Range Sum Query 2D - Immutable
difficulty: Medium
topic: Arrays & Hashing
pattern: 2-D prefix sums (inclusion-exclusion)
link: https://leetcode.com/problems/range-sum-query-2d-immutable/
lists: [Interview Extras]
followup_of: ["0303 Range Sum Query - Immutable"]
related: ["0221 Maximal Square", "1277 Count Square Submatrices with All Ones", "0308 Range Sum Query 2D - Mutable"]
---

# 0304. Range Sum Query 2D - Immutable

## ⚡ 30-Second Summary
**Pattern:** 2-D prefix sums with inclusion-exclusion
**Key insight:** Let `P[r][c]` be the sum of the top-left r × c block, with an extra zero row and column. Build it as `P[r+1][c+1] = m[r][c] + P[r][c+1] + P[r+1][c] − P[r][c]`. Answer a rectangle with `P[r2+1][c2+1] − P[r1][c2+1] − P[r2+1][c1] + P[r1][c1]`. The top-left corner block gets subtracted twice, so add it back once.
**Go-to:** Padded 2-D prefix table, O(m·n) build, O(1) per query, O(m·n) space

## Problem
Build a class over a fixed matrix that answers many "sum of the rectangle from (row1, col1) to (row2, col2), inclusive" queries in O(1) each. [LeetCode](https://leetcode.com/problems/range-sum-query-2d-immutable/)

**Examples:**
```
Input:  ["NumMatrix","sumRegion","sumRegion","sumRegion"]
        [[[[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]]],
         [2,1,4,3],[1,1,2,2],[1,2,2,4]]
Output: [null,8,11,12]
Why:    Rows 2-4 × cols 1-3 sum to 8; rows 1-2 × cols 1-2 sum to 11; rows 1-2 × cols 2-4 sum to 12.
```

**Constraints:**
- 1 ≤ m, n ≤ 200; up to 10⁴ queries, so each query must be O(1).
- −10⁴ ≤ values ≤ 10⁴: the full sum is at most 4·10⁸, which fits in an int.

## Hints
<details><summary>Hint 1</summary>
In 1-D you used prefix sums. What's the 2-D version of "sum of everything before i"?
</details>
<details><summary>Hint 2</summary>
Draw the rectangle inside the top-left block that ends at its bottom-right corner. Which blocks do you remove, and which part did you remove twice?
</details>
<details><summary>Hint 3</summary>
P is (m+1) × (n+1). P[r+1][c+1] = m[r][c] + P[r][c+1] + P[r+1][c] − P[r][c]. Query = P[r2+1][c2+1] − P[r1][c2+1] − P[r2+1][c1] + P[r1][c1].
</details>

## Clarifying Questions
- Is the matrix ever updated? (No.)
- Are coordinates inclusive and valid? (Yes, row1 ≤ row2, col1 ≤ col2.)
- How many queries? (Up to 10⁴, so precomputing pays off.)

## Example Walkthrough
For the 2×2 matrix `[[1,2],[3,4]]`: P = `[[0,0,0],[0,1,3],[0,4,10]]`. The query (1,1)-(1,1) is P[2][2] − P[1][2] − P[2][1] + P[1][1] = 10 − 3 − 4 + 1 = 4. ✓

## Approaches

### 1. Loop over the Rectangle: O(1) build, O(m·n) per query
Correct but slow with many queries.

### 2. Row Prefix Sums: O(m·n) build, O(m) per query
A 1-D prefix per row; each query sums one O(1) slice per row. A good stepping stone.

### 3. 2-D Prefix Sums ⭐ Go-to: O(m·n) build, O(1) per query
**Why it's the go-to:** constant-time queries, and the four-term formula is standard enough that interviewers expect it.

## Dry Run (Approach 3)
Query (2,1)-(4,3) on the example. The padded P values used:

| term | meaning | value |
|------|---------|-------|
| P[5][4] | rows 0-4, cols 0-3 | 38 |
| − P[2][4] | rows 0-1, cols 0-3 | −24 |
| − P[5][1] | rows 0-4, col 0 | −14 |
| + P[2][1] | rows 0-1, col 0 (removed twice) | +8 |
| | | **8** |

## Edge Case Check
- Single cell query → that cell's value. ✅
- Whole matrix → P[m][n]. ✅
- Query touching row 0 or column 0 → the padding row/column is 0. ✅

## ⚠️ Pitfalls
- **No padding** means `r1 − 1 = −1` checks everywhere. Pad with a zero row and column.
- **Sign error in inclusion-exclusion:** the overlap corner is **added** back, not subtracted.
- **Index shift:** prefix indices are +1 versus matrix indices (`P[r2+1][c2+1]`).
- **Python `[[0] * (n+1)] * (m+1)`** aliases rows; use a comprehension.

## 🎯 What the Interviewer Wants
- The 2-D prefix definition and inclusion-exclusion, explained with a picture.
- Clean padded indexing.
- Know that updates need a 2-D Fenwick tree (LC 308).

## Follow-ups
- **1-D version:** [LC 0303 Range Sum Query - Immutable](../0303-range-sum-query-immutable/)
- **With updates:** LC 0308 Range Sum Query 2D - Mutable (not added yet). 2-D Fenwick tree.
- **Prefix-style DP on grids:** [LC 0221 Maximal Square](../../14-2d-dp/0221-maximal-square/)
