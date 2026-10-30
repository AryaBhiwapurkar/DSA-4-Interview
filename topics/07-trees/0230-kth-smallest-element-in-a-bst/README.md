---
number: 230
title: Kth Smallest Element in a BST
difficulty: Medium
topic: Trees
pattern: Inorder traversal
link: https://leetcode.com/problems/kth-smallest-element-in-a-bst/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0098 Validate Binary Search Tree", "0173 Binary Search Tree Iterator", "0530 Minimum Absolute Difference in BST"]
---

# 0230. Kth Smallest Element in a BST

## ⚡ 30-Second Summary
**Pattern:** Inorder traversal (sorted order of a BST)
**Key insight:** Inorder visits BST values in ascending order, so the k-th visited node is the answer. An iterative inorder with an explicit stack can stop as soon as it pops the k-th node.
**Go-to:** Iterative inorder with early stop, O(h + k) time, O(h) space

## Problem
Given a BST and an integer k (1-indexed), return the k-th smallest value.

**Examples:**
```
Input:  root = [3,1,4,null,2], k = 1
Output: 1
Why:    Sorted values are 1,2,3,4; the first is 1.

Input:  root = [5,3,6,2,4,null,null,1], k = 3
Output: 3
Why:    Sorted values are 1,2,3,4,5,6; the third is 3.
```

**Constraints:**
- 1 ≤ k ≤ n ≤ 10⁴.
- Follow-up: frequent inserts/deletes plus kth queries.

## Hints
<details><summary>Hint 1</summary>
Which traversal of a BST gives values in sorted order?
</details>
<details><summary>Hint 2</summary>
Do you need to visit the whole tree?
</details>
<details><summary>Hint 3</summary>
Iterative inorder: push lefts, pop, count; when the count hits k, return; else go right.
</details>

## Clarifying Questions
- 1-indexed k? (Yes.)
- Is k always valid? (Yes.)
- Will the tree change between queries? (That's the follow-up.)

## Example Walkthrough
`[5,3,6,2,4,null,null,1], k = 3`: push 5, 3, 2, 1. Pop 1 (1st), pop 2 (2nd), pop 3 (3rd) → 3.

## Approaches

### 1. Full Inorder Into a List: O(n) time, O(n) space
Collect all values, return list[k-1].

### 2. Iterative Inorder, Stop at k ⭐ Go-to: O(h + k) time, O(h) space
**Why it's the go-to:** stops early, no extra list, and the stack template is reused by 0173.

## Dry Run (Approach 2)
`[3,1,4,null,2], k = 1`

| step | action | stack | count |
|------|--------|-------|-------|
| 1 | push 3, 1 (go left) | 3, 1 | 0 |
| 2 | pop 1 | 3 | 1 = k → **return 1** |

## Edge Case Check
- k = n: the maximum (walks the whole tree). ✅
- Skewed tree: stack holds up to n nodes. ✅

## ⚠️ Pitfalls
- **Using preorder/level order**: not sorted.
- **Off-by-one on k** (1-indexed).
- **Recursive version without early exit**: still correct, but visits everything.

## 🎯 What the Interviewer Wants
- "Inorder of a BST is sorted" stated immediately.
- Early termination.
- Follow-up: store subtree sizes in each node to answer in O(h) after updates (order-statistic tree).

## Follow-ups
- **Iterator over a BST:** [LC 0173 Binary Search Tree Iterator](../0173-binary-search-tree-iterator/)
- **Frequent updates:** augment nodes with subtree size; descend by comparing k with the left size.
- **Validate sortedness:** [LC 0098 Validate Binary Search Tree](../0098-validate-binary-search-tree/)
