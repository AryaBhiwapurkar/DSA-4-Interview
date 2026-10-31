---
number: 417
title: Pacific Atlantic Water Flow
difficulty: Medium
topic: Graphs
pattern: Reverse DFS from both oceans
link: https://leetcode.com/problems/pacific-atlantic-water-flow/
lists: [NeetCode 150]
followup_of: []
related: ["0130 Surrounded Regions", "0200 Number of Islands", "0778 Swim in Rising Water"]
---

# 0417. Pacific Atlantic Water Flow

## ⚡ 30-Second Summary
**Pattern:** Reverse flood fill from the targets
**Key insight:** Asking "where can this cell's water reach?" for every cell repeats work. Flip it: start at each ocean's border and walk *uphill* (to neighbours of equal or greater height). Those are exactly the cells that can drain into that ocean. The answer is the intersection of the two sets.
**Go-to:** Two reverse DFS/BFS passes, O(m·n) time, O(m·n) space

## Problem
A grid of heights sits between the Pacific (top and left edges) and the Atlantic (bottom and right edges). Rain flows from a cell to a side-neighbour of equal or lower height, and from edge cells into the adjacent ocean. Return every cell whose water can reach both oceans. Any order. [LeetCode](https://leetcode.com/problems/pacific-atlantic-water-flow/)

**Examples:**
```
Input:  heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
Why:    e.g. (2,2) with height 5 can flow up-left to the Pacific and down-right to the Atlantic.

Input:  heights = [[1]]
Output: [[0,0]]
Why:    A single cell touches all four edges, so both oceans.
```

**Constraints:**
- 1 ≤ m, n ≤ 200; heights in [0, 10⁵].

## Hints
<details><summary>Hint 1</summary>
Running a search from every cell is O((m·n)²). Which cells definitely reach the Pacific?
</details>
<details><summary>Hint 2</summary>
The Pacific border cells. If water can flow from X down to a Pacific-reaching cell Y, then X reaches the Pacific too. Which direction should you search?
</details>
<details><summary>Hint 3</summary>
DFS from all Pacific border cells, moving to neighbours with height ≥ current. Same for the Atlantic. Return cells in both visited sets.
</details>

## Clarifying Questions
- Equal heights allow flow? (Yes, ≤.)
- Corner cells (0, n-1) and (m-1, 0)? (They touch both oceans.)
- Output order? (Any.)

## Example Walkthrough
For example 1, the Pacific pass marks the whole top row and left column, then climbs inward. The Atlantic pass does the same from the bottom row and right column. Cells in both: the top-right corner area (0,4), (1,3), (1,4), the peak (2,2), and the bottom-left area (3,0), (3,1), (4,0).

## Approaches

### 1. DFS from Every Cell: O((m·n)²) time, O(m·n) space
From each cell, flow downhill and see whether both oceans' edges are touched. Simple, too slow at 200 × 200.

### 2. Reverse DFS from Both Oceans ⭐ Go-to: O(m·n) time, O(m·n) space
Two uphill flood fills, each visiting every cell at most once; intersect.
**Why it's the go-to:** linear, and the "reverse the direction, start from the target" trick is the point of the problem.

## Dry Run (Approach 2)
Example 1. P = reached only from the Pacific, A = only from the Atlantic, **B** = both.

| row | heights | reach |
|-----|---------|-------|
| 0 | 1 2 2 3 5 | P P P P **B** |
| 1 | 3 2 3 4 4 | P P P **B B** |
| 2 | 2 4 5 3 1 | P P **B** A A |
| 3 | 6 7 1 4 5 | **B B** A A A |
| 4 | 5 1 1 2 4 | **B** A A A A |

The B cells are the answer.

## Edge Case Check
- 1 × 1 grid: both oceans. ✅
- Single row or column: every cell touches both oceans. ✅
- Flat grid: every cell reaches everything. ✅

## ⚠️ Pitfalls
- **Wrong comparison direction** in the reverse search: go to neighbours with height **≥** current.
- **Per-cell DFS without memo** is O((m·n)²).
- **Python recursion** on 200 × 200 can overflow; use a stack or BFS.
- **Seeding corners twice** is harmless if you check visited first.

## 🎯 What the Interviewer Wants
- The reverse-search idea and why it's correct.
- Linear complexity, clean bounds checks, and set intersection.

## Follow-ups
- **Same border-first idea:** [LC 0130 Surrounded Regions](../0130-surrounded-regions/)
- **Minimum time to cross a height grid:** [LC 0778 Swim in Rising Water](../../12-advanced-graphs/0778-swim-in-rising-water/)
