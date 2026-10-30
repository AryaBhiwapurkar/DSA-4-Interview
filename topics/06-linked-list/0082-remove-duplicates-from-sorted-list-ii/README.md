---
number: 82
title: Remove Duplicates from Sorted List II
difficulty: Medium
topic: Linked List
pattern: Dummy + skip duplicate runs
link: https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
lists: [LC Top Interview 150]
followup_of: []
related: ["0083 Remove Duplicates from Sorted List", "0026 Remove Duplicates from Sorted Array", "1836 Remove Duplicates From an Unsorted Linked List"]
---

# 0082. Remove Duplicates from Sorted List II

## ⚡ 30-Second Summary
**Pattern:** Dummy node + skip whole runs of duplicates
**Key insight:** In a sorted list, duplicates are adjacent runs. Keep `prev` = last node known to be unique. If `curr` starts a run (curr.next has the same value), skip the entire run and link prev past it; otherwise curr is unique, so advance prev.
**Go-to:** One pass with a dummy, O(n) time, O(1) space

## Problem
Given a sorted linked list, delete every node whose value appears more than once, keeping only values that are unique in the original list. Return the sorted result.

**Examples:**
```
Input:  head = [1,2,3,3,4,4,5]
Output: [1,2,5]
Why:    3 and 4 appear twice, so all their copies go.

Input:  head = [1,1,1,2,3]
Output: [2,3]
Why:    The head itself is part of a duplicate run, so the head changes.
```

**Constraints:**
- 0 ≤ n ≤ 300 (empty list allowed).
- Sorted ascending.

## Hints
<details><summary>Hint 1</summary>
Unlike LC 0083, you remove ALL copies, so even the first node of a run goes. Which node do you need to hold on to?
</details>
<details><summary>Hint 2</summary>
The node before the run. And the head itself might be in a run: what trick handles that?
</details>
<details><summary>Hint 3</summary>
dummy → head, prev = dummy. If curr.next and curr.val == curr.next.val, advance curr past all nodes with that value and set prev.next = curr. Else prev = curr, curr = curr.next.
</details>

## Clarifying Questions
- Keep one copy or remove all copies? (Remove all.)
- Is the list sorted? (Yes; for unsorted input, count values first.)
- Can the whole list disappear? (Yes, e.g. [1,1].)

## Example Walkthrough
`[1,1,1,2,3]`, dummy → 1 …
- curr 1 starts a run: skip all 1s, curr = 2; dummy.next = 2.
- curr 2: next is 3 (different), so prev = 2. curr 3: unique, prev = 3. Result [2,3].

## Approaches

### 1. Count Values, Then Relink: O(n) time, O(n) space
First pass counts each value; second pass keeps nodes with count 1. Works even if the list weren't sorted.

### 2. Dummy + Skip Runs ⭐ Go-to: O(n) time, O(1) space
Uses sortedness: duplicates are contiguous.
**Why it's the go-to:** one pass, constant space, and the dummy covers runs at the head.

## Dry Run (Approach 2)
`[1,2,3,3,4,4,5]`

| curr | starts a run? | action | prev | list so far |
|------|---------------|--------|------|-------------|
| 1 | no | prev = 1 | 1 | 1 |
| 2 | no | prev = 2 | 2 | 1,2 |
| 3 | yes | skip 3,3; prev.next = 4 | 2 | 1,2 → 4… |
| 4 | yes | skip 4,4; prev.next = 5 | 2 | 1,2 → 5 |
| 5 | no | prev = 5 | 5 | **1,2,5** |

## Edge Case Check
- Empty list: return null. ✅
- All duplicates `[1,1]`: dummy.next = null. ✅
- Run at the end `[1,2,2]`: prev(1).next = null. ✅
- No duplicates: unchanged. ✅

## ⚠️ Pitfalls
- **Advancing `prev` after skipping a run**: prev must stay put, since the next node might start another run.
- **Comparing with prev.val** instead of looking ahead at curr.next.
- **No dummy**: a run at the head needs special-case code.
- **C++ / Go null checks**: guard `curr.next` before reading its value.

## 🎯 What the Interviewer Wants
- See the difference from 0083 (remove all vs keep one).
- Dummy node for the head case, and "prev only moves past unique nodes".
- Mention the counting approach for unsorted input.

## Follow-ups
- **Keep one copy of each:** LC 0083 Remove Duplicates from Sorted List (not added yet)
- **Array version, keep one:** [LC 0026 Remove Duplicates from Sorted Array](../../02-two-pointers/0026-remove-duplicates-from-sorted-array/)
- **Unsorted list:** count first: LC 1836 Remove Duplicates From an Unsorted Linked List (not added yet)
