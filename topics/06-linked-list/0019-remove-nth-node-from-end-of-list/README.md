---
number: 19
title: Remove Nth Node From End of List
difficulty: Medium
topic: Linked List
pattern: Fast/slow with n gap
link: https://leetcode.com/problems/remove-nth-node-from-end-of-list/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0876 Middle of the Linked List", "0061 Rotate List", "1721 Swapping Nodes in a Linked List"]
---

# 0019. Remove Nth Node From End of List

## ⚡ 30-Second Summary
**Pattern:** Two pointers with a fixed gap + dummy node
**Key insight:** Put `fast` n nodes ahead of `slow`. Move both until fast is on the last node; slow is then just before the node to delete. A dummy in front lets this work when the head itself is removed.
**Go-to:** One pass with an n-gap and a dummy, O(L) time, O(1) space

## Problem
Remove the n-th node from the end of a linked list and return the head. n is always valid (1 ≤ n ≤ length).

**Examples:**
```
Input:  head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]
Why:    The 2nd from the end is 4.

Input:  head = [1], n = 1
Output: []
Why:    Removing the only node leaves an empty list.

Input:  head = [1,2], n = 1
Output: [1]
Why:    The last node goes.
```

**Constraints:**
- 1 ≤ length ≤ 30; 1 ≤ n ≤ length (always valid).
- Follow-up: do it in one pass.

## Hints
<details><summary>Hint 1</summary>
With the length L, which node from the front do you need to unlink?
</details>
<details><summary>Hint 2</summary>
For one pass: if one pointer is exactly n nodes ahead of another, where is the trailing pointer when the leader reaches the end?
</details>
<details><summary>Hint 3</summary>
Start both at a dummy before head. Move fast n steps. Then move both until fast.next is null. Now slow.next is the target: slow.next = slow.next.next.
</details>

## Clarifying Questions
- Is n always valid? (Yes.)
- Can the head be the one removed? (Yes, when n == length.)
- One pass required? (It's the follow-up; two passes are fine to start.)

## Example Walkthrough
`[1,2,3,4,5], n = 2`, dummy → 1 → … → 5
- fast moves 2 steps from dummy: fast = 2.
- Move both until fast.next is null: (slow, fast) = (1,3), (2,4), (3,5).
- slow = 3, so unlink 4: 3 → 5. Result [1,2,3,5].

## Approaches

### 1. Two Passes (Count Length): O(L) time, O(1) space
Count L, then walk to node L - n (from a dummy) and unlink the next one.

### 2. One Pass With an n-Gap ⭐ Go-to: O(L) time, O(1) space
Fast leads by n; when fast hits the last node, slow is the predecessor.
**Why it's the go-to:** answers the follow-up directly; the dummy handles removing the head.

## Dry Run (Approach 2)
`[1,2], n = 2` (removes the head)

| step | slow | fast | note |
|------|------|------|------|
| start | dummy | dummy | |
| advance fast ×2 | dummy | 2 | fast.next is null already |
| unlink | dummy.next = 2 | | result **[2]** |

## Edge Case Check
- Remove the head (n == L): slow stays at the dummy; return dummy.next. ✅
- Single node, n = 1: result empty. ✅
- Remove the last node (n = 1): slow ends at the second-to-last. ✅

## ⚠️ Pitfalls
- **No dummy node**: removing the head needs a special case (and is the most common bug).
- **Off-by-one in the gap**: with both starting at the dummy, advance fast exactly n times and loop while `fast.next`.
- **Returning `head` instead of `dummy.next`**: wrong when the head was removed.
- **C++ memory**: in real code `delete` the removed node; LeetCode doesn't require it.

## 🎯 What the Interviewer Wants
- Two-pass first, then the gap trick for one pass.
- The dummy-node idea and why it removes the head special case.
- Exact loop bounds explained with a tiny example.

## Follow-ups
- **Find the middle:** fast moves 2, slow moves 1: LC 0876 Middle of the Linked List (not added yet)
- **Rotate by k (needs the k-th from the end too):** [LC 0061 Rotate List](../0061-rotate-list/)
- **Swap the k-th from start and end:** LC 1721 Swapping Nodes in a Linked List (not added yet)
- **n might be invalid:** check fast doesn't hit null while building the gap.
