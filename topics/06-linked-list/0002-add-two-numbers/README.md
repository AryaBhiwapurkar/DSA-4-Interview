---
number: 2
title: Add Two Numbers
difficulty: Medium
topic: Linked List
pattern: Digit-wise add with carry
link: https://leetcode.com/problems/add-two-numbers/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0445 Add Two Numbers II", "0066 Plus One", "0067 Add Binary", "0415 Add Strings"]
---

# 0002. Add Two Numbers

## ⚡ 30-Second Summary
**Pattern:** Digit-by-digit addition with a carry
**Key insight:** The digits are stored least-significant first, which is exactly the order you add them by hand. Walk both lists together, add digit + digit + carry, emit sum % 10, carry sum / 10. Keep going while either list or the carry is left.
**Go-to:** Iterative with a dummy head, O(max(m, n)) time, O(1) extra space

## Problem
Two non-negative integers are stored as linked lists of digits in reverse order (ones digit first). Return their sum as a linked list in the same format. No leading zeros except the number 0 itself.

**Examples:**
```
Input:  l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Why:    342 + 465 = 807, written backward.

Input:  l1 = [0], l2 = [0]
Output: [0]
Why:    0 + 0 = 0.

Input:  l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]
Why:    9999999 + 9999 = 10009998; the final carry adds a new digit.
```

**Constraints:**
- 1 ≤ length ≤ 100, so the numbers can have 100 digits: converting to an int overflows.
- Digits 0-9, no leading zeros.

## Hints
<details><summary>Hint 1</summary>
Why not convert both lists to integers? (Think about 100-digit numbers.)
</details>
<details><summary>Hint 2</summary>
The lists are ones-digit first. How would you add two numbers on paper, starting from which end?
</details>
<details><summary>Hint 3</summary>
Loop while l1, l2, or carry: sum = carry + (l1 ? l1.val : 0) + (l2 ? l2.val : 0); append sum % 10; carry = sum / 10.
</details>

## Clarifying Questions
- Digit order? (Reversed: ones first.)
- Can the lists have different lengths? (Yes.)
- Can I modify the input lists? (Prefer building a new list.)

## Example Walkthrough
`[2,4,3] + [5,6,4]`
- 2 + 5 = 7, carry 0 → 7.
- 4 + 6 = 10 → 0, carry 1.
- 3 + 4 + 1 = 8 → 8. Both lists done, no carry. Result [7,0,8].

## Approaches

### 1. Iterative With Carry ⭐ Go-to: O(max(m, n)) time, O(1) extra space
One loop over both lists plus the carry, building the result after a dummy node. (Converting to integers is the tempting brute force, but it overflows beyond 19 digits in C++/Go.)
**Why it's the go-to:** handles unequal lengths and the final carry in a single loop condition.

### 2. Recursive: O(max(m, n)) time, O(max(m, n)) stack
`add(l1, l2, carry)` returns the node for this digit and recurses for the rest. Neat, but uses stack space.

## Dry Run (Approach 1)
`[9,9,9,9,9,9,9] + [9,9,9,9]`

| step | d1 | d2 | carry in | sum | digit | carry out |
|------|----|----|----------|-----|-------|-----------|
| 1 | 9 | 9 | 0 | 18 | 8 | 1 |
| 2-4 | 9 | 9 | 1 | 19 | 9 | 1 |
| 5-7 | 9 | - | 1 | 10 | 0 | 1 |
| 8 | - | - | 1 | 1 | 1 | 0 |
| result | | | | | **[8,9,9,9,0,0,0,1]** | |

## Edge Case Check
- Different lengths: missing digits count as 0. ✅
- Final carry: the loop condition includes `carry`, adding a new node. ✅
- 0 + 0: one node [0]. ✅

## ⚠️ Pitfalls
- **Converting to integers**: overflows for long inputs (Python survives with big ints, but it misses the point).
- **Stopping when one list ends**: the other list and the carry still matter.
- **Forgetting the last carry**: 5 + 5 must give [0,1], not [0].
- **Dereferencing a null list** when lengths differ: guard each access.

## 🎯 What the Interviewer Wants
- Recognize reverse order = natural addition order.
- One loop with `l1 || l2 || carry` and no duplicated tail-handling code.
- Clean dummy-head construction.

## Follow-ups
- **Digits stored most-significant first:** reverse both, or use two stacks: LC 0445 Add Two Numbers II (not added yet)
- **Strings or arrays instead of lists:** LC 0415 Add Strings (not added yet), [LC 0067 Add Binary](../../18-bit-manipulation/0067-add-binary/), LC 0066 Plus One (not added yet)
- **Multiply two numbers:** grade-school multiplication into an array of digits.
