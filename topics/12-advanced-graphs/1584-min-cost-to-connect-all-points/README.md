---
number: 1584
title: Min Cost to Connect All Points
difficulty: Medium
topic: Advanced Graphs
pattern: MST (Prim's)
link: https://leetcode.com/problems/min-cost-to-connect-all-points/
lists: [NeetCode 150]
followup_of: []
related: ["0684 Redundant Connection", "1135 Connecting Cities With Minimum Cost", "0743 Network Delay Time"]
---

# 1584. Min Cost to Connect All Points

## ⚡ 30-Second Summary
**Pattern:** Minimum spanning tree on a complete graph
**Key insight:** "Connect everything at minimum total cost" is an MST. Every pair of points is an edge (E ≈ n²/2), so array-based Prim's at O(n²) beats sorting all edges.
**Go-to:** Prim's with a `dist` array, O(n²) time, O(n) space

## Problem
You get points on a 2-D plane. Connecting two points costs their Manhattan distance `|x1 - x2| + |y1 - y2|`. Return the minimum total cost so that every pair of points is connected by some path. [LeetCode](https://leetcode.com/problems/min-cost-to-connect-all-points/)

**Examples:**
```
Input:  points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
Output: 20
Why:    The MST uses edges of cost 4, 3, 4 and 9 (see the dry run).

Input:  points = [[3,12],[-2,5],[-4,1]]
Output: 18
Why:    (3,12)-(-2,5) costs 12 and (-2,5)-(-4,1) costs 6. The third edge (17) is not needed.
```

**Constraints:**
- 1 ≤ n ≤ 1000, so O(n²) ≈ 10⁶ work, fine. Edge lists hold ≈ 5·10⁵ edges.
- Coordinates in ±10⁶, so one distance ≤ 4·10⁶ fits in an int.
- Points are distinct.

## Hints
<details><summary>Hint 1</summary>
You want a set of edges that connects everything with minimum total weight and no cycles. What is that structure called?
</details>
<details><summary>Hint 2</summary>
Two classic algorithms build it: one sorts edges, one grows a tree from a start node. The graph here is complete. Which one avoids building all n² edges?
</details>
<details><summary>Hint 3</summary>
Prim's: keep `dist[v]` = cheapest edge from the current tree to v. Repeat n times: pick the unvisited v with the smallest dist, add it to the total, then update dist for every other unvisited point using the distance from v.
</details>

## Clarifying Questions
- Manhattan distance, not Euclidean? (Manhattan.)
- Only one point? (Cost 0.)
- Duplicate points? (No, all distinct.)
- Could the total overflow? (It's at most n-1 edges of ≤ 4·10⁶ each; real MSTs are far smaller. Use `long long` if unsure.)

## Example Walkthrough
Example 2: three points, three possible edges: A-B = 12, B-C = 6, A-C = 17. A tree on 3 nodes needs 2 edges. Take the two cheapest that don't form a cycle: 6 + 12 = 18.

## Approaches

### 1. Kruskal: O(n² log n) time, O(n²) space
Build all n(n-1)/2 edges, sort, add each edge whose endpoints are in different Union-Find components. Correct, but sorting half a million edges is heavy.

### 2. Prim with a Heap: O(n² log n) time, O(n²) space
Grow from point 0. Pop the cheapest edge into an unvisited point, then push edges from it to every unvisited point. Lazy heap, skip visited on pop.

### 3. Prim with an Array ⭐ Go-to: O(n²) time, O(n) space
Same as approach 2, but find the next point by a linear scan over `dist` instead of a heap. On a dense graph that scan is cheaper than heap operations.
**Why it's the go-to:** optimal for a complete graph, no heap and no edge list, and the loop is short.

## Dry Run (Approach 3)
Example 1. P0(0,0), P1(2,2), P2(3,10), P3(5,2), P4(7,0). dist = [d0..d4].

| step | pick u | dist[u] | total | dist after updating from u |
|------|--------|---------|-------|----------------------------|
| 1 | P0 | 0 | 0 | [–, 4, 13, 7, 7] |
| 2 | P1 | 4 | 4 | [–, –, 9, 3, 7] |
| 3 | P3 | 3 | 7 | [–, –, 9, –, 4] |
| 4 | P4 | 4 | 11 | [–, –, 9, –, –] |
| 5 | P2 | 9 | **20** | |

Note step 2: P4 stays at 7 because the distance from P1 (5 + 2 = 7) is no better.

## Edge Case Check
- One point: the loop picks P0 with dist 0 → 0. ✅
- Collinear or equal-distance ties: any tie break gives the same MST weight. ✅
- Negative coordinates (example 2): `abs` handles them. ✅

## ⚠️ Pitfalls
- **Using Euclidean distance**: the problem says Manhattan.
- **Kruskal without Union-Find** (or a cycle check) picks cycle edges.
- **Prim: forgetting to skip in-tree points** when updating or scanning.
- **Python heap version** builds O(n²) tuples; it can be slow on n = 1000. The array version is safer.

## 🎯 What the Interviewer Wants
- Recognize MST from "connect all with min total cost".
- Know both Prim's and Kruskal's, and say why array-based Prim's fits a complete graph.
- Clear complexity talk: E = O(n²), so O(n²) is optimal.

## Follow-ups
- **Explicit sparse edge list:** Kruskal or heap Prim's, e.g. LC 1135 Connecting Cities With Minimum Cost (not added yet)
- **Union-Find refresher:** [LC 0684 Redundant Connection](../../11-graphs/0684-redundant-connection/)
- **Shortest paths instead of a spanning tree:** [LC 0743 Network Delay Time](../0743-network-delay-time/). A shortest-path tree is not an MST.
