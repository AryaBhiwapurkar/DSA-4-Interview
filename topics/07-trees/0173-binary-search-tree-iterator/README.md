---
number: 173
title: Binary Search Tree Iterator
difficulty: Medium
topic: Trees
pattern: Controlled inorder with stack
link: https://leetcode.com/problems/binary-search-tree-iterator/
lists: [LC Top Interview 150]
followup_of: ["0230 Kth Smallest Element in a BST"]
related: ["0230 Kth Smallest Element in a BST", "0094 Binary Tree Inorder Traversal", "0284 Peeking Iterator"]
---

# 0173. Binary Search Tree Iterator

## ⚡ 30-Second Summary
**Pattern:** Iterative inorder, paused between steps
**Key insight:** The iterative inorder loop has two moves: "push the whole left spine" and "pop one node, then push the left spine of its right child". Split it so each `next()` does one pop. The stack never holds more than h nodes.
**Go-to:** Stack of the pending left spine, O(1) amortized next, O(h) space

## Problem
Implement an iterator over a BST that returns values in ascending order: `next()` returns the next smallest value, `hasNext()` says whether any remain. Target O(1) average time and O(h) memory.

**Examples:**
```
Input:  ["BSTIterator","next","next","hasNext","next","hasNext","next","hasNext","next","hasNext"]
        [[[7,3,15,null,null,9,20]],[],[],[],[],[],[],[],[],[]]
Output: [null,3,7,true,9,true,15,true,20,false]
Why:    Sorted order is 3,7,9,15,20; hasNext is false only after 20.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵; up to 10⁵ calls; `next()` is only called when a value remains.
- Follow-up: O(1) average time and O(h) memory.

## Hints
<details><summary>Hint 1</summary>
Flattening to a sorted array works, but uses O(n) memory. What does the iterative inorder keep on its stack?
</details>
<details><summary>Hint 2</summary>
Only the nodes on the current left spine: at most h of them.
</details>
<details><summary>Hint 3</summary>
Constructor: push the left spine of root. next(): pop node, push the left spine of node.right, return node.val. hasNext(): stack not empty.
</details>

## Clarifying Questions
- Is `next()` always valid? (Yes.)
- Can the tree change during iteration? (No.)

## Example Walkthrough
Root 7: push 7, 3. next → pop 3 (no right) = 3. next → pop 7, push spine of 15: 15, 9 → 7. next → 9, next → 15 (push 20), next → 20. Stack empty → hasNext false.

## Approaches

### 1. Flatten to an Array: O(n) init, O(1) next, O(n) space
Inorder into a list once; keep an index.

### 2. Controlled Stack ⭐ Go-to: O(1) amortized next, O(h) space
Each node is pushed and popped exactly once over the whole iteration.
**Why it's the go-to:** meets the O(h) memory follow-up.

## Dry Run (Approach 2)
`[7,3,15,null,null,9,20]`

| call | pop | push (left spine of right child) | stack after | output |
|------|-----|----------------------------------|-------------|--------|
| init | | 7, 3 | 7, 3 | null |
| next | 3 | - | 7 | 3 |
| next | 7 | 15, 9 | 15, 9 | 7 |
| hasNext | | | | true |
| next | 9 | - | 15 | 9 |
| next | 15 | 20 | 20 | 15 |
| next | 20 | - | (empty) | 20 |
| hasNext | | | | false |

## Edge Case Check
- Single node: one next, then hasNext false. ✅
- Right-skewed tree: stack size stays 1. ✅

## ⚠️ Pitfalls
- **Pushing the right child itself** without its left spine: breaks sorted order.
- **Precomputing everything**: violates O(h) memory.
- **Calling hasNext with side effects**: it must not advance the iterator.

## 🎯 What the Interviewer Wants
- The amortized O(1) argument (each node pushed/popped once).
- O(h) memory, with the flatten approach as a stepping stone.

## Follow-ups
- **Kth smallest using the same stack:** [LC 0230 Kth Smallest Element in a BST](../0230-kth-smallest-element-in-a-bst/)
- **Reverse iterator (descending):** push right spines instead.
- **Two iterators to find a pair summing to k in a BST:** one ascending, one descending (two pointers on a tree).
