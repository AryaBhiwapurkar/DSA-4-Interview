---
number: 427
title: Construct Quad Tree
difficulty: Medium
topic: Trees
pattern: Divide & conquer on grid
link: https://leetcode.com/problems/construct-quad-tree/
lists: [LC Top Interview 150]
followup_of: []
related: ["0558 Logical OR of Two Binary Grids Represented as Quad-Trees", "0108 Convert Sorted Array to Binary Search Tree"]
---

# 0427. Construct Quad Tree

## ⚡ 30-Second Summary
**Pattern:** Divide and conquer on a square region
**Key insight:** A region becomes a leaf if all its cells are equal; otherwise split it into four quadrants and build each recursively. Building bottom-up lets you merge: if all four children are leaves with the same value, collapse them into one leaf, so no separate uniformity scan is needed.
**Go-to:** Check-then-split recursion, O(n² log n) time, O(log n) stack

## Problem
Given an n × n grid of 0s and 1s (n a power of 2), build its quad tree. Each node has `val`, `isLeaf` and four children (topLeft, topRight, bottomLeft, bottomRight). A uniform region is a leaf with that value; a mixed region is an internal node with four children. The output is a level order of [isLeaf, val] pairs with null for absent children. [LeetCode](https://leetcode.com/problems/construct-quad-tree/)

**Examples:**
```
Input:  grid = [[0,1],[1,0]]
Output: [[0,1],[1,0],[1,1],[1,1],[1,0]]
Why:    The 2×2 grid is mixed, so the root is internal; each cell is a leaf
        (values 0, 1, 1, 0).

Input:  grid = 8×8: top-left 4×4 all 1, top-right 4×4 has 0s on top and 1s
        below, bottom-left all 1, bottom-right all 0
Output: [[0,1],[1,1],[0,1],[1,1],[1,0],null,null,null,null,[1,0],[1,0],[1,1],[1,1]]
Why:    Only the top-right quadrant is mixed; it splits into four uniform 2×2 leaves.
```

**Constraints:**
- n = 2^x with 0 ≤ x ≤ 6, so n ≤ 64.
- Internal nodes may have any val; LeetCode's examples use 1.

## Hints
<details><summary>Hint 1</summary>
When is a region a single leaf?
</details>
<details><summary>Hint 2</summary>
If it isn't uniform, what are the four sub-problems?
</details>
<details><summary>Hint 3</summary>
build(r, c, size): if all cells equal → leaf. Else half = size / 2 and build the four quadrants. Or build the quadrants first and merge if all four are leaves with the same value.
</details>

## Clarifying Questions
- Is n always a power of two? (Yes.)
- Value of internal nodes? (Any; use 1 to match LeetCode's examples.)

## Example Walkthrough
`[[0,1],[1,0]]`: not uniform → split into 1×1 regions: 0, 1, 1, 0 (all leaves). Level order: root [0,1], then [1,0], [1,1], [1,1], [1,0].

## Approaches

### 1. Check Then Split ⭐ Go-to: O(n² log n) time, O(log n) stack
Scan the region; if uniform, make a leaf, else recurse into 4 quadrants. Each level of recursion scans the whole grid once, and there are log n levels.
**Why it's the go-to:** simplest to write and explain; with n ≤ 64 the extra log factor doesn't matter.

### 2. Split Then Merge (Bottom-Up): O(n²) time, O(log n) stack
Base case 1×1 → leaf. After building four children, if all are leaves with the same value, return one merged leaf. Every cell is touched once.

## Dry Run (Approach 1)
8×8 example (TL, TR, BL, BR quadrants of size 4)

| region | uniform? | result |
|--------|----------|--------|
| whole 8×8 | no | internal, recurse |
| TL 4×4 | yes (1) | leaf [1,1] |
| TR 4×4 | no | internal → four 2×2 leaves: 0, 0, 1, 1 |
| BL 4×4 | yes (1) | leaf [1,1] |
| BR 4×4 | yes (0) | leaf [1,0] |

## Edge Case Check
- 1×1 grid: a single leaf. ✅
- Fully uniform grid: one leaf at the root. ✅
- Checkerboard: a full tree down to 1×1 leaves. ✅

## ⚠️ Pitfalls
- **Quadrant order**: topLeft, topRight, bottomLeft, bottomRight. Mixing up rows and columns swaps TR and BL.
- **Merging children with different values** in the bottom-up version.
- **Serializing**: leaves get four null children in level order, and trailing nulls are trimmed.

## 🎯 What the Interviewer Wants
- A clean recursive decomposition with correct quadrant offsets.
- Complexity of both versions, and the bottom-up merge as the optimization.

## Follow-ups
- **OR of two quad trees:** merge recursively; collapse four equal leaves: LC 0558 Logical OR of Two Binary Grids Represented as Quad-Trees (not added yet)
- **Prefix sums** make the uniformity check O(1) per region, giving O(n²) for the top-down version too.
