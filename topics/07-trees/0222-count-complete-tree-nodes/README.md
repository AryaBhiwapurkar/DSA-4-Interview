---
number: 222
title: Count Complete Tree Nodes
difficulty: Easy
topic: Trees
pattern: Compare left/right heights
link: https://leetcode.com/problems/count-complete-tree-nodes/
lists: [LC Top Interview 150]
followup_of: []
related: ["0104 Maximum Depth of Binary Tree", "0958 Check Completeness of a Binary Tree"]
---

# 0222. Count Complete Tree Nodes

## ⚡ 30-Second Summary
**Pattern:** Use completeness to skip perfect subtrees
**Key insight:** In a complete tree, if the leftmost depth equals the rightmost depth, the tree is perfect and has 2^h - 1 nodes. Otherwise recurse into both children; at least one of them is perfect, so each level only does real work on one path: O(log² n).
**Go-to:** Spine heights + recursion, O(log² n) time, O(log n) space

## Problem
Count the nodes of a complete binary tree (every level full except possibly the last, which is filled from the left), in less than O(n) time. [LeetCode](https://leetcode.com/problems/count-complete-tree-nodes/)

**Examples:**
```
Input:  root = [1,2,3,4,5,6]
Output: 6
Why:    Six nodes; the last level has 4, 5, 6.

Input:  root = []
Output: 0
Why:    Empty tree.

Input:  root = [1]
Output: 1
Why:    Just the root.
```

**Constraints:**
- 0 ≤ n ≤ 5·10⁴; the tree is guaranteed complete.
- Follow-up: faster than O(n).

## Hints
<details><summary>Hint 1</summary>
A plain traversal is O(n). What's special about a complete tree?
</details>
<details><summary>Hint 2</summary>
How many nodes does a perfect tree of height h have? How can you check perfection quickly?
</details>
<details><summary>Hint 3</summary>
Walk the left spine and the right spine. Equal → 2^h - 1. Else 1 + count(left) + count(right).
</details>

## Clarifying Questions
- Guaranteed complete? (Yes; otherwise the shortcut is invalid.)
- Empty tree? (0.)

## Example Walkthrough
`[1,2,3,4,5,6]`: left spine 1-2-4 (3), right spine 1-3 (2) → not perfect. Left child 2: spines 2-4, 2-5 equal (2) → 3 nodes. Right child 3: spines 3-6 (2) vs 3 (1) → recurse: 6 → 1, null → 0 → 1 + 1 + 0 = 2. Total 1 + 3 + 2 = 6.

## Approaches

### 1. Plain DFS Count: O(n) time, O(h) space
1 + count(left) + count(right). Correct for any tree.

### 2. Spine Heights + Recursion ⭐ Go-to: O(log² n) time, O(log n) space
**Why it's the go-to:** answers the follow-up with a few lines; O(log n) recursion levels × O(log n) spine walks.

## Dry Run (Approach 2)
`[1,2,3,4,5,6,7]`

| node | left spine | right spine | perfect? | count |
|------|------------|-------------|----------|-------|
| 1 | 3 | 3 | yes | 2³ - 1 = **7** |

## Edge Case Check
- Perfect tree: answered at the root in O(log n). ✅
- Last level with a single node `[1,2,3,4]`: recursion → 4. ✅
- Empty: 0. ✅

## ⚠️ Pitfalls
- **Measuring heights with a full DFS**: O(n) per call. Walk only the spines.
- **`1 << h` with h in the wrong unit**: spine length counts nodes, nodes = 2^h - 1.
- **Using it on a non-complete tree**: wrong answers.

## 🎯 What the Interviewer Wants
- Exploit the completeness guarantee.
- Derive O(log² n): at each level, one of the two recursive calls is a perfect subtree (O(log n) to detect).

## Follow-ups
- **Binary search on the last level:** check whether leaf index k exists by following bits; also O(log² n).
- **Check completeness:** BFS until the first null, then no more nodes: LC 0958 Check Completeness of a Binary Tree (not added yet)
