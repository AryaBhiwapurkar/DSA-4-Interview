---
number: 543
title: Diameter of Binary Tree
difficulty: Easy
topic: Trees
pattern: DFS height, update global
link: https://leetcode.com/problems/diameter-of-binary-tree/
lists: [NeetCode 150]
followup_of: ["0104 Maximum Depth of Binary Tree"]
related: ["0104 Maximum Depth of Binary Tree", "0124 Binary Tree Maximum Path Sum", "1245 Tree Diameter"]
---

# 0543. Diameter of Binary Tree

## ⚡ 30-Second Summary
**Pattern:** DFS returns height; a global tracks the best path through each node
**Key insight:** The longest path that "bends" at a node has length height(left) + height(right) (in edges). The DFS returns height upward but records left + right at every node.
**Go-to:** Single DFS with a global max, O(n) time, O(h) space

## Problem
Return the number of edges on the longest path between any two nodes. The path doesn't have to go through the root. [LeetCode](https://leetcode.com/problems/diameter-of-binary-tree/)

**Examples:**
```
Input:  root = [1,2,3,4,5]
Output: 3
Why:    4 → 2 → 1 → 3 (or 5 → 2 → 1 → 3) has 3 edges.

Input:  root = [1,2]
Output: 1
Why:    One edge.
```

**Constraints:**
- 1 ≤ n ≤ 10⁴.

## Hints
<details><summary>Hint 1</summary>
Every path has a highest node where it bends. What's the longest path bending at a given node?
</details>
<details><summary>Hint 2</summary>
left height + right height. Computing heights separately for every node is O(n²). Can one DFS give both?
</details>
<details><summary>Hint 3</summary>
DFS returns 1 + max(L, R) (height in nodes) and updates best = max(best, L + R).
</details>

## Clarifying Questions
- Edges or nodes? (Edges.)
- Must it pass through the root? (No.)

## Example Walkthrough
`[1,2,3,4,5]`: h(4) = h(5) = 1, h(2) = 2 with best = 1 + 1 = 2; h(3) = 1; at 1: best = 2 + 1 = 3.

## Approaches

### 1. Height Per Node: O(n²) worst case, O(h) space
For each node compute height(left) + height(right) with a separate height function.

### 2. Single DFS With Global Max ⭐ Go-to: O(n) time, O(h) space
Return height, update the answer on the way up.
**Why it's the go-to:** linear, and it's the template for 0124 and many "path in tree" problems.

## Dry Run (Approach 2)
`[1,2,3,4,5]`

| node | L | R | best = max(best, L+R) | returns 1+max(L,R) |
|------|---|---|-----------------------|--------------------|
| 4 | 0 | 0 | 0 | 1 |
| 5 | 0 | 0 | 0 | 1 |
| 2 | 1 | 1 | 2 | 2 |
| 3 | 0 | 0 | 2 | 1 |
| 1 | 2 | 1 | **3** | 3 |

## Edge Case Check
- Single node: 0. ✅
- Longest path not through the root (big left subtree, tiny right): the global catches it lower down. ✅

## ⚠️ Pitfalls
- **Returning L + R** instead of the height: the parent needs a single branch.
- **Counting nodes** instead of edges (off by one).
- **Only checking the root**: misses paths in subtrees.

## 🎯 What the Interviewer Wants
- The "return one thing, record another" pattern.
- O(n) instead of the O(n²) height-per-node approach.

## Follow-ups
- **Weighted, possibly negative values:** [LC 0124 Binary Tree Maximum Path Sum](../0124-binary-tree-maximum-path-sum/)
- **General tree / graph:** two BFS passes: LC 1245 Tree Diameter (not added yet)
- **Height only:** [LC 0104 Maximum Depth of Binary Tree](../0104-maximum-depth-of-binary-tree/)
