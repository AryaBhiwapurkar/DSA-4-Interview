---
number: 530
title: Minimum Absolute Difference in BST
difficulty: Easy
topic: Trees
pattern: Inorder, track prev
link: https://leetcode.com/problems/minimum-absolute-difference-in-bst/
lists: [LC Top Interview 150]
followup_of: []
related: ["0783 Minimum Distance Between BST Nodes", "0098 Validate Binary Search Tree", "0230 Kth Smallest Element in a BST"]
---

# 0530. Minimum Absolute Difference in BST

## ⚡ 30-Second Summary
**Pattern:** Inorder traversal, compare with the previous value
**Key insight:** In sorted order, the closest pair of values is always adjacent. Inorder gives the sorted order, so track the previous value and take the minimum of (val - prev).
**Go-to:** Inorder with a `prev` variable, O(n) time, O(h) space

## Problem
Return the minimum absolute difference between the values of any two different nodes in a BST. [LeetCode](https://leetcode.com/problems/minimum-absolute-difference-in-bst/)

**Examples:**
```
Input:  root = [4,2,6,1,3]
Output: 1
Why:    Sorted 1,2,3,4,6: adjacent gaps are 1,1,1,2.

Input:  root = [1,0,48,null,null,12,49]
Output: 1
Why:    Sorted 0,1,12,48,49: the gaps 0→1 and 48→49 are both 1.
```

**Constraints:**
- 2 ≤ n ≤ 10⁴; values 0 ≤ val ≤ 10⁵.

## Hints
<details><summary>Hint 1</summary>
In a sorted array, where is the minimum difference?
</details>
<details><summary>Hint 2</summary>
Between neighbours. How do you visit a BST in sorted order?
</details>
<details><summary>Hint 3</summary>
Inorder; keep the previous value; best = min(best, val - prev).
</details>

## Clarifying Questions
- Distinct nodes, values may repeat? (Values are non-negative; a BST here has unique values.)
- At least two nodes? (Yes.)

## Example Walkthrough
`[4,2,6,1,3]` inorder: 1, 2 (gap 1), 3 (1), 4 (1), 6 (2) → 1.

## Approaches

### 1. Inorder Into a List, Then Adjacent Gaps: O(n) time, O(n) space

### 2. Inorder With `prev` ⭐ Go-to: O(n) time, O(h) space
**Why it's the go-to:** no extra list; same structure as 0098's inorder check.

## Dry Run (Approach 2)
`[1,0,48,null,null,12,49]`

| visit | prev | gap | best |
|-------|------|-----|------|
| 0 | none | - | ∞ |
| 1 | 0 | 1 | 1 |
| 12 | 1 | 11 | 1 |
| 48 | 12 | 36 | 1 |
| 49 | 48 | 1 | **1** |

## Edge Case Check
- Two nodes: one gap. ✅
- Gap at the very end of the order: still compared. ✅

## ⚠️ Pitfalls
- **Comparing only parent and child**: the closest values may be far apart in the tree (e.g. root and the leftmost node of its right subtree).
- **Initialising prev to 0 or -1 as a real value**: use a "none" marker (or -∞) so the first node isn't compared.

## 🎯 What the Interviewer Wants
- Reduce to "adjacent in sorted order".
- O(h) space with a running prev.

## Follow-ups
- **Same problem, different number:** LC 0783 Minimum Distance Between BST Nodes (not added yet)
- **Not a BST:** sort all values first, O(n log n).
- **Inorder template:** [LC 0230 Kth Smallest Element in a BST](../0230-kth-smallest-element-in-a-bst/)
