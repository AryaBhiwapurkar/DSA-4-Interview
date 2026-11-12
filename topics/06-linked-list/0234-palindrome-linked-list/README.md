---
number: 234
title: Palindrome Linked List
difficulty: Easy
topic: Linked List
pattern: Find middle + reverse second half + compare
link: https://leetcode.com/problems/palindrome-linked-list/
lists: [Interview Extras]
followup_of: []
related: ["0206 Reverse Linked List", "0876 Middle of the Linked List", "0143 Reorder List", "0125 Valid Palindrome"]
---

# 0234. Palindrome Linked List

## ⚡ 30-Second Summary
**Pattern:** Middle (fast/slow) → reverse the back half → walk both halves together
**Key insight:** You can't walk a singly linked list backwards, so reverse the second half in place. Then compare it node by node with the first half. Reverse it back afterwards so the caller's list is unchanged.
**Go-to:** Fast/slow + in-place reversal, O(n) time, O(1) space

## Problem
Return whether the values of a singly linked list read the same forwards and backwards. [LeetCode](https://leetcode.com/problems/palindrome-linked-list/)

**Examples:**
```
Input:  head = [1,2,2,1]
Output: true
Why:    Reversed it's still 1,2,2,1.

Input:  head = [1,2]
Output: false
Why:    Reversed it's 2,1.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵; 0 ≤ values ≤ 9.
- Follow-up: O(n) time and O(1) space.

## Hints
<details><summary>Hint 1</summary>
With an array this is two pointers from both ends. What stops you from doing that on the list?
</details>
<details><summary>Hint 2</summary>
You can't move backwards, but you can reverse part of the list. Which part, and how do you find where it starts?
</details>
<details><summary>Hint 3</summary>
Fast/slow pointers stop slow at the end of the first half. Reverse slow.next onward, compare from head and from the reversed head until the reversed half ends, then reverse it back.
</details>

## Clarifying Questions
- Can I modify the list temporarily? (Usually yes, as long as I restore it.)
- Single node → true? (Yes.)
- Compare values, not node identity? (Values.)

## Example Walkthrough
`[1,2,2,1]`: the first half ends at the first 2. Reversing the back half [2,1] gives [1,2]. Compare 1 = 1 and 2 = 2 → true. Reverse it back to restore 1→2→2→1.

## Approaches

### 1. Copy to an Array: O(n) time, O(n) space
Copy the values out, then two pointers from both ends. Simplest; fails the follow-up.

### 2. Recursion with a Front Pointer: O(n) time, O(n) stack
Recurse to the tail and compare each node, on the way back up, with a front pointer that advances. Clever, but uses n stack frames: risky at 10⁵.

### 3. Reverse the Second Half ⭐ Go-to: O(n) time, O(1) space
Find the end of the first half, reverse what follows, compare, restore.
**Why it's the go-to:** meets the follow-up using two building blocks you already know (LC 876 + LC 206).

## Dry Run (Approach 3)
`[1,2,3,2,1]` (odd length: the middle node is skipped).

| step | state |
|------|-------|
| find first-half end | slow: 1 → 2 → 3 (fast: 1 → 3 → 1(last), stops) → first half ends at 3 |
| reverse slow.next | [2,1] → [1,2] |
| compare | 1 = 1, 2 = 2, reversed half ends → **true** |
| restore | 3.next = reverse([1,2]) → list is 1,2,3,2,1 again |

## Edge Case Check
- One node → the second half is empty, so there's nothing to compare → true. ✅
- Two equal nodes `[1,1]` → true; `[1,2]` → false. ✅
- Odd length → the middle node belongs to the first half and is never compared. ✅

## ⚠️ Pitfalls
- **Wrong loop condition for the middle:** use `fast.next && fast.next.next` so slow stops at the end of the first half (the first middle for even n).
- **Comparing until the first half ends:** the first half can be one longer (odd n); loop over the reversed second half instead.
- **Not restoring the list:** the caller may still use it, and interviewers notice.

## 🎯 What the Interviewer Wants
- The O(1)-space version built from middle + reverse.
- Correct handling of odd vs even lengths.
- Mention restoring the input.

## Follow-ups
- **Reverse a list:** [LC 0206 Reverse Linked List](../0206-reverse-linked-list/)
- **Find the middle:** [LC 0876 Middle of the Linked List](../0876-middle-of-the-linked-list/)
- **Same three steps, then interleave:** [LC 0143 Reorder List](../0143-reorder-list/)
- **String version:** [LC 0125 Valid Palindrome](../../02-two-pointers/0125-valid-palindrome/)
