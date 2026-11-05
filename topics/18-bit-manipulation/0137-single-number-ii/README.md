---
number: 137
title: Single Number II
difficulty: Medium
topic: Bit Manipulation
pattern: Bit counting mod 3
link: https://leetcode.com/problems/single-number-ii/
lists: [LC Top Interview 150]
followup_of: ["0136 Single Number"]
related: ["0260 Single Number III", "0268 Missing Number"]
---

# 0137. Single Number II

## ⚡ 30-Second Summary
**Pattern:** Count each bit position modulo 3
**Key insight:** XOR fails because three copies don't cancel. Look at one bit position instead: every tripled number adds 0 or 3 to that column's count, so `count % 3` is exactly the single number's bit. Do this for all 32 bits and rebuild the number.
**Go-to:** Per-bit counting, O(32·n) time, O(1) space

## Problem
In an array where every value appears exactly three times except one value that appears once, return that one value, in linear time with constant extra space. [LeetCode](https://leetcode.com/problems/single-number-ii/)

**Examples:**
```
Input:  nums = [2,2,3,2]
Output: 3
Why:    The three 2s drop out of every bit column.

Input:  nums = [0,1,0,1,0,1,99]
Output: 99
Why:    Zeros and ones each appear three times.
```

**Constraints:**
- 1 ≤ n ≤ 3·10⁴, values span the **full 32-bit signed range** (negatives matter for bit 31).
- O(1) extra space.

## Hints
<details><summary>Hint 1</summary>
XOR cancels pairs. What property do numbers appearing three times have, per bit?
</details>
<details><summary>Hint 2</summary>
For a fixed bit b, count how many numbers have it set. What does that count look like modulo 3?
</details>
<details><summary>Hint 3</summary>
For b in 0..31: total = Σ ((x >> b) & 1); if total % 3 == 1, set bit b in the result. Handle bit 31 as the sign (cast in C++, subtract 2³² in Python).
</details>

## Clarifying Questions
- Exactly three times for the others? (Yes.)
- Negatives? (Yes, so the sign bit must be handled.)
- Is O(32n) acceptable as O(n)? (Yes, 32 is a constant.)

## Example Walkthrough
`[2,2,3,2]`: bit 0 is set only in 3 → count 1 → set. Bit 1 is set in all four (2 = 10, 3 = 11) → count 4 → 4 % 3 = 1 → set. Result 11 = 3.

## Approaches

### 1. Hash Map: O(n) time, O(n) space
Count occurrences, return the value with count 1.

### 2. Bit Counting ⭐ Go-to: O(32·n) time, O(1) space
**Why it's the go-to:** easy to explain and to generalise (every other number appears k times → use % k).

### 3. ones / twos State Machine: O(n) time, O(1) space
`ones` and `twos` hold, per bit, whether it's been seen 1 or 2 times mod 3: `ones = (ones ^ x) & ~twos; twos = (twos ^ x) & ~ones`. Elegant, but hard to derive on the spot; mention it as the optimisation.

## Dry Run (Approach 2)
`[2,2,3,2]`

| bit b | values with bit b set | total | total % 3 | result so far |
|-------|-----------------------|-------|-----------|---------------|
| 0 | 3 | 1 | 1 | 01 |
| 1 | 2, 2, 3, 2 | 4 | 1 | 11 |
| 2..31 | none | 0 | 0 | 11 = **3** |

## Edge Case Check
- Negative single (`… -4 …`) → bit 31 is set; converted back to −4. ✅
- n = 1 → the only element. ✅
- Single is 0 → every column count is a multiple of 3 → 0. ✅

## ⚠️ Pitfalls
- **Python sign:** the rebuilt value is unsigned 32-bit; subtract 2³² if bit 31 is set.
- **C++ `1 << 31`** on int overflows; use `1u` and an unsigned accumulator.
- **Signed right shift** spreads the sign bit; shift `(uint32_t)x` in C++.
- **Order of updates in ones/twos:** `twos` must use the *new* `ones`.

## 🎯 What the Interviewer Wants
- Explain why XOR doesn't work, then the per-bit mod-3 idea.
- Correct handling of negative numbers.
- Bonus: the ones/twos state machine, and the general "k times" version.

## Follow-ups
- **Others appear twice:** [LC 0136 Single Number](../0136-single-number/)
- **Two singles, others twice:** LC 0260 Single Number III (not added yet). Split by a differing bit.
- **Others appear k times:** same counting with % k.
