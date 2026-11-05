---
number: 190
title: Reverse Bits
difficulty: Easy
topic: Bit Manipulation
pattern: Shift and build
link: https://leetcode.com/problems/reverse-bits/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0191 Number of 1 Bits", "0007 Reverse Integer"]
---

# 0190. Reverse Bits

## ⚡ 30-Second Summary
**Pattern:** Pop the lowest bit of n, push it onto the result
**Key insight:** Repeat 32 times: `res = (res << 1) | (n & 1)`, then `n >>= 1`. The bit you read first (n's bit 0) gets shifted left 31 more times, so it lands in bit 31. Always run exactly 32 iterations so leading zeros of n become trailing zeros of the result.
**Go-to:** Bit-by-bit loop, O(32) time, O(1) space

## Problem
Treat the input as a 32-bit pattern, reverse the order of its bits, and return the value of the reversed pattern as an unsigned 32-bit number. [LeetCode](https://leetcode.com/problems/reverse-bits/)

**Examples:**
```
Input:  n = 43261596   (00000010100101000001111010011100)
Output: 964176192      (00111001011110000010100101000000)
Why:    Reading the bit string backwards gives the output pattern.

Input:  n = 2147483644 (01111111111111111111111111111100)
Output: 1073741822     (00111111111111111111111111111110)
Why:    The two trailing zeros move to the front, the leading zero to the back.
```

**Constraints:**
- 32-bit input. Older versions pass an unsigned value up to 2³² − 1; the current one passes a non-negative int.
- Follow-up: called many times, how would you optimise?

## Hints
<details><summary>Hint 1</summary>
How do you read n's bits one at a time from the right?
</details>
<details><summary>Hint 2</summary>
How do you append a bit to the right end of a growing result?
</details>
<details><summary>Hint 3</summary>
Loop exactly 32 times: res = (res << 1) | (n & 1); n >>= 1. Use an unsigned 32-bit type (or mask in Python).
</details>

## Clarifying Questions
- Fixed 32 bits, including leading zeros? (Yes.)
- Signed or unsigned output? (Unsigned value of the reversed pattern.)
- Called repeatedly? (Cache reversed bytes in a 256-entry table.)

## Example Walkthrough
n = 1: the single 1 bit is read on the first iteration and shifted left 31 more times, ending at bit 31 → 2³¹ = 2147483648. Stopping when n becomes 0 would return 1 instead.

## Approaches

### 1. Bit by Bit ⭐ Go-to: O(32) time, O(1) space
**Why it's the go-to:** obviously correct and short; the "always 32 iterations" detail is what's being tested.

### 2. Divide and Conquer Swaps: O(5) steps, O(1) space
Swap the 16-bit halves, then bytes inside each half, then nibbles, pairs and single bits, using masks. Good to mention for the "many calls" follow-up.

## Dry Run (Approach 1)
n = 11 (…0001011), first 4 of the 32 iterations:

| iter | n & 1 | res (bin) | n after >> 1 |
|------|-------|-----------|--------------|
| 1 | 1 | 1 | 101 |
| 2 | 1 | 11 | 10 |
| 3 | 0 | 110 | 1 |
| 4 | 1 | 1101 | 0 |

The remaining 28 iterations append zeros: res = 1101 followed by 28 zeros = 0xD0000000 = **3489660928**.

## Edge Case Check
- n = 0 → 0. ✅
- n = 1 → 2147483648. ✅
- All ones except bit 1 (0xFFFFFFFD) → 0xBFFFFFFF = 3221225471. ✅

## ⚠️ Pitfalls
- **Stopping when n hits 0** drops the trailing zeros of the result.
- **Signed types in C++:** shifting into bit 31 of an `int` is undefined (pre-C++20) and prints negative; use `uint32_t`.
- **Python has no 32-bit wraparound:** mask left shifts with `& 0xFFFFFFFF` when they can overflow.
- **Java/C# `>>` sign-extends** negative inputs; use `>>>` in Java.

## 🎯 What the Interviewer Wants
- The pop/push loop with exactly 32 steps.
- Unsigned arithmetic awareness.
- For repeated calls: byte lookup table or the mask-swap version.

## Follow-ups
- **Count the 1 bits instead:** [LC 0191 Number of 1 Bits](../0191-number-of-1-bits/)
- **Reverse decimal digits with overflow checks:** [LC 0007 Reverse Integer](../0007-reverse-integer/)
- **Many calls:** precompute reverse[0..255] and combine four bytes.
