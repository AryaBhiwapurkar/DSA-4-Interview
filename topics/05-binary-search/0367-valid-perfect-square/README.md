---
number: 367
title: Valid Perfect Square
difficulty: Easy
topic: Binary Search
pattern: Exact-match binary search on the answer (root)
link: https://leetcode.com/problems/valid-perfect-square/
lists: [Interview Extras]
followup_of: ["0069 Sqrt(x)"]
related: ["0069 Sqrt(x)", "0704 Binary Search", "0633 Sum of Square Numbers"]
---

# 0367. Valid Perfect Square

## ⚡ 30-Second Summary
**Pattern:** Binary search for an r with r · r == num
**Key insight:** `r · r` grows with r, so search r in [1, num]. If `mid²` is too small go right, too big go left, equal means yes. If the range empties, there's no integer root. Compute `mid²` in 64-bit.
**Go-to:** Binary search on the root, O(log num) time, O(1) space

## Problem
Given a positive integer, return whether it is the square of an integer, without using a built-in square root. [LeetCode](https://leetcode.com/problems/valid-perfect-square/)

**Examples:**
```
Input:  num = 16
Output: true
Why:    4 × 4 = 16.

Input:  num = 14
Output: false
Why:    3² = 9 and 4² = 16, so nothing in between squares to 14.
```

**Constraints:**
- 1 ≤ num ≤ 2³¹ − 1: `mid * mid` overflows 32-bit for mid > 46340.

## Hints
<details><summary>Hint 1</summary>
If num is a perfect square, its root r is somewhere in [1, num]. How do the squares of that range behave?
</details>
<details><summary>Hint 2</summary>
They strictly increase, so you can binary search for an r whose square is exactly num.
</details>
<details><summary>Hint 3</summary>
Standard lo ≤ hi search: mid² == num → true; mid² < num → lo = mid + 1; else hi = mid − 1. If the loop ends, return false. Keep mid² in a 64-bit integer.
</details>

## Clarifying Questions
- Is num always positive? (Yes, ≥ 1.)
- Are sqrt / pow off limits? (Yes; floating sqrt also has precision risk at the top of the range.)
- Is num a 32-bit int? (Yes, up to 2³¹ − 1.)

## Example Walkthrough
num = 16: search [1, 16]. mid = 8, 64 > 16 → [1, 7]. mid = 4, 16 == 16 → true.

## Approaches

### 1. Linear Root Scan: O(√num) time, O(1) space
Try r = 1, 2, … while r² ≤ num. About 46k steps at the top: acceptable, but not what's asked for.

### 2. Binary Search on the Root ⭐ Go-to: O(log num) time, O(1) space
Exact-match search over [1, num] using a 64-bit square.
**Why it's the go-to:** about 31 steps, and the template is the one you already know from LC 704.

### 3. Newton's Method: O(log num) time, O(1) space
Start at x = num and repeat `x = (x + num / x) / 2` while x² > num. Integer Newton converges to ⌊√num⌋ from above; then check x² == num. Faster in practice, but harder to justify on the spot.

## Dry Run (Approach 2)
num = 14 (the "no" case).

| lo | hi | mid | mid² | action |
|----|----|-----|------|--------|
| 1 | 14 | 7 | 49 | too big → hi = 6 |
| 1 | 6 | 3 | 9 | too small → lo = 4 |
| 4 | 6 | 5 | 25 | too big → hi = 4 |
| 4 | 4 | 4 | 16 | too big → hi = 3 |
| 4 | 3 | | | lo > hi → **false** |

## Edge Case Check
- num = 1 → mid = 1, 1 == 1 → true. ✅
- num = 2147483647 → the first mid² is ~10¹⁸; fine in 64-bit, would overflow in 32-bit. ✅
- num = 2147395600 = 46340² → true. ✅

## ⚠️ Pitfalls
- **`mid * mid` in int** overflows; use `long long` (Python is fine).
- **`(double)sqrt(num)` then cast** can be off by one for large values: why the problem bans it.
- **Searching up to num with `lo + hi`** in int: use `lo + (hi - lo) / 2`.

## 🎯 What the Interviewer Wants
- Binary search on a numeric answer, not on an array.
- Overflow awareness on the square.
- Bonus: mention Newton's method and its O(log) convergence.

## Follow-ups
- **Return ⌊√x⌋ instead of a yes/no:** [LC 0069 Sqrt(x)](../0069-sqrtx/)
- **Is c a sum of two squares?** two pointers over [0, √c]: LC 0633 Sum of Square Numbers (not added yet)
- **Plain sorted-array search:** [LC 0704 Binary Search](../0704-binary-search/)
