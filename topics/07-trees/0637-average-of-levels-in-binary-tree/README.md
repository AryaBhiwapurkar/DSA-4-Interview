---
number: 637
title: Average of Levels in Binary Tree
difficulty: Easy
topic: Trees
pattern: BFS by level
link: https://leetcode.com/problems/average-of-levels-in-binary-tree/
lists: [LC Top Interview 150]
followup_of: ["0102 Binary Tree Level Order Traversal"]
related: ["0102 Binary Tree Level Order Traversal", "0515 Find Largest Value in Each Tree Row"]
---

# 0637. Average of Levels in Binary Tree

## ⚡ 30-Second Summary
**Pattern:** Level-order BFS with a per-level sum
**Key insight:** Same as 0102, but instead of storing each level, sum its values and divide by the level size. Sum in 64-bit: a level can hold thousands of values near 2³¹.
**Go-to:** BFS with level size, O(n) time, O(w) space

## Problem
Return the average value of the nodes on each level, top to bottom (answers within 10⁻⁵ are accepted). [LeetCode](https://leetcode.com/problems/average-of-levels-in-binary-tree/)

**Examples:**
```
Input:  root = [3,9,20,null,null,15,7]
Output: [3.00000,14.50000,11.00000]
Why:    Levels are [3], [9,20], [15,7].

Input:  root = [3,9,20,15,7]
Output: [3.00000,14.50000,11.00000]
Why:    Same averages, though 15 and 7 now hang under 9.
```

**Constraints:**
- 1 ≤ n ≤ 10⁴; values span the full 32-bit range, so a level sum overflows int.

## Hints
<details><summary>Hint 1</summary>
You already know how to process the tree level by level.
</details>
<details><summary>Hint 2</summary>
What do you need per level? A sum and a count.
</details>
<details><summary>Hint 3</summary>
Inside the level-size loop, add values into a 64-bit sum; append sum / size.
</details>

## Clarifying Questions
- Precision? (Within 10⁻⁵.)
- Value range? (32-bit, so use 64-bit sums.)

## Example Walkthrough
`[3,9,20,null,null,15,7]`: level sums 3, 29, 22 with sizes 1, 2, 2 → 3, 14.5, 11.

## Approaches

### 1. BFS With Level Sum ⭐ Go-to: O(n) time, O(w) space
**Why it's the go-to:** the 0102 template with a running sum.

### 2. DFS Collecting (sum, count) per Depth: O(n) time, O(h) space
Preorder with depth; accumulate into arrays indexed by depth, divide at the end.

## Dry Run (Approach 1)
`[3,9,20,15,7]`

| level | nodes | sum | size | avg |
|-------|-------|-----|------|-----|
| 0 | 3 | 3 | 1 | 3.0 |
| 1 | 9, 20 | 29 | 2 | 14.5 |
| 2 | 15, 7 | 22 | 2 | 11.0 |

## Edge Case Check
- Large values `[2147483647,2147483647,2147483647]`: level 1 sum is 2³² - 2, fits in 64-bit → 2147483647.0. ✅
- Single node: its value. ✅

## ⚠️ Pitfalls
- **int overflow** in the level sum (C++/Java). Use `long long` / `double`.
- **Integer division**: divide as floating point.

## 🎯 What the Interviewer Wants
- Reuse level-order BFS.
- Mention overflow without being asked.

## Follow-ups
- **Max per level:** LC 0515 Find Largest Value in Each Tree Row (not added yet)
- **Level lists:** [LC 0102 Binary Tree Level Order Traversal](../0102-binary-tree-level-order-traversal/)
