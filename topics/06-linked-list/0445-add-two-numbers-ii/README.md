---
number: 445
title: Add Two Numbers II
difficulty: Medium
topic: Linked List
pattern: Stacks to read digits from the back + build the result by prepending
link: https://leetcode.com/problems/add-two-numbers-ii/
lists: [Interview Extras]
followup_of: ["0002 Add Two Numbers"]
related: ["0002 Add Two Numbers", "0206 Reverse Linked List", "0415 Add Strings"]
---

# 0445. Add Two Numbers II

## ⚡ 30-Second Summary
**Pattern:** LC 2, but the digits come most significant first
**Key insight:** Addition starts at the last digit, which the list reaches last. Push both lists' digits onto stacks so you can pop them from the back. Then add with a carry, prepending each new digit node to the result, so it comes out most-significant-first without a final reverse.
**Go-to:** Two stacks + prepend, O(m + n) time, O(m + n) space

## Problem
Two non-negative integers are stored as linked lists with the most significant digit first. Return their sum in the same format. No leading zeros except the number 0 itself. [LeetCode](https://leetcode.com/problems/add-two-numbers-ii/)

**Examples:**
```
Input:  l1 = [7,2,4,3], l2 = [5,6,4]
Output: [7,8,0,7]
Why:    7243 + 564 = 7807.

Input:  l1 = [2,4,3], l2 = [5,6,4]
Output: [8,0,7]
Why:    243 + 564 = 807.

Input:  l1 = [0], l2 = [0]
Output: [0]
Why:    0 + 0 = 0.
```

**Constraints:**
- 1 ≤ length ≤ 100 each: far beyond 64-bit, so you can't convert to an integer.
- Follow-up: don't reverse the input lists.

## Hints
<details><summary>Hint 1</summary>
Addition starts at the ones digit. Where is the ones digit in these lists?
</details>
<details><summary>Hint 2</summary>
At the end. Reversing the lists works, but the follow-up says not to. Which data structure gives you the last element first?
</details>
<details><summary>Hint 3</summary>
Push each list's digits on a stack. Pop both while either is non-empty or carry > 0, create the digit node, and set node.next = head; head = node.
</details>

## Clarifying Questions
- Can I modify the input lists? (The follow-up says no.)
- Leading zeros in the input? (No, except a lone 0.)
- Numbers up to 100 digits, so no integer conversion? (Right.)

## Example Walkthrough
`7243 + 564`: stacks give 3,4,2,7 and 4,6,5. Add 3+4 = 7, 4+6 = 10 (digit 0, carry 1), 2+5+1 = 8, 7 = 7. Prepending each digit builds 7 → 8 → 0 → 7.

## Approaches

### 1. Reverse, Add (LC 2), Reverse: O(m + n) time, O(1) extra
Reverse both inputs, run LC 2, then reverse the result. Minimal extra space, but it modifies the inputs (unless you reverse them back).

### 2. Two Stacks + Prepend ⭐ Go-to: O(m + n) time, O(m + n) space
Stacks give the digits back to front, and prepending puts the result in the right order.
**Why it's the go-to:** meets the "don't modify the input" follow-up, with simple loop logic.

### 3. Pad + Recursion: O(m + n) time, O(m + n) stack
Pad the shorter list with leading zeros (or track the length difference), recurse to the end, and return the carry upwards. Correct, but fiddly to code under pressure.

## Dry Run (Approach 2)
`[9,9] + [1]` (carry produces a new leading digit).

| pop a | pop b | carry in | sum | node | carry out | result |
|-------|-------|----------|-----|------|-----------|--------|
| 9 | 1 | 0 | 10 | 0 | 1 | [0] |
| 9 | – | 1 | 10 | 0 | 1 | [0,0] |
| – | – | 1 | 1 | 1 | 0 | **[1,0,0]** |

## Edge Case Check
- [0] + [0] → [0]. ✅
- Very different lengths → the shorter stack empties first; treat it as 0. ✅
- Final carry → the loop condition `|| carry` adds the leading 1. ✅

## ⚠️ Pitfalls
- **Converting to int/long:** overflows at 100 digits (Python big ints would work but miss the point).
- **Dropping the final carry:** include `carry` in the loop condition.
- **Appending then forgetting to reverse:** prepend instead, so no reverse is needed.

## 🎯 What the Interviewer Wants
- See that the digit order is the whole problem, and pick stacks (or recursion) to handle it.
- Respect the "no reversal" follow-up.
- Clean carry handling.

## Follow-ups
- **Least significant digit first:** [LC 0002 Add Two Numbers](../0002-add-two-numbers/)
- **Reverse in place (approach 1's tool):** [LC 0206 Reverse Linked List](../0206-reverse-linked-list/)
- **Same addition on strings:** LC 0415 Add Strings (not added yet)
