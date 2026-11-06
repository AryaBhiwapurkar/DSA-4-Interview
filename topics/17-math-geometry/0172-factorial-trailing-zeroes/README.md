---
number: 172
title: Factorial Trailing Zeroes
difficulty: Medium
topic: Math & Geometry
pattern: Count factors of 5
link: https://leetcode.com/problems/factorial-trailing-zeroes/
lists: [LC Top Interview 150]
followup_of: []
related: ["0793 Preimage Size of Factorial Zeroes Function", "0050 Pow(x, n)"]
---

# 0172. Factorial Trailing Zeroes

## ⚡ 30-Second Summary
**Pattern:** Legendre's formula: count how many times 5 divides n!
**Key insight:** Each trailing zero is a factor 10 = 2 · 5, and n! has far more 2s than 5s, so count the 5s. ⌊n/5⌋ numbers contribute one 5, ⌊n/25⌋ contribute a second, ⌊n/125⌋ a third, and so on. Divide n by 5 repeatedly and add up the quotients.
**Go-to:** Sum of n/5 + n/25 + …, O(log₅ n) time, O(1) space

## Problem
Return how many zeros n! ends with, without computing n! itself. [LeetCode](https://leetcode.com/problems/factorial-trailing-zeroes/)

**Examples:**
```
Input:  n = 3
Output: 0
Why:    3! = 6, no factor of 5 yet.

Input:  n = 5
Output: 1
Why:    5! = 120: one 5 paired with a 2.

Input:  n = 0
Output: 0
Why:    0! = 1.
```

**Constraints:**
- 0 ≤ n ≤ 10⁴. n! has tens of thousands of digits, so computing it isn't an option in C++.
- Follow-up: O(log n) time.

## Hints
<details><summary>Hint 1</summary>
A trailing zero means a factor of 10. Which prime factors make 10, and which is scarcer in n!?
</details>
<details><summary>Hint 2</summary>
How many of 1..n are multiples of 5? Some of them (25, 50, …) contain more than one 5.
</details>
<details><summary>Hint 3</summary>
count = 0; while n &gt; 0: n /= 5; count += n. Return count.
</details>

## Clarifying Questions
- Is n = 0 allowed? (Yes, 0! = 1, so the answer is 0.)
- Do you want the count, or the digits? (The count only.)

## Example Walkthrough
`n = 30`: multiples of 5 are 5, 10, 15, 20, 25, 30 → 6 fives. 25 = 5² adds one more → 7. Check: 30/5 = 6, 6/5 = 1, 1/5 = 0 → 6 + 1 = 7.

## Approaches

### 1. Count 5s in Each Number: O(n log n) time, O(1) space
For every k in 5, 10, …, n, divide out 5s and count them. Correct but linear in n.

### 2. Divide by Powers of 5 ⭐ Go-to: O(log n) time, O(1) space
**Why it's the go-to:** two lines, it meets the follow-up, and the 2-vs-5 argument is the whole proof.

## Dry Run (Approach 2)
`n = 100`

| step | n after /5 | count |
|------|------------|-------|
| 1 | 20 | 20 |
| 2 | 4 | 24 |
| 3 | 0 | **24** |

## Edge Case Check
- `n = 0`, `n = 4` → 0. ✅
- `n = 25` → 5 + 1 = 6. ✅
- `n = 10⁴` → 2000 + 400 + 80 + 16 + 3 = 2499. ✅

## ⚠️ Pitfalls
- **Computing n!** overflows a 64-bit integer at n = 21; even Python's big ints are wasteful.
- **Only counting n/5** misses the extra 5s in 25, 125, … (n = 25 gives 6, not 5).
- **Multiplying the divisor up** (`for (i = 5; i <= n; i *= 5)`) can overflow `int` for large n; dividing n is safer.

## 🎯 What the Interviewer Wants
- Reduce "trailing zeros" to "factors of 5", with the 2s argument.
- Handle higher powers of 5.
- O(log n), with no factorial computed.

## Follow-ups
- **How many x have exactly k trailing zeros in x!?** LC 0793 Preimage Size of Factorial Zeroes Function (not added yet). Binary search on this function.
- **Trailing zeros in another base:** factor the base and take the minimum over its prime powers.
