---
number: 199
title: Binary Tree Right Side View
difficulty: Medium
topic: Trees
pattern: BFS, last per level
link: https://leetcode.com/problems/binary-tree-right-side-view/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: ["0102 Binary Tree Level Order Traversal"]
related: ["0102 Binary Tree Level Order Traversal", "0116 Populating Next Right Pointers in Each Node"]
---

# 0199. Binary Tree Right Side View

## ⚡ 30-Second Summary
**Pattern:** Level order, keep the last node of each level
**Key insight:** Standing on the right, you see exactly one node per level: the rightmost one. It isn't always in the right subtree (a deeper left branch shows through when the right side is shorter).
**Go-to:** BFS by level, record the last node, O(n) time, O(w) space

## Problem
Return the values visible when looking at the tree from the right side, top to bottom. [LeetCode](https://leetcode.com/problems/binary-tree-right-side-view/)

**Examples:**
```
Input:  root = [1,2,3,null,5,null,4]
Output: [1,3,4]
Why:    The rightmost node of each level is 1, 3 and 4.

Input:  root = [1,2,3,4,null,null,null,5]
Output: [1,3,4,5]
Why:    Levels 3 and 4 exist only on the left, so their nodes are visible.

Input:  root = [1,null,3]
Output: [1,3]
Why:    A right chain.

Input:  root = []
Output: []
Why:    Nothing to see.
```

**Constraints:**
- 0 ≤ n ≤ 100.

## Hints
<details><summary>Hint 1</summary>
Is the answer simply "walk right children from the root"? Try example 2.
</details>
<details><summary>Hint 2</summary>
You need one node per level: which one?
</details>
<details><summary>Hint 3</summary>
BFS by level and take the last node; or DFS visiting right first and record the first node seen at each new depth.
</details>

## Clarifying Questions
- One value per level, top to bottom? (Yes.)
- Empty tree? (Return [].)

## Example Walkthrough
`[1,2,3,4,null,null,null,5]`: levels [1], [2,3], [4], [5] → last of each: 1, 3, 4, 5.

## Approaches

### 1. BFS, Last per Level ⭐ Go-to: O(n) time, O(w) space
**Why it's the go-to:** a one-line change to 0102 and easy to justify.

### 2. DFS Right-First: O(n) time, O(h) space
Visit right before left; the first node reached at each depth (depth == len(res)) is the visible one.

## Dry Run (Approach 1)
`[1,2,3,null,5,null,4]`

| level | nodes | last |
|-------|-------|------|
| 0 | 1 | 1 |
| 1 | 2, 3 | 3 |
| 2 | 5, 4 | 4 |

## Edge Case Check
- Left-only deep branch: BFS still sees it. ✅
- Empty tree: []. ✅

## ⚠️ Pitfalls
- **Only following right children**: fails example 2.
- **DFS left-first** with "first seen per depth" gives the left view instead.

## 🎯 What the Interviewer Wants
- Catch the "right child isn't always visible" trap.
- Either BFS or right-first DFS, explained.

## Follow-ups
- **Left side view:** take the first node per level (or DFS left-first).
- **Level order itself:** [LC 0102 Binary Tree Level Order Traversal](../0102-binary-tree-level-order-traversal/)
- **Link each node to its right neighbour:** [LC 0117 Populating Next Right Pointers in Each Node II](../0117-populating-next-right-pointers-in-each-node-ii/)
