---
number: 778
title: Swim in Rising Water
difficulty: Hard
topic: Advanced Graphs
pattern: Dijkstra on max edge
link: https://leetcode.com/problems/swim-in-rising-water/
lists: [NeetCode 150]
followup_of: []
related: ["1631 Path With Minimum Effort", "0743 Network Delay Time", "0417 Pacific Atlantic Water Flow"]
---

# 0778. Swim in Rising Water

## ⚡ 30-Second Summary
**Pattern:** Minimax path (minimize the maximum on the path)
**Key insight:** The time needed for a path is its **highest cell**. Run Dijkstra where a path's cost is `max(cost so far, next cell)` instead of a sum. Max never decreases along a path, so Dijkstra's greedy choice still holds.
**Go-to:** Dijkstra with a min-heap on max height, O(n² log n) time, O(n²) space

## Problem
An n × n grid holds distinct heights 0..n²-1. At time t, the water level is t and you can swim between 4-adjacent cells if both have height ≤ t (swimming itself is instant). Return the least time t at which you can get from the top-left to the bottom-right cell. [LeetCode](https://leetcode.com/problems/swim-in-rising-water/)

**Examples:**
```
Input:  grid = [[0,2],[1,3]]
Output: 3
Why:    The target cell itself has height 3, so you must wait until t = 3 whatever path you take.

Input:  grid = [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
Output: 16
Why:    Walk the top row and down to 5. Every way on from there needs 16 or more. Step onto 16, then snake left along row 2 (15..12) and right along the bottom row (10..6).
```

**Constraints:**
- 1 ≤ n ≤ 50, so n² ≤ 2500 cells.
- Heights are a permutation of 0..n²-1, so the answer is at most n²-1.

## Hints
<details><summary>Hint 1</summary>
For one fixed path, what time t do you need? It depends on just one cell of the path.
</details>
<details><summary>Hint 2</summary>
You want the path whose highest cell is as low as possible. Either guess t and check reachability, or adapt a shortest-path algorithm.
</details>
<details><summary>Hint 3</summary>
Dijkstra with key = max height on the path so far. Start with (grid[0][0], 0, 0). Pop the smallest key; neighbours get key max(key, their height). The first time the target pops, that key is the answer.
</details>

## Clarifying Questions
- Do I need to wait for the start cell's own height? (Yes, the start counts.)
- 4-directional moves only? (Yes.)
- Heights distinct and in 0..n²-1? (Yes, which bounds a binary search.)

## Example Walkthrough
Extra case `[[3,2],[0,1]]`: you're standing on height 3 at the start, so nothing can happen before t = 3. At t = 3 every cell is open → 3. This is why the heap starts with key `grid[0][0]`, not 0.

## Approaches

### 1. Binary Search on t + DFS: O(n² log n) time, O(n²) space
Reachability is monotonic in t: if you can make it at t, you can at t+1. Binary search the smallest t in [0, n²-1], checking with a flood fill over cells ≤ t.

### 2. Dijkstra on Max Height ⭐ Go-to: O(n² log n) time, O(n²) space
Min-heap of (max height so far, r, c). Each cell is pushed once (marking on push is safe, because the key is max(t, height) and t only grows as pops proceed).
**Why it's the go-to:** one pass, and it's the same Dijkstra template as 0743 with `+` swapped for `max`.

## Dry Run (Approach 2)
Example 1: `[[0,2],[1,3]]`.

| pop (t, r, c) | push | heap after |
|---------------|------|------------|
| (0, 0, 0) | (2, 0, 1), (1, 1, 0) | (1,1,0), (2,0,1) |
| (1, 1, 0) | (max(1,3)=3, 1, 1) | (2,0,1), (3,1,1) |
| (2, 0, 1) | (1,1) already seen | (3,1,1) |
| (3, 1, 1) | target | return **3** |

## Edge Case Check
- n = 1: the start is the target, return grid[0][0] = 0. ✅
- High start cell (extra case): the initial key is 3, not 0. ✅
- Long snake path (example 2): the heap explores 0..5 first, is forced through 16, then reaches the target via cells below 16. ✅

## ⚠️ Pitfalls
- **Summing heights** (plain Dijkstra) instead of taking the max.
- **Starting the heap at 0** instead of grid[0][0].
- **Binary search bounds:** lo = 0, hi = n²-1, and check the start cell inside the reachability test.
- **Python:** the recursive flood fill on 2500 cells is fine, but an explicit stack avoids recursion-limit worries.

## 🎯 What the Interviewer Wants
- Reframe as "minimize the max on a path".
- Either approach, with a clear argument for correctness (monotonicity for binary search, non-decreasing key for Dijkstra).
- Bonus: mention the Union-Find alternative (add cells in height order until start and end connect).

## Follow-ups
- **Minimize the max height difference between steps:** LC 1631 Path With Minimum Effort (not added yet). The same minimax Dijkstra on edge weights.
- **Sum-of-weights version:** [LC 0743 Network Delay Time](../0743-network-delay-time/)
- **Water flowing downhill to borders:** [LC 0417 Pacific Atlantic Water Flow](../../11-graphs/0417-pacific-atlantic-water-flow/)
