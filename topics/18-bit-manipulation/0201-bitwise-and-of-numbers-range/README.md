---
number: 201
title: Bitwise AND of Numbers Range
difficulty: Medium
topic: Bit Manipulation
pattern: Common prefix
link: https://leetcode.com/problems/bitwise-and-of-numbers-range/
lists: [LC Top Interview 150]
followup_of: []
related: ["0191 Number of 1 Bits", "0338 Counting Bits"]
---

# 0201. Bitwise AND of Numbers Range

## ⚡ 30-Second Summary
**Pattern:** Common binary prefix of left and right
**Key insight:** If left and right differ in some bit, then somewhere between them that bit (and every bit below it) is 0, because counting up from left to right flips it. So the AND is just their **common prefix** followed by zeros. Shift both right until they're equal, then shift back.
**Go-to:** Shift to the common prefix, O(32) time, O(1) space

## Problem
Given 0 ≤ left ≤ right ≤ 2³¹ − 1, return the bitwise AND of every integer from left to right inclusive. [LeetCode](https://leetcode.com/problems/bitwise-and-of-numbers-range/)

**Examples:**
```
Input:  left = 5, right = 7
Output: 4
Why:    101 & 110 & 111 = 100: only the shared leading 1 survives.

Input:  left = 0, right = 0
Output: 0
Why:    A single number, 0.

Input:  left = 1, right = 2147483647
Output: 0
Why:    The range crosses every power of two, so every bit is 0 in some number.
```

**Constraints:**
- 0 ≤ left ≤ right ≤ 2³¹ − 1: looping over the range can take 2·10⁹ steps.

## Hints
<details><summary>Hint 1</summary>
Write 5, 6, 7 in binary. Which bits stay 1 in all of them?
</details>
<details><summary>Hint 2</summary>
Find the highest bit where left and right differ. What happens to that bit and the bits below it as you count from left to right?
</details>
<details><summary>Hint 3</summary>
While left ≠ right: left >>= 1, right >>= 1, shift++. Return left << shift. (Or: while right > left, right &= right − 1; return right.)
</details>

## Clarifying Questions
- Inclusive range? (Yes.)
- Non-negative only? (Yes, 0..2³¹ − 1.)
- left == right? (Return it.)

## Example Walkthrough
`12, 15`: 1100 and 1111. They differ in the low two bits; between them those bits run through 00, 01, 10, 11, so each is 0 somewhere. The common prefix 11 stays: 1100 = 12.

## Approaches

### 1. Brute Force: O(right − left) time, O(1) space
AND everything, stopping early at 0. It can still take ~2·10⁹ steps (e.g. [2³⁰, 2³¹ − 1] never reaches 0).

### 2. Common Prefix ⭐ Go-to: O(32) time, O(1) space
**Why it's the go-to:** at most 31 shifts, and the "differing bits get zeroed" argument is short.

### 3. Clear Lowest Bits: O(32) time, O(1) space
Keep removing right's lowest set bit while right > left; what remains is the common prefix. Same idea via `n & (n − 1)`.

## Dry Run (Approach 2)
left = 5 (101), right = 7 (111)

| shift | left | right | equal? |
|-------|------|-------|--------|
| 0 | 101 | 111 | no |
| 1 | 10 | 11 | no |
| 2 | 1 | 1 | yes |

Result: 1 << 2 = 100 = **4**.

## Edge Case Check
- left == right → no shifts → itself. ✅
- left = 0 → prefix is 0 → 0. ✅
- Range crossing a power of two (1..INT_MAX) → 0. ✅

## ⚠️ Pitfalls
- **Brute force loops** time out, and in C++ `x++` past INT_MAX overflows.
- **Shifting only one side**, or comparing after shifting by a fixed amount, loses the prefix.
- **Returning left instead of left << shift** forgets to restore the zeros.

## 🎯 What the Interviewer Wants
- The observation that differing bits are zeroed somewhere in the range.
- The common-prefix computation in O(32).
- Optionally the `n & (n − 1)` variant.

## Follow-ups
- **The `n & (n − 1)` trick itself:** [LC 0191 Number of 1 Bits](../0191-number-of-1-bits/)
- **Bit patterns across a range of numbers:** [LC 0338 Counting Bits](../0338-counting-bits/)
- **OR of a range:** the common prefix followed by all 1s.
