---
number: 105
title: Construct Binary Tree from Preorder and Inorder Traversal
difficulty: Medium
topic: Trees
pattern: Recursion + inorder index map
link: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0106 Construct Binary Tree from Inorder and Postorder Traversal", "0889 Construct Binary Tree from Preorder and Postorder Traversal", "0297 Serialize and Deserialize Binary Tree"]
---

# 0105. Construct Binary Tree from Preorder and Inorder Traversal

## ⚡ 30-Second Summary
**Pattern:** Recursion over index ranges + a value → inorder-index map
**Key insight:** The first preorder value is the root. Its position in inorder splits inorder into the left subtree (before it) and the right subtree (after it), and the left size tells you how many of the following preorder values belong to the left. A hashmap makes finding the root's inorder position O(1).
**Go-to:** Recursion with a preorder pointer and inorder index map, O(n) time, O(n) space

## Problem
Given the preorder and inorder traversals of a binary tree with unique values, rebuild and return the tree.

**Examples:**
```
Input:  preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]
Why:    3 is the root; inorder puts 9 on its left and 15,20,7 on its right.

Input:  preorder = [-1], inorder = [-1]
Output: [-1]
Why:    One node.
```

**Constraints:**
- 1 ≤ n ≤ 3000; values unique (otherwise the split is ambiguous).

## Hints
<details><summary>Hint 1</summary>
Which traversal tells you the root immediately?
</details>
<details><summary>Hint 2</summary>
Once you know the root, how does inorder tell you which values are in the left subtree?
</details>
<details><summary>Hint 3</summary>
Keep a global index into preorder. build(lo, hi) over the inorder range: root = preorder[idx++], mid = pos[root], left = build(lo, mid-1), right = build(mid+1, hi). Build left before right.
</details>

## Clarifying Questions
- Unique values? (Yes, required.)
- Are both traversals consistent? (Yes.)

## Example Walkthrough
preorder [3,9,20,15,7], inorder [9,3,15,20,7]:
- Root 3 (inorder index 1): left inorder [9], right [15,20,7].
- Next preorder 9 → left subtree root, no children.
- Next 20 → right root; inorder splits [15] and [7]; then 15, then 7.

## Approaches

### 1. Slice and Search Linearly: O(n²) time, O(n²) space
Find the root in inorder with a linear scan and recurse on copied sub-arrays. Clear but slow on skewed trees.

### 2. Index Ranges + Hashmap ⭐ Go-to: O(n) time, O(n) space
No copying; preorder consumed left to right by a shared pointer.
**Why it's the go-to:** linear and the standard expected answer.

## Dry Run (Approach 2)
pos = {9:0, 3:1, 15:2, 20:3, 7:4}

| call (lo, hi) | preorder idx → root | mid | children ranges |
|---------------|---------------------|-----|-----------------|
| (0, 4) | 0 → 3 | 1 | (0,0), (2,4) |
| (0, 0) | 1 → 9 | 0 | empty, empty |
| (2, 4) | 2 → 20 | 3 | (2,2), (4,4) |
| (2, 2) | 3 → 15 | 2 | empty |
| (4, 4) | 4 → 7 | 4 | empty |

## Edge Case Check
- Single node: one call. ✅
- Fully skewed tree: recursion depth n (3000), fine in C++/Go; borderline-OK in Python (raise the limit). ✅

## ⚠️ Pitfalls
- **Building right before left**: the preorder pointer would assign values to the wrong subtree.
- **Linear search for the root** each time: O(n²).
- **Off-by-one in ranges**: empty when lo > hi.

## 🎯 What the Interviewer Wants
- Explain why preorder gives roots and inorder gives the split.
- Hashmap for O(1) lookups and index ranges instead of slicing.

## Follow-ups
- **Inorder + postorder:** [LC 0106 Construct Binary Tree from Inorder and Postorder Traversal](../0106-construct-binary-tree-from-inorder-and-postorder-traversal/)
- **Preorder + postorder (ambiguous in general):** LC 0889 Construct Binary Tree from Preorder and Postorder Traversal (not added yet)
- **Single traversal with null markers is enough:** [LC 0297 Serialize and Deserialize Binary Tree](../0297-serialize-and-deserialize-binary-tree/)
