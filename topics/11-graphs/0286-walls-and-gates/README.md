---
number: 286
title: Walls and Gates
difficulty: Medium
topic: Graphs
pattern: Multi-source BFS
link: https://leetcode.com/problems/walls-and-gates/
lists: [NeetCode 150]
followup_of: []
related: ["0994 Rotting Oranges", "0542 01 Matrix", "0317 Shortest Distance from All Buildings"]
---

# 0286. Walls and Gates

## ⚡ 30-Second Summary
**Pattern:** Multi-source BFS
**Key insight:** Instead of one BFS per room or per gate, put *all* gates in the queue at distance 0 and run one BFS. Rooms are reached in order of distance from the nearest gate, so the first time a room is filled is its answer.
**Go-to:** Multi-source BFS from all gates, O(m·n) time, O(m·n) queue

## Problem
A grid holds -1 (wall), 0 (gate) and INF = 2147483647 (empty room). Fill every empty room, in place, with its step distance to the nearest gate; leave it INF if no gate is reachable (LeetCode Premium). [LeetCode](https://leetcode.com/problems/walls-and-gates/)

**Examples:**
```
Input:  rooms = [[INF,-1,0,INF],[INF,INF,INF,-1],[INF,-1,INF,-1],[0,-1,INF,INF]]
Output: [[3,-1,0,1],[2,2,1,-1],[1,-1,2,-1],[0,-1,3,4]]
Why:    Each room gets the step count to whichever of the two gates is closer.

Input:  rooms = [[-1]]
Output: [[-1]]
Why:    Just a wall, nothing to fill.
```

**Constraints:**
- 1 ≤ m, n ≤ 250; cells are -1, 0 or 2³¹ - 1.

## Hints
<details><summary>Hint 1</summary>
BFS from a single gate gives distances to that gate. How would you combine many gates?
</details>
<details><summary>Hint 2</summary>
What if all gates start at the same time, like ripples spreading together?
</details>
<details><summary>Hint 3</summary>
Queue every gate. Pop a cell; for each neighbour that is still INF, set it to cell + 1 and push it. Walls and filled rooms are never touched again.
</details>

## Clarifying Questions
- Movement: 4 directions? (Yes.)
- Unreachable rooms? (Stay INF.)
- In place? (Yes, return nothing.)

## Example Walkthrough
Gates at (0,2) and (3,0). Step 1 fills (1,2), (0,3), (2,0) with 1. Step 2 fills (2,2), (1,1), (1,0) with 2. Step 3 fills (3,2), (0,0) with 3. Step 4 fills (3,3) with 4.

## Approaches

### 1. BFS from Each Gate: O(k · m·n) time, O(m·n) space
For every gate, BFS and keep `min(current, dist)`. Correct, but repeats the whole grid per gate (k gates).

### 2. Multi-Source BFS ⭐ Go-to: O(m·n) time, O(m·n) space
One BFS seeded with all gates. A cell is filled only while INF, so each is processed once.
**Why it's the go-to:** linear, short, and the "INF means unvisited" check removes the need for a visited set.

## Dry Run (Approach 2)
Example 1 (row, col)

| BFS level | cells filled | value |
|-----------|--------------|-------|
| 0 (seed) | gates (0,2), (3,0) | 0 |
| 1 | (1,2), (0,3), (2,0) | 1 |
| 2 | (2,2), (1,1), (1,0) | 2 |
| 3 | (3,2), (0,0) | 3 |
| 4 | (3,3) | 4 |

## Edge Case Check
- No gates: nothing is queued, rooms stay INF. ✅
- Room walled off from all gates: never reached, stays INF. ✅
- Only walls: unchanged. ✅

## ⚠️ Pitfalls
- **DFS instead of BFS**: DFS reaches cells by long paths first; you'd need repeated relaxation.
- **Per-room BFS to the nearest gate**: O((m·n)²).
- **Overwriting a filled room**: only fill cells that are still INF, or a farther gate can overwrite a closer answer.
- **C++ INF**: use `INT_MAX` (2147483647), not a smaller sentinel.

## 🎯 What the Interviewer Wants
- Recognise "nearest of many sources" → multi-source BFS.
- Explain why the first visit is the shortest distance.

## Follow-ups
- **Spreading with a time answer:** [LC 0994 Rotting Oranges](../0994-rotting-oranges/)
- **Distance to nearest 0 in a binary matrix:** LC 0542 01 Matrix (not added yet)
- **Sum of distances to all buildings:** LC 0317 Shortest Distance from All Buildings (not added yet), one BFS per building.
