---
number: 101
title: Symmetric Tree
difficulty: Easy
topic: Trees
pattern: Mirror DFS
link: https://leetcode.com/problems/symmetric-tree/
lists: [LC Top Interview 150]
followup_of: ["0100 Same Tree"]
related: ["0100 Same Tree", "0226 Invert Binary Tree"]
---

# 0101. Symmetric Tree

## ⚡ 30-Second Summary
**Pattern:** Mirror DFS (Same Tree with crossed children)
**Key insight:** A tree is symmetric iff its left and right subtrees are mirrors. Two trees a, b are mirrors iff a.val == b.val, a.left mirrors b.right, and a.right mirrors b.left.
**Go-to:** Recursive mirror check, O(n) time, O(h) space

## Problem
Return whether a binary tree is a mirror image of itself around its center. [LeetCode](https://leetcode.com/problems/symmetric-tree/)

**Examples:**
```
Input:  root = [1,2,2,3,4,4,3]
Output: true
Why:    Each level reads the same from both ends: 2,2 and 3,4,4,3.

Input:  root = [1,2,2,null,3,null,3]
Output: false
Why:    Both 3s are right children, so the mirror would need one on the left.
```

**Constraints:**
- 1 ≤ n ≤ 1000.
- Follow-up: solve it both recursively and iteratively.

## Hints
<details><summary>Hint 1</summary>
Compare the tree with itself, but walk one copy left-first and the other right-first.
</details>
<details><summary>Hint 2</summary>
Which pairs of nodes must be equal? The outer pair (left.left, right.right) and the inner pair (left.right, right.left).
</details>
<details><summary>Hint 3</summary>
mirror(a, b): both null → true; one null → false; else a.val == b.val && mirror(a.left, b.right) && mirror(a.right, b.left).
</details>

## Clarifying Questions
- Values and structure both must mirror? (Yes.)
- Single node? (Symmetric.)

## Example Walkthrough
`[1,2,2,3,4,4,3]`: mirror(2, 2) → values equal; outer mirror(3, 3) ✓; inner mirror(4, 4) ✓. True.

## Approaches

### 1. Recursive Mirror Check ⭐ Go-to: O(n) time, O(h) space
Same Tree logic with left/right crossed.
**Why it's the go-to:** a tiny change to a well-known function.

### 2. Iterative Queue of Pairs: O(n) time, O(w) space
Push (left, right); for each popped pair push (a.left, b.right) and (a.right, b.left).

## Dry Run (Approach 1)
`[1,2,2,null,3,null,3]`

| pair | check | result |
|------|-------|--------|
| (2, 2) | equal | recurse |
| outer (null, 3) | one null | **false** |

## Edge Case Check
- Single node: mirror(null, null) = true. ✅
- Same values, wrong shape: one-null case catches it. ✅

## ⚠️ Pitfalls
- **Comparing left.left with right.left** (same side): that's Same Tree, not mirror.
- **Checking each level's values as a palindrome without nulls**: shape differences slip through.

## 🎯 What the Interviewer Wants
- Reduce to "are two subtrees mirrors" and reuse the Same Tree shape.
- Both recursive and iterative versions.

## Follow-ups
- **Identical trees:** [LC 0100 Same Tree](../0100-same-tree/)
- **Make a mirror:** [LC 0226 Invert Binary Tree](../0226-invert-binary-tree/)
