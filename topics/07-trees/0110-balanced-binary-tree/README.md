---
number: 110
title: Balanced Binary Tree
difficulty: Easy
topic: Trees
pattern: DFS height with early exit
link: https://leetcode.com/problems/balanced-binary-tree/
lists: [NeetCode 150]
followup_of: ["0104 Maximum Depth of Binary Tree"]
related: ["0104 Maximum Depth of Binary Tree", "0543 Diameter of Binary Tree", "1382 Balance a Binary Search Tree"]
---

# 0110. Balanced Binary Tree

## ⚡ 30-Second Summary
**Pattern:** Bottom-up height with a sentinel for "unbalanced"
**Key insight:** A tree is height-balanced if, at every node, the subtree heights differ by at most 1. Compute heights bottom-up and return -1 as soon as any subtree is unbalanced, so each node is visited once.
**Go-to:** Bottom-up DFS returning height or -1, O(n) time, O(h) space

## Problem
Return whether a binary tree is height-balanced: for every node, the heights of its left and right subtrees differ by no more than one. [LeetCode](https://leetcode.com/problems/balanced-binary-tree/)

**Examples:**
```
Input:  root = [3,9,20,null,null,15,7]
Output: true
Why:    At the root the heights are 1 and 2; every other node is fine too.

Input:  root = [1,2,2,3,3,null,null,4,4]
Output: false
Why:    At the root the heights are 3 (left) and 1 (right).

Input:  root = []
Output: true
Why:    An empty tree is balanced.
```

**Constraints:**
- 0 ≤ n ≤ 5000.

## Hints
<details><summary>Hint 1</summary>
Checking the root alone isn't enough. Every node must satisfy the rule.
</details>
<details><summary>Hint 2</summary>
Calling height() from every node is O(n²). Can one bottom-up pass both compute heights and check balance?
</details>
<details><summary>Hint 3</summary>
Return -1 for "unbalanced". If either child returns -1, or |L - R| > 1, return -1. Else return 1 + max(L, R).
</details>

## Clarifying Questions
- Balance checked at every node, not just the root? (Every node.)
- Empty tree? (Balanced.)

## Example Walkthrough
`[1,2,2,3,3,null,null,4,4]`: h(4) = 1, h(3 with 4s) = 2, h(other 3) = 1 → h(left 2) = 3; h(right 2) = 1. At the root |3 - 1| = 2 > 1 → false.

## Approaches

### 1. Top-Down: O(n²) worst case, O(h) space
At each node compare height(left) and height(right), then recurse into both children. Heights get recomputed many times on skewed trees.

### 2. Bottom-Up With -1 Sentinel ⭐ Go-to: O(n) time, O(h) space
One pass; -1 propagates up immediately.
**Why it's the go-to:** linear, and the "-1 means failure" trick is reusable.

## Dry Run (Approach 2)
`[3,9,20,null,null,15,7]`

| node | L | R | \|L-R\| | returns |
|------|---|---|-------|---------|
| 9 | 0 | 0 | 0 | 1 |
| 15, 7 | 0 | 0 | 0 | 1 |
| 20 | 1 | 1 | 0 | 2 |
| 3 | 1 | 2 | 1 | 3 → **true** |

## Edge Case Check
- Empty: true. ✅
- Chain of 3 nodes: at the top |2 - 0| = 2 → false. ✅
- Root balanced but a subtree isn't: -1 bubbles up. ✅

## ⚠️ Pitfalls
- **Only checking the root**: `[1,2,2,3,null,null,3,4,null,null,4]` has equal root heights but unbalanced subtrees.
- **Forgetting to propagate -1** from a child.
- **Confusing with "complete" or "full"** trees: different definitions.

## 🎯 What the Interviewer Wants
- Spot the O(n²) top-down approach and improve it.
- A clean sentinel or (balanced, height) pair return.

## Follow-ups
- **Rebalance a BST:** inorder to an array, rebuild from the middle: LC 1382 Balance a Binary Search Tree (not added yet)
- **Heights only:** [LC 0104 Maximum Depth of Binary Tree](../0104-maximum-depth-of-binary-tree/)
- **Same bottom-up shape, different metric:** [LC 0543 Diameter of Binary Tree](../0543-diameter-of-binary-tree/)
