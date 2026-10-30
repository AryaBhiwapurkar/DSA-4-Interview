---
number: 108
title: Convert Sorted Array to Binary Search Tree
difficulty: Easy
topic: Trees
pattern: Divide at middle
link: https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
lists: [LC Top Interview 150]
followup_of: []
related: ["0109 Convert Sorted List to Binary Search Tree", "1382 Balance a Binary Search Tree", "0110 Balanced Binary Tree"]
---

# 0108. Convert Sorted Array to Binary Search Tree

## ⚡ 30-Second Summary
**Pattern:** Divide and conquer at the middle element
**Key insight:** Picking the middle of a sorted range as the root puts half the values on each side, so the BST is height-balanced. Recurse on the left and right halves.
**Go-to:** Recursive middle split, O(n) time, O(log n) stack

## Problem
Convert a sorted array (ascending, distinct) into a height-balanced BST. Any balanced BST is accepted.

**Examples:**
```
Input:  nums = [-10,-3,0,5,9]
Output: [0,-3,9,-10,null,5]
Why:    0 is the middle; each half is built the same way. [0,-10,5,null,-3,null,9]
        (choosing the left middle) is also accepted.

Input:  nums = [1,3]
Output: [3,1]
Why:    With two values either can be the root; [1,null,3] is also accepted.
```

**Constraints:**
- 1 ≤ n ≤ 10⁴; strictly increasing.

## Hints
<details><summary>Hint 1</summary>
Which element should be the root so both sides have about the same size?
</details>
<details><summary>Hint 2</summary>
The left half is itself a sorted array that must become the left subtree.
</details>
<details><summary>Hint 3</summary>
build(lo, hi): if lo > hi return null; mid = (lo + hi) / 2; node(nums[mid]) with left = build(lo, mid - 1), right = build(mid + 1, hi).
</details>

## Clarifying Questions
- Any balanced BST accepted? (Yes, the choice of middle is free.)
- Duplicates? (No, strictly increasing.)

## Example Walkthrough
`[-10,-3,0,5,9]` with the left middle: root 0; left [-10,-3] → root -10, right child -3; right [5,9] → root 5, right child 9. Result [0,-10,5,null,-3,null,9].

## Approaches

### 1. Recursive Middle Split ⭐ Go-to: O(n) time, O(log n) stack
**Why it's the go-to:** a direct translation of the idea; each element becomes one node.

### 2. Iterative With a Stack of (node, lo, hi): O(n) time, O(log n) space
Same splits without recursion: create the root, push its pending ranges, fill children as you pop.

## Dry Run (Approach 1)
`[-10,-3,0,5,9]` (mid = (lo + hi) / 2)

| range | mid | node | left range | right range |
|-------|-----|------|------------|-------------|
| 0..4 | 2 | 0 | 0..1 | 3..4 |
| 0..1 | 0 | -10 | empty | 1..1 |
| 1..1 | 1 | -3 | empty | empty |
| 3..4 | 3 | 5 | empty | 4..4 |
| 4..4 | 4 | 9 | empty | empty |

## Edge Case Check
- Single element: one node. ✅
- Two elements: either middle gives a valid balanced tree. ✅

## ⚠️ Pitfalls
- **Inserting elements one by one** in sorted order: produces a skewed (unbalanced) tree.
- **Slicing arrays in each call**: O(n log n) copying; pass indices.
- **Expecting the exact LeetCode output**: several trees are valid.

## 🎯 What the Interviewer Wants
- Why the middle guarantees balance.
- Index-based recursion, O(n) total.

## Follow-ups
- **Sorted linked list input:** find the middle with slow/fast or simulate inorder: LC 0109 Convert Sorted List to Binary Search Tree (not added yet)
- **Rebalance an existing BST:** inorder to an array, then this: LC 1382 Balance a Binary Search Tree (not added yet)
- **Check balance:** [LC 0110 Balanced Binary Tree](../0110-balanced-binary-tree/)
