---
number: 66
title: Plus One
difficulty: Easy
topic: Math & Geometry
pattern: Carry from the end
link: https://leetcode.com/problems/plus-one/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0067 Add Binary", "0002 Add Two Numbers", "0043 Multiply Strings"]
---

# 0066. Plus One

## ⚡ 30-Second Summary
**Pattern:** Walk from the last digit, propagating the carry
**Key insight:** Adding 1 only changes the trailing run of 9s plus the digit before it. Scan from the right. A digit below 9 gets bumped by one and you return at once. A 9 becomes 0 and the carry moves left. If every digit was a 9, the answer is 1 followed by n zeros.
**Go-to:** Right-to-left carry with early return, O(n) time, O(1) extra (O(n) only for all 9s)

## Problem
A non-negative integer is stored as an array of its digits, most significant first, with no leading zeros. Return the digit array of that number plus one. [LeetCode](https://leetcode.com/problems/plus-one/)

**Examples:**
```
Input:  digits = [1,2,3]
Output: [1,2,4]
Why:    123 + 1 = 124, no carry.

Input:  digits = [4,3,2,1]
Output: [4,3,2,2]
Why:    Only the last digit changes.

Input:  digits = [9]
Output: [1,0]
Why:    9 + 1 = 10, so the array grows by one.
```

**Constraints:**
- 1 ≤ n ≤ 100, so the number can be up to 100 digits long and won't fit in any built-in integer type.
- No leading zeros (except the number 0 itself).

## Hints
<details><summary>Hint 1</summary>
Why can't you convert to an integer, add one and convert back?
</details>
<details><summary>Hint 2</summary>
Which digits change when you add 1? When does the carry stop?
</details>
<details><summary>Hint 3</summary>
From the right: if digit &lt; 9, increment it and return. Otherwise set it to 0 and continue. If the loop finishes, put a 1 in front.
</details>

## Clarifying Questions
- Can the array be modified in place? (Yes, LeetCode accepts that.)
- Leading zeros in the input? (No.)
- Max length? (100, so don't parse into an int.)

## Example Walkthrough
`[1,9,9]`: last 9 → 0, carry. Middle 9 → 0, carry. The 1 becomes 2 → return `[2,0,0]`. Only the trailing 9s and one more digit were touched.

## Approaches

Converting to a number, adding and splitting back works in Python (big ints) but overflows in C++ past about 19 digits. Mention it only to reject it.

### 1. General Carry Loop: O(n) time, O(1) extra
Classic addition: `sum = d + carry`, `d = sum % 10`, `carry = sum / 10`, starting with carry = 1. Always walks the full array.

### 2. Early-exit Carry ⭐ Go-to: O(n) worst, O(1) extra
**Why it's the go-to:** shortest code, stops at the first non-9, and the all-9s case is a single line.

## Dry Run (Approach 2)
`[9,9,9]`

| i | digit before | action | digits |
|---|--------------|--------|--------|
| 2 | 9 | set 0, carry | [9,9,0] |
| 1 | 9 | set 0, carry | [9,0,0] |
| 0 | 9 | set 0, carry | [0,0,0] |
| end | | prepend 1 | **[1,0,0,0]** |

## Edge Case Check
- `[0]` → `[1]`. ✅
- All 9s → length grows by one. ✅
- Last digit < 9 → one step. ✅

## ⚠️ Pitfalls
- **Parsing into `int` / `long long`** overflows for 100-digit inputs.
- **Forgetting the all-9s case** returns `[0,0,0]`.
- **C++ `insert(begin(), 1)`** is O(n). That's fine here, since it happens at most once.

## 🎯 What the Interviewer Wants
- Digit-by-digit addition without converting the whole number.
- Early exit, and the all-9s case handled cleanly.
- O(n) worst case, with O(1) extra space in the typical case.

## Follow-ups
- **Add two binary strings:** [LC 0067 Add Binary](../../18-bit-manipulation/0067-add-binary/)
- **Add two numbers stored in linked lists:** [LC 0002 Add Two Numbers](../../06-linked-list/0002-add-two-numbers/)
- **Multiply instead of add:** [LC 0043 Multiply Strings](../0043-multiply-strings/)
