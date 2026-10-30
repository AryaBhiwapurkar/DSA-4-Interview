---
number: 86
title: Partition List
difficulty: Medium
topic: Linked List
pattern: Two dummy lists
link: https://leetcode.com/problems/partition-list/
lists: [LC Top Interview 150]
followup_of: []
related: ["0328 Odd Even Linked List", "0075 Sort Colors", "2161 Partition Array According to Given Pivot"]
---

# 0086. Partition List

## ⚡ 30-Second Summary
**Pattern:** Two dummy-headed lists, then concatenate
**Key insight:** Walk the list once and append each node to either a "less than x" list or a "≥ x" list. Appending keeps the original relative order in both (a stable partition). Join less → greater, and terminate the greater list.
**Go-to:** Two dummy lists, O(n) time, O(1) extra space

## Problem
Given a linked list and a value x, rearrange it so all nodes with value < x come before nodes with value ≥ x, preserving the original relative order inside each group.

**Examples:**
```
Input:  head = [1,4,3,2,5,2], x = 3
Output: [1,2,2,4,3,5]
Why:    Values < 3 (1,2,2) first, then the rest (4,3,5), each in original order.

Input:  head = [2,1], x = 2
Output: [1,2]
Why:    1 < 2 moves ahead of 2.
```

**Constraints:**
- 0 ≤ n ≤ 200 (empty list allowed).
- Values and x in [-200, 200].

## Hints
<details><summary>Hint 1</summary>
Swapping nodes in place to partition is messy and breaks the order. What if you build the two groups separately?
</details>
<details><summary>Hint 2</summary>
Two lists, each with a dummy head and a tail pointer. Where does each node go?
</details>
<details><summary>Hint 3</summary>
Append to `less` if val < x, else to `greater`. At the end: greaterTail.next = null, lessTail.next = greaterDummy.next. Return lessDummy.next.
</details>

## Clarifying Questions
- Must relative order be kept? (Yes, within both groups.)
- Where do values equal to x go? (In the ≥ group.)
- Empty list? (Return null.)

## Example Walkthrough
`[1,4,3,2,5,2], x = 3`
- 1 → less. 4 → greater. 3 → greater. 2 → less. 5 → greater. 2 → less.
- less: 1,2,2. greater: 4,3,5. Join: 1,2,2,4,3,5.

## Approaches

### 1. Collect Values Into Two Arrays, Rebuild: O(n) time, O(n) space
Split the values, concatenate, build a new list. Simple, but extra memory and new nodes.

### 2. Two Dummy Lists ⭐ Go-to: O(n) time, O(1) extra space
Relink the existing nodes into two chains, then join them.
**Why it's the go-to:** single pass, stable, no special cases thanks to the dummies.

## Dry Run (Approach 2)
`[2,1], x = 2`

| node | < 2? | less chain | greater chain |
|------|------|------------|---------------|
| 2 | no | (empty) | 2 |
| 1 | yes | 1 | 2 |
| join | | 1 → 2 → null | |
| result | | **[1,2]** | |

## Edge Case Check
- Empty list: both chains empty, return null. ✅
- All < x: greater chain empty; lessTail.next = null. ✅
- All ≥ x: less chain empty; result is the greater chain. ✅

## ⚠️ Pitfalls
- **Not setting `greaterTail.next = null`**: the last greater node may still point at a less node, creating a cycle.
- **Returning `head`**: the first node might have moved.
- **Putting equal values in the wrong group**: `< x` goes first; `== x` goes to the second group.

## 🎯 What the Interviewer Wants
- Stability explained (appending preserves order).
- Dummy nodes to avoid special cases.
- The cycle bug from not terminating the second chain.

## Follow-ups
- **Group by odd/even position:** same two-chain idea: LC 0328 Odd Even Linked List (not added yet)
- **Three-way partition (Dutch flag) on an array:** LC 0075 Sort Colors (not added yet)
- **Array version with a pivot:** LC 2161 Partition Array According to Given Pivot (not added yet)
