---
number: 191
title: Number of 1 Bits
difficulty: Easy
topic: Bit Manipulation
pattern: n & (n-1)
link: https://leetcode.com/problems/number-of-1-bits/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0338 Counting Bits", "0461 Hamming Distance", "0231 Power of Two"]
---

# 0191. Number of 1 Bits

## ⚡ 30-Second Summary
**Pattern:** Clear the lowest set bit with `n & (n - 1)`
**Key insight:** Subtracting 1 flips the lowest 1 bit to 0 and every 0 below it to 1. AND-ing with the original wipes exactly that lowest 1. Repeat until n is 0, counting the steps: one per set bit.
**Go-to:** `n &= n - 1` loop, O(number of set bits) time, O(1) space

## Problem
Return how many 1 bits a positive integer has in binary (its Hamming weight). [LeetCode](https://leetcode.com/problems/number-of-1-bits/)

**Examples:**
```
Input:  n = 11
Output: 3
Why:    11 is 1011 in binary.

Input:  n = 128
Output: 1
Why:    A power of two has a single 1 bit.

Input:  n = 2147483645
Output: 30
Why:    That's 2³¹ − 3: all 31 low bits set except bit 1.
```

**Constraints:**
- 1 ≤ n ≤ 2³¹ − 1.
- Follow-up: the function is called many times; how would you speed it up?

## Hints
<details><summary>Hint 1</summary>
You could check each of the 32 bits. Can you jump straight from one set bit to the next?
</details>
<details><summary>Hint 2</summary>
Write n and n − 1 in binary next to each other. Which bits differ?
</details>
<details><summary>Hint 3</summary>
n & (n − 1) is n with its lowest 1 removed. Loop while n ≠ 0: n &= n − 1, count++.
</details>

## Clarifying Questions
- Signed or unsigned input? (Positive here; older versions passed an unsigned 32-bit value.)
- Called many times? (Then a lookup table per byte, or the built-in popcount.)

## Example Walkthrough
`n = 12` (1100): n − 1 = 1011, n & (n − 1) = 1000. Then 1000 & 0111 = 0. Two steps → two set bits. The trailing zeros were skipped for free.

## Approaches

### 1. Shift and Check: O(32) time, O(1) space
Add `n & 1`, shift right, repeat. Always 32 steps (or up to the top bit).

### 2. n & (n − 1) ⭐ Go-to: O(#set bits) time, O(1) space
**Why it's the go-to:** it's the bit trick interviewers expect, and it reappears in Power of Two, Counting Bits and AND of a range.

### 3. Built-in: O(1) time, O(1) space
`__builtin_popcount`, `int.bit_count()`. Mention it, but show a manual version.

## Dry Run (Approach 2)
`n = 11`

| step | n (bin) | n − 1 (bin) | n & (n − 1) | count |
|------|---------|-------------|-------------|-------|
| 1 | 1011 | 1010 | 1010 | 1 |
| 2 | 1010 | 1001 | 1000 | 2 |
| 3 | 1000 | 0111 | 0000 | **3** |

## Edge Case Check
- n = 1 → 1. ✅
- All 31 bits set (2147483647) → 31. ✅
- Power of two → 1 step. ✅

## ⚠️ Pitfalls
- **Signed right shift in C++/Java** on negative numbers drags the sign bit in; use `uint32_t` (or `>>>` in Java).
- **Python negatives:** `n >> 1` never reaches 0 for negative n; mask with `& 0xFFFFFFFF`.
- **Precedence:** `n & 1 == 0` parses as `n & (1 == 0)` in C++; add parentheses.

## 🎯 What the Interviewer Wants
- The `n & (n − 1)` trick and why it works.
- Awareness of signed vs unsigned shifts.
- For the follow-up: a 256-entry byte table or hardware popcount.

## Follow-ups
- **Counts for every number 0..n:** [LC 0338 Counting Bits](../0338-counting-bits/)
- **Differing bits between two numbers:** LC 0461 Hamming Distance (not added yet). popcount(x ^ y).
- **Is n a power of two?** LC 0231 Power of Two (not added yet). n > 0 and n & (n − 1) == 0.
