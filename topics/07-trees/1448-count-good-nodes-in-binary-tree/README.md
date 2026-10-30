---
number: 1448
title: Count Good Nodes in Binary Tree
difficulty: Medium
topic: Trees
pattern: DFS with path max
link: https://leetcode.com/problems/count-good-nodes-in-binary-tree/
lists: [NeetCode 150]
followup_of: []
related: ["0112 Path Sum", "0129 Sum Root to Leaf Numbers", "0098 Validate Binary Search Tree"]
---

# 1448. Count Good Nodes in Binary Tree

## ⚡ 30-Second Summary
**Pattern:** DFS carrying the max value on the path from the root
**Key insight:** A node is "good" if no node above it on its root path is larger. So pass down the max seen so far; a node is good iff val ≥ that max, and the max for its children is max(max, val).
**Go-to:** Preorder DFS with path max, O(n) time, O(h) space

## Problem
A node X is good if, on the path from the root to X, no node has a value greater than X. Count the good nodes.

**Examples:**
```
Input:  root = [3,1,4,3,null,1,5]
Output: 4
Why:    The root 3, the 4, the 5, and the lower 3 (path 3 → 1 → 3) are good.

Input:  root = [3,3,null,4,2]
Output: 3
Why:    3, 3 and 4 are good; 2 is below a 3.

Input:  root = [1]
Output: 1
Why:    The root is always good.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵; values in ±10⁴.

## Hints
<details><summary>Hint 1</summary>
What do you need to know about the path above a node to decide if it's good?
</details>
<details><summary>Hint 2</summary>
Only the maximum value on that path.
</details>
<details><summary>Hint 3</summary>
dfs(node, maxSoFar): good = val ≥ maxSoFar; recurse with max(maxSoFar, val); return good + left + right.
</details>

## Clarifying Questions
- Equal values count as good? (Yes, "no node greater".)
- Is the root good? (Always.)

## Example Walkthrough
`[3,1,4,3,null,1,5]`: 3 (max 3) good; 1 (max 3) no; 3 under 1 (max 3) good; 4 (max 3) good; 1 under 4 (max 4) no; 5 (max 4) good → 4.

## Approaches

### 1. Preorder DFS With Path Max ⭐ Go-to: O(n) time, O(h) space
**Why it's the go-to:** one parameter carries all the needed context.

### 2. BFS With (node, maxSoFar) Pairs: O(n) time, O(w) space
Same idea iteratively; avoids recursion depth on a 10⁵-node chain (important in Python).

## Dry Run (Approach 1)
`[3,3,null,4,2]`

| node | maxSoFar | good? | max for children |
|------|----------|-------|------------------|
| 3 (root) | -∞ | yes | 3 |
| 3 | 3 | yes | 3 |
| 4 | 3 | yes | 4 |
| 2 | 3 | no | 3 |
| total | | **3** | |

## Edge Case Check
- Single node: 1. ✅
- Equal values down a path: all good (≥). ✅
- Strictly decreasing chain: only the root is good. ✅

## ⚠️ Pitfalls
- **Using `>` instead of `≥`**: equal values are good.
- **Starting maxSoFar at 0**: values can be negative. Start at the root's value or -∞.
- **Python recursion depth** on a skewed 10⁵-node tree: use the BFS version.

## 🎯 What the Interviewer Wants
- Recognise "state passed down the path" as the DFS parameter.
- Explain the difference between top-down state (path max) and bottom-up results (counts).

## Follow-ups
- **Path sums instead of maxima:** [LC 0112 Path Sum](../0112-path-sum/)
- **Bounds passed down:** [LC 0098 Validate Binary Search Tree](../0098-validate-binary-search-tree/)
