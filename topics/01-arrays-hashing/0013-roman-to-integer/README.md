---
number: 13
title: Roman to Integer
difficulty: Easy
topic: Arrays & Hashing
pattern: Hashmap lookup, subtractive rule
link: https://leetcode.com/problems/roman-to-integer/
lists: [LC Top Interview 150]
followup_of: []
related: ["0012 Integer to Roman"]
---

# 0013. Roman to Integer

## ⚡ 30-Second Summary
**Pattern:** Symbol-value lookup with a look-ahead
**Key insight:** A symbol is subtracted exactly when a larger symbol follows it (IV, IX, XL, XC, CD, CM); otherwise it's added.
**Go-to:** Single pass comparing each symbol with the next, O(n) time, O(1) space

## Problem
Convert a valid Roman numeral string to an integer. Symbols are I=1, V=5, X=10, L=50, C=100, D=500, M=1000, and the six subtractive pairs IV, IX, XL, XC, CD, CM stand for 4, 9, 40, 90, 400, 900.

**Examples:**
```
Input:  s = "III"
Output: 3
Why:    1 + 1 + 1.

Input:  s = "LVIII"
Output: 58
Why:    50 + 5 + 3.

Input:  s = "MCMXCIV"
Output: 1994
Why:    1000 + (1000 - 100) + (100 - 10) + (5 - 1).
```

**Constraints:**
- 1 ≤ |s| ≤ 15.
- s is a valid numeral in [1, 3999], so no input validation is needed.

## Hints
<details><summary>Hint 1</summary>
Ignoring IV-style pairs, the answer is just a sum. What makes the pairs special?
</details>
<details><summary>Hint 2</summary>
In a valid numeral, symbols normally go from large to small. When does a smaller one come before a larger one?
</details>
<details><summary>Hint 3</summary>
For each symbol, look at the next one: if the next is bigger, subtract the current value, else add it.
</details>

## Clarifying Questions
- Is the input always a valid numeral? (Yes.)
- Uppercase only? Range? (Uppercase, 1–3999.)

## Example Walkthrough
`s = "MCMXCIV"`
- M (next C smaller): +1000. C (next M bigger): -100. M: +1000. X (next C bigger): -10. C: +100. I (next V bigger): -1. V (last): +5.
- Total: 1000 - 100 + 1000 - 10 + 100 - 1 + 5 = 1994.

## Approaches

### 1. Match Two-Char Pairs First: O(n) time, O(1) space
At each index, if `s[i..i+1]` is one of the six subtractive pairs, add its value and skip 2; else add the single symbol. Correct but needs a second table.

### 2. Compare With Next ⭐ Go-to: O(n) time, O(1) space
Add `val[s[i]]`, unless `val[s[i]] < val[s[i+1]]`, in which case subtract it.
**Why it's the go-to:** one table, one rule, and it falls straight out of how Roman numerals are written.

## Dry Run (Approach 2)
`s = "MCMXCIV"`

| i | sym | val | next val | op | total |
|---|-----|-----|----------|----|-------|
| 0 | M | 1000 | 100 | + | 1000 |
| 1 | C | 100 | 1000 | - | 900 |
| 2 | M | 1000 | 10 | + | 1900 |
| 3 | X | 10 | 100 | - | 1890 |
| 4 | C | 100 | 1 | + | 1990 |
| 5 | I | 1 | 5 | - | 1989 |
| 6 | V | 5 | - | + | 1994 |

## Edge Case Check
- Single symbol, `"M"`: no next, added. ✅
- Repeated symbols, `"III"`: equal next is not bigger, so added. ✅
- `"MMMCMXCIX"` (3999): all subtractive pairs handled. ✅

## ⚠️ Pitfalls
- **Out-of-bounds look-ahead:** guard `i + 1 < n` before reading `s[i+1]`.
- **Using `<=` instead of `<`** would subtract repeated symbols like the first I in "II".
- **C++ `map[c]`** on a missing key inserts 0; use a switch or a fixed array for the lookup.

## 🎯 What the Interviewer Wants
- Spot the single rule (smaller before larger means subtract).
- Clean bounds handling on the look-ahead.
- Quick and bug-free: this is a warm-up.

## Follow-ups
- **The reverse conversion:** [LC 0012 Integer to Roman](../0012-integer-to-roman/)
- **Validate the numeral too:** check allowed pairs and max repeats (no more than 3 of I/X/C/M, never repeat V/L/D).
- **Right-to-left variant:** subtract if the value is smaller than the previous one added.
