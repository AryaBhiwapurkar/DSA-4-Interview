---
number: 695
title: Max Area of Island
difficulty: Medium
topic: Graphs
pattern: Grid DFS
link: https://leetcode.com/problems/max-area-of-island/
lists: [NeetCode 150]
followup_of: ["0200 Number of Islands"]
related: ["0200 Number of Islands", "0463 Island Perimeter", "0827 Making A Large Island"]
---

# 0695. Max Area of Island

## ⚡ 30-Second Summary
**Pattern:** Flood fill that returns a size
**Key insight:** Same scan as 0200, but the DFS returns how many cells it sank: `1 + dfs(4 neighbours)`, with water / out-of-bounds / visited returning 0. Track the maximum over all starts.
**Go-to:** DFS returning area, O(m·n) time, O(m·n) worst-case stack

## Problem
In a binary grid (1 = land), an island is a 4-connected group of 1s and its area is the number of cells. Return the largest area, or 0 if there is no land. [LeetCode](https://leetcode.com/problems/max-area-of-island/)

**Examples:**
```
Input:  grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],
                [0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],
                [0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
Output: 6
Why:    The island around (3,8)-(5,10) has 6 cells; the others have 1, 4, 4, 5 and 5. Diagonals don't join islands.

Input:  grid = [[0,0,0,0,0,0,0,0]]
Output: 0
Why:    No land at all.
```

**Constraints:**
- 1 ≤ m, n ≤ 50, cells are 0 or 1.

## Hints
<details><summary>Hint 1</summary>
You can already count islands (0200). What extra number does each flood fill need to produce?
</details>
<details><summary>Hint 2</summary>
How does a cell's island area relate to its neighbours' contributions?
</details>
<details><summary>Hint 3</summary>
`area(r, c)` = 0 if out of bounds or water; else set the cell to 0 and return 1 + the four recursive calls. Answer = max over all cells.
</details>

## Clarifying Questions
- 4-directional? (Yes.)
- No land at all? (Return 0.)
- May I modify the grid? (Yes, or keep a visited array.)

## Example Walkthrough
Scanning example 1: islands found at (0,2) area 1, (0,7) area 4, (2,1) area 4, (2,4) area 5, (3,8) area 6, (6,7) area 5. Maximum 6.

## Approaches

### 1. DFS Returning Area ⭐ Go-to: O(m·n) time, O(m·n) stack worst case
Recursive sink that sums cells.
**Why it's the go-to:** a one-line change from 0200; every cell visited once.

### 2. BFS Counting Pops: O(m·n) time, O(m·n) queue worst case
BFS from each new land cell, counting popped cells. No recursion.

## Dry Run (Approach 1)
Example 1, row-major scan

| start cell | island area | best |
|------------|-------------|------|
| (0,2) | 1 | 1 |
| (0,7) | 4 | 4 |
| (2,1) | 4 | 4 |
| (2,4) | 5 | 5 |
| (3,8) | 6 | **6** |
| (6,7) | 5 | 6 |

## Edge Case Check
- All water: 0. ✅
- All land 50 × 50: 2500, recursion depth up to 2500 (fine in C++; the Python version raises the recursion limit). ✅
- Single cell of land: 1. ✅

## ⚠️ Pitfalls
- **Not marking before recursing**: neighbours count the same cell again (infinite recursion).
- **Initialising best to 1** or forgetting the no-land case.
- **Diagonal neighbours** merge islands that should be separate.

## 🎯 What the Interviewer Wants
- Reuse of the flood fill with a return value.
- Clean base cases and linear complexity.

## Follow-ups
- **Count islands:** [LC 0200 Number of Islands](../0200-number-of-islands/)
- **Flip one 0 to maximise the island:** LC 0827 Making A Large Island (not added yet), label islands with ids and sizes first.
- **Perimeter of one island:** LC 0463 Island Perimeter (not added yet)
