---
number: 67
title: Add Binary
difficulty: Easy
topic: Bit Manipulation
pattern: Carry addition
link: https://leetcode.com/problems/add-binary/
lists: [LC Top Interview 150]
followup_of: []
related: ["0002 Add Two Numbers", "0371 Sum of Two Integers", "0415 Add Strings"]
---

# 0067. Add Binary

## ⚡ 30-Second Summary
**Pattern:** Schoolbook addition from the right, carrying
**Key insight:** Walk both strings from their last character, adding digit + digit + carry. Write `s & 1`, carry `s >> 1`. Keep looping while either string has digits **or** a carry remains, then reverse.
**Go-to:** Two pointers + carry, O(max(m, n)) time and space

## Problem
Two non-negative numbers are written as binary strings. Return their sum, also as a binary string. [LeetCode](https://leetcode.com/problems/add-binary/)

**Examples:**
```
Input:  a = "11", b = "1"
Output: "100"
Why:    3 + 1 = 4; the carry ripples through both 1s.

Input:  a = "1010", b = "1011"
Output: "10101"
Why:    10 + 11 = 21; the final carry adds a new leading digit.
```

**Constraints:**
- 1 ≤ m, n ≤ 10⁴: far too long for a 64-bit int.
- No leading zeros except "0" itself.

## Hints
<details><summary>Hint 1</summary>
How do you add two decimal numbers on paper? Which end do you start from?
</details>
<details><summary>Hint 2</summary>
The strings may have different lengths. How do you keep reading when one runs out?
</details>
<details><summary>Hint 3</summary>
i, j at the ends, carry = 0. While i ≥ 0 or j ≥ 0 or carry: s = carry + a[i] + b[j] (when present), append s % 2, carry = s / 2. Reverse at the end.
</details>

## Clarifying Questions
- Can the inputs be very long? (Yes, up to 10⁴: no int conversion in C++.)
- Leading zeros in input? (No, except "0".)
- Return format? (A string, no leading zeros.)

## Example Walkthrough
`"1111" + "1"`: column 0: 1 + 1 = 10 → write 0, carry 1. Columns 1–3: 1 + carry = 10 each time → write 0, carry 1. Both strings done, but carry = 1 → write 1. Reversed: "10000".

## Approaches

### 1. Pad + Column Add: O(max(m, n)) time and space
Left-pad the shorter string with zeros so both have the same length, then add column by column. Simple, at the cost of copies. (In Python, `bin(int(a, 2) + int(b, 2))[2:]` also works thanks to big ints, but interviewers want the manual version.)

### 2. Two Pointers + Carry ⭐ Go-to: O(max(m, n)) time and space
**Why it's the go-to:** no padding, a single loop, and the "or carry" condition handles the final digit.

## Dry Run (Approach 2)
`a = "1010"`, `b = "1011"`

| a[i] | b[j] | carry in | s | write | carry out |
|------|------|----------|---|-------|-----------|
| 0 | 1 | 0 | 1 | 1 | 0 |
| 1 | 1 | 0 | 2 | 0 | 1 |
| 0 | 0 | 1 | 1 | 1 | 0 |
| 1 | 1 | 0 | 2 | 0 | 1 |
| – | – | 1 | 1 | 1 | 0 |

Written "10101" (least significant first) → reversed **"10101"**.

## Edge Case Check
- `"0" + "0"` → "0". ✅
- Different lengths (`"1" + "111"`) → "1000". ✅
- Final carry (`"1111" + "1"`) → extra leading 1. ✅

## ⚠️ Pitfalls
- **Converting to int** overflows in C++/Java for long inputs.
- **Dropping the final carry** (loop only while i or j ≥ 0).
- **Prepending to a string each step** is O(n²); append then reverse.
- **Mixing chars and ints:** subtract '0' when reading, add '0' when writing.

## 🎯 What the Interviewer Wants
- Clean right-to-left addition with a carry.
- Different lengths and the final carry handled in one loop.
- Linear time with no quadratic string building.

## Follow-ups
- **Decimal strings:** LC 0415 Add Strings (not added yet). Same loop with base 10.
- **Digits in linked lists:** [LC 0002 Add Two Numbers](../../06-linked-list/0002-add-two-numbers/)
- **Add without + at all:** [LC 0371 Sum of Two Integers](../0371-sum-of-two-integers/)
