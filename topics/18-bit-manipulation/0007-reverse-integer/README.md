---
number: 7
title: Reverse Integer
difficulty: Medium
topic: Bit Manipulation
pattern: Digit pop with overflow check
link: https://leetcode.com/problems/reverse-integer/
lists: [NeetCode 150]
followup_of: []
related: ["0008 String to Integer (atoi)", "0190 Reverse Bits", "0009 Palindrome Number"]
---

# 0007. Reverse Integer

## ⚡ 30-Second Summary
**Pattern:** Pop the last digit, push it onto the result, and check for overflow **before** pushing
**Key insight:** `d = x % 10; x /= 10; r = r * 10 + d`. Since 64-bit ints aren't allowed, test `r > INT_MAX / 10` (or equal with d > 7), and the matching INT_MIN test (d < −8), before multiplying.
**Go-to:** Pop and check, O(number of digits) time, O(1) space

## Problem
Reverse the decimal digits of a signed 32-bit integer, keeping its sign. If the reversed value falls outside the 32-bit signed range, return 0. You may not use 64-bit integers. [LeetCode](https://leetcode.com/problems/reverse-integer/)

**Examples:**
```
Input:  x = 123
Output: 321
Why:    Digits in reverse order.

Input:  x = -123
Output: -321
Why:    The sign stays in front.

Input:  x = 120
Output: 21
Why:    The trailing zero becomes a leading zero and disappears.
```

**Constraints:**
- −2³¹ ≤ x ≤ 2³¹ − 1.
- **No 64-bit integers allowed**, so a `long long` check is off the table.

## Hints
<details><summary>Hint 1</summary>
How do you take the last digit off a number, and how do you add a digit to the end of another?
</details>
<details><summary>Hint 2</summary>
r * 10 + d can overflow. What condition on r (and d) tells you that before you compute it?
</details>
<details><summary>Hint 3</summary>
Before r = r*10 + d: return 0 if r > INT_MAX/10 or (r == INT_MAX/10 and d > 7); similarly r < INT_MIN/10 or (r == INT_MIN/10 and d < −8). In C++ this handles negatives directly because % keeps the sign.
</details>

## Clarifying Questions
- Overflow → return 0? (Yes.)
- 64-bit allowed? (No.)
- Leading zeros after reversing? (Dropped: 120 → 21.)

## Example Walkthrough
`-2147483412`: C++ pops the digits as −2, −1, −4, … (they keep the sign). Before the last digit, r = −214384741, which is above INT_MIN / 10 = −214748364, so pushing −2 is safe: the result is −2143847412, which fits.

## Approaches

### 1. String Reverse + Range Check: O(d) time, O(d) space
Reverse the digit string and parse it into a 64-bit value, then range-check. Easy, but uses 64 bits, which the problem forbids.

### 2. Pop and Check ⭐ Go-to: O(d) time, O(1) space
**Why it's the go-to:** it respects the 32-bit restriction, and the pre-check is the point of the problem.

## Dry Run (Approach 2)
x = 1534236469 (INT_MAX / 10 = 214748364)

| step | d | r before | check | r after |
|------|---|----------|-------|---------|
| 1 | 9 | 0 | ok | 9 |
| 2 | 6 | 9 | ok | 96 |
| … | … | … | ok | … |
| 9 | 5 | 96463243 | ok | 964632435 |
| 10 | 1 | 964632435 | 964632435 > 214748364 | **return 0** |

## Edge Case Check
- x = INT_MIN → reversed would be 8463847412 → 0, and no `abs(INT_MIN)` is ever computed. ✅
- Trailing zeros (120) → 21. ✅
- x = 0 → loop never runs → 0. ✅

## ⚠️ Pitfalls
- **Checking after multiplying:** the overflow has already happened (UB in C++).
- **`abs(INT_MIN)` in C++** overflows; the C++ go-to works on the signed value directly.
- **Python `%` with negatives** returns a non-negative digit (−123 % 10 == 7); take abs() and restore the sign.
- **Using `long long`** silently violates the stated restriction.

## 🎯 What the Interviewer Wants
- The digit pop/push loop.
- A correct pre-multiplication overflow check for both signs.
- Awareness of language differences in `%` and `/`.

## Follow-ups
- **Parse a string with overflow clamping:** LC 0008 String to Integer (atoi) (not added yet). Same pre-check, clamp instead of 0.
- **Is the number a palindrome?** [LC 0009 Palindrome Number](../../17-math-geometry/0009-palindrome-number/). Reverse half the digits.
- **Reverse binary digits:** [LC 0190 Reverse Bits](../0190-reverse-bits/)
