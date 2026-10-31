---
number: 91
title: Decode Ways
difficulty: Medium
topic: 1-D Dynamic Programming
pattern: Linear DP on 1/2 digits
link: https://leetcode.com/problems/decode-ways/
lists: [NeetCode 150]
followup_of: ["0070 Climbing Stairs"]
related: ["0639 Decode Ways II", "0139 Word Break"]
---

# 0091. Decode Ways

## ⚡ 30-Second Summary
**Pattern:** Climbing Stairs with conditions
**Key insight:** `dp[i]` = decodings of the first i digits. The last code is either one digit (valid if it isn't '0') or two digits (valid if 10..26). Add the matching earlier counts. Zeros are the whole difficulty.
**Go-to:** Bottom-up with two variables, O(n) time, O(1) space

## Problem
Letters are encoded as numbers: A = 1, B = 2, …, Z = 26. Given a digit string, count how many ways it can be split back into letters. A code can't have a leading zero ("06" is not 6). [LeetCode](https://leetcode.com/problems/decode-ways/)

**Examples:**
```
Input:  s = "12"
Output: 2
Why:    1|2 = "AB" or 12 = "L".

Input:  s = "226"
Output: 3
Why:    2|2|6, 22|6, 2|26.

Input:  s = "06"
Output: 0
Why:    A code can't begin with 0, and "06" isn't a valid two-digit code either.
```

**Constraints:**
- 1 ≤ n ≤ 100, digits only, and leading zeros are possible.
- The answer fits in a 32-bit int.

## Hints
<details><summary>Hint 1</summary>
How is this like Climbing Stairs? What do "1 step" and "2 steps" correspond to?
</details>
<details><summary>Hint 2</summary>
A one-digit step is only allowed for some digits, and a two-digit step only for some pairs. Which ones?
</details>
<details><summary>Hint 3</summary>
dp[0] = 1, dp[1] = (s[0] != '0'). For i ≥ 2: dp[i] = (s[i-1] != '0' ? dp[i-1] : 0) + (10 ≤ s[i-2..i-1] ≤ 26 ? dp[i-2] : 0). Keep two variables.
</details>

## Clarifying Questions
- Is "0" alone decodable? (No. Only 1..26.)
- Can the string start with 0? (Yes, then the answer is 0.)
- Is "06" a valid two-digit code? (No.)
- Does the answer fit in an int? (Yes per LC.)

## Example Walkthrough
"11106": the "0" must pair with the 1 before it as "10", so the split ends …|10|6. The prefix "11" in front is free: 1|1 or 11. That gives 2 ways: 1|1|10|6 and 11|10|6.

## Approaches

### 1. Memoized Recursion: O(n) time, O(n) space
ways(i) = decodings of the suffix from i. Return 0 at a '0', 1 at the end, else ways(i+1) plus ways(i+2) if the pair is 10..26.

### 2. Two Variables ⭐ Go-to: O(n) time, O(1) space
Same recurrence forward over prefixes, keeping dp[i-2] and dp[i-1].
**Why it's the go-to:** iterative, constant space, and the two conditions are easy to state.

## Dry Run (Approach 2)
"2101" (the zero kills the single-digit option and forces "10").

| i | s[i-1] | single ok? | pair | pair ok? | dp[i] |
|---|--------|------------|------|----------|-------|
| 0 | | | | | 1 |
| 1 | 2 | yes | | | 1 |
| 2 | 1 | yes (+dp1 = 1) | 21 | yes (+dp0 = 1) | 2 |
| 3 | 0 | no | 10 | yes (+dp1 = 1) | 1 |
| 4 | 1 | yes (+dp3 = 1) | 01 | no | **1** |

Only 2|10|1 works.

## Edge Case Check
- Leading zero "06": dp1 = 0, and the pair 06 is invalid → 0. ✅
- "10": single '0' not allowed, pair 10 valid → 1. ✅
- "27": 27 > 26 → only 2|7 → 1. ✅
- "11106": the 0 forces "10", so only the leading "11" branches → 2. ✅

## ⚠️ Pitfalls
- **Treating '0' as a valid single digit.**
- **Accepting "06" as a pair**: check `>= 10`, not just `<= 26`.
- **dp[0] = 1** (empty prefix) is required for the pair rule at i = 2.
- **C++ char arithmetic:** `s[i] - '0'`, not `s[i]`.

## 🎯 What the Interviewer Wants
- Map it to the stairs recurrence, with validity checks on each step.
- Handle every zero case without being prompted.
- Show the O(1) space version.

## Follow-ups
- **With '*' wildcards, mod 10⁹+7:** LC 0639 Decode Ways II (not added yet). Same DP, with case counting for each '*'.
- **Split a string using dictionary words:** [LC 0139 Word Break](../0139-word-break/)
- **List all decodings:** backtracking, exponential output.
