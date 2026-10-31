---
number: 130
title: Surrounded Regions
difficulty: Medium
topic: Graphs
pattern: DFS from border
link: https://leetcode.com/problems/surrounded-regions/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0200 Number of Islands", "0417 Pacific Atlantic Water Flow", "1020 Number of Enclaves"]
---

# 0130. Surrounded Regions

## ⚡ 30-Second Summary
**Pattern:** Flood fill from the border (reverse thinking)
**Key insight:** An 'O' survives exactly when it's connected to an 'O' on the border. Instead of checking every region, flood-fill from border 'O's and mark them safe; everything still 'O' afterwards is captured.
**Go-to:** DFS from border cells, O(m·n) time, O(m·n) worst-case stack

## Problem
In a grid of 'X' and 'O', every group of 4-connected 'O' cells that doesn't touch the edge of the grid is captured: flip it to 'X' in place. [LeetCode](https://leetcode.com/problems/surrounded-regions/)

**Examples:**
```
Input:  board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
Output: [["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
Why:    The 3-cell group in the middle is enclosed; the bottom 'O' sits on the edge and stays.

Input:  board = [["X"]]
Output: [["X"]]
Why:    Nothing to capture.
```

**Constraints:**
- 1 ≤ m, n ≤ 200, so up to 4·10⁴ cells (deep recursion is possible).

## Hints
<details><summary>Hint 1</summary>
Which 'O' cells can never be captured?
</details>
<details><summary>Hint 2</summary>
Those on the border, and anything connected to them. Can you find all of those in one pass?
</details>
<details><summary>Hint 3</summary>
DFS from every border 'O', marking cells 'T'. Then sweep: 'O' → 'X', 'T' → 'O'.
</details>

## Clarifying Questions
- 4-directional or 8? (4.)
- Modify in place? (Yes, return nothing.)
- Does a diagonal touch to the border save a region? (No.)

## Example Walkthrough
Example 1: the only border 'O' is (3,1). Its neighbour (2,1) is 'X', so only (3,1) is safe. The sweep flips (1,1), (1,2), (2,2) to 'X' and restores (3,1).

## Approaches

### 1. BFS per Region: O(m·n) time, O(m·n) space
For each unvisited 'O', BFS its whole region, remember whether any cell is on the border, and flip the region if not. Linear, but needs a visited grid and a cell list per region.

### 2. DFS from the Border ⭐ Go-to: O(m·n) time, O(m·n) stack worst case
Mark border-connected 'O's as 'T', then one sweep fixes the board.
**Why it's the go-to:** the reverse view removes the "does this region touch the edge?" bookkeeping; very little code.

## Dry Run (Approach 2)
Example 1

| phase | cell | before | after | note |
|-------|------|--------|-------|------|
| border DFS | (3,1) | O | T | only border 'O'; neighbour (2,1) is X |
| sweep | (1,1) | O | X | not reached from border |
| sweep | (1,2) | O | X | |
| sweep | (2,2) | O | X | |
| sweep | (3,1) | T | O | restored |

## Edge Case Check
- All 'O': every cell is border-connected, nothing changes. ✅
- 1 or 2 rows/cols: every cell is on the border, nothing flips. ✅
- 'O' region touching the border only through a diagonal: captured. ✅

## ⚠️ Pitfalls
- **Flipping while scanning** from inside: you can't know a region is enclosed until it's fully explored.
- **Python recursion limit** on a 200×200 all-'O' board: use an explicit stack.
- **No third symbol:** safe cells must be marked with something other than 'O' (here 'T'), or the DFS can't tell visited from unvisited and the sweep can't tell safe from captured.

## 🎯 What the Interviewer Wants
- The reverse "start from the border" insight.
- Linear complexity and in-place marking.

## Follow-ups
- **Count enclosed land cells:** LC 1020 Number of Enclaves (not added yet), same border flood.
- **Two borders, reverse flow:** [LC 0417 Pacific Atlantic Water Flow](../0417-pacific-atlantic-water-flow/)
- **Count regions instead:** [LC 0200 Number of Islands](../0200-number-of-islands/)
