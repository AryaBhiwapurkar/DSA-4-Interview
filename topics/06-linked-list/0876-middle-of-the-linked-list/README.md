---
number: 876
title: Middle of the Linked List
difficulty: Easy
topic: Linked List
pattern: Fast/slow pointers
link: https://leetcode.com/problems/middle-of-the-linked-list/
lists: [Interview Extras]
followup_of: []
related: ["0234 Palindrome Linked List", "0143 Reorder List", "0148 Sort List", "0141 Linked List Cycle"]
---

# 0876. Middle of the Linked List

## ⚡ 30-Second Summary
**Pattern:** Fast pointer moves 2, slow moves 1
**Key insight:** When fast reaches the end, slow has walked half as far: it's at the middle. With `while fast && fast.next`, slow lands on the **second** middle for even lengths, which is what this problem wants.
**Go-to:** Fast/slow pointers, O(n) time, O(1) space

## Problem
Return the middle node of a singly linked list. If there are two middle nodes, return the second one. [LeetCode](https://leetcode.com/problems/middle-of-the-linked-list/)

**Examples:**
```
Input:  head = [1,2,3,4,5]
Output: [3,4,5]
Why:    3 is the middle of five nodes; the output is the list from there on.

Input:  head = [1,2,3,4,5,6]
Output: [4,5,6]
Why:    Six nodes have two middles (3 and 4); take the second.
```

**Constraints:**
- 1 ≤ n ≤ 100.

## Hints
<details><summary>Hint 1</summary>
The two-pass way: count the nodes, then walk n / 2 steps. Can you do it in one pass?
</details>
<details><summary>Hint 2</summary>
Move two pointers at different speeds. When the faster one finishes, where is the slower one?
</details>
<details><summary>Hint 3</summary>
slow = fast = head; while fast and fast.next: slow += 1 step, fast += 2 steps. Return slow.
</details>

## Clarifying Questions
- For even length, first or second middle? (Second here; LC 234 / 143 / 148 want the first.)
- Return the node, not the value? (The node.)
- Can the list be empty? (No, n ≥ 1.)

## Example Walkthrough
`[1,2,3,4,5]`: (slow, fast) = (1,1) → (2,3) → (3,5). fast.next is null, so stop: slow = 3.

## Approaches

### 1. Count, then Walk: O(n) time, O(1) space
Count n, then step n / 2 times from head. Two passes, but perfectly fine.

### 2. Fast/Slow Pointers ⭐ Go-to: O(n) time, O(1) space
One pass, two pointers.
**Why it's the go-to:** it's the building block for LC 234, 143 and 148; know both loop conditions by heart.

## Dry Run (Approach 2)
`[1,2,3,4,5,6]`

| step | slow | fast | fast && fast.next? |
|------|------|------|--------------------|
| 0 | 1 | 1 | yes |
| 1 | 2 | 3 | yes |
| 2 | 3 | 5 | yes |
| 3 | 4 | null | no → return **4** |

## Edge Case Check
- One node → loop never runs → itself. ✅
- Two nodes → slow moves once → the second node. ✅

## ⚠️ Pitfalls
- **Mixing up the two loop conditions:**
  - `fast && fast.next` → second middle.
  - `fast.next && fast.next.next` → first middle.
- **Using `n / 2` vs `(n − 1) / 2`** in the counting version flips which middle you get.

## 🎯 What the Interviewer Wants
- The fast/slow idea in one clean pass.
- Knowing which middle each loop condition gives.

## Follow-ups
- **Middle as the split point for a palindrome check:** [LC 0234 Palindrome Linked List](../0234-palindrome-linked-list/)
- **Split, reverse, interleave:** [LC 0143 Reorder List](../0143-reorder-list/)
- **Split for merge sort:** [LC 0148 Sort List](../0148-sort-list/)
- **Same two speeds for cycle detection:** [LC 0141 Linked List Cycle](../0141-linked-list-cycle/)
