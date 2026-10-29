---
number: 12
title: Integer to Roman
difficulty: Medium
topic: Arrays & Hashing
pattern: Greedy over value table
link: https://leetcode.com/problems/integer-to-roman/
lists: [LC Top Interview 150]
followup_of: []
related: ["0013 Roman to Integer", "0273 Integer to English Words"]
---

# 0012. Integer to Roman

## ⚡ 30-Second Summary
**Pattern:** Greedy over a descending value table
**Key insight:** Put the six subtractive forms (CM, CD, XC, XL, IX, IV) into the symbol table next to the basic ones. Then repeatedly take the largest value that fits; the subtractive cases fall out automatically.
**Go-to:** Greedy over 13 (value, symbol) pairs, O(1) time and space

## Problem
Convert an integer in [1, 3999] to its Roman numeral, using the standard subtractive forms (4 = IV, 9 = IX, 40 = XL, 90 = XC, 400 = CD, 900 = CM) and never repeating a symbol more than three times.

**Examples:**
```
Input:  num = 3749
Output: "MMMDCCXLIX"
Why:    3000 = MMM, 700 = DCC, 40 = XL, 9 = IX.

Input:  num = 58
Output: "LVIII"
Why:    50 = L, 8 = VIII.

Input:  num = 1994
Output: "MCMXCIV"
Why:    1000 = M, 900 = CM, 90 = XC, 4 = IV.
```

**Constraints:**
- 1 ≤ num ≤ 3999, so the output is at most 15 characters.

## Hints
<details><summary>Hint 1</summary>
Ignore 4s and 9s for a moment: how would you greedily build 3000 + 700 + 8?
</details>
<details><summary>Hint 2</summary>
The 4s and 9s are only six special pairs. Can you treat them as extra "symbols"?
</details>
<details><summary>Hint 3</summary>
Table in descending order: 1000 M, 900 CM, 500 D, 400 CD, 100 C, 90 XC, 50 L, 40 XL, 10 X, 9 IX, 5 V, 4 IV, 1 I. Subtract the largest that fits, repeat.
</details>

## Clarifying Questions
- Range? (1–3999; nothing for 0 or negatives.)
- Standard subtractive notation only? (Yes.)

## Example Walkthrough
`num = 1994`
- 1000 fits: "M", left 994. 900 fits: "MCM", left 94.
- 90 fits: "MCMXC", left 4. 4 fits: "MCMXCIV", left 0.

## Approaches

### 1. Digit Lookup Tables: O(1) time and space
Precompute strings for each digit at each place: `thousands[num/1000] + hundreds[num%1000/100] + tens[num%100/10] + ones[num%10]`. Very fast, but four hand-written tables.

### 2. Greedy Over Value Table ⭐ Go-to: O(1) time and space
Walk the 13-entry table from largest to smallest; while `num ≥ value`, append the symbol and subtract.
**Why it's the go-to:** one small table, one loop, and it's easy to argue correct (Roman numerals are a canonical greedy system once the six pairs are included).

## Dry Run (Approach 2)
`num = 3749`

| value | symbol | times taken | output | left |
|-------|--------|-------------|--------|------|
| 1000 | M | 3 | MMM | 749 |
| 500 | D | 1 | MMMD | 249 |
| 100 | C | 2 | MMMDCC | 49 |
| 40 | XL | 1 | MMMDCCXL | 9 |
| 9 | IX | 1 | MMMDCCXLIX | 0 |

## Edge Case Check
- num = 1: "I". ✅
- num = 3999: "MMMCMXCIX". ✅
- num = 4, 9, 40, 90, 400, 900: each a single table entry. ✅

## ⚠️ Pitfalls
- **Table not in descending order** (or missing a pair) breaks the greedy.
- **Using `if` instead of `while`** for each table entry misses repeats like "III".
- **Two separate arrays drifting out of sync:** keep (value, symbol) together as pairs.

## 🎯 What the Interviewer Wants
- The insight that subtractive pairs are just more table entries.
- Clean greedy loop, quick to write.

## Follow-ups
- **The reverse conversion:** [LC 0013 Roman to Integer](../0013-roman-to-integer/)
- **Integer to English words:** chunk by thousands with lookup tables: LC 0273 Integer to English Words (not added yet)
- **Validate a numeral:** round-trip it through both conversions and compare.
