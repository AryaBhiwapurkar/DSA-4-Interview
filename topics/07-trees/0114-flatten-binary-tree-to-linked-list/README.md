---
number: 114
title: Flatten Binary Tree to Linked List
difficulty: Medium
topic: Trees
pattern: Reverse preorder / Morris
link: https://leetcode.com/problems/flatten-binary-tree-to-linked-list/
lists: [LC Top Interview 150]
followup_of: []
related: ["0430 Flatten a Multilevel Doubly Linked List", "0897 Increasing Order Search Tree", "0144 Binary Tree Preorder Traversal"]
---

# 0114. Flatten Binary Tree to Linked List

## ⚡ 30-Second Summary
**Pattern:** Splice each left subtree in front of the right subtree (Morris-style)
**Key insight:** In preorder, a node's left subtree comes right after it, and the right subtree comes right after the left subtree's last node (its rightmost node). So for each node with a left child: find the rightmost node of the left subtree, hang the current right subtree there, move left to right, null the left. Then step right.
**Go-to:** In-place splicing, O(n) time, O(1) space

## Problem
Flatten a binary tree in place into a "linked list" using the `right` pointers, in preorder order, with every `left` pointer set to null.

**Examples:**
```
Input:  root = [1,2,5,3,4,null,6]
Output: [1,null,2,null,3,null,4,null,5,null,6]
Why:    Preorder is 1,2,3,4,5,6, chained through right pointers.

Input:  root = []
Output: []
Why:    Nothing to flatten.

Input:  root = [0]
Output: [0]
Why:    A single node is already flat.
```

**Constraints:**
- 0 ≤ n ≤ 2000.
- Follow-up: O(1) extra space.

## Hints
<details><summary>Hint 1</summary>
Easy with an array of preorder nodes. Can you rewire pointers as you go instead?
</details>
<details><summary>Hint 2</summary>
In preorder, what comes right before a node's right subtree?
</details>
<details><summary>Hint 3</summary>
The rightmost node of its left subtree. Attach the right subtree there, move the left subtree to the right, clear left, advance.
</details>

## Clarifying Questions
- In place? (Yes, return nothing.)
- Preorder order? (Yes.)

## Example Walkthrough
`[1,2,5,3,4,null,6]`
- At 1: left subtree 2(3,4), its rightmost is 4. 4.right = 5(…). 1.right = 2, 1.left = null.
- At 2: left 3, rightmost 3. 3.right = 4. 2.right = 3. Continue to 3, 4, 5 (5 has only a right child).

## Approaches

### 1. Preorder Into a List, Then Relink: O(n) time, O(n) space
Collect nodes in preorder; set nodes[i].left = null, nodes[i].right = nodes[i+1].

### 2. Reverse Preorder With `prev`: O(n) time, O(h) stack
Visit right, left, node (reverse preorder); set node.right = prev, node.left = null, prev = node. Elegant recursion.

### 3. In-Place Splicing ⭐ Go-to: O(n) time, O(1) space
**Why it's the go-to:** meets the follow-up; each edge is walked a constant number of times overall.

## Dry Run (Approach 3)
`[1,2,5,3,4,null,6]`

| cur | left? | rightmost of left | rewiring | next cur |
|-----|-------|-------------------|----------|----------|
| 1 | 2 | 4 | 4.right = 5; 1.right = 2; 1.left = null | 2 |
| 2 | 3 | 3 | 3.right = 4; 2.right = 3 | 3 |
| 3 | no | | | 4 |
| 4 | no | | | 5 |
| 5 | no | | | 6 → done |

## Edge Case Check
- Empty / single node: nothing to do. ✅
- Already a right chain: no left children, loop just walks. ✅
- Left-only chain: each step splices one node. ✅

## ⚠️ Pitfalls
- **Forgetting `left = null`**: LeetCode checks it.
- **Reverse preorder visiting left before right**: produces the wrong order.
- **Overwriting `right` before saving it** in the splice.

## 🎯 What the Interviewer Wants
- A correct O(n)-space version first, then the O(1) splice.
- Explain why the rightmost node of the left subtree is the predecessor of the right subtree.

## Follow-ups
- **Doubly linked list with child pointers:** LC 0430 Flatten a Multilevel Doubly Linked List (not added yet)
- **Inorder version for a BST:** LC 0897 Increasing Order Search Tree (not added yet)
- **Morris traversal in general:** O(1)-space inorder/preorder by threading rightmost pointers.
