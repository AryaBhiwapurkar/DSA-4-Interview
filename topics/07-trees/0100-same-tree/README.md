---
number: 100
title: Same Tree
difficulty: Easy
topic: Trees
pattern: Parallel DFS
link: https://leetcode.com/problems/same-tree/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0101 Symmetric Tree", "0572 Subtree of Another Tree", "0226 Invert Binary Tree"]
---

# 0100. Same Tree

## ⚡ 30-Second Summary
**Pattern:** Parallel DFS on two trees
**Key insight:** Two trees are equal iff both are null, or both exist with equal values and their left subtrees are equal and their right subtrees are equal.
**Go-to:** Recursive parallel DFS, O(n) time, O(h) space

## Problem
Return whether two binary trees have the same structure and the same values at every position.

**Examples:**
```
Input:  p = [1,2,3], q = [1,2,3]
Output: true
Why:    Identical shape and values.

Input:  p = [1,2], q = [1,null,2]
Output: false
Why:    Same values, but 2 is a left child in one and a right child in the other.

Input:  p = [1,2,1], q = [1,1,2]
Output: false
Why:    Same shape, children's values swapped.
```

**Constraints:**
- 0 ≤ n ≤ 100 per tree.

## Hints
<details><summary>Hint 1</summary>
Compare the roots first. What are all the cases involving null?
</details>
<details><summary>Hint 2</summary>
If both roots exist and match, what must also hold?
</details>
<details><summary>Hint 3</summary>
both null → true; one null → false; values differ → false; else recurse left-left and right-right.
</details>

## Clarifying Questions
- Structure must match too, not just values? (Yes.)
- Both empty? (Equal.)

## Example Walkthrough
`[1,2]` vs `[1,null,2]`: roots 1 = 1. Left: 2 vs null → one null → false.

## Approaches

### 1. Recursive Parallel DFS ⭐ Go-to: O(n) time, O(h) space
Four base cases, two recursive calls.
**Why it's the go-to:** the building block for 0572 and 0101.

### 2. Iterative With a Queue of Pairs: O(n) time, O(w) space
Push (p, q) pairs; pop and apply the same checks; push (p.left, q.left), (p.right, q.right).

## Dry Run (Approach 1)
`[1,2,1]` vs `[1,1,2]`

| pair | check | result |
|------|-------|--------|
| (1, 1) | equal, recurse | |
| (2, 1) | values differ | false |
| root | left is false | **false** (short-circuit) |

## Edge Case Check
- Both empty: true. ✅
- One empty: false. ✅
- Same values, different shape: caught by the one-null case. ✅

## ⚠️ Pitfalls
- **Comparing traversals without null markers**: different shapes can give the same inorder/preorder.
- **Checking values before null checks**: dereferences null.

## 🎯 What the Interviewer Wants
- All null cases handled cleanly before touching values.
- Short-circuiting with `&&`.

## Follow-ups
- **Mirror equality:** [LC 0101 Symmetric Tree](../0101-symmetric-tree/)
- **Contains a copy somewhere:** [LC 0572 Subtree of Another Tree](../0572-subtree-of-another-tree/)
- **Equal up to swapping children (flip equivalent):** check both pairings at each node.
