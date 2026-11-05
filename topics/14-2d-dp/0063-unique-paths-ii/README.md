---
number: 63
title: Unique Paths II
difficulty: Medium
topic: 2-D Dynamic Programming
pattern: Grid DP with obstacles
link: https://leetcode.com/problems/unique-paths-ii/
lists: [LC Top Interview 150]
followup_of: ["0062 Unique Paths"]
related: ["0064 Minimum Path Sum", "0980 Unique Paths III"]
---

# 0063. Unique Paths II

## ⚡ 30-Second Summary
**Pattern:** Grid DP, count paths, blocked cells contribute 0
**Key insight:** Same recurrence as 0062, but an obstacle cell has 0 paths. Don't hardcode the first row/column to 1: everything after an obstacle there is 0. Seeding `row[0] = 1` and running the general update handles it.
**Go-to:** 1-D rolling row, O(m·n) time, O(n) space

## Problem
Same robot as LC 62 (right/down only, top-left to bottom-right), but some cells are blocked (marked 1). Count the paths that avoid every blocked cell. [LeetCode](https://leetcode.com/problems/unique-paths-ii/)

**Examples:**
```
Input:  obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
Output: 2
Why:    The centre is blocked, so only the two paths around the edge (right-right-down-down and down-down-right-right) remain.

Input:  obstacleGrid = [[0,1],[0,0]]
Output: 1
Why:    The top-right cell is blocked, so you must go down first, then right.
```

**Constraints:**
- 1 ≤ m, n ≤ 100, cells are 0 or 1.
- The answer is ≤ 2·10⁹.
- The start or the end can itself be an obstacle.

## Hints
<details><summary>Hint 1</summary>
Start from the 0062 recurrence. What should the count be for a blocked cell?
</details>
<details><summary>Hint 2</summary>
In 0062 the top row was all 1s. What happens to the top-row cells to the right of an obstacle?
</details>
<details><summary>Hint 3</summary>
Use one row, all 0 except row[0] = 1 (if the start is open). For every cell: if blocked, row[c] = 0; else if c > 0, row[c] += row[c-1]. This handles the first row and column with no special cases.
</details>

## Clarifying Questions
- Can the start or end be blocked? (Yes → answer 0.)
- 1 means blocked, 0 open? (Yes.)
- Can I modify the input grid? (Ask; the 1-D row avoids it anyway.)

## Example Walkthrough
`[[0,0,0],[0,1,0],[0,0,0]]`: top row [1,1,1]. Middle row: col 0 = 1, col 1 blocked → 0, col 2 = 1 + 0 = 1. Bottom row: [1, 1+0=1, 1+1=2]. Answer 2.

## Approaches

### 1. Memoized Recursion: O(m·n) time, O(m·n) space
paths(r, c) = 0 if out of bounds or blocked, 1 at the start, else paths(r-1, c) + paths(r, c-1).

### 2. 2-D Table: O(m·n) time, O(m·n) space
Same fill as 0062 with blocked cells forced to 0 and the first row/column computed, not hardcoded.

### 3. 1-D Rolling Row ⭐ Go-to: O(m·n) time, O(n) space
One row, seeded with row[0] = 1, and a single uniform update for every cell.
**Why it's the go-to:** no special cases for the edges, and it's the 0062 answer with one extra line.

## Dry Run (Approach 3)
`[[0,1],[0,0]]`, row starts [1, 0].

| r | c | cell | update | row |
|---|---|------|--------|-----|
| 0 | 0 | open | keep (c = 0) | [1, 0] |
| 0 | 1 | blocked | row[1] = 0 | [1, 0] |
| 1 | 0 | open | keep (c = 0) | [1, 0] |
| 1 | 1 | open | row[1] += row[0] | [1, **1**] |

## Edge Case Check
- Start blocked `[[1]]` → row[0] set to 0 on the first cell → 0. ✅
- End blocked `[[0,0],[0,1]]` → last cell forced to 0 → 0. ✅
- Obstacle in the first column `[[0],[1],[0]]` → everything below is 0 → 0. ✅

## ⚠️ Pitfalls
- **Hardcoding the first row/column to 1** ignores obstacles that cut them off.
- **Forgetting the start can be blocked** returns 1 for `[[1]]`.
- **C++ overflow:** the guarantee covers only the final answer. A cell walled off from the target can hold a bigger count, so use `long long` for the row.
- **Modifying the input grid in place** to store counts: works, but say so; it destroys the caller's data.

## 🎯 What the Interviewer Wants
- Adapt 0062 cleanly: blocked → 0.
- Handle the edges without special-casing (or special-case them correctly).
- Mention O(n) space.

## Follow-ups
- **No obstacles, closed form:** [LC 0062 Unique Paths](../0062-unique-paths/)
- **Minimise the sum along the path:** [LC 0064 Minimum Path Sum](../0064-minimum-path-sum/)
- **Visit every empty cell exactly once:** LC 0980 Unique Paths III (not added yet). Backtracking.
