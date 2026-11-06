---
number: 21
title: Merge Two Sorted Lists
difficulty: Easy
topic: Linked List
pattern: Dummy head merge
link: https://leetcode.com/problems/merge-two-sorted-lists/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0023 Merge k Sorted Lists", "0088 Merge Sorted Array", "0148 Sort List"]
---

# 0021. Merge Two Sorted Lists

## ⚡ 30-Second Summary
**Pattern:** Dummy head + tail pointer merge
**Key insight:** Repeatedly take the smaller of the two front nodes and append it to a tail. A dummy node in front removes the "which node is the head?" special case. When one list runs out, attach the other in one step.
**Go-to:** Iterative merge with a dummy node, O(m + n) time, O(1) space

## Problem
Merge two sorted linked lists into one sorted list by splicing their nodes together, and return its head. [LeetCode](https://leetcode.com/problems/merge-two-sorted-lists/)

**Examples:**
```
Input:  list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]
Why:    Interleave by always taking the smaller front value.

Input:  list1 = [], list2 = []
Output: []
Why:    Nothing to merge.

Input:  list1 = [], list2 = [0]
Output: [0]
Why:    One empty list: the answer is the other list.
```

**Constraints:**
- 0 ≤ each length ≤ 50 (either or both can be empty).
- Both lists sorted non-decreasing.

## Hints
<details><summary>Hint 1</summary>
Like merging in merge sort: which node must come first in the result?
</details>
<details><summary>Hint 2</summary>
The head depends on the first comparison. How can you avoid writing that as a special case?
</details>
<details><summary>Hint 3</summary>
Start with a dummy node and tail = dummy. While both lists are non-empty, link the smaller to tail.next and advance. Then link whichever list remains. Return dummy.next.
</details>

## Clarifying Questions
- Can either list be empty? (Yes.)
- Splice existing nodes or create new ones? (Splice.)
- Is the order stable for equal values? (Doesn't matter for values; taking from list1 on ties keeps it stable.)

## Example Walkthrough
`[1,2,4]` and `[1,3,4]`
- 1 vs 1 → take list1's 1. 2 vs 1 → take list2's 1. 2 vs 3 → 2. 4 vs 3 → 3. 4 vs 4 → list1's 4.
- list1 is empty: attach the rest of list2 ([4]). Result 1,1,2,3,4,4.

## Approaches

### 1. Collect, Sort, Rebuild: O((m+n) log(m+n)) time, O(m+n) space
Ignores that inputs are sorted.

### 2. Recursive Merge: O(m + n) time, O(m + n) stack
`if l1.val <= l2.val: l1.next = merge(l1.next, l2); return l1` (and symmetric). Short, but uses stack.

### 3. Iterative With Dummy ⭐ Go-to: O(m + n) time, O(1) space
Tail pointer + dummy head; attach the leftover list at the end.
**Why it's the go-to:** O(1) space, no special cases; it's the merge step reused by 0023 and 0148.

## Dry Run (Approach 3)
`[5]` and `[1,2,3]`

| l1 | l2 | take | result so far |
|----|----|------|---------------|
| 5 | 1 | l2 (1) | 1 |
| 5 | 2 | l2 (2) | 1,2 |
| 5 | 3 | l2 (3) | 1,2,3 |
| 5 | null | attach l1 | **1,2,3,5** |

## Edge Case Check
- Both empty: dummy.next is null. ✅
- One empty: loop skipped, attach the other. ✅
- All of one list smaller than the other: one list is consumed, the other attached whole. ✅

## ⚠️ Pitfalls
- **Forgetting to attach the leftover**: drops the tail of the longer list.
- **Returning `dummy` instead of `dummy.next`.**
- **Not advancing `tail`** after linking: overwrites the same next pointer.
- **C++: heap-allocating the dummy** and leaking it; a stack `ListNode dummy;` is cleaner.

## 🎯 What the Interviewer Wants
- The dummy-node idiom, explained in one sentence.
- O(1) space by splicing, not copying.
- Mention the recursive version and its stack cost.

## Follow-ups
- **Merge k sorted lists:** heap or divide and conquer: [LC 0023 Merge k Sorted Lists](../0023-merge-k-sorted-lists/)
- **Arrays instead of lists, in place:** [LC 0088 Merge Sorted Array](../../02-two-pointers/0088-merge-sorted-array/)
- **Sort a list with merge sort:** [LC 0148 Sort List](../0148-sort-list/)
