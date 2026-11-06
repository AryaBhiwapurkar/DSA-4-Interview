---
number: 9
title: Palindrome Number
difficulty: Easy
topic: Math & Geometry
pattern: Reverse half the number
link: https://leetcode.com/problems/palindrome-number/
lists: [LC Top Interview 150]
followup_of: []
related: ["0007 Reverse Integer", "0125 Valid Palindrome", "0234 Palindrome Linked List"]
---

# 0009. Palindrome Number

## ⚡ 30-Second Summary
**Pattern:** Pop digits off the end and build the reversed lower half
**Key insight:** Reverse only until the reversed part is at least as big as what's left. At that point you've seen half the digits, and nothing can overflow. Even length: `x == rev`. Odd length: `x == rev / 10`, which drops the middle digit. Negatives, and positives ending in 0, are never palindromes.
**Go-to:** Reverse half, O(log₁₀ x) time, O(1) space

## Problem
Decide whether an integer reads the same forwards and backwards in base 10. The follow-up asks you to do it without converting to a string. [LeetCode](https://leetcode.com/problems/palindrome-number/)

**Examples:**
```
Input:  x = 121
Output: true
Why:    1-2-1 is symmetric.

Input:  x = -121
Output: false
Why:    The minus sign only appears on the left, so reversed it's "121-".

Input:  x = 10
Output: false
Why:    Reversed it would start with 0 ("01"), which doesn't match.
```

**Constraints:**
- −2³¹ ≤ x ≤ 2³¹ − 1, so a full reverse can overflow a 32-bit int (e.g. 2147483647 → 7463847412).

## Hints
<details><summary>Hint 1</summary>
Which inputs can you reject straight away, before looking at any digits?
</details>
<details><summary>Hint 2</summary>
Reversing the whole number can overflow. Do you need all of it reversed to compare?
</details>
<details><summary>Hint 3</summary>
Reject x &lt; 0 and (x % 10 == 0 and x ≠ 0). Then, while x &gt; rev: rev = rev·10 + x % 10, x /= 10. Answer: x == rev or x == rev / 10.
</details>

## Clarifying Questions
- Are negatives allowed? (Yes, and they're never palindromes.)
- Is string conversion allowed? (Allowed, but the follow-up says avoid it.)
- Is 0 a palindrome? (Yes.)

## Example Walkthrough
`x = 12321`: pop 1 → x = 1232, rev = 1. Pop 2 → x = 123, rev = 12. Pop 3 → x = 12, rev = 123. Now x < rev, so stop. The length is odd, so compare x with rev / 10 = 12. They match → true.

## Approaches

### 1. String Compare: O(d) time, O(d) space
`to_string(x)` and compare it with its reverse. Fine as a first answer, but it ignores the follow-up.

### 2. Full Reverse in 64 Bits: O(d) time, O(1) space
Reverse the whole number in a `long long` and compare it with x. Correct, but you need the wider type.

### 3. Reverse Half ⭐ Go-to: O(d) time, O(1) space
**Why it's the go-to:** no string, no overflow, and it shows you noticed the trailing-zero trap.

## Dry Run (Approach 3)
`x = 1221`

| step | x | rev | x > rev? |
|------|---|-----|----------|
| start | 1221 | 0 | yes |
| 1 | 122 | 1 | yes |
| 2 | 12 | 12 | no → stop |

Even length: x == rev (12 == 12) → **true**. For `x = 10`, the trailing-zero check rejects it before the loop.

## Edge Case Check
- `0` → true (the zero check excludes x = 0). ✅
- `10`, `100` → false via the trailing-zero rule. ✅
- Single digit `7` → loop runs once (rev = 7, x = 0), then x == rev / 10 → true. ✅
- `2147483647` → never overflows, since only half is reversed. ✅

## ⚠️ Pitfalls
- **Missing the trailing-zero check:** for `10` the loop ends with x = 0, rev = 1, and `rev / 10 == 0 == x` wrongly says true.
- **Full reverse in a C++ `int`** overflows for large inputs (undefined behaviour).
- **Python `%` and `//` on negatives** round towards −∞ (`-121 % 10 == 9`). Return early for negatives so it never matters.

## 🎯 What the Interviewer Wants
- Early exits for negatives and trailing zeros.
- The half-reverse trick and why it avoids overflow.
- Odd vs even length handled with `rev / 10`.

## Follow-ups
- **Reverse with overflow checks:** [LC 0007 Reverse Integer](../../18-bit-manipulation/0007-reverse-integer/)
- **String palindrome, skipping non-alphanumerics:** [LC 0125 Valid Palindrome](../../02-two-pointers/0125-valid-palindrome/)
- **Palindrome linked list:** LC 0234 Palindrome Linked List (not added yet). Reverse the second half.
