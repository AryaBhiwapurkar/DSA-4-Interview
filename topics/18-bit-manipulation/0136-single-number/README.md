---
number: 136
title: Single Number
difficulty: Easy
topic: Bit Manipulation
pattern: XOR
link: https://leetcode.com/problems/single-number/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0137 Single Number II", "0260 Single Number III", "0268 Missing Number"]
---

# 0136. Single Number

## ⚡ 30-Second Summary
**Pattern:** XOR cancellation
**Key insight:** `x ^ x = 0`, `x ^ 0 = x`, and XOR is commutative and associative. XOR-ing the whole array makes every pair cancel, leaving the single number.
**Go-to:** XOR everything, O(n) time, O(1) space

## Problem
In an array where every value occurs exactly twice except for one value that occurs once, return that one value, using linear time and constant extra space. [LeetCode](https://leetcode.com/problems/single-number/)

**Examples:**
```
Input:  nums = [2,2,1]
Output: 1
Why:    The two 2s cancel.

Input:  nums = [4,1,2,1,2]
Output: 4
Why:    The 1s and 2s pair off, wherever they sit.

Input:  nums = [1]
Output: 1
Why:    Nothing to pair with.
```

**Constraints:**
- 1 ≤ n ≤ 3·10⁴, values in [-3·10⁴, 3·10⁴], negatives allowed.
- O(1) extra space is required.

## Hints
<details><summary>Hint 1</summary>
A hash set solves it in O(n) space. Which operation on two equal numbers gives a "nothing" result?
</details>
<details><summary>Hint 2</summary>
Think about XOR: what is a ^ a? What is a ^ 0? Does order matter?
</details>
<details><summary>Hint 3</summary>
Start with 0 and XOR in every element. Pairs vanish; the result is the single number.
</details>

## Clarifying Questions
- Exactly twice for all others? (Yes. Three times is LC 137.)
- Negatives? (Yes; XOR doesn't care.)
- Extra space allowed? (O(1) required.)

## Example Walkthrough
`[4,1,2,1,2]`: 0^4 = 4, ^1 = 5, ^2 = 7, ^1 = 6, ^2 = 4. The partial results look random, but the 1s and 2s cancel in the end.

## Approaches

### 1. Hash Set: O(n) time, O(n) space
Add on first sight, remove on second; the one left is the answer.

### 2. Sort: O(n log n) time, O(1) extra
After sorting, pairs sit at (0,1), (2,3), …; the first mismatched pair starts with the answer.

### 3. XOR ⭐ Go-to: O(n) time, O(1) space
**Why it's the go-to:** it meets both constraints in one line, and the three XOR identities are the whole proof.

## Dry Run (Approach 3)
`[4,1,2,1,2]` in binary

| v | v (bin) | x after ^= v |
|---|---------|--------------|
| 4 | 100 | 100 (4) |
| 1 | 001 | 101 (5) |
| 2 | 010 | 111 (7) |
| 1 | 001 | 110 (6) |
| 2 | 010 | 100 (**4**) |

## Edge Case Check
- Single element → itself. ✅
- Negative single (`[-3,7,7]`) → -3. ✅
- Single at the end of a sorted array → caught by the sort version's fallback. ✅

## ⚠️ Pitfalls
- **Summing instead of XOR** (2·sum(set) − sum) needs O(n) space for the set and can overflow.
- **Python `reduce` without an initial value** fails on an empty list (fine here, n ≥ 1).
- **Assuming non-negative values** in bit-counting variants; XOR itself is safe.

## 🎯 What the Interviewer Wants
- The hash-set baseline, then XOR with the identities stated.
- O(1) space reasoning.
- Ready for the variants (three times, two singles).

## Follow-ups
- **Others appear three times:** [LC 0137 Single Number II](../0137-single-number-ii/)
- **Two singles:** LC 0260 Single Number III (not added yet). XOR all, split by the lowest set bit.
- **Missing number in 0..n:** [LC 0268 Missing Number](../0268-missing-number/)
