---
number: 323
title: Number of Connected Components in an Undirected Graph
difficulty: Medium
topic: Graphs
pattern: Union-Find / DFS
link: https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/
lists: [NeetCode 150]
followup_of: []
related: ["0200 Number of Islands", "0261 Graph Valid Tree", "0547 Number of Provinces", "0684 Redundant Connection"]
---

# 0323. Number of Connected Components in an Undirected Graph

## ⚡ 30-Second Summary
**Pattern:** Union-Find (or DFS) counting components
**Key insight:** Start with n components, one per node. Every edge that joins two *different* components merges them, so count drops by one; an edge inside a component changes nothing. The final count is the answer.
**Go-to:** Union-Find with a running count, O(n + E · α(n)) time, O(n) space

## Problem
Given n nodes 0..n-1 and a list of undirected edges, return how many connected components the graph has (LeetCode Premium). [LeetCode](https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/)

**Examples:**
```
Input:  n = 5, edges = [[0,1],[1,2],[3,4]]
Output: 2
Why:    {0,1,2} and {3,4}.

Input:  n = 5, edges = [[0,1],[1,2],[2,3],[3,4]]
Output: 1
Why:    A single chain through all five nodes.
```

**Constraints:**
- 1 ≤ n ≤ 2000, up to 5000 edges, no duplicates or self-loops.

## Hints
<details><summary>Hint 1</summary>
If there were no edges, how many components would there be?
</details>
<details><summary>Hint 2</summary>
When does adding an edge reduce that number, and when doesn't it?
</details>
<details><summary>Hint 3</summary>
count = n. For each edge, if find(a) ≠ find(b), union them and count--. Return count.
</details>

## Clarifying Questions
- Isolated nodes count as components? (Yes, each is its own.)
- Undirected, no duplicates? (Yes.)

## Example Walkthrough
Example 1: count 5. Edge 0-1 merges → 4. Edge 1-2 merges → 3. Edge 3-4 merges → 2.

## Approaches

### 1. DFS from Each Unvisited Node: O(n + E) time, O(n + E) space
Build an adjacency list; each DFS started from an unvisited node is a new component.

### 2. Union-Find with Count ⭐ Go-to: O(n + E · α(n)) time, O(n) space
Decrement on every successful union.
**Why it's the go-to:** no adjacency list, works when edges stream in, and the same DSU solves 0261 and 0684.

## Dry Run (Approach 2)
`n = 5, edges = [[0,1],[1,2],[3,4]]` (union by rank)

| edge | find(a), find(b) | merged? | parent after | count |
|------|------------------|---------|--------------|-------|
| start | | | [0,1,2,3,4] | 5 |
| 0-1 | 0, 1 | yes | [0,0,2,3,4] | 4 |
| 1-2 | 0, 2 | yes | [0,0,0,3,4] | 3 |
| 3-4 | 3, 4 | yes | [0,0,0,3,3] | **2** |

## Edge Case Check
- No edges: n components. ✅
- Edge inside a component (cycle), `n = 4, [[0,1],[1,2],[2,0]]`: third union fails, count stays 2. ✅
- n = 1: 1. ✅

## ⚠️ Pitfalls
- **Decrementing on every edge**: only successful unions merge components.
- **Comparing `parent[a] == parent[b]`** instead of `find(a) == find(b)`: parents aren't roots.
- **No path compression / rank**: chains make `find` O(n).

## 🎯 What the Interviewer Wants
- Either method, with the "start at n, decrement on merge" reasoning for Union-Find.
- Clean DSU with path compression and union by rank.

## Follow-ups
- **Grid version:** [LC 0200 Number of Islands](../0200-number-of-islands/)
- **Is it a single tree?** [LC 0261 Graph Valid Tree](../0261-graph-valid-tree/)
- **Adjacency-matrix input:** LC 0547 Number of Provinces (not added yet)
