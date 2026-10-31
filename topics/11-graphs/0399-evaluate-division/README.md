---
number: 399
title: Evaluate Division
difficulty: Medium
topic: Graphs
pattern: Weighted graph DFS / weighted Union-Find
link: https://leetcode.com/problems/evaluate-division/
lists: [LC Top Interview 150]
followup_of: []
related: ["0323 Number of Connected Components in an Undirected Graph", "0684 Redundant Connection", "0990 Satisfiability of Equality Equations"]
---

# 0399. Evaluate Division

## ⚡ 30-Second Summary
**Pattern:** Weighted directed graph, path product
**Key insight:** `a / b = k` is an edge a → b with weight k and an edge b → a with weight 1/k. Then `x / y` is the product of weights along any path from x to y (ratios telescope: x/m · m/y = x/y). No path or unknown variable → -1.
**Go-to:** DFS per query multiplying weights, O(Q · (V + E)) time, O(V + E) space

## Problem
You get equations like "a / b = 2.0" and queries like "a / c = ?". Answer each query from the equations, or -1.0 if it can't be determined (including any variable never seen). Equations are consistent and no division by zero occurs. [LeetCode](https://leetcode.com/problems/evaluate-division/)

**Examples:**
```
Input:  equations = [["a","b"],["b","c"]], values = [2.0,3.0],
        queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
Why:    a/c = a/b · b/c = 6; b/a flips 2 to 0.5; "e" and "x" never appear, so even x/x is unknown.

Input:  equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0],
        queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
Output: [3.75000,0.40000,5.00000,0.20000]
Why:    1.5 · 2.5 = 3.75 and 1/2.5 = 0.4; "bc" and "cd" are just variable names.

Input:  equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
Output: [0.50000,2.00000,-1.00000,-1.00000]
Why:    Direct, inverse, then two queries with an unknown variable.
```

**Constraints:**
- Up to 20 equations and 20 queries; variable names up to 5 letters; values in (0, 20].
- Tiny input, so a DFS per query is plenty.

## Hints
<details><summary>Hint 1</summary>
Draw each variable as a node. What does "a / b = 2" look like as edges?
</details>
<details><summary>Hint 2</summary>
If a/b and b/c are known, how do you get a/c? What does that mean along a path?
</details>
<details><summary>Hint 3</summary>
Add a→b (k) and b→a (1/k). For each query, if either variable is unknown return -1; else DFS from x carrying the running product, return it on reaching y, -1 if y is unreachable.
</details>

## Clarifying Questions
- Unknown variable, even `x / x`? (-1.0.)
- Known variable divided by itself? (1.0.)
- Can equations contradict each other? (No, assume consistent.)

## Example Walkthrough
Example 1: edges a→b 2, b→a 0.5, b→c 3, c→b 1/3. Query a/c: a → b (×2) → c (×3) = 6. Query b/a: one edge, 0.5. Query a/e: e unknown → -1.

## Approaches

### 1. DFS per Query ⭐ Go-to: O(Q · (V + E)) time, O(V + E) space
Search from the numerator to the denominator, multiplying edge weights.
**Why it's the go-to:** the graph model is the whole insight, and the code is a plain DFS.

### 2. Weighted Union-Find: O((E + Q) · α) time, O(V) space
Each node stores `weight[x] = x / parent[x]`. `find` compresses paths while multiplying weights, so after it `weight[x] = x / root`. Union a/b = k by attaching root(a) under root(b) with weight `k · w_b / w_a`. Query x/y: same root → `w_x / w_y`, else -1. Best when queries are many.

## Dry Run (Approach 1)
Example 1, query `a / c`

| node | product so far | neighbours (weight) | action |
|------|----------------|---------------------|--------|
| a | 1 | b (2) | visit b |
| b | 2 | a (0.5) visited, c (3) | visit c |
| c | 6 | | c is the target → **6.0** |

## Edge Case Check
- `x / x` with x unknown: -1 (check existence first). ✅
- `a / a` with a known: DFS starts at the target → 1.0. ✅
- Variables in different components: DFS exhausts → -1. ✅

## ⚠️ Pitfalls
- **Returning 1.0 for an unknown x / x**: test membership before the "same node" shortcut.
- **Only adding one direction** per equation: b/a becomes unreachable.
- **No visited set**: the reverse edges create 2-cycles, so DFS loops forever.
- **C++ `adj[x]` on a missing key** inserts it, which can make an unknown variable look known; use `count` first.

## 🎯 What the Interviewer Wants
- The modelling step: ratios as weighted edges, answer = path product.
- Correct -1 handling.
- Knowing weighted Union-Find as the follow-up for heavy query loads.

## Follow-ups
- **Many queries:** weighted Union-Find (approach 2) or precompute all pairs with Floyd-Warshall (V ≤ 40).
- **Equality / inequality constraints only:** LC 0990 Satisfiability of Equality Equations (not added yet), plain Union-Find.
