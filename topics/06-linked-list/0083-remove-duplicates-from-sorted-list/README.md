---
number: 83
title: Remove Duplicates from Sorted List
difficulty: Easy
topic: Linked List
pattern: Single pointer, skip equal successors
link: https://leetcode.com/problems/remove-duplicates-from-sorted-list/
lists: [Interview Extras]
followup_of: []
related: ["0082 Remove Duplicates from Sorted List II", "0026 Remove Duplicates from Sorted Array", "0203 Remove Linked List Elements"]
---

# 0083. Remove Duplicates from Sorted List

## ⚡ 30-Second Summary
**Pattern:** Compare each node with its next; unlink the next while it's equal
**Key insight:** The list is sorted, so equal values are adjacent. At node cur: if `cur.next.val == cur.val`, skip it (`cur.next = cur.next.next`) and stay on cur; otherwise move on. The head is never removed, so no dummy is needed.
**Go-to:** Iterative skip, O(n) time, O(1) space

## Problem
Given a sorted linked list, remove duplicate values so each value appears once, and return the list (still sorted). [LeetCode](https://leetcode.com/problems/remove-duplicates-from-sorted-list/)

**Examples:**
```
Input:  head = [1,1,2]
Output: [1,2]
Why:    The second 1 goes.

Input:  head = [1,1,2,3,3]
Output: [1,2,3]
Why:    One extra 1 and one extra 3 go.
```

**Constraints:**
- 0 ≤ n ≤ 300; sorted ascending; values in [−100, 100].

## Hints
<details><summary>Hint 1</summary>
Where can the duplicates of a value be, given the list is sorted?
</details>
<details><summary>Hint 2</summary>
Right after the first occurrence. So you only ever compare a node with its next.
</details>
<details><summary>Hint 3</summary>
While cur and cur.next: equal → cur.next = cur.next.next (don't advance); different → cur = cur.next.
</details>

## Clarifying Questions
- Keep one copy of each value (not remove all copies)? (Keep one; removing all copies is LC 82.)
- Is the list sorted? (Yes; otherwise you'd need a hash set.)
- Free the removed nodes? (In C++, yes if you own them.)

## Example Walkthrough
`[1,1,2,3,3]`: at the first 1, the next is 1 → unlink it; now the next is 2 → move to 2; next is 3 → move to 3; next is 3 → unlink; next is null → done. Result [1,2,3].

## Approaches

### 1. Recursion: O(n) time, O(n) stack
Dedupe `head.next` recursively, then drop `head.next` if it equals head. Short, but n frames.

### 2. Iterative Skip ⭐ Go-to: O(n) time, O(1) space
One pointer, unlinking equal successors.
**Why it's the go-to:** about four lines, constant space, and the head never changes.

## Dry Run (Approach 2)
`[1,1,1,2]`

| cur | cur.next | equal? | action | list |
|-----|----------|--------|--------|------|
| 1a | 1b | yes | unlink 1b | 1a,1c,2 |
| 1a | 1c | yes | unlink 1c | 1a,2 |
| 1a | 2 | no | cur = 2 | 1a,2 |
| 2 | null | – | stop | **[1,2]** |

## Edge Case Check
- Empty list → return null. ✅
- All the same `[1,1,1]` → stays on the head, unlinking everything after it. ✅
- No duplicates → just walks. ✅

## ⚠️ Pitfalls
- **Advancing after unlinking:** with three or more equal values you'd skip one comparison and leave a duplicate.
- **Memory leak in C++:** `delete` the unlinked node if the list owns its nodes.
- **Using a dummy and comparing with it:** unnecessary here; the first node always stays.

## 🎯 What the Interviewer Wants
- Use the sorted order: only compare neighbours.
- Correct "don't advance after a removal" logic.
- Contrast with LC 82 (drop every copy), which needs a dummy.

## Follow-ups
- **Remove every value that has duplicates:** [LC 0082 Remove Duplicates from Sorted List II](../0082-remove-duplicates-from-sorted-list-ii/)
- **Array version with two pointers:** [LC 0026 Remove Duplicates from Sorted Array](../../02-two-pointers/0026-remove-duplicates-from-sorted-array/)
- **Remove by value:** LC 0203 Remove Linked List Elements (not added yet)
