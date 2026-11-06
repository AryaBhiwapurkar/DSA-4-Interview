---
number: 6
title: Zigzag Conversion
difficulty: Medium
topic: Arrays & Hashing
pattern: Row simulation
link: https://leetcode.com/problems/zigzag-conversion/
lists: [LC Top Interview 150]
followup_of: []
related: ["0054 Spiral Matrix"]
---

# 0006. Zigzag Conversion

## ⚡ 30-Second Summary
**Pattern:** Simulate the row index bouncing between top and bottom
**Key insight:** You don't need the 2-D grid. Each character just goes to row 0, 1, ..., numRows-1, then back up to 1, and repeats. Append each char to its row's string and concatenate the rows.
**Go-to:** Row buckets with a bouncing index, O(n) time, O(n) space

## Problem
Write the string in a zigzag over `numRows` rows (down the rows, then diagonally back up, repeating), then read it row by row and return the result. [LeetCode](https://leetcode.com/problems/zigzag-conversion/)

**Examples:**
```
Input:  s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"
Why:    Rows are "PAHN", "APLSIIG", "YIR":
          P   A   H   N
          A P L S I I G
          Y   I   R

Input:  s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Why:    Rows are "PIN", "ALSIG", "YAHR", "PI":
          P     I     N
          A   L S   I G
          Y A   H R
          P     I

Input:  s = "A", numRows = 1
Output: "A"
Why:    One row: the string is unchanged.
```

**Constraints:**
- 1 ≤ |s| ≤ 1000; 1 ≤ numRows ≤ 1000.
- s contains letters, ',' and '.'.

## Hints
<details><summary>Hint 1</summary>
Do you really need to know the column of each character, or only its row?
</details>
<details><summary>Hint 2</summary>
Write down the row of each index for numRows = 3: 0,1,2,1,0,1,2,1,0,...
</details>
<details><summary>Hint 3</summary>
Keep one string per row and a direction (+1/-1). Flip direction at row 0 and row numRows-1.
</details>

## Clarifying Questions
- What if numRows is 1, or ≥ |s|? (The string is returned unchanged.)
- Is the pattern down-then-diagonal-up exactly as shown? (Yes.)

## Example Walkthrough
`s = "PAYPALISHIRING", numRows = 3`
- Row sequence: 0 1 2 1 0 1 2 1 0 1 2 1 0 1.
- Row 0 gets P A H N, row 1 gets A P L S I I G, row 2 gets Y I R.
- Concatenate: "PAHN" + "APLSIIG" + "YIR".

## Approaches

### 1. Direct Index Math: O(n) time, O(n) output
The pattern repeats every `cycle = 2·(numRows-1)` characters. Row r takes indices `r, r+cycle, ...`, and middle rows also take `cycle - r + k·cycle` in between. No buffers, but easy to get the middle-row formula wrong.

### 2. Row Buckets ⭐ Go-to: O(n) time, O(n) space
`rows[r] += c`; flip direction at the top and bottom row; join rows.
**Why it's the go-to:** it mirrors the picture, so it's hard to get wrong, and it's still linear.

## Dry Run (Approach 2)
`s = "PAYPALI", numRows = 3`

| i | c | row | dir after | rows |
|---|---|-----|-----------|------|
| 0 | P | 0 | +1 | [P, -, -] |
| 1 | A | 1 | +1 | [P, A, -] |
| 2 | Y | 2 | -1 | [P, A, Y] |
| 3 | P | 1 | -1 | [P, AP, Y] |
| 4 | A | 0 | +1 | [PA, AP, Y] |
| 5 | L | 1 | +1 | [PA, APL, Y] |
| 6 | I | 2 | -1 | [PA, APL, YI] |

Result: "PA" + "APL" + "YI" = "PAAPLYI".

## Edge Case Check
- numRows = 1: return s immediately (otherwise the direction flips every step and the index goes out of range). ✅
- numRows ≥ |s|: each char lands in its own row in order, unchanged. ✅
- |s| = 1: unchanged. ✅

## ⚠️ Pitfalls
- **numRows = 1 not special-cased:** row bounces between 0 and 0 with dir flips, or cycle = 0 causes division/infinite-loop issues in the index-math version.
- **Flipping direction at the wrong time:** flip when you *land* on row 0 or numRows-1, before moving.
- **Building with `+=` on immutable strings (Python/Go)** is fine at n = 1000; use lists/builders in general.

## 🎯 What the Interviewer Wants
- Realize the grid is unnecessary.
- Clean bounce logic and the numRows = 1 edge case.

## Follow-ups
- **O(1) extra space besides the output:** index-math approach (Approach 1).
- **Decode: given the zigzag string, recover s:** compute each row's length from the cycle, then read back in zigzag order.
- **Another traversal-order simulation:** [LC 0054 Spiral Matrix](../../17-math-geometry/0054-spiral-matrix/)
