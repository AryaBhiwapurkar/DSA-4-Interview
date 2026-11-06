---
number: 43
title: Multiply Strings
difficulty: Medium
topic: Math & Geometry
pattern: Grade-school multiplication
link: https://leetcode.com/problems/multiply-strings/
lists: [NeetCode 150]
followup_of: ["0415 Add Strings"]
related: ["0066 Plus One", "0067 Add Binary", "0002 Add Two Numbers"]
---

# 0043. Multiply Strings

## ⚡ 30-Second Summary
**Pattern:** Long multiplication into a position array
**Key insight:** Digit `num1[i]` times digit `num2[j]` lands in positions `i + j` (carry) and `i + j + 1` (units) of an array of length m + n. The product never has more than m + n digits. Add every pair's product at `i + j + 1`, push the overflow into `i + j`, then strip leading zeros.
**Go-to:** Position array, O(m·n) time, O(m + n) space

## Problem
Two non-negative integers are given as decimal strings. Return their product as a string, without big-integer libraries and without converting the whole inputs to integers. [LeetCode](https://leetcode.com/problems/multiply-strings/)

**Examples:**
```
Input:  num1 = "2", num2 = "3"
Output: "6"
Why:    Single digits: 2 · 3.

Input:  num1 = "123", num2 = "456"
Output: "56088"
Why:    123 · 456 = 56088; both numbers fit in 3 digits, so the product needs at most 6.
```

**Constraints:**
- 1 ≤ length ≤ 200, so the numbers overflow every built-in type.
- Digits only, no leading zeros except "0" itself.

## Hints
<details><summary>Hint 1</summary>
How did you multiply multi-digit numbers by hand at school? What's the most digits the result can have?
</details>
<details><summary>Hint 2</summary>
Index digits from the left. Where in the result does num1[i] · num2[j] belong?
</details>
<details><summary>Hint 3</summary>
res = m + n zeros. For i, j from the right: sum = d1·d2 + res[i+j+1]; res[i+j+1] = sum % 10; res[i+j] += sum / 10. Skip leading zeros, and return "0" if nothing is left.
</details>

## Clarifying Questions
- Can either input be "0"? (Yes, and the answer must be "0", not "000".)
- Negative numbers? (No.)
- Can I convert single digits with `c - '0'`? (Yes, just not the whole string.)

## Example Walkthrough
`"12" · "34"` with res of length 4. The pairs (from the right): 2·4 = 8 → res[3]. 2·3 = 6 → res[2]. 1·4 = 4 → res[2] = 10, which writes 0 and carries 1 to res[1]. 1·3 = 3 → res[1] = 4. res = [0,4,0,8] → "408".

## Approaches

### 1. Multiply by Each Digit + Add Strings: O(m·n) time, O(m + n) space
For every digit of num2, build `num1 · digit` with the right number of trailing zeros and add it to a running total using string addition (LC 415). This is what you do on paper, but it needs two helpers and lots of string copying.

### 2. Position Array ⭐ Go-to: O(m·n) time, O(m + n) space
**Why it's the go-to:** one double loop, no string addition helper, and the `i + j` / `i + j + 1` index rule is easy to justify.

## Dry Run (Approach 2)
`"123" · "456"`, res length 6. Rows are i (digit of num1), columns are j (digit of num2), both from the right.

| i, j | d1·d2 | pos i+j+1 | res after |
|------|-------|-----------|-----------|
| 2,2 | 3·6 = 18 | 5 | [0,0,0,0,1,8] |
| 2,1 | 3·5 = 15 | 4 | [0,0,0,1,6,8] |
| 2,0 | 3·4 = 12 | 3 | [0,0,1,3,6,8] |
| 1,2 | 2·6 = 12 | 4 | [0,0,1,4,8,8] |
| 1,1 | 2·5 = 10 | 3 | [0,0,2,4,8,8] |
| 1,0 | 2·4 = 8 | 2 | [0,1,0,4,8,8] |
| 0,2 | 1·6 = 6 | 3 | [0,1,1,0,8,8] |
| 0,1 | 1·5 = 5 | 2 | [0,1,6,0,8,8] |
| 0,0 | 1·4 = 4 | 1 | [0,5,6,0,8,8] |

Strip the leading 0 → **"56088"**.

## Edge Case Check
- `"0" · "52"` → all zeros → "0". ✅
- `"9" · "9"` → [8,1] → "81" (uses both slots). ✅
- `"999" · "999"` → 998001, exactly m + n = 6 digits. ✅

## ⚠️ Pitfalls
- **Not stripping leading zeros**, or stripping them all and returning "" for a zero product.
- **Handling the carry in the wrong order:** add the old `res[i+j+1]` before splitting into % 10 and / 10.
- **C++ `char` arithmetic:** `num1[i] * num2[j]` multiplies ASCII codes. Subtract `'0'` first.
- **Python `int(num1) * int(num2)`** works but breaks the rules; mention it and move on.

## 🎯 What the Interviewer Wants
- The m + n digit bound and the index mapping.
- Careful carry handling, plus the "0" result.
- Clean code with no big-integer shortcuts.

## Follow-ups
- **Addition version:** LC 0415 Add Strings (not added yet)
- **Add one to a digit array:** [LC 0066 Plus One](../0066-plus-one/)
- **Binary strings:** [LC 0067 Add Binary](../../18-bit-manipulation/0067-add-binary/)
- **Very large inputs:** Karatsuba (O(n^1.585)) or FFT multiplication. Name them only.
