---
number: 200
title: Number of Islands
difficulty: Medium
topic: Graphs
pattern: Grid DFS/BFS flood fill
link: https://leetcode.com/problems/number-of-islands/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0695 Max Area of Island", "0130 Surrounded Regions", "0323 Number of Connected Components in an Undirected Graph", "0305 Number of Islands II"]
---

# 0200. Number of Islands

## ⚡ 30-Second Summary
**Pattern:** Flood fill (connected components on a grid)
**Key insight:** Scan the grid; every time you hit unvisited land, that's a new island. Flood-fill it (DFS or BFS) so none of its cells start another count. Overwriting '1' with '0' doubles as the visited set.
**Go-to:** DFS flood fill, O(m·n) time, O(m·n) worst-case stack

## Problem
Given a grid of '1' (land) and '0' (water), count the islands: groups of land cells connected horizontally or vertically. Everything outside the grid is water. [LeetCode](https://leetcode.com/problems/number-of-islands/)

**Examples:**
```
Input:  grid = [["1","1","1","1","0"],["1","1","0","1","0"],["1","1","0","0","0"],["0","0","0","0","0"]]
Output: 1
Why:    All the land cells touch through some chain of side-neighbours.

Input:  grid = [["1","1","0","0","0"],["1","1","0","0","0"],["0","0","1","0","0"],["0","0","0","1","1"]]
Output: 3
Why:    A 2×2 block top-left, a single cell in the middle, and a pair bottom-right. Diagonals don't connect.
```

**Constraints:**
- 1 ≤ m, n ≤ 300, so up to 9·10⁴ cells. Linear time is required, and recursion can get deep.

## Hints
<details><summary>Hint 1</summary>
This is "count connected components". What's a node and what's an edge?
</details>
<details><summary>Hint 2</summary>
When you find a land cell you haven't seen, how do you make sure the rest of its island isn't counted again?
</details>
<details><summary>Hint 3</summary>
For each cell: if '1', count++ and DFS that sets every reachable '1' to '0'.
</details>

## Clarifying Questions
- 4- or 8-directional connectivity? (4.)
- May I modify the grid? (If not, use a visited array.)
- Can the grid be empty? (No, m, n ≥ 1.)

## Example Walkthrough
Example 2: (0,0) is land → island 1, sinks the 2×2 block. Next land in scan order is (2,2) → island 2, just itself. Then (3,3) → island 3, sinks (3,3) and (3,4).

## Approaches

### 1. DFS Flood Fill ⭐ Go-to: O(m·n) time, O(m·n) stack worst case
Recursive sink from each newly found land cell.
**Why it's the go-to:** shortest correct code; every cell is visited a constant number of times.

### 2. BFS Flood Fill: O(m·n) time, O(min(m, n)) queue typically
Same scan, but sink with a queue. Avoids deep recursion; mark cells when *enqueuing*, not when popping.

### 3. Union-Find: O(m·n · α) time, O(m·n) space
Start with count = number of land cells; union each land cell with its right and down land neighbours, decrementing on every successful union. Overkill for a static grid, but it's the base for the online version (0305).

## Dry Run (Approach 1)
Example 2, row-major scan

| scan hits | count | cells sunk by the DFS |
|-----------|-------|-----------------------|
| (0,0) | 1 | (0,0), (1,0), (1,1), (0,1) |
| (2,2) | 2 | (2,2) |
| (3,3) | 3 | (3,3), (3,4) |
| rest | 3 | all '0' now |

## Edge Case Check
- All water: 0. ✅
- All land: 1. ✅
- Checkerboard `101/010/101`: 5 (diagonals don't connect). ✅

## ⚠️ Pitfalls
- **Python recursion limit** on a 300×300 all-land grid: use BFS or an explicit stack.
- **BFS marking on pop** instead of on push: the same cell is enqueued many times.
- **Chars, not ints:** the grid holds '1'/'0' characters; comparing to 1 is always false.
- **Counting diagonals** by using 8 directions.

## 🎯 What the Interviewer Wants
- Recognise connected components and pick DFS or BFS.
- Mention the trade-off: modify input vs a visited set; recursion depth vs queue.
- Bonus: Union-Find and when it's the better tool (dynamic additions).

## Follow-ups
- **Largest island area:** [LC 0695 Max Area of Island](../0695-max-area-of-island/)
- **Islands added one at a time:** LC 0305 Number of Islands II, Union-Find (not added yet)
- **Same count on an explicit graph:** [LC 0323 Number of Connected Components](../0323-number-of-connected-components-in-an-undirected-graph/)
- **Distinct island shapes:** LC 0694 Number of Distinct Islands, record the DFS path signature (not added yet)
