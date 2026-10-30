---
number: 106
title: Construct Binary Tree from Inorder and Postorder Traversal
difficulty: Medium
topic: Trees
pattern: Recursion + inorder index map
link: https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
lists: [LC Top Interview 150]
followup_of: ["0105 Construct Binary Tree from Preorder and Inorder Traversal"]
related: ["0105 Construct Binary Tree from Preorder and Inorder Traversal", "0889 Construct Binary Tree from Preorder and Postorder Traversal"]
---

# 0106. Construct Binary Tree from Inorder and Postorder Traversal

## ⚡ 30-Second Summary
**Pattern:** Recursion over inorder ranges, consuming postorder from the end
**Key insight:** The last postorder value is the root. Walking postorder backwards gives root, then the right subtree's roots, then the left's. So build the **right** subtree first, using the inorder position map to split ranges.
**Go-to:** Postorder pointer from the end + inorder index map, O(n) time, O(n) space

## Problem
Given the inorder and postorder traversals of a binary tree with unique values, rebuild and return the tree.

**Examples:**
```
Input:  inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
Output: [3,9,20,null,null,15,7]
Why:    3 is last in postorder, so it's the root; inorder splits [9] | [15,20,7].

Input:  inorder = [-1], postorder = [-1]
Output: [-1]
Why:    One node.
```

**Constraints:**
- 1 ≤ n ≤ 3000; values unique.

## Hints
<details><summary>Hint 1</summary>
Where is the root in postorder?
</details>
<details><summary>Hint 2</summary>
If you read postorder from the back, which subtree's nodes come next?
</details>
<details><summary>Hint 3</summary>
idx = n - 1; build(lo, hi): root = post[idx--], mid = pos[root], right = build(mid+1, hi) FIRST, then left = build(lo, mid-1).
</details>

## Clarifying Questions
- Unique values? (Yes.)
- Consistent input? (Yes.)

## Example Walkthrough
post from the back: 3 (root), 20 (right subtree root), 7 (20's right), 15 (20's left), 9 (3's left).

## Approaches

### 1. Slice and Search Linearly: O(n²) time, O(n²) space
Root = last of postorder, linear find in inorder, recurse on copies.

### 2. Index Ranges + Hashmap ⭐ Go-to: O(n) time, O(n) space
**Why it's the go-to:** mirror image of 0105; only the pointer direction and the build order change.

## Dry Run (Approach 2)
pos = {9:0, 3:1, 15:2, 20:3, 7:4}

| call (lo, hi) | post idx → root | mid | next calls (right first) |
|---------------|-----------------|-----|--------------------------|
| (0, 4) | 4 → 3 | 1 | (2,4) then (0,0) |
| (2, 4) | 3 → 20 | 3 | (4,4) then (2,2) |
| (4, 4) | 2 → 7 | 4 | - |
| (2, 2) | 1 → 15 | 2 | - |
| (0, 0) | 0 → 9 | 0 | - |

## Edge Case Check
- Single node. ✅
- Skewed trees: depth n. ✅

## ⚠️ Pitfalls
- **Building left first**: wrong, because postorder read backwards visits the right subtree first.
- **Same O(n²) trap** with a linear search.

## 🎯 What the Interviewer Wants
- Adapt 0105 by reasoning about traversal order, not memorizing.

## Follow-ups
- **Preorder + inorder:** [LC 0105 Construct Binary Tree from Preorder and Inorder Traversal](../0105-construct-binary-tree-from-preorder-and-inorder-traversal/)
- **Preorder + postorder:** LC 0889 Construct Binary Tree from Preorder and Postorder Traversal (not added yet)
