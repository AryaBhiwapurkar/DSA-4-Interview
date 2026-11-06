---
number: 69
title: Sqrt(x)
difficulty: Easy
topic: Binary Search
pattern: Binary search on answer
link: https://leetcode.com/problems/sqrtx/
lists: [LC Top Interview 150]
followup_of: []
related: ["0367 Valid Perfect Square", "0050 Pow(x, n)", "0875 Koko Eating Bananas"]
---

# 0069. Sqrt(x)

## ⚡ 30-Second Summary
**Pattern:** Binary search on the answer
**Key insight:** The answer is the largest k with k² ≤ x. The predicate "k² ≤ x" is true then false as k grows (monotonic), so binary search over k in [0, x] finds the last true.
**Go-to:** Binary search on k with 64-bit squares, O(log x) time, O(1) space

## Problem
Given a non-negative integer x, return ⌊√x⌋ without using any built-in power or square-root function. [LeetCode](https://leetcode.com/problems/sqrtx/)

**Examples:**
```
Input:  x = 4
Output: 2
Why:    2² = 4 exactly.

Input:  x = 8
Output: 2
Why:    √8 ≈ 2.83, rounded down to 2 (3² = 9 is too big).
```

**Constraints:**
- 0 ≤ x ≤ 2³¹ - 1, so mid² can reach ~4.6·10¹⁸: compute it in 64-bit.
- No `sqrt`, `pow`, or `**`.

## Hints
<details><summary>Hint 1</summary>
You're looking for an integer k. If you guess k and k² > x, what do you know about the answer?
</details>
<details><summary>Hint 2</summary>
"k² ≤ x" is a monotonic predicate over k. Find the last k where it's true.
</details>
<details><summary>Hint 3</summary>
Search [0, x]. If mid² ≤ x, record mid and go right; else go left. Compute mid² in 64-bit (or compare mid ≤ x / mid).
</details>

## Clarifying Questions
- Return type: floor of the root? (Yes.)
- x = 0 and x = 1? (0 and 1.)
- Can I use floating-point sqrt? (No.)

## Example Walkthrough
`x = 8`: range [0, 8].
- mid 4: 16 > 8, so hi = 3.
- mid 1: 1 ≤ 8, ans = 1, lo = 2.
- mid 2: 4 ≤ 8, ans = 2, lo = 3.
- mid 3: 9 > 8, hi = 2. Stop. Answer 2.

## Approaches

### 1. Linear Scan: O(√x) time, O(1) space
Increase k while (k+1)² ≤ x. About 46 341 steps at most: passes, but not what's asked.

### 2. Binary Search on Answer ⭐ Go-to: O(log x) time, O(1) space
Find the last k with k² ≤ x.
**Why it's the go-to:** a textbook "binary search on the answer" and easy to make bug-free.

### 3. Newton's Method: O(log x) iterations (quadratic convergence), O(1) space
Integer iteration r = (r + x / r) / 2 starting from r = x, while r² > x. Fastest in practice; worth mentioning as a follow-up.

## Dry Run (Approach 2)
`x = 15` (just below the perfect square 16)

| lo | hi | mid | mid² | ≤ 15? | ans | action |
|----|----|-----|------|-------|-----|--------|
| 0 | 15 | 7 | 49 | no | 0 | hi = 6 |
| 0 | 6 | 3 | 9 | yes | 3 | lo = 4 |
| 4 | 6 | 5 | 25 | no | 3 | hi = 4 |
| 4 | 4 | 4 | 16 | no | 3 | hi = 3 |
| 4 | 3 | | | | | stop, return **3** |

At x = 2147395599 the very first mid is ~1.07·10⁹, whose square overflows 32 bits, which is why the square is computed in 64-bit.

## Edge Case Check
- x = 0 → 0, x = 1 → 1. ✅
- Perfect square (4) → exact root. ✅
- x = 2³¹ - 1 → 46340 (46340² = 2147395600 ≤ 2147483647). ✅

## ⚠️ Pitfalls
- **Overflow in mid × mid**: use `long long` in C++ or compare `mid <= x / mid` (with mid > 0).
- **Starting hi at x with lo = 1**: fine, but handle x = 0 separately; starting at lo = 0 avoids that.
- **Returning lo instead of the last good mid**: with the "record ans" style, return ans.
- **Newton with float division**: use integer division to stay exact.

## 🎯 What the Interviewer Wants
- Frame it as "last k with k² ≤ x" (binary search on the answer).
- Handle overflow explicitly.
- Bonus: mention Newton's method and that hi can be x/2 + 1 for x ≥ 2.

## Follow-ups
- **Is x a perfect square?** same search, check equality: LC 0367 Valid Perfect Square (not added yet)
- **Real-valued root to 1e-6:** binary search on doubles for a fixed number of iterations.
- **Binary search on the answer, harder:** [LC 0875 Koko Eating Bananas](../0875-koko-eating-bananas/)
- **Fast exponent:** [LC 0050 Pow(x, n)](../../17-math-geometry/0050-powx-n/)
