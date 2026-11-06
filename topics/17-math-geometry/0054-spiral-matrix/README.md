---
number: 54
title: Spiral Matrix
difficulty: Medium
topic: Math & Geometry
pattern: Shrinking boundaries
link: https://leetcode.com/problems/spiral-matrix/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0059 Spiral Matrix II", "0048 Rotate Image", "0885 Spiral Matrix III"]
---

# 0054. Spiral Matrix

## ⚡ 30-Second Summary
**Pattern:** Four boundaries that close in after each side is walked
**Key insight:** Keep `top, bottom, left, right`. Walk the top row and move top down, then the right column and move right in. Next the bottom row, right to left, but only if top ≤ bottom still. Then the left column upward, only if left ≤ right. Those two guards stop a single leftover row or column from being read twice.
**Go-to:** Shrinking boundaries, O(m·n) time, O(1) extra space

## Problem
Return every element of an m × n matrix in clockwise spiral order, starting at the top-left corner. [LeetCode](https://leetcode.com/problems/spiral-matrix/)

**Examples:**
```
Input:  matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,3,6,9,8,7,4,5]
Why:    Outer ring clockwise (1..4), then the centre 5.

Input:  matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]
Why:    The outer ring, then the inner ring is a single row 6, 7 walked once.
```

**Constraints:**
- 1 ≤ m, n ≤ 10. Not necessarily square, which is where the bugs come from.

## Hints
<details><summary>Hint 1</summary>
After you walk the whole top row, which row will you never visit again?
</details>
<details><summary>Hint 2</summary>
Track the four edges of the part not yet visited. What changes after each of the four sides?
</details>
<details><summary>Hint 3</summary>
While top ≤ bottom and left ≤ right: top row left→right, top++; right column top→bottom, right--; if top ≤ bottom, bottom row right→left, bottom--; if left ≤ right, left column bottom→top, left++.
</details>

## Clarifying Questions
- Clockwise from the top-left? (Yes.)
- Rectangular, possibly a single row or column? (Yes.)
- Can I modify the matrix? (Not needed; the boundary version doesn't.)

## Example Walkthrough
A single column `[[1],[2],[3]]`. The top row gives 1, top = 1. The right column gives 2, 3, right = −1. The bottom row guard (top 1 ≤ bottom 2) passes, but its loop runs from right = −1 down to left = 0, so it adds nothing. The left column guard (0 ≤ −1) fails. The result is [1,2,3], each read once.

## Approaches

### 1. Direction Vectors + Visited: O(m·n) time, O(m·n) space
Move in the current direction and turn right when the next cell is out of bounds or already visited. Simple rules, but it needs a visited grid (or overwrites the input with a sentinel).

### 2. Shrinking Boundaries ⭐ Go-to: O(m·n) time, O(1) extra
**Why it's the go-to:** no extra grid, four plain loops, and the two guards are easy to explain.

## Dry Run (Approach 2)
`[[1,2,3,4],[5,6,7,8],[9,10,11,12]]`

| side | cells | t, b, l, r after |
|------|-------|------------------|
| start | | 0, 2, 0, 3 |
| top → | 1 2 3 4 | 1, 2, 0, 3 |
| right ↓ | 8 12 | 1, 2, 0, 2 |
| bottom ← (1 ≤ 2) | 11 10 9 | 1, 1, 0, 2 |
| left ↑ (0 ≤ 2) | 5 | 1, 1, 1, 2 |
| top → | 6 7 | 2, 1, 1, 2 |
| right ↓ | (none: t > b) | 2, 1, 1, 1 |
| bottom ← guard 2 ≤ 1 fails | skip | |
| left ↑ (1 ≤ 1) | (none: b < t) | 2, 1, 2, 1 |

The loop ends → **[1,2,3,4,8,12,11,10,9,5,6,7]**.

## Edge Case Check
- One row `[[1,2,3]]` → [1,2,3]; the bottom guard stops it reading the row again backwards. ✅
- One column → each element once (see walkthrough). ✅
- 1×1 → [x]. ✅

## ⚠️ Pitfalls
- **Missing the two guards** duplicates the middle row or column on non-square inputs (e.g. 3×4 gives 6, 7, 6).
- **Off-by-one on inclusive bounds:** `right = n − 1`, `bottom = m − 1`, and loops use `<=`.
- **Visited-grid version in Python:** `[[False] * n] * m` shares one row m times. Use a comprehension.

## 🎯 What the Interviewer Wants
- A clean simulation with the four boundaries.
- Non-square edge cases handled without special-casing.
- O(1) extra space beyond the output.

## Follow-ups
- **Fill 1..n² in spiral order:** LC 0059 Spiral Matrix II (not added yet). Same loop, writing instead of reading.
- **Spiral outward from a start cell:** LC 0885 Spiral Matrix III (not added yet)
- **Another ring-by-ring matrix problem:** [LC 0048 Rotate Image](../0048-rotate-image/)
