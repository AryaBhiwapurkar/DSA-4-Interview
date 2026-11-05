---
number: 120
title: Triangle
difficulty: Medium
topic: 2-D Dynamic Programming
pattern: Bottom-up DP
link: https://leetcode.com/problems/triangle/
lists: [LC Top Interview 150]
followup_of: []
related: ["0064 Minimum Path Sum", "0931 Minimum Falling Path Sum"]
---

# 0120. Triangle

## ⚡ 30-Second Summary
**Pattern:** Bottom-up DP on a triangle
**Key insight:** From cell (r, i) you can step to (r+1, i) or (r+1, i+1). Going **bottom-up**, every cell has both children, so there are no edge cases, and the answer ends up in the apex: `dp[i] = tri[r][i] + min(dp[i], dp[i+1])`.
**Go-to:** Bottom-up with one array the size of the last row, O(n²) time, O(n) space

## Problem
A triangle of numbers is given row by row (row r has r+1 entries). Walk from the top to the bottom, each step moving to one of the two adjacent numbers in the next row, and return the smallest possible sum. [LeetCode](https://leetcode.com/problems/triangle/)

**Examples:**
```
Input:  triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
Output: 11
Why:    2 → 3 → 5 → 1. Picking the smaller child each time (greedy) happens to work here, but not in general.

Input:  triangle = [[-10]]
Output: -10
Why:    One row, one number.
```

**Constraints:**
- 1 ≤ rows ≤ 200, values in [-10⁴, 10⁴]. Values can be negative.
- Follow-up asks for O(n) extra space, n = number of rows.

## Hints
<details><summary>Hint 1</summary>
Greedy fails: a small number now can lead to a huge one later. Try [[1],[2,3],[100,100,1]] in your head.
</details>
<details><summary>Hint 2</summary>
Going top-down, the edges of each row have only one parent. Is there a direction where every cell has exactly two options?
</details>
<details><summary>Hint 3</summary>
Start dp as a copy of the last row. For rows from second-last up to 0: dp[i] = tri[r][i] + min(dp[i], dp[i+1]) for i = 0..r. Left to right is safe because dp[i+1] isn't overwritten yet. Return dp[0].
</details>

## Clarifying Questions
- "Adjacent" means index i or i+1 in the next row? (Yes.)
- Negative numbers? (Yes, so no early pruning.)
- Can I modify the input? (Ask; in-place bottom-up is O(1) extra.)

## Example Walkthrough
`[[1],[2,3],[100,100,1]]`: greedy takes 1 → 2 → 100 = 103. Bottom-up: row 1 becomes [2+min(100,100), 3+min(100,1)] = [102, 4], apex 1 + min(102, 4) = 5 (1 → 3 → 1).

## Approaches

### 1. Top-down Memo: O(n²) time, O(n²) space
best(r, i) = tri[r][i] + min(best(r+1, i), best(r+1, i+1)), with best on the last row = the value.

### 2. Bottom-up, O(n) Space ⭐ Go-to: O(n²) time, O(n) space
dp = last row, then fold each row upwards. Answer is dp[0].
**Why it's the go-to:** meets the O(n) follow-up, no boundary cases, and the answer lands in a single cell.

### 3. Top-down Table: O(n²) time, O(n) space
Also works (dp from the apex, with min over the last row at the end), but the first and last entries of each row need special handling.

## Dry Run (Approach 2)
`[[2],[3,4],[6,5,7],[4,1,8,3]]`

| row r | dp after folding row r |
|-------|------------------------|
| start (row 3) | [4, 1, 8, 3] |
| 2 | [6+1, 5+1, 7+3] = [7, 6, 10] |
| 1 | [3+6, 4+6] = [9, 10] |
| 0 | [2+9] = [**11**] |

## Edge Case Check
- One row `[[-10]]` → dp = [-10]. ✅
- All negatives: min still works, nothing assumes positives. ✅
- Greedy trap `[[1],[2,3],[100,100,1]]` → 5. ✅

## ⚠️ Pitfalls
- **Greedy** (smaller child each step) fails.
- **Top-down boundaries:** row edges have one parent; off-by-ones are easy.
- **Python aliasing:** `dp = triangle[-1]` then writing to dp mutates the input; copy with `[:]`.
- **Sentinel overflow** in C++ if you pad with INT_MAX and add to it.

## 🎯 What the Interviewer Wants
- Spot that bottom-up removes the boundary cases.
- O(n) space with one array (the follow-up).
- Explain why left-to-right updates are safe.

## Follow-ups
- **Rectangular grid, right/down:** [LC 0064 Minimum Path Sum](../0064-minimum-path-sum/)
- **Square matrix, 3 children per cell:** LC 0931 Minimum Falling Path Sum (not added yet)
- **Return the path:** store the chosen child at each cell and walk down from the apex.
