---
number: 124
title: Binary Tree Maximum Path Sum
difficulty: Hard
topic: Trees
pattern: DFS gain, update global
link: https://leetcode.com/problems/binary-tree-maximum-path-sum/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: ["0543 Diameter of Binary Tree"]
related: ["0543 Diameter of Binary Tree", "0112 Path Sum", "0687 Longest Univalue Path"]
---

# 0124. Binary Tree Maximum Path Sum

## ⚡ 30-Second Summary
**Pattern:** DFS returning the best one-sided "gain", global for the best bent path
**Key insight:** Every path has a top node where it bends. At node X, the best path bending there is X + max(0, gain(left)) + max(0, gain(right)), clamping negative branches to 0 (just don't take them). The parent can only continue through one side, so return X + max(0, gainL, gainR).
**Go-to:** Single DFS with a global max, O(n) time, O(h) space

## Problem
A path is any sequence of connected nodes, each used at most once (it doesn't need to pass through the root and has at least one node). Return the maximum sum over all paths.

**Examples:**
```
Input:  root = [1,2,3]
Output: 6
Why:    2 → 1 → 3.

Input:  root = [-10,9,20,null,null,15,7]
Output: 42
Why:    15 → 20 → 7; including -10 would only lower the sum.
```

**Constraints:**
- 1 ≤ n ≤ 3·10⁴; values in [-1000, 1000], so the answer can be negative (all-negative tree).

## Hints
<details><summary>Hint 1</summary>
Like 0543 (diameter), every path bends at one highest node. What's the best path bending at a given node?
</details>
<details><summary>Hint 2</summary>
A negative branch never helps. What should the parent receive from a child: a bent path or a straight one?
</details>
<details><summary>Hint 3</summary>
gain(n) = n.val + max(0, gain(l), gain(r)); best = max(best, n.val + max(0, gain(l)) + max(0, gain(r))). Start best at -∞.
</details>

## Clarifying Questions
- At least one node in the path? (Yes, so an all-negative tree returns its largest value.)
- Must it go through the root? (No.)

## Example Walkthrough
`[-10,9,20,null,null,15,7]`: gain(15) = 15, gain(7) = 7; at 20: best = 20 + 15 + 7 = 42, return 20 + 15 = 35. gain(9) = 9. At -10: best stays 42 (-10 + 9 + 35 = 34).

## Approaches

### 1. Try Every Node as the Top, Recomputing Gains: O(n²) time, O(h) space
For each node, compute the best downward gains of its children with a separate DFS. Correct but repeats work.

### 2. Single DFS With Global Max ⭐ Go-to: O(n) time, O(h) space
**Why it's the go-to:** linear; the same "return one branch, record the bend" template as 0543.

## Dry Run (Approach 2)
`[1,2,3]`

| node | gainL | gainR | best candidate | returns |
|------|-------|-------|----------------|---------|
| 2 | 0 | 0 | 2 | 2 |
| 3 | 0 | 0 | 3 | 3 |
| 1 | 2 | 3 | 1 + 2 + 3 = **6** | 4 |

## Edge Case Check
- All negative `[-3]`: best = -3 (best starts at -∞, not 0). ✅
- `[2,-1]`: the -1 branch is clamped to 0 → 2. ✅
- Best path entirely in a subtree: recorded there by the global. ✅

## ⚠️ Pitfalls
- **Initialising best to 0**: wrong for all-negative trees.
- **Returning the bent path to the parent**: a path can't fork.
- **Forgetting to clamp negative gains** with max(0, ·).

## 🎯 What the Interviewer Wants
- The two quantities (returned gain vs. recorded bent path) and why they differ.
- Correct negative handling.

## Follow-ups
- **Unweighted version (edges):** [LC 0543 Diameter of Binary Tree](../0543-diameter-of-binary-tree/)
- **Longest path with equal values:** LC 0687 Longest Univalue Path (not added yet)
- **Root-to-leaf sums only:** [LC 0112 Path Sum](../0112-path-sum/)
