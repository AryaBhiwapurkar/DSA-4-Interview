---
number: 206
title: Reverse Linked List
difficulty: Easy
topic: Linked List
pattern: Iterative reversal
link: https://leetcode.com/problems/reverse-linked-list/
lists: [NeetCode 150]
followup_of: []
related: ["0092 Reverse Linked List II", "0025 Reverse Nodes in k-Group", "0234 Palindrome Linked List", "0143 Reorder List"]
---

# 0206. Reverse Linked List

## ⚡ 30-Second Summary
**Pattern:** Iterative pointer reversal (prev / curr / next)
**Key insight:** Walk the list once and flip each `next` pointer to point backward. Save `curr.next` before overwriting it, or the rest of the list is lost.
**Go-to:** Iterative three-pointer reversal, O(n) time, O(1) space

## Problem
Given the head of a singly linked list, reverse it and return the new head. [LeetCode](https://leetcode.com/problems/reverse-linked-list/)

**Examples:**
```
Input:  head = [1,2,3,4,5]
Output: [5,4,3,2,1]
Why:    Every link points the other way; the old tail is the new head.

Input:  head = [1,2]
Output: [2,1]
Why:    Two nodes swap roles.

Input:  head = []
Output: []
Why:    Nothing to reverse.
```

**Constraints:**
- 0 ≤ n ≤ 5000 (empty list allowed).
- Follow-up asks for both iterative and recursive versions.

## Hints
<details><summary>Hint 1</summary>
To reverse one link (a → b), b.next must become a. What do you lose when you do that?
</details>
<details><summary>Hint 2</summary>
You lose b's old next. So you need to remember it before rewiring. How many pointers is that?
</details>
<details><summary>Hint 3</summary>
prev = null, curr = head. Loop: nxt = curr.next; curr.next = prev; prev = curr; curr = nxt. Return prev.
</details>

## Clarifying Questions
- Can the list be empty or have one node? (Yes, both.)
- Reverse in place or return a new list? (In place is expected.)
- Recursion allowed? (Yes, but depth n = 5000 is fine in C++/Go, borderline in Python's default limit of 1000.)

## Example Walkthrough
`1 → 2 → 3`
- curr 1: save 2, point 1 → null. prev = 1.
- curr 2: save 3, point 2 → 1. prev = 2.
- curr 3: save null, point 3 → 2. prev = 3. curr is null: return 3 → 2 → 1.

## Approaches

### 1. Copy Values, Rebuild: O(n) time, O(n) space
Collect values into an array and build a new list backward. Works, but uses extra space and doesn't reverse the nodes.

### 2. Iterative Three Pointers ⭐ Go-to: O(n) time, O(1) space
Flip links one at a time.
**Why it's the go-to:** O(1) space, no recursion depth, and it's the building block for 0092, 0025, 0143, 0234.

### 3. Recursive: O(n) time, O(n) stack
Reverse the rest, then `head.next.next = head; head.next = null`. Elegant, but uses stack space.

## Dry Run (Approach 2)
`[1,2,3,4,5]`

| step | curr | nxt (saved) | after `curr.next = prev` | prev |
|------|------|-------------|--------------------------|------|
| 1 | 1 | 2 | 1 → null | 1 |
| 2 | 2 | 3 | 2 → 1 | 2 |
| 3 | 3 | 4 | 3 → 2 | 3 |
| 4 | 4 | 5 | 4 → 3 | 4 |
| 5 | 5 | null | 5 → 4 | 5 |
| end | null | | | return **5** |

## Edge Case Check
- Empty: loop never runs, return null. ✅
- One node: its next becomes null (it already was), return it. ✅
- Recursive base case covers both: `if !head or !head.next: return head`. ✅

## ⚠️ Pitfalls
- **Overwriting `curr.next` before saving it**: the rest of the list is gone.
- **Returning `head` instead of `prev`**: head is now the tail.
- **Recursive version forgetting `head.next = null`**: creates a 2-node cycle at the end.
- **Python recursion limit (~1000)**: n = 5000 needs the iterative version or `sys.setrecursionlimit`.

## 🎯 What the Interviewer Wants
- Bug-free iterative version in under two minutes.
- Be able to write the recursive one and explain its O(n) stack cost.
- Draw the pointers; say the invariant: "prev is the reversed prefix, curr is the rest".

## Follow-ups
- **Reverse only positions left..right:** [LC 0092 Reverse Linked List II](../0092-reverse-linked-list-ii/)
- **Reverse in groups of k:** [LC 0025 Reverse Nodes in k-Group](../0025-reverse-nodes-in-k-group/)
- **Palindrome check in O(1) space:** reverse the second half: LC 0234 Palindrome Linked List (not added yet)
- **Interleave first and reversed second half:** [LC 0143 Reorder List](../0143-reorder-list/)
