---
number: 98
title: Validate Binary Search Tree
difficulty: Medium
topic: Trees
pattern: DFS with bounds
link: https://leetcode.com/problems/validate-binary-search-tree/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0230 Kth Smallest Element in a BST", "0530 Minimum Absolute Difference in BST", "0501 Find Mode in Binary Search Tree"]
---

# 0098. Validate Binary Search Tree

## ⚡ 30-Second Summary
**Pattern:** DFS passing an open interval (low, high)
**Key insight:** Comparing a node only with its children isn't enough: every node in the left subtree must be smaller than *all* ancestors it went left from. Pass down the allowed range; going left tightens high, going right tightens low.
**Go-to:** DFS with bounds (or inorder strictly increasing), O(n) time, O(h) space

## Problem
Return whether a binary tree is a valid BST: for every node, all values in its left subtree are strictly less, and all values in its right subtree are strictly greater.

**Examples:**
```
Input:  root = [2,1,3]
Output: true
Why:    1 < 2 < 3.

Input:  root = [5,1,4,null,null,3,6]
Output: false
Why:    4 is in 5's right subtree but is smaller than 5.
```

**Constraints:**
- 1 ≤ n ≤ 10⁴; values span the full 32-bit range, so INT_MIN/INT_MAX can't be sentinels.

## Hints
<details><summary>Hint 1</summary>
Check `[5,4,6,null,null,3,7]`: every parent-child pair looks fine. Why is it still invalid?
</details>
<details><summary>Hint 2</summary>
3 is in 5's right subtree. Each node has a range of allowed values set by its ancestors.
</details>
<details><summary>Hint 3</summary>
valid(node, lo, hi): lo < val < hi, then valid(left, lo, val) and valid(right, val, hi). Use null / 64-bit bounds. Or: an inorder traversal must be strictly increasing.
</details>

## Clarifying Questions
- Duplicates allowed? (No: strictly less / strictly greater.)
- Value range? (Full int range: bounds must not use INT_MIN/INT_MAX as "infinity".)

## Example Walkthrough
`[5,4,6,null,null,3,7]`: at 6 the range is (5, ∞) ✓; at 3 (left of 6) the range is (5, 6) and 3 ≤ 5 → false.

## Approaches

### 1. Inorder Must Be Strictly Increasing: O(n) time, O(h) space
Inorder of a BST is sorted. Track the previous value; any `val ≤ prev` fails.

### 2. DFS With Bounds ⭐ Go-to: O(n) time, O(h) space
Pass (lo, hi); check and tighten.
**Why it's the go-to:** states the BST definition directly and catches the "grandparent" violations explicitly. (Approach 1 is equally good; pick whichever you can explain best.)

## Dry Run (Approach 2)
`[5,1,4,null,null,3,6]`

| node | (lo, hi) | in range? |
|------|----------|-----------|
| 5 | (-∞, ∞) | yes |
| 1 | (-∞, 5) | yes |
| 4 | (5, ∞) | **no → false** |

## Edge Case Check
- `[2147483647]`: bounds as null / 64-bit: true. ✅
- Duplicates `[2,2,2]`: strict comparison → false. ✅
- Single node: true. ✅

## ⚠️ Pitfalls
- **Only checking children**: misses `[5,4,6,null,null,3,7]`.
- **INT_MIN/INT_MAX sentinels**: fail on nodes with those exact values. Use `long long`, nullable bounds, or Python `float('inf')`.
- **≤ vs <**: duplicates are invalid.

## 🎯 What the Interviewer Wants
- Explain why a local parent-child check is wrong.
- Handle the extreme-value edge case.
- Know both the bounds and the inorder solutions.

## Follow-ups
- **Kth smallest via inorder:** [LC 0230 Kth Smallest Element in a BST](../0230-kth-smallest-element-in-a-bst/)
- **Fix a BST with two swapped nodes:** inorder, find the two inversions: LC 0099 Recover Binary Search Tree (not added yet)
- **Min difference between values:** [LC 0530 Minimum Absolute Difference in BST](../0530-minimum-absolute-difference-in-bst/)
