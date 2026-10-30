---
number: 148
title: Sort List
difficulty: Medium
topic: Linked List
pattern: Merge sort on list
link: https://leetcode.com/problems/sort-list/
lists: [LC Top Interview 150]
followup_of: ["0021 Merge Two Sorted Lists"]
related: ["0021 Merge Two Sorted Lists", "0147 Insertion Sort List", "0023 Merge k Sorted Lists"]
---

# 0148. Sort List

## ⚡ 30-Second Summary
**Pattern:** Merge sort on a linked list
**Key insight:** Merge sort fits linked lists perfectly: splitting at the middle is a slow/fast walk, and merging two sorted lists needs no extra array (0021). Top-down recursion uses O(log n) stack; the bottom-up version merges runs of size 1, 2, 4, … iteratively for true O(1) space.
**Go-to:** Top-down merge sort, O(n log n) time, O(log n) stack

## Problem
Sort a linked list in ascending order and return its head. Follow-up: O(n log n) time with O(1) memory.

**Examples:**
```
Input:  head = [4,2,1,3]
Output: [1,2,3,4]
Why:    Plain ascending sort.

Input:  head = [-1,5,3,4,0]
Output: [-1,0,3,4,5]
Why:    Negatives sort first.

Input:  head = []
Output: []
Why:    Nothing to sort.
```

**Constraints:**
- 0 ≤ n ≤ 5·10⁴, so O(n²) sorts (insertion sort) are too slow.
- Values in ±10⁵.

## Hints
<details><summary>Hint 1</summary>
Which O(n log n) sort doesn't need random access?
</details>
<details><summary>Hint 2</summary>
Merge sort: split, sort halves, merge. How do you split a list at the middle?
</details>
<details><summary>Hint 3</summary>
slow = head, fast = head.next; advance until fast hits the end; cut after slow. Recurse on both halves and merge with a dummy node. For O(1) space, merge runs of width 1, 2, 4, … bottom-up.
</details>

## Clarifying Questions
- Stable? (Not required, but merge sort is stable if ties take from the left.)
- Can I copy values into an array? (Works, but it's O(n) space and dodges the point.)
- O(1) memory required? (It's the follow-up; recursion uses O(log n).)

## Example Walkthrough
`[4,2,1,3]`
- Split → [4,2] and [1,3]. Split again → [4],[2] and [1],[3].
- Merge → [2,4] and [1,3]. Merge → [1,2,3,4].

## Approaches

### 1. Copy Values, Sort, Write Back: O(n log n) time, O(n) space
Fine to mention, but the interviewer wants a list algorithm.

### 2. Top-Down Merge Sort ⭐ Go-to: O(n log n) time, O(log n) stack
Split with slow/fast, recurse, merge.
**Why it's the go-to:** short and reuses 0021's merge; mention bottom-up for the O(1) follow-up.

### 3. Bottom-Up Merge Sort: O(n log n) time, O(1) space
For width = 1, 2, 4, …: walk the list, cut off two runs of `width`, merge them, append to the result tail. More pointer bookkeeping, but meets the strict follow-up.

## Dry Run (Approach 2)
`[-1,5,3,4,0]`

| level | split | merged result |
|-------|-------|---------------|
| 0 | [-1,5,3] \| [4,0] | |
| 1 | [-1,5] \| [3] and [4] \| [0] | |
| 2 | [-1] \| [5] | [-1,5] |
| 1 | | [-1,5] + [3] = [-1,3,5]; [4] + [0] = [0,4] |
| 0 | | [-1,3,5] + [0,4] = **[-1,0,3,4,5]** |

## Edge Case Check
- Empty or single node: base case, return as is. ✅
- Two nodes: fast = head.next, so slow stays at head and the split is 1 + 1 (no infinite recursion). ✅
- Duplicates `[2,1,2,1]`: [1,1,2,2]. ✅

## ⚠️ Pitfalls
- **Starting fast at head** (instead of head.next): for two nodes, slow moves to the second node and the left half never shrinks → infinite recursion.
- **Not cutting** (`slow.next = null`) before recursing.
- **Bottom-up: forgetting to reconnect** the merged run to the previous tail and to advance the tail to the end of the merged run.
- **Python recursion depth** is log n here, so it's fine (≈16 for 5·10⁴).

## 🎯 What the Interviewer Wants
- Pick merge sort and explain why (no random access needed, merge is O(1) space on lists).
- Correct split for even lengths.
- Know the bottom-up variant for strict O(1) space.

## Follow-ups
- **Merge step on its own:** [LC 0021 Merge Two Sorted Lists](../0021-merge-two-sorted-lists/)
- **Simpler but O(n²):** LC 0147 Insertion Sort List (not added yet)
- **Merge many lists:** [LC 0023 Merge k Sorted Lists](../0023-merge-k-sorted-lists/)
- **Quicksort on a list:** possible (partition into three lists) but worst case O(n²).
