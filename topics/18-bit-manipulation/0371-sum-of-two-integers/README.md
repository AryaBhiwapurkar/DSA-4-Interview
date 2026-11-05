---
number: 371
title: Sum of Two Integers
difficulty: Medium
topic: Bit Manipulation
pattern: XOR + carry
link: https://leetcode.com/problems/sum-of-two-integers/
lists: [NeetCode 150]
followup_of: []
related: ["0067 Add Binary", "0002 Add Two Numbers", "0029 Divide Two Integers"]
---

# 0371. Sum of Two Integers

## ⚡ 30-Second Summary
**Pattern:** Binary addition with bit operators
**Key insight:** `a ^ b` adds each column ignoring carries; `(a & b) << 1` is exactly the carries, moved one column left. Add those two the same way, repeating until there's no carry. In Python, mask to 32 bits, or negatives loop forever.
**Go-to:** XOR + carry loop, O(32) time, O(1) space

## Problem
Compute the sum of two 32-bit signed integers without using the `+` or `-` operators. [LeetCode](https://leetcode.com/problems/sum-of-two-integers/)

**Examples:**
```
Input:  a = 1, b = 2
Output: 3
Why:    01 and 10 share no bits, so XOR alone gives 11.

Input:  a = 2, b = 3
Output: 5
Why:    10 + 11: XOR is 01, the carry is 100; adding those gives 101.
```

**Constraints:**
- −1000 ≤ a, b ≤ 1000, but the method must work for any 32-bit ints.
- Negatives use two's complement.

## Hints
<details><summary>Hint 1</summary>
Add two single bits by hand. Which bit operation gives the sum bit, and which gives the carry?
</details>
<details><summary>Hint 2</summary>
Do that for all bits at once: one number for "sum ignoring carries", another for "the carries". How do you combine them?
</details>
<details><summary>Hint 3</summary>
while b ≠ 0: carry = (a & b) << 1; a = a ^ b; b = carry. In C++ do it on unsigned; in Python mask with 0xFFFFFFFF and convert back if bit 31 is set.
</details>

## Clarifying Questions
- Negative inputs? (Yes.)
- Is overflow possible? (Not in the given range; with full ints, wrap like a 32-bit add.)
- Can I use `++`, `sum()` or other tricks? (No, that's against the spirit.)

## Example Walkthrough
−1 + 1 in 32 bits: −1 is all ones. XOR gives all ones except bit 0 → carry is 10. Each round the carry moves one column left and clears one more bit, until the carry falls off bit 31 and a = 0. In Python, without the mask the carry keeps growing forever.

## Approaches

### 1. Full Adder Bit by Bit: O(32) time, O(1) space
For each bit position: sum = x ^ y ^ carry, carry = (x & y) | (carry & (x ^ y)). The hardware view, very explicit.

### 2. XOR + Carry ⭐ Go-to: O(32) time, O(1) space
**Why it's the go-to:** four lines, and the two identities (XOR = sum without carry, AND = carry) are the full explanation.

## Dry Run (Approach 2)
a = 2 (010), b = 3 (011)

| round | a | b | a ^ b | (a & b) << 1 |
|-------|---|---|-------|--------------|
| 1 | 010 | 011 | 001 | 100 |
| 2 | 001 | 100 | 101 | 000 |

b = 0 → a = 101 = **5**.

## Edge Case Check
- Opposite signs (`1000, −1000`) → 0. ✅
- Both negative (`−12, −8`) → −20. ✅
- `−1 + 1` → 0 after the carry runs off the top. ✅

## ⚠️ Pitfalls
- **Python infinite loop:** negative numbers have infinite sign bits; mask every step with `& 0xFFFFFFFF`.
- **Python result conversion:** a masked value above 0x7FFFFFFF is negative: `~(a ^ 0xFFFFFFFF)`.
- **C++ shifting a negative int left** is undefined before C++20; use `uint32_t`.
- **Updating a before computing the carry** loses the AND of the old values.

## 🎯 What the Interviewer Wants
- The XOR / AND identities, then the loop.
- Language-specific handling of negatives (masking in Python, unsigned in C++).
- Why the loop terminates (the carry moves left each round, at most 32 times).

## Follow-ups
- **Binary strings instead of ints:** [LC 0067 Add Binary](../0067-add-binary/)
- **Digits in linked lists:** [LC 0002 Add Two Numbers](../../06-linked-list/0002-add-two-numbers/)
- **Subtract:** a + (~b + 1), using the same adder.
- **Divide without * / %:** LC 0029 Divide Two Integers (not added yet). Shifted subtraction.
