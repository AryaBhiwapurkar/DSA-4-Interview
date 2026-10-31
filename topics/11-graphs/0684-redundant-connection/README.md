---
number: 684
title: Redundant Connection
difficulty: Medium
topic: Graphs
pattern: Union-Find
link: https://leetcode.com/problems/redundant-connection/
lists: [NeetCode 150]
followup_of: []
related: ["0261 Graph Valid Tree", "0323 Number of Connected Components in an Undirected Graph", "0685 Redundant Connection II"]
---

# 0684. Redundant Connection

## ⚡ 30-Second Summary
**Pattern:** Union-Find cycle detection, edge by edge
**Key insight:** Add edges in input order. The first edge whose two endpoints are already connected closes the (only) cycle. Since all other cycle edges came before it, it is also the *last* cycle edge in the input, which is what the problem asks for.
**Go-to:** Union-Find, O(n · α(n)) time, O(n) space

## Problem
A tree on nodes 1..n had one extra edge added, giving n edges. Return an edge you can remove so the rest is a tree; if several work, return the one appearing last in the input. [LeetCode](https://leetcode.com/problems/redundant-connection/)

**Examples:**
```
Input:  edges = [[1,2],[1,3],[2,3]]
Output: [2,3]
Why:    1-2-3 is a triangle; any of its edges works, and [2,3] comes last.

Input:  edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
Output: [1,4]
Why:    The cycle is 1-2-3-4-1. [1,5] isn't on it, so the last cycle edge is [1,4].
```

**Constraints:**
- 3 ≤ n ≤ 1000, exactly n edges, no duplicates, the graph is connected.

## Hints
<details><summary>Hint 1</summary>
Adding one edge to a tree creates exactly one cycle. Which edges are candidates?
</details>
<details><summary>Hint 2</summary>
Build the graph edge by edge. When does an edge first close a cycle?
</details>
<details><summary>Hint 3</summary>
Union-Find: for each [a, b], if find(a) == find(b), return [a, b]; otherwise union them.
</details>

## Clarifying Questions
- Exactly one extra edge? (Yes.)
- Several answers: which one? (The last one in input order.)
- 1-indexed nodes? (Yes, size the DSU n + 1.)

## Example Walkthrough
Example 2: union 1-2, 2-3, 3-4 (all succeed, one set {1,2,3,4}). Edge 1-4: both already in the same set → answer [1,4]. Edge 1-5 is never reached.

## Approaches

### 1. DFS Before Each Edge: O(n²) time, O(n) space
For each edge [a, b], DFS in the graph built so far; if b is already reachable from a, return it. Otherwise add the edge.

### 2. Union-Find ⭐ Go-to: O(n · α(n)) time, O(n) space
First failed union is the answer.
**Why it's the go-to:** near-linear, tiny code, and the "first failure = last cycle edge" argument is easy to state.

## Dry Run (Approach 2)
`edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]`

| edge | find(a) | find(b) | action | sets |
|------|---------|---------|--------|------|
| 1-2 | 1 | 2 | union | {1,2} |
| 2-3 | 1 | 3 | union | {1,2,3} |
| 3-4 | 1 | 4 | union | {1,2,3,4} |
| 1-4 | 1 | 1 | same root → **return [1,4]** | |

## Edge Case Check
- Extra edge is the last edge: found on the final union. ✅
- Cycle edge appears early, non-cycle edges after it: the answer is still the last *cycle* edge (example 2). ✅

## ⚠️ Pitfalls
- **DSU sized n instead of n + 1** with 1-indexed labels.
- **Comparing `parent[a] == parent[b]`** instead of their roots misses cycles once trees get deeper than one level.
- **Directed version** (0685) needs in-degree handling; this approach alone is wrong there.

## 🎯 What the Interviewer Wants
- Union-Find with path compression and rank.
- Why the first failure matches "last in input".

## Follow-ups
- **Directed graph:** LC 0685 Redundant Connection II (not added yet)
- **Check the whole graph is a tree:** [LC 0261 Graph Valid Tree](../0261-graph-valid-tree/)
