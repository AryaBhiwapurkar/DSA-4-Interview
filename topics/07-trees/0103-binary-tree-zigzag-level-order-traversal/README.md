---
number: 103
title: Binary Tree Zigzag Level Order Traversal
difficulty: Medium
topic: Trees
pattern: BFS, alternate direction
link: https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
lists: [LC Top Interview 150]
followup_of: ["0102 Binary Tree Level Order Traversal"]
related: ["0102 Binary Tree Level Order Traversal", "0199 Binary Tree Right Side View"]
---

# 0103. Binary Tree Zigzag Level Order Traversal

## ⚡ 30-Second Summary
**Pattern:** Level-order BFS, flip every other level
**Key insight:** Keep the normal left-to-right BFS (so children are always queued correctly) and only change how each level's values are written: forward on even levels, reversed on odd ones.
**Go-to:** BFS + write each level forward or backward, O(n) time, O(w) space

## Problem
Return the level order traversal, but alternate direction: left to right on the first level, right to left on the next, and so on. [LeetCode](https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/)

**Examples:**
```
Input:  root = [3,9,20,null,null,15,7]
Output: [[3],[20,9],[15,7]]
Why:    Level 1 is read right to left, level 2 left to right again.

Input:  root = [1]
Output: [[1]]
Why:    One level.

Input:  root = []
Output: []
Why:    No levels.
```

**Constraints:**
- 0 ≤ n ≤ 2000.

## Hints
<details><summary>Hint 1</summary>
Could you just run 0102 and post-process?
</details>
<details><summary>Hint 2</summary>
Changing the order you push children gets messy. Change only how you store each level.
</details>
<details><summary>Hint 3</summary>
Pre-size the level array; write index i (left to right) or size-1-i (right to left) depending on the level's parity.
</details>

## Clarifying Questions
- First level left to right? (Yes.)
- Empty tree? (Return [].)

## Example Walkthrough
Levels from BFS: [3], [9,20], [15,7]. Level 1 is odd → stored reversed as [20,9]. Result [[3],[20,9],[15,7]].

## Approaches

### 1. BFS + Index by Direction ⭐ Go-to: O(n) time, O(w) space
Fill `level[leftToRight ? i : size-1-i]`.
**Why it's the go-to:** the BFS stays standard; no reversing, no deque tricks.

### 2. BFS + Reverse Odd Levels: O(n) time, O(w) space
Build each level normally and reverse it when the level index is odd. Simplest to write; the reversal is O(level size), so still linear overall.

## Dry Run (Approach 1)
`[3,9,20,null,null,15,7]`

| level | BFS order | direction | stored |
|-------|-----------|-----------|--------|
| 0 | 3 | → | [3] |
| 1 | 9, 20 | ← | [20,9] |
| 2 | 15, 7 | → | [15,7] |

## Edge Case Check
- Empty: []. ✅
- Single-node levels: direction doesn't matter. ✅

## ⚠️ Pitfalls
- **Flipping the child push order** each level: easy to get wrong for deeper levels.
- **Forgetting to toggle the direction** after each level.

## 🎯 What the Interviewer Wants
- Keep traversal and presentation separate.
- O(n) overall.

## Follow-ups
- **Plain level order:** [LC 0102 Binary Tree Level Order Traversal](../0102-binary-tree-level-order-traversal/)
- **Vertical order:** BFS with column indices and a map.
