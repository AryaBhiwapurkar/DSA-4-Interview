---
number: 994
title: Rotting Oranges
difficulty: Medium
topic: Graphs
pattern: Multi-source BFS
link: https://leetcode.com/problems/rotting-oranges/
lists: [NeetCode 150]
followup_of: []
related: ["0286 Walls and Gates", "0542 01 Matrix", "0200 Number of Islands"]
---

# 0994. Rotting Oranges

## ⚡ 30-Second Summary
**Pattern:** Multi-source BFS, level by level
**Key insight:** All rotten oranges spread at the same time, so seed the queue with every rotten orange and process one BFS level per minute. Count fresh oranges up front; if any remain when the queue empties, return -1.
**Go-to:** Multi-source BFS with a fresh counter, O(m·n) time, O(m·n) space

## Problem
In a grid, 0 is empty, 1 a fresh orange, 2 a rotten one. Every minute, each fresh orange next to (4-directionally) a rotten one becomes rotten. Return the minutes until no fresh orange is left, or -1 if that never happens. [LeetCode](https://leetcode.com/problems/rotting-oranges/)

**Examples:**
```
Input:  grid = [[2,1,1],[1,1,0],[0,1,1]]
Output: 4
Why:    The rot spreads from the top-left corner and reaches the bottom-right orange on minute 4.

Input:  grid = [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Why:    The bottom-left orange is cut off: both of its neighbours are empty cells, so it never rots.

Input:  grid = [[0,2]]
Output: 0
Why:    No fresh oranges at the start, so zero minutes.
```

**Constraints:**
- 1 ≤ m, n ≤ 10.

## Hints
<details><summary>Hint 1</summary>
Several oranges are rotten at the start and they spread together. How do you simulate "together"?
</details>
<details><summary>Hint 2</summary>
BFS processes nodes in rounds by distance. What does one round mean here?
</details>
<details><summary>Hint 3</summary>
Queue all 2s, count all 1s. While the queue is non-empty and fresh > 0: process exactly the current queue size, rot fresh neighbours (fresh--, enqueue), minutes++. Return fresh == 0 ? minutes : -1.
</details>

## Clarifying Questions
- No fresh oranges at all? (0, even if there are no rotten ones.)
- Fresh oranges but no rotten ones? (-1.)
- Diagonal spread? (No.)

## Example Walkthrough
Example 1: minute 1 rots (0,1), (1,0). Minute 2: (0,2), (1,1). Minute 3: (2,1). Minute 4: (2,2). Fresh count hits 0 → 4.

## Approaches

### 1. Repeated Full-Grid Simulation: O((m·n)²) time, O(m·n) space
Each minute, scan the whole grid and rot fresh oranges next to rotten ones (using a copy, so new rot doesn't spread in the same minute). Stop when nothing changes.

### 2. Multi-Source BFS ⭐ Go-to: O(m·n) time, O(m·n) space
One BFS from all rotten oranges, one level per minute.
**Why it's the go-to:** linear and the level loop maps exactly to "minutes".

## Dry Run (Approach 2)
Example 1

| minute | rotted this minute | fresh left | queue for next minute |
|--------|--------------------|------------|-----------------------|
| 0 | (seed) (0,0) | 6 | [(0,0)] |
| 1 | (1,0), (0,1) | 4 | [(1,0), (0,1)] |
| 2 | (1,1), (0,2) | 2 | [(1,1), (0,2)] |
| 3 | (2,1) | 1 | [(2,1)] |
| 4 | (2,2) | 0 | stop → **4** |

## Edge Case Check
- No fresh oranges: loop never runs → 0. ✅
- Isolated fresh orange: fresh > 0 at the end → -1. ✅
- No rotten but fresh present: queue empty → -1. ✅

## ⚠️ Pitfalls
- **Counting one extra minute**: stop the loop when fresh hits 0 (`while q and fresh`), or the last level adds a minute with nothing to rot.
- **Mixing levels**: process exactly `len(queue)` items per minute.
- **Rotting in place during a full-grid scan** (approach 1) lets rot travel several cells in one minute.

## 🎯 What the Interviewer Wants
- Multi-source BFS with levels as time.
- The fresh counter for the -1 check, and the edge cases at 0.

## Follow-ups
- **Distances instead of a single time:** [LC 0286 Walls and Gates](../0286-walls-and-gates/)
- **Nearest 0 for every cell:** LC 0542 01 Matrix (not added yet)
