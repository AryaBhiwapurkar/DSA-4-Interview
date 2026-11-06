---
number: 104
title: Maximum Depth of Binary Tree
difficulty: Easy
topic: Trees
pattern: DFS height
link: https://leetcode.com/problems/maximum-depth-of-binary-tree/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0111 Minimum Depth of Binary Tree", "0110 Balanced Binary Tree", "0543 Diameter of Binary Tree"]
---

# 0104. Maximum Depth of Binary Tree

## ⚡ 30-Second Summary
**Pattern:** DFS returning height
**Key insight:** depth(node) = 1 + max(depth(left), depth(right)), with depth(null) = 0. The answer is built bottom-up from the children.
**Go-to:** Recursive DFS, O(n) time, O(h) space

## Problem
Return the number of nodes on the longest root-to-leaf path. [LeetCode](https://leetcode.com/problems/maximum-depth-of-binary-tree/)

**Examples:**
```
Input:  root = [3,9,20,null,null,15,7]
Output: 3
Why:    3 → 20 → 15 (or 7) has three nodes.

Input:  root = [1,null,2]
Output: 2
Why:    A chain of two nodes.
```

**Constraints:**
- 0 ≤ n ≤ 10⁴; a skewed tree makes recursion depth 10⁴.

## Hints
<details><summary>Hint 1</summary>
If you knew the depth of both subtrees, what's the depth of the whole tree?
</details>
<details><summary>Hint 2</summary>
What's the depth of an empty tree?
</details>
<details><summary>Hint 3</summary>
Return 0 for null, else 1 + max(left, right). Or BFS and count levels.
</details>

## Clarifying Questions
- Depth counts nodes, not edges? (Nodes.)
- Empty tree? (0.)

## Example Walkthrough
`[3,9,20,null,null,15,7]`: depth(9) = 1, depth(15) = depth(7) = 1, depth(20) = 2, depth(3) = 1 + max(1, 2) = 3.

## Approaches

### 1. Recursive DFS ⭐ Go-to: O(n) time, O(h) space
One line of logic.
**Why it's the go-to:** the template for every "compute something from both children" problem.

### 2. BFS Level Count: O(n) time, O(w) space
Process the queue level by level and count levels. No recursion, so no stack-depth concerns.

## Dry Run (Approach 1)
`[1,null,2]`

| call | left | right | returns |
|------|------|-------|---------|
| depth(2) | 0 | 0 | 1 |
| depth(1) | 0 | 1 | **2** |

## Edge Case Check
- Empty: 0. ✅
- Single node: 1. ✅
- Skewed 10⁴ deep: fine in C++/Go; Python needs BFS or a raised recursion limit. ✅

## ⚠️ Pitfalls
- **Counting edges** instead of nodes (off by one).
- **Python recursion limit (~1000)** on a 10⁴-deep chain; use BFS or `sys.setrecursionlimit`.
- **BFS without the level-size loop** counts nodes, not levels.

## 🎯 What the Interviewer Wants
- Recursive solution immediately; iterative BFS on request.
- O(h) space, worst case O(n) for a skewed tree.

## Follow-ups
- **Minimum depth (to the nearest leaf):** careful with one-child nodes: LC 0111 Minimum Depth of Binary Tree (not added yet)
- **Balanced check using heights:** [LC 0110 Balanced Binary Tree](../0110-balanced-binary-tree/)
- **Longest path between any two nodes:** [LC 0543 Diameter of Binary Tree](../0543-diameter-of-binary-tree/)
