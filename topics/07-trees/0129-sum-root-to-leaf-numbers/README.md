---
number: 129
title: Sum Root to Leaf Numbers
difficulty: Medium
topic: Trees
pattern: DFS carrying the number
link: https://leetcode.com/problems/sum-root-to-leaf-numbers/
lists: [LC Top Interview 150]
followup_of: []
related: ["0112 Path Sum", "0257 Binary Tree Paths", "1022 Sum of Root To Leaf Binary Numbers"]
---

# 0129. Sum Root to Leaf Numbers

## ⚡ 30-Second Summary
**Pattern:** DFS carrying the number built so far
**Key insight:** Going down one level appends a digit: cur = cur·10 + val. At a leaf, cur is a complete number; add it. The answer for a subtree is the sum over its leaves.
**Go-to:** Recursive DFS, O(n) time, O(h) space

## Problem
Each node holds a digit 0-9. Every root-to-leaf path spells a number (root digit first). Return the sum of all those numbers.

**Examples:**
```
Input:  root = [1,2,3]
Output: 25
Why:    Paths give 12 and 13.

Input:  root = [4,9,0,5,1]
Output: 1026
Why:    Paths give 495, 491 and 40.
```

**Constraints:**
- 1 ≤ n ≤ 1000; depth ≤ 10, so every number fits in a 32-bit int.

## Hints
<details><summary>Hint 1</summary>
If the path so far spells 49 and the next digit is 5, what's the new number?
</details>
<details><summary>Hint 2</summary>
What should a leaf return, and what should an internal node return?
</details>
<details><summary>Hint 3</summary>
dfs(node, cur): cur = cur·10 + val; leaf → cur; else dfs(left, cur) + dfs(right, cur) (null → 0).
</details>

## Clarifying Questions
- Leading zeros? (Fine: a root of 0 just contributes 0·10.)
- Overflow? (Depth ≤ 10 keeps sums in range.)

## Example Walkthrough
`[4,9,0,5,1]`: 4 → 49 → 495 (leaf), 491 (leaf); 4 → 40 (leaf). 495 + 491 + 40 = 1026.

## Approaches

### 1. Recursive DFS ⭐ Go-to: O(n) time, O(h) space
**Why it's the go-to:** the number is the only state, passed as a parameter.

### 2. BFS With (node, number) Pairs: O(n) time, O(w) space
Same idea iteratively; add the number when a leaf is popped.

## Dry Run (Approach 1)
`[1,2,3]`

| node | cur | leaf? | returns |
|------|-----|-------|---------|
| 2 | 12 | yes | 12 |
| 3 | 13 | yes | 13 |
| 1 | 1 | no | **25** |

## Edge Case Check
- Single node: its digit. ✅
- One-child nodes: the null side returns 0, not cur. ✅

## ⚠️ Pitfalls
- **Returning `cur` at null nodes**: double-counts paths through one-child nodes.
- **Building strings and parsing**: works but slower and clunky.

## 🎯 What the Interviewer Wants
- Top-down accumulation (cur·10 + val) with bottom-up summing.
- Correct leaf vs null handling.

## Follow-ups
- **List the paths as strings:** LC 0257 Binary Tree Paths (not added yet)
- **Binary digits:** cur·2 + val: LC 1022 Sum of Root To Leaf Binary Numbers (not added yet)
- **Target sum instead:** [LC 0112 Path Sum](../0112-path-sum/)
