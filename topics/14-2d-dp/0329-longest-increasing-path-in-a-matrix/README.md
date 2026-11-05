---
number: 329
title: Longest Increasing Path in a Matrix
difficulty: Hard
topic: 2-D Dynamic Programming
pattern: DFS + memo
link: https://leetcode.com/problems/longest-increasing-path-in-a-matrix/
lists: [NeetCode 150]
followup_of: []
related: ["0300 Longest Increasing Subsequence", "0200 Number of Islands", "2328 Number of Increasing Paths in a Grid"]
---

# 0329. Longest Increasing Path in a Matrix

## ⚡ 30-Second Summary
**Pattern:** DFS with memoization on a DAG
**Key insight:** Edges only go to strictly larger neighbours, so the grid is a DAG: no cycles, no visited set needed. `longest(r, c) = 1 + max(longest(neighbour))` over larger neighbours, and each cell's answer never changes, so cache it.
**Go-to:** DFS + memo from every cell, O(m·n) time, O(m·n) space

## Problem
Find the length of the longest path in a grid where each step goes up, down, left or right to a strictly larger value. [LeetCode](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/)

**Examples:**
```
Input:  matrix = [[9,9,4],[6,6,8],[2,1,1]]
Output: 4
Why:    1 → 2 → 6 → 9, starting at the bottom-middle 1 and going left, then up twice.

Input:  matrix = [[3,4,5],[3,2,6],[2,2,1]]
Output: 4
Why:    3 → 4 → 5 → 6 along the top row and down. Moving diagonally isn't allowed.

Input:  matrix = [[1]]
Output: 1
Why:    A single cell is a path of length 1.
```

**Constraints:**
- 1 ≤ m, n ≤ 200, so m·n ≤ 4·10⁴; recursion can go that deep on a snake-shaped path.
- Values in [0, 2³¹-1].

## Hints
<details><summary>Hint 1</summary>
Do you need a visited set for this DFS? Can a strictly increasing path ever return to a cell?
</details>
<details><summary>Hint 2</summary>
The longest path starting at a cell doesn't depend on how you reached it. What does that let you reuse?
</details>
<details><summary>Hint 3</summary>
dfs(r, c) = 1 + max over 4 neighbours with a bigger value of dfs(neighbour), or 1 if none. Memoize per cell, call it from every cell, return the max.
</details>

## Clarifying Questions
- Strictly increasing? (Yes: equal values don't connect.)
- Diagonal moves? (No, 4 directions.)
- Length counts cells, not steps? (Cells: a lone cell is 1.)

## Example Walkthrough
Example 1: the bottom-middle 1 can go to 2 (left) or 6 (up). From 2 the only larger neighbour is 6, from 6 it's 9, and from 9 nothing, so that chain is 4. When the outer loop later starts at the 2, its value (3) is already in the memo.

## Approaches

### 1. Plain DFS: exponential worst case, O(m·n) space
DFS from every cell without caching. Correct, but it recomputes the same sub-paths over and over.

### 2. DFS + Memo ⭐ Go-to: O(m·n) time, O(m·n) space
Each cell is solved once, with 4 neighbour checks.
**Why it's the go-to:** it's the brute force plus one array. The "no visited set because it's a DAG" argument is the key insight to say out loud.

### 3. Topological Sort: O(m·n) time, O(m·n) space
Count each cell's larger neighbours (out-degree). BFS from local maxima, peeling layers like Kahn's algorithm; the number of layers is the answer. Iterative, with no recursion-depth worries.

## Dry Run (Approach 2)
Example 1. Memo after all calls (the value at each cell is the longest path starting there):

| r \ c | 0 | 1 | 2 |
|-------|---|---|---|
| 0 | 9 → 1 | 9 → 1 | 4 → 2 |
| 1 | 6 → 2 | 6 → 2 | 8 → 1 |
| 2 | 2 → 3 | 1 → **4** | 1 → 2 |

(2,1): neighbours larger than 1 are 2 (memo 3) and 6 (memo 2) → 1 + 3 = **4**.

## Edge Case Check
- All equal `[[7,7],[7,7]]` → no edges → 1. ✅
- Snake `[[1,2,3],[6,5,4],[7,8,9]]` → the whole grid, 9. ✅
- Single cell → 1. ✅

## ⚠️ Pitfalls
- **Adding a visited set** is unnecessary, and if it isn't reset properly it breaks memo reuse.
- **Using ≥ instead of >** creates cycles among equal values.
- **Python recursion limit:** a snake path can be 4·10⁴ deep; raise the limit or use the topological version.
- **Memo sentinel:** 0 works because every answer is ≥ 1.

## 🎯 What the Interviewer Wants
- Spot the DAG and explain why memo is valid.
- O(m·n) complexity.
- Bonus: the topological-sort alternative and the recursion-depth trade-off.

## Follow-ups
- **1-D version:** [LC 0300 Longest Increasing Subsequence](../../13-1d-dp/0300-longest-increasing-subsequence/)
- **Count all increasing paths:** LC 2328 Number of Increasing Paths in a Grid (not added yet). Same memo, sum instead of max.
- **Grid DFS basics:** [LC 0200 Number of Islands](../../11-graphs/0200-number-of-islands/)
