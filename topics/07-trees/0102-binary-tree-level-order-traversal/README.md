---
number: 102
title: Binary Tree Level Order Traversal
difficulty: Medium
topic: Trees
pattern: BFS by level
link: https://leetcode.com/problems/binary-tree-level-order-traversal/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0103 Binary Tree Zigzag Level Order Traversal", "0199 Binary Tree Right Side View", "0637 Average of Levels in Binary Tree", "0107 Binary Tree Level Order Traversal II"]
---

# 0102. Binary Tree Level Order Traversal

## ⚡ 30-Second Summary
**Pattern:** BFS, one level per outer iteration
**Key insight:** A queue holds the nodes of exactly one level if you snapshot its size before popping. Pop that many nodes (one level), push their children (the next level).
**Go-to:** BFS with level-size loop, O(n) time, O(w) space

## Problem
Return the node values level by level, left to right, as a list of lists. [LeetCode](https://leetcode.com/problems/binary-tree-level-order-traversal/)

**Examples:**
```
Input:  root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]
Why:    Three levels, each read left to right.

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
Which data structure visits nodes in the order "all of depth 0, then all of depth 1, …"?
</details>
<details><summary>Hint 2</summary>
A plain BFS mixes levels in one stream. How do you know where one level ends?
</details>
<details><summary>Hint 3</summary>
At the start of each round, the queue holds exactly one level. Record its size, pop that many, collect their values.
</details>

## Clarifying Questions
- Empty tree? (Return [].)
- Left to right within each level? (Yes.)

## Example Walkthrough
Queue [3] → level [3], push 9, 20. Queue [9, 20] → level [9, 20], push 15, 7. Queue [15, 7] → level [15, 7]. Done.

## Approaches

### 1. BFS With Level Size ⭐ Go-to: O(n) time, O(w) space
**Why it's the go-to:** the canonical level-order template; 0199, 0637, 0103 are small edits of it.

### 2. DFS With Depth: O(n) time, O(h) space
Preorder DFS passing depth; append to `res[depth]` (create it when depth == len(res)). Left-before-right keeps the order.

## Dry Run (Approach 1)
`[3,9,20,null,null,15,7]`

| round | queue at start | size | level | pushed |
|-------|----------------|------|-------|--------|
| 1 | 3 | 1 | [3] | 9, 20 |
| 2 | 9, 20 | 2 | [9,20] | 15, 7 |
| 3 | 15, 7 | 2 | [15,7] | - |

## Edge Case Check
- Empty tree: return [] (don't push null). ✅
- Skewed tree: one node per level. ✅

## ⚠️ Pitfalls
- **Using `q.size()` as the loop bound while pushing**: the size changes mid-loop. Snapshot it.
- **Pushing null children** then forgetting to skip them.
- **Python `list.pop(0)`** is O(n); use `deque.popleft()`.

## 🎯 What the Interviewer Wants
- The level-size snapshot without hesitation.
- Mention the DFS-with-depth alternative.

## Follow-ups
- **Bottom-up order:** reverse the result: LC 0107 Binary Tree Level Order Traversal II (not added yet)
- **Zigzag:** [LC 0103 Binary Tree Zigzag Level Order Traversal](../0103-binary-tree-zigzag-level-order-traversal/)
- **Last node per level:** [LC 0199 Binary Tree Right Side View](../0199-binary-tree-right-side-view/)
- **Average per level:** [LC 0637 Average of Levels in Binary Tree](../0637-average-of-levels-in-binary-tree/)
