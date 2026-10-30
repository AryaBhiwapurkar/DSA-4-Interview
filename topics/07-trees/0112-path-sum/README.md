---
number: 112
title: Path Sum
difficulty: Easy
topic: Trees
pattern: DFS with remaining sum
link: https://leetcode.com/problems/path-sum/
lists: [LC Top Interview 150]
followup_of: []
related: ["0113 Path Sum II", "0437 Path Sum III", "0129 Sum Root to Leaf Numbers", "0124 Binary Tree Maximum Path Sum"]
---

# 0112. Path Sum

## ⚡ 30-Second Summary
**Pattern:** DFS passing the remaining target
**Key insight:** Subtract each node's value from the target as you go down. At a leaf, the path works iff the remainder is exactly zero. Only leaves count as path ends.
**Go-to:** Recursive DFS, O(n) time, O(h) space

## Problem
Return whether the tree has a root-to-leaf path whose values add up to `targetSum`.

**Examples:**
```
Input:  root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
Output: true
Why:    5 → 4 → 11 → 2 sums to 22.

Input:  root = [1,2,3], targetSum = 5
Output: false
Why:    The only root-to-leaf sums are 3 and 4.

Input:  root = [], targetSum = 0
Output: false
Why:    An empty tree has no paths.
```

**Constraints:**
- 0 ≤ n ≤ 5000; values and target in ±1000 / ±10⁴, so negatives are allowed (no early pruning on sum > target).

## Hints
<details><summary>Hint 1</summary>
How does the target change as you step from a node to its child?
</details>
<details><summary>Hint 2</summary>
Where must the path end?
</details>
<details><summary>Hint 3</summary>
If null → false. If leaf → remaining == val. Else recurse into both children with target - val.
</details>

## Clarifying Questions
- Must the path end at a leaf? (Yes.)
- Negative values? (Yes, so you can't stop early when the sum exceeds the target.)
- Empty tree with target 0? (False: no path exists.)

## Example Walkthrough
`[1,2], target 1`: root 1 isn't a leaf (it has child 2), so the path must continue to 2: sum 3 → false.

## Approaches

### 1. Recursive DFS ⭐ Go-to: O(n) time, O(h) space
**Why it's the go-to:** three cases, very short.

### 2. Iterative DFS With a Stack of (node, remaining): O(n) time, O(h) space
Same logic without recursion.

## Dry Run (Approach 1)
`[5,4,8,11,null,13,4,7,2,null,null,null,1], target 22` (left branch)

| node | remaining before | leaf? | result |
|------|------------------|-------|--------|
| 5 | 22 | no | recurse with 17 |
| 4 | 17 | no | recurse with 13 |
| 11 | 13 | no | recurse with 2 |
| 7 | 2 | yes | 7 ≠ 2 → false |
| 2 | 2 | yes | 2 = 2 → **true** |

## Edge Case Check
- Empty tree: false. ✅
- Root with one child, target = root value: false (root isn't a leaf). ✅
- Negative values: no pruning, all paths explored. ✅

## ⚠️ Pitfalls
- **Returning true at a null child** when the remainder is 0: lets internal nodes count as path ends.
- **Pruning when the running sum exceeds the target**: wrong with negatives.

## 🎯 What the Interviewer Wants
- Correct leaf definition.
- Clean top-down state (remaining sum).

## Follow-ups
- **Return all such paths:** backtracking with a path list: LC 0113 Path Sum II (not added yet)
- **Paths starting anywhere, going down:** prefix sums + hashmap: LC 0437 Path Sum III (not added yet)
- **Numbers formed by paths:** [LC 0129 Sum Root to Leaf Numbers](../0129-sum-root-to-leaf-numbers/)
