---
number: 236
title: Lowest Common Ancestor of a Binary Tree
difficulty: Medium
topic: Trees
pattern: Postorder DFS
link: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
lists: [LC Top Interview 150]
followup_of: ["0235 Lowest Common Ancestor of a Binary Search Tree"]
related: ["0235 Lowest Common Ancestor of a Binary Search Tree", "1650 Lowest Common Ancestor of a Binary Tree III", "1123 Lowest Common Ancestor of Deepest Leaves"]
---

# 0236. Lowest Common Ancestor of a Binary Tree

## ⚡ 30-Second Summary
**Pattern:** Postorder DFS that reports "found p, q, or their LCA"
**Key insight:** dfs(node) returns p or q if one is in its subtree (or the node itself is one), or null otherwise. If both children return non-null, p and q are on different sides, so this node is the LCA. If only one side returns non-null, pass it up.
**Go-to:** Recursive postorder, O(n) time, O(h) space

## Problem
Given a binary tree (not a BST) and two distinct nodes p and q in it, return their lowest common ancestor (a node may be its own ancestor). [LeetCode](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/)

**Examples:**
```
Input:  root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Why:    5 and 1 are on different sides of the root.

Input:  root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Why:    4 is a descendant of 5, and 5 is its own ancestor.

Input:  root = [1,2], p = 1, q = 2
Output: 1
Why:    The root is one of them.
```

**Constraints:**
- 2 ≤ n ≤ 10⁵; values unique; p ≠ q; both exist.

## Hints
<details><summary>Hint 1</summary>
Without ordering, you can't know which side to go. What can each subtree tell its parent?
</details>
<details><summary>Hint 2</summary>
"I contain p", "I contain q", "I contain both", or "neither".
</details>
<details><summary>Hint 3</summary>
If node is null, p, or q → return node. L = dfs(left), R = dfs(right). If both non-null → node. Else return whichever is non-null.
</details>

## Clarifying Questions
- BST? (No, general binary tree.)
- Both nodes exist? (Yes. If not guaranteed, track counts separately.)

## Example Walkthrough
p = 5, q = 4: dfs(5) returns 5 immediately (node is p) without exploring below. At 3: left returns 5, right (subtree 1) returns null → answer 5. That's correct because q must be under p.

## Approaches

### 1. Parent Pointers + Ancestor Set: O(n) time, O(n) space
BFS/DFS to record each node's parent; walk up from p into a set; walk up from q until hitting the set.

### 2. Recursive Postorder ⭐ Go-to: O(n) time, O(h) space
**Why it's the go-to:** short, one pass, no extra maps.

## Dry Run (Approach 2)
`[3,5,1,6,2,0,8,null,null,7,4]`, p = 5, q = 1

| node | L | R | returns |
|------|---|---|---------|
| 5 | (is p) | | 5 |
| 1 | (is q) | | 1 |
| 3 | 5 | 1 | **3** (both sides non-null) |

## Edge Case Check
- One node is the other's ancestor: returned on the way up. ✅
- p or q is the root: returned immediately. ✅

## ⚠️ Pitfalls
- **Assuming both exist when they might not**: the early return on p would wrongly report p.
- **Comparing values instead of nodes** is fine only because values are unique.
- **Python recursion depth** on a 10⁵-node chain: use the parent-pointer version.

## 🎯 What the Interviewer Wants
- The return-value contract stated clearly.
- Compare with the BST version (0235), which uses ordering for O(h).

## Follow-ups
- **BST version:** [LC 0235 Lowest Common Ancestor of a Binary Search Tree](../0235-lowest-common-ancestor-of-a-binary-search-tree/)
- **Nodes with parent pointers:** two-pointer walk like linked-list intersection: LC 1650 Lowest Common Ancestor of a Binary Tree III (not added yet)
- **LCA of the deepest leaves:** return (depth, lca) pairs: LC 1123 Lowest Common Ancestor of Deepest Leaves (not added yet)
