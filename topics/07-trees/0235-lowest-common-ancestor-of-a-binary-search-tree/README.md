---
number: 235
title: Lowest Common Ancestor of a Binary Search Tree
difficulty: Medium
topic: Trees
pattern: BST split point
link: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
lists: [NeetCode 150]
followup_of: []
related: ["0236 Lowest Common Ancestor of a Binary Tree", "0098 Validate Binary Search Tree", "1650 Lowest Common Ancestor of a Binary Tree III"]
---

# 0235. Lowest Common Ancestor of a Binary Search Tree

## ⚡ 30-Second Summary
**Pattern:** Walk down the BST to the split point
**Key insight:** If both p and q are smaller than the node, the LCA is in the left subtree; if both are larger, it's in the right. Otherwise they split here (or one of them is this node), so this node is the LCA.
**Go-to:** Iterative descent, O(h) time, O(1) space

## Problem
Given a BST and two nodes p and q in it, return their lowest common ancestor: the deepest node that has both as descendants (a node counts as its own descendant).

**Examples:**
```
Input:  root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
Output: 6
Why:    2 is left of 6 and 8 is right of 6: they split at the root.

Input:  root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
Output: 2
Why:    4 is inside 2's subtree, and 2 counts as its own ancestor.

Input:  root = [2,1], p = 2, q = 1
Output: 2
Why:    The root is one of the two nodes.
```

**Constraints:**
- 2 ≤ n ≤ 10⁵; values unique; p ≠ q; both exist in the tree.

## Hints
<details><summary>Hint 1</summary>
The BST property tells you which side each of p and q is on. When must the LCA be the current node?
</details>
<details><summary>Hint 2</summary>
When p and q aren't on the same strict side.
</details>
<details><summary>Hint 3</summary>
Loop: if both < node, go left; if both > node, go right; else return node.
</details>

## Clarifying Questions
- Are p and q guaranteed to exist? (Yes.)
- Unique values? (Yes.)
- Can p be an ancestor of q? (Yes, then p is the answer.)

## Example Walkthrough
p = 3, q = 5 in the first tree: 6 → both smaller → go to 2 → both larger → go to 4 → 3 < 4 < 5, split → 4.

## Approaches

### 1. Recursive Descent: O(h) time, O(h) stack
Same logic with recursion.

### 2. Iterative Descent ⭐ Go-to: O(h) time, O(1) space
A simple while loop.
**Why it's the go-to:** constant space, no recursion, and it uses the BST property fully. (The general 0236 postorder also works but ignores the ordering.)

## Dry Run (Approach 2)
`p = 2, q = 4`

| node | p, q vs node | action |
|------|--------------|--------|
| 6 | both smaller | go left |
| 2 | p == node | **return 2** |

## Edge Case Check
- One node is the ancestor of the other: returned as soon as reached. ✅
- p and q on opposite sides of the root: returns the root. ✅

## ⚠️ Pitfalls
- **Using ≤ / ≥ in the "go left/right" checks**: if p equals the node, you must stop here, not move.
- **Comparing node pointers instead of values** when p/q come from different copies (on LeetCode they're real nodes, so values are fine).
- **Ignoring the BST property** and running the general O(n) algorithm: works, but misses the point.

## 🎯 What the Interviewer Wants
- Use the BST ordering to get O(h).
- Iterative, O(1) space.

## Follow-ups
- **General binary tree (no ordering):** [LC 0236 Lowest Common Ancestor of a Binary Tree](../0236-lowest-common-ancestor-of-a-binary-tree/)
- **Nodes have parent pointers:** like intersecting two linked lists: LC 1650 Lowest Common Ancestor of a Binary Tree III (not added yet)
- **Many queries:** binary lifting / Euler tour + RMQ.
