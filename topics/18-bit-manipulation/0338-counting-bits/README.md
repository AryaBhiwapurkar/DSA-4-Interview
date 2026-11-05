---
number: 338
title: Counting Bits
difficulty: Easy
topic: Bit Manipulation
pattern: DP on bits
link: https://leetcode.com/problems/counting-bits/
lists: [NeetCode 150]
followup_of: ["0191 Number of 1 Bits"]
related: ["0070 Climbing Stairs", "0461 Hamming Distance"]
---

# 0338. Counting Bits

## ⚡ 30-Second Summary
**Pattern:** DP where each number reuses a smaller number's answer
**Key insight:** `i >> 1` is i with its last bit chopped off, and it's smaller than i, so its count is already known. Add back the chopped bit: `ans[i] = ans[i >> 1] + (i & 1)`.
**Go-to:** DP on `i >> 1`, O(n) time, O(1) extra space

## Problem
For every integer i from 0 to n, compute how many 1 bits i has, and return them as an array. [LeetCode](https://leetcode.com/problems/counting-bits/)

**Examples:**
```
Input:  n = 2
Output: [0,1,1]
Why:    0, 1 and 10 in binary.

Input:  n = 5
Output: [0,1,1,2,1,2]
Why:    3 is 11 and 5 is 101, two bits each; 4 is 100, one bit.
```

**Constraints:**
- 0 ≤ n ≤ 10⁵.
- Follow-up: O(n), without a built-in popcount.

## Hints
<details><summary>Hint 1</summary>
Counting each number separately is O(n log n). How is i's binary form related to a smaller number's?
</details>
<details><summary>Hint 2</summary>
Shifting right by one removes the last bit. What do you lose, and how do you add it back?
</details>
<details><summary>Hint 3</summary>
ans[0] = 0; for i ≥ 1, ans[i] = ans[i >> 1] + (i & 1). Equivalently ans[i] = ans[i & (i − 1)] + 1.
</details>

## Clarifying Questions
- Include 0 and n? (Yes, n + 1 entries.)
- Built-ins allowed? (The follow-up says no.)

## Example Walkthrough
i = 6 (110): 6 >> 1 = 3 (11), which has 2 bits; the dropped bit is 0, so ans[6] = 2. i = 7 (111): 7 >> 1 = 3, dropped bit 1, so ans[7] = 3.

## Approaches

### 1. Popcount Each: O(n log n) time, O(1) extra
Run LC 191 on every i. Fine, but misses the reuse.

### 2. DP on i >> 1 ⭐ Go-to: O(n) time, O(1) extra
**Why it's the go-to:** one line, obviously correct (the right shift is always smaller), and it answers the follow-up.

### 3. DP on i & (i − 1): O(n) time, O(1) extra
i with its lowest 1 removed is smaller and has exactly one fewer bit. Equally good; pick whichever you can explain.

## Dry Run (Approach 2)
n = 8

| i | bin | i >> 1 | i & 1 | ans[i] |
|---|-----|--------|-------|--------|
| 1 | 1 | 0 | 1 | 0 + 1 = 1 |
| 2 | 10 | 1 | 0 | 1 |
| 3 | 11 | 1 | 1 | 2 |
| 4 | 100 | 2 | 0 | 1 |
| 5 | 101 | 2 | 1 | 2 |
| 6 | 110 | 3 | 0 | 2 |
| 7 | 111 | 3 | 1 | 3 |
| 8 | 1000 | 4 | 0 | **1** |

## Edge Case Check
- n = 0 → [0]. ✅
- Powers of two → 1. ✅
- 2^k − 1 → k. ✅

## ⚠️ Pitfalls
- **Precedence:** `ans[i >> 1] + i & 1` parses as `(ans[i >> 1] + i) & 1`.
- **Off-by-one:** the array has n + 1 entries.
- **Using the "highest power of two" offset DP** works but needs extra bookkeeping; the shift version is simpler.

## 🎯 What the Interviewer Wants
- Spot the subproblem (i >> 1 or i & (i − 1)).
- O(n) without built-ins.
- Clean precedence and indexing.

## Follow-ups
- **Single number's bit count:** [LC 0191 Number of 1 Bits](../0191-number-of-1-bits/)
- **Same "reuse a smaller answer" idea:** [LC 0070 Climbing Stairs](../../13-1d-dp/0070-climbing-stairs/)
- **Sum of bit counts up to n in O(log n):** count each bit position's contribution by cycles of length 2^(k+1).
