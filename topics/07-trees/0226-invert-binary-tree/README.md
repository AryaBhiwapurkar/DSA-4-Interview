---
number: 226
title: Invert Binary Tree
difficulty: Easy
topic: Trees
pattern: DFS swap children
link: https://leetcode.com/problems/invert-binary-tree/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0101 Symmetric Tree", "0100 Same Tree", "0104 Maximum Depth of Binary Tree"]
---

# 0226. Invert Binary Tree

## ⚡ 30-Second Summary
**Pattern:** DFS, swap children at every node
**Key insight:** The mirror of a tree is: swap the root's left and right, then mirror each subtree. Every node is handled independently, so any traversal order works.
**Go-to:** Recursive DFS, O(n) time, O(h) space

## Problem
Mirror a binary tree (swap every node's left and right child) and return its root. [LeetCode](https://leetcode.com/problems/invert-binary-tree/)

**Examples:**
```
Input:  root = [4,2,7,1,3,6,9]
Output: [4,7,2,9,6,3,1]
Why:    Every level reads right-to-left after the flip.

Input:  root = [2,1,3]
Output: [2,3,1]
Why:    The two children swap.

Input:  root = []
Output: []
Why:    Nothing to invert.
```

**Constraints:**
- 0 ≤ n ≤ 100.

## Hints
<details><summary>Hint 1</summary>
What does inverting do to just the root?
</details>
<details><summary>Hint 2</summary>
After swapping the root's children, the two subtrees still need inverting. Same problem, smaller.
</details>
<details><summary>Hint 3</summary>
If null, return null. Swap left and right, recurse on both, return the node.
</details>

## Clarifying Questions
- In place or a new tree? (In place is fine.)
- Empty tree? (Return null.)

## Example Walkthrough
`[2,1,3]`: swap at 2 gives left = 3, right = 1. Both are leaves (swapping their null children changes nothing). Result [2,3,1].

## Approaches

### 1. Recursive DFS ⭐ Go-to: O(n) time, O(h) space
Swap, then recurse.
**Why it's the go-to:** three lines and obviously correct.

### 2. Iterative BFS: O(n) time, O(w) space
Queue of nodes; pop, swap its children, push the non-null ones. Avoids deep recursion on skewed trees.

## Dry Run (Approach 1)
`[4,2,7,1,3,6,9]`

| node | before (L, R) | after (L, R) |
|------|---------------|--------------|
| 4 | 2, 7 | 7, 2 |
| 7 | 6, 9 | 9, 6 |
| 2 | 1, 3 | 3, 1 |
| leaves | null, null | null, null |
| result | | **[4,7,2,9,6,3,1]** |

## Edge Case Check
- Empty tree: null. ✅
- Single node: unchanged. ✅
- Skewed tree: recursion depth n (≤ 100 here, fine). ✅

## ⚠️ Pitfalls
- **Assigning `left = invert(right)` then `right = invert(left)`**: the second call sees the already-overwritten left. Save one side first or swap before recursing.
- **Returning nothing** from the recursive helper when the caller expects the node.

## 🎯 What the Interviewer Wants
- Instant recursive solution and its O(h) stack cost.
- An iterative version on request.

## Follow-ups
- **Is a tree its own mirror?** [LC 0101 Symmetric Tree](../0101-symmetric-tree/)
- **Are two trees identical?** [LC 0100 Same Tree](../0100-same-tree/)
- **Are two trees mirrors of each other?** Same Tree with left/right crossed.
