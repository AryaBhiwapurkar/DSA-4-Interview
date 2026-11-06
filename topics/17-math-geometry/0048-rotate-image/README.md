---
number: 48
title: Rotate Image
difficulty: Medium
topic: Math & Geometry
pattern: Transpose + reverse rows
link: https://leetcode.com/problems/rotate-image/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0054 Spiral Matrix", "0189 Rotate Array", "0867 Transpose Matrix"]
---

# 0048. Rotate Image

## ⚡ 30-Second Summary
**Pattern:** Break the rotation into two in-place reflections
**Key insight:** A 90° clockwise turn sends (r, c) to (c, n−1−r). That's a transpose (r, c) → (c, r) followed by mirroring each row (c → n−1−c). Both steps are simple in-place swaps.
**Go-to:** Transpose, then reverse every row, O(n²) time, O(1) space

## Problem
Rotate an n × n matrix 90° clockwise, in place, without allocating a second matrix. [LeetCode](https://leetcode.com/problems/rotate-image/)

**Examples:**
```
Input:  matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[7,4,1],[8,5,2],[9,6,3]]
Why:    The first column read bottom-up (7,4,1) becomes the first row.

Input:  matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
Why:    Same rule on a 4×4: each column, read bottom-up, becomes a row.
```

**Constraints:**
- 1 ≤ n ≤ 20, square matrix.
- Must be in place (O(1) extra space).

## Hints
<details><summary>Hint 1</summary>
Write down where cell (r, c) ends up after the rotation.
</details>
<details><summary>Hint 2</summary>
Can you get there with two simpler moves, each of which is just swapping pairs of cells?
</details>
<details><summary>Hint 3</summary>
Transpose: swap m[r][c] with m[c][r] for c &gt; r. Then reverse each row. (Counter-clockwise: transpose, then reverse the order of the rows instead.)
</details>

## Clarifying Questions
- Clockwise or counter-clockwise? (Clockwise.)
- Always square? (Yes; a non-square rotation can't be done in place.)
- Return a new matrix or modify? (Modify in place.)

## Example Walkthrough
3×3 `[[1,2,3],[4,5,6],[7,8,9]]`. Transpose → `[[1,4,7],[2,5,8],[3,6,9]]`. Reverse each row → `[[7,4,1],[8,5,2],[9,6,3]]`. ✓

## Approaches

### 1. Copy into a New Matrix: O(n²) time, O(n²) space
`out[c][n-1-r] = m[r][c]`, then copy back. Easy to get right, but it breaks the in-place rule.

### 2. Transpose + Reverse ⭐ Go-to: O(n²) time, O(1) space
**Why it's the go-to:** two standard loops you can't really get wrong, and the same idea handles every rotation direction.

### 3. Rotate Four Cells at a Time: O(n²) time, O(1) space
Work ring by ring. For each offset, cycle the four cells top → right → bottom → left with one temporary. Each cell moves once, but the index arithmetic is error-prone.

## Dry Run (Approach 2)
4×4 example, transpose step (swaps above the diagonal):

| after | matrix |
|-------|--------|
| start | [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]] |
| transpose | [[5,2,13,15],[1,4,3,14],[9,8,6,12],[11,10,7,16]] |
| reverse rows | **[[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]** |

## Edge Case Check
- 1×1 → unchanged. ✅
- 2×2 `[[1,2],[3,4]]` → `[[3,1],[4,2]]`. ✅
- Odd n: the centre cell stays put. ✅

## ⚠️ Pitfalls
- **Transposing the whole square** (`c` from 0) swaps every pair twice and undoes itself. Start at `c = r + 1`.
- **Wrong order for the direction:** transpose then reverse rows is clockwise; reversing rows first, then transposing, is counter-clockwise.
- **Python `matrix = [...]`** rebinds the name and leaves the caller's matrix untouched. Use `matrix[:] = ...` or mutate in place.

## 🎯 What the Interviewer Wants
- The (r, c) → (c, n−1−r) mapping, derived not memorised.
- In-place with O(1) extra space.
- Optional: the four-way swap, and how to do counter-clockwise or 180°.

## Follow-ups
- **Walk the matrix in rings:** [LC 0054 Spiral Matrix](../0054-spiral-matrix/)
- **Rotate a 1-D array by reversals:** [LC 0189 Rotate Array](../../01-arrays-hashing/0189-rotate-array/)
- **Non-square transpose:** LC 0867 Transpose Matrix (not added yet). Needs a new m × n → n × m matrix.
