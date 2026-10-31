---
number: 261
title: Graph Valid Tree
difficulty: Medium
topic: Graphs
pattern: n-1 edges + connected
link: https://leetcode.com/problems/graph-valid-tree/
lists: [NeetCode 150]
followup_of: []
related: ["0323 Number of Connected Components in an Undirected Graph", "0684 Redundant Connection", "0207 Course Schedule"]
---

# 0261. Graph Valid Tree

## ⚡ 30-Second Summary
**Pattern:** Tree = connected + acyclic, equivalently exactly n - 1 edges + no cycle
**Key insight:** An undirected graph on n nodes is a tree iff it has exactly n - 1 edges and no cycle (or n - 1 edges and connected). Check the count first, then Union-Find: an edge whose ends already share a root closes a cycle.
**Go-to:** Edge count + Union-Find, O(n + E · α(n)) time, O(n) space

## Problem
Given n nodes labeled 0..n-1 and a list of undirected edges, decide whether they form a valid tree (LeetCode Premium). [LeetCode](https://leetcode.com/problems/graph-valid-tree/)

**Examples:**
```
Input:  n = 5, edges = [[0,1],[0,2],[0,3],[1,4]]
Output: true
Why:    4 edges for 5 nodes, all reachable from 0, no loop.

Input:  n = 5, edges = [[0,1],[1,2],[2,3],[1,3],[1,4]]
Output: false
Why:    5 edges for 5 nodes is one too many; 1-2-3-1 is a cycle.
```

**Constraints:**
- 1 ≤ n ≤ 2000, up to 5000 edges, no self-loops or duplicate edges.

## Hints
<details><summary>Hint 1</summary>
What two properties make a graph a tree?
</details>
<details><summary>Hint 2</summary>
How many edges must a tree on n nodes have? What does that count alone rule out?
</details>
<details><summary>Hint 3</summary>
If edges ≠ n - 1 return false. Otherwise union each edge; if both ends already share a root, it's a cycle → false. Else true.
</details>

## Clarifying Questions
- Undirected? (Yes, [0,1] and [1,0] are the same edge.)
- Duplicate edges or self-loops? (No.)
- n = 1 with no edges? (A single node is a tree: true.)

## Example Walkthrough
Example 1: 4 = n - 1 edges. Union 0-1, 0-2, 0-3, 1-4: each joins two different sets → no cycle → true.
Example 2: 5 edges ≠ 4 → false right away.

## Approaches

### 1. DFS Connectivity + Edge Count: O(n + E) time, O(n + E) space
If edges ≠ n - 1, false. Else DFS from 0 and check all n nodes are reached. (With n - 1 edges, connected ⇔ acyclic.)

### 2. Edge Count + Union-Find ⭐ Go-to: O(n + E · α(n)) time, O(n) space
Count check, then union every edge; a failed union means a cycle.
**Why it's the go-to:** no adjacency list, no recursion, and the failed-union idea carries over to 0684 and 0323.

## Dry Run (Approach 2)
`n = 4, edges = [[0,1],[1,2],[2,0]]`: 3 = n - 1 edges, so the count check passes, but node 3 is isolated and 0-1-2 is a cycle.

| edge | find(a) | find(b) | action | sets |
|------|---------|---------|--------|------|
| 0-1 | 0 | 1 | union | {0,1} {2} {3} |
| 1-2 | 0 | 2 | union | {0,1,2} {3} |
| 2-0 | 0 | 0 | same root → **cycle, false** | |

## Edge Case Check
- n = 1, no edges: count 0 = n - 1, nothing to union → true. ✅
- Disconnected forest, `n = 4, [[0,1],[2,3]]`: 2 ≠ 3 edges → false. ✅
- Right count but cycle + isolated node: caught by the union check (above). ✅

## ⚠️ Pitfalls
- **Only checking for cycles**: a forest with no cycles but 2 components isn't a tree. The edge count fixes it.
- **Only checking connectivity** without the count: a connected graph with a cycle passes.
- **DFS on an undirected graph without a parent check** sees the edge back to the parent as a cycle (if you detect cycles with DFS).

## 🎯 What the Interviewer Wants
- The definition of a tree in graph terms and the n - 1 edge shortcut.
- Union-Find (or DFS) implemented cleanly, with path compression.

## Follow-ups
- **Count the components instead:** [LC 0323 Number of Connected Components](../0323-number-of-connected-components-in-an-undirected-graph/)
- **Find the edge that makes the cycle:** [LC 0684 Redundant Connection](../0684-redundant-connection/)
- **Directed version (rooted tree):** LC 0685 Redundant Connection II (not added yet)
