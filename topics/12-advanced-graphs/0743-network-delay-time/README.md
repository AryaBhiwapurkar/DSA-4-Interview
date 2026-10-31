---
number: 743
title: Network Delay Time
difficulty: Medium
topic: Advanced Graphs
pattern: Dijkstra
link: https://leetcode.com/problems/network-delay-time/
lists: [NeetCode 150]
followup_of: []
related: ["0787 Cheapest Flights Within K Stops", "1514 Path with Maximum Probability", "0778 Swim in Rising Water"]
---

# 0743. Network Delay Time

## ⚡ 30-Second Summary
**Pattern:** Single-source shortest path, non-negative weights
**Key insight:** The time for every node to hear the signal is the **largest** shortest-path distance from k. Weights are non-negative, so Dijkstra works.
**Go-to:** Dijkstra with a min-heap, O(E log V) time, O(V + E) space

## Problem
You get directed edges `(u, v, w)`: a signal takes `w` time to travel from `u` to `v`. Nodes are labelled 1..n. A signal is sent from node `k`. Return the minimum time until all n nodes have received it, or -1 if some node can never receive it. [LeetCode](https://leetcode.com/problems/network-delay-time/)

**Examples:**
```
Input:  times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
Output: 2
Why:    Nodes 1 and 3 hear at time 1, node 4 at time 2 (via 3). The last one decides.

Input:  times = [[1,2,1]], n = 2, k = 1
Output: 1
Why:    One edge, one hop.

Input:  times = [[1,2,1]], n = 2, k = 2
Output: -1
Why:    The edge points away from node 1 towards node 2, so starting at 2 nothing reaches node 1.
```

**Constraints:**
- 1 ≤ n ≤ 100, up to 6000 edges, 0 ≤ w ≤ 100: all distances fit in an int.
- Edges are directed; no duplicate (u, v) pairs.

## Hints
<details><summary>Hint 1</summary>
When does the last node receive the signal, in terms of shortest paths?
</details>
<details><summary>Hint 2</summary>
You need the shortest path from k to every node, and all weights are non-negative. Which classic algorithm fits?
</details>
<details><summary>Hint 3</summary>
Dijkstra: a min-heap of (distance, node), start with (0, k). Pop, skip if stale, relax outgoing edges. Answer = max over all distances, or -1 if any is still infinity.
</details>

## Clarifying Questions
- Are edges directed? (Yes.)
- Can weights be zero or negative? (Zero yes, negative no, so Dijkstra is safe.)
- Are nodes 1-indexed? (Yes, size the arrays n + 1.)
- Duplicate edges or self-loops? (No duplicates per LC; the code handles them anyway.)

## Example Walkthrough
Extra case: `times = [[1,2,4],[1,3,1],[3,2,1],[2,4,1]], n = 4, k = 1`.
The direct edge 1→2 costs 4, but 1→3→2 costs 2. Then 2→4 makes node 4 reachable at 3. Distances: {1:0, 2:2, 3:1, 4:3}, so the answer is 3. A plain BFS that ignores weights would get this wrong.

## Approaches

### 1. Bellman-Ford: O(V·E) time, O(V) space
Relax every edge, n-1 rounds (stop early if a round changes nothing). Simple and handles negative weights, but slower.

### 2. Dijkstra ⭐ Go-to: O(E log V) time, O(V + E) space
Always expand the closest unsettled node; its distance is then final. Use a lazy heap: push on every improvement and skip stale entries on pop.
**Why it's the go-to:** it's the textbook answer for non-negative weights, and the lazy-heap version is about 15 lines.

## Dry Run (Approach 2)
Extra case above, k = 1. dist shown as [d1, d2, d3, d4].

| pop | stale? | relax | dist after | heap after |
|-----|--------|-------|------------|------------|
| (0,1) | no | 1→2: 4, 1→3: 1 | [0,4,1,∞] | (1,3), (4,2) |
| (1,3) | no | 3→2: 2 < 4 | [0,2,1,∞] | (2,2), (4,2) |
| (2,2) | no | 2→4: 3 | [0,2,1,3] | (3,4), (4,2) |
| (3,4) | no | none | [0,2,1,3] | (4,2) |
| (4,2) | yes, 4 > 2 | skip | | empty |

max(dist) = **3**.

## Edge Case Check
- Unreachable node (example 3): distance stays ∞ → -1. ✅
- n = 1: dist = [0], so the answer is 0. ✅
- Zero-weight edges: Dijkstra still correct (non-negative). ✅

## ⚠️ Pitfalls
- **Returning the distance to one node** instead of the max over all nodes.
- **Not skipping stale heap entries**: still correct but re-relaxes edges, which costs time.
- **C++ `INT_MAX + w` overflow** in Bellman-Ford: check `dist[u] != INT_MAX` first.
- **1-indexed nodes**: arrays of size n + 1, and take the max over indices 1..n only (index 0 would stay ∞ and force -1).

## 🎯 What the Interviewer Wants
- Recognize "time for all to receive" = max shortest distance.
- Name Dijkstra and why non-negative weights matter.
- Write the heap version cleanly, with the stale-entry check, and state O(E log V).

## Follow-ups
- **At most k edges allowed:** [LC 0787 Cheapest Flights Within K Stops](../0787-cheapest-flights-within-k-stops/)
- **Path cost is the max cell, not the sum:** [LC 0778 Swim in Rising Water](../0778-swim-in-rising-water/)
- **Maximize a product of probabilities:** LC 1514 Path with Maximum Probability (not added yet). Same Dijkstra with a max-heap.
- **Negative weights?** Bellman-Ford, which can also detect negative cycles.
