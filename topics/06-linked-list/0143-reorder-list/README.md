---
number: 143
title: Reorder List
difficulty: Medium
topic: Linked List
pattern: Find mid + reverse + merge
link: https://leetcode.com/problems/reorder-list/
lists: [NeetCode 150]
followup_of: []
related: ["0206 Reverse Linked List", "0876 Middle of the Linked List", "0234 Palindrome Linked List", "0021 Merge Two Sorted Lists"]
---

# 0143. Reorder List

## ⚡ 30-Second Summary
**Pattern:** Find middle + reverse second half + interleave
**Key insight:** The order L0, Ln, L1, Ln-1, … alternates between the front half (forward) and the back half (backward). Split at the middle, reverse the back half, then weave the two lists together.
**Go-to:** Mid + reverse + merge, O(n) time, O(1) space

## Problem
Rearrange a linked list L0 → L1 → … → Ln into L0 → Ln → L1 → Ln-1 → L2 → … by relinking nodes (not by changing values). Modify it in place; return nothing. [LeetCode](https://leetcode.com/problems/reorder-list/)

**Examples:**
```
Input:  head = [1,2,3,4]
Output: [1,4,2,3]
Why:    First, last, second, second-last.

Input:  head = [1,2,3,4,5]
Output: [1,5,2,4,3]
Why:    Same pattern; the middle node 3 ends up last.
```

**Constraints:**
- 1 ≤ n ≤ 5·10⁴.
- Nodes must be relinked; values can't be swapped.

## Hints
<details><summary>Hint 1</summary>
You need to walk the back half from the end. A singly linked list can't go backward... unless you change it.
</details>
<details><summary>Hint 2</summary>
Three classic subroutines combine here. Which ones? (Middle, reverse, merge.)
</details>
<details><summary>Hint 3</summary>
Find the middle with slow/fast, cut after it, reverse the second half, then alternately link one node from each half.
</details>

## Clarifying Questions
- Swap values or relink nodes? (Relink.)
- Return a new head? (No, void; the head stays the same.)
- Odd length: where does the middle go? (It ends up last.)

## Example Walkthrough
`[1,2,3,4,5]`
- Middle: slow stops at 3. First half 1 → 2 → 3, second half 4 → 5.
- Reverse second: 5 → 4.
- Weave: 1, 5, 2, 4, 3. Result [1,5,2,4,3].

## Approaches

### 1. Array of Nodes + Two Pointers: O(n) time, O(n) space
Store node pointers in an array, then link nodes[i] → nodes[j] → nodes[i+1] … moving i up and j down. Easy, but O(n) memory.

### 2. Mid + Reverse + Merge ⭐ Go-to: O(n) time, O(1) space
Three O(n) passes, constant memory.
**Why it's the go-to:** it's what interviewers are looking for, and it shows you can compose 0876 + 0206 + a merge.

## Dry Run (Approach 2)
`[1,2,3,4]`

| phase | state |
|-------|-------|
| find mid (slow/fast) | slow = 2 (fast stops at 3 since 3.next.next is null) |
| cut | first: 1 → 2, second: 3 → 4 |
| reverse second | 4 → 3 |
| weave step 1 | 1 → 4, then 4 → 2 |
| weave step 2 | 2 → 3, then 3 → (second exhausted) |
| result | **1 → 4 → 2 → 3** |

## Edge Case Check
- One node: second half empty, nothing changes. ✅
- Two nodes `[1,2]`: first [1], second [2]; weave gives [1,2]. ✅
- Odd length: first half is longer by one, so its extra node is last. ✅

## ⚠️ Pitfalls
- **Not cutting the first half** (`slow.next = null`): creates a cycle after weaving.
- **Middle choice**: use `while fast.next and fast.next.next` so the first half is the same size or one longer.
- **Losing pointers while weaving**: save both `next`s before relinking.
- **Swapping values**: not allowed and misses the point.

## 🎯 What the Interviewer Wants
- Decompose into three known subroutines and say so up front.
- O(1) space, with the array version as a stepping stone.
- Careful pointer bookkeeping during the weave.

## Follow-ups
- **Reverse a list:** [LC 0206 Reverse Linked List](../0206-reverse-linked-list/)
- **Find the middle:** LC 0876 Middle of the Linked List (not added yet)
- **Palindrome check with the same split + reverse:** LC 0234 Palindrome Linked List (not added yet)
- **Merge two lists by value instead of alternating:** [LC 0021 Merge Two Sorted Lists](../0021-merge-two-sorted-lists/)
