---
number: 115
title: Distinct Subsequences
difficulty: Hard
topic: 2-D Dynamic Programming
pattern: Two-string DP
link: https://leetcode.com/problems/distinct-subsequences/
lists: [NeetCode 150]
followup_of: []
related: ["1143 Longest Common Subsequence", "0392 Is Subsequence", "0940 Distinct Subsequences II"]
---

# 0115. Distinct Subsequences

## ⚡ 30-Second Summary
**Pattern:** Two-string counting DP over prefixes
**Key insight:** `dp[i][j]` = ways `s[:i]` can produce `t[:j]`. The last char of s is either not used (`dp[i-1][j]`) or, if it equals `t[j-1]`, used to match it (`+ dp[i-1][j-1]`). Base: `dp[i][0] = 1` (empty t is matched by choosing nothing).
**Go-to:** 2-D table, O(m·n) time, O(m·n) space (1-D backwards row as the follow-up)

## Problem
Count the number of distinct ways to delete characters from s so that what remains is exactly t. Two ways differ if they keep different index sets. [LeetCode](https://leetcode.com/problems/distinct-subsequences/)

**Examples:**
```
Input:  s = "rabbbit", t = "rabbit"
Output: 3
Why:    s has three b's and t needs two; drop any one of them: C(3, 2) = 3.

Input:  s = "babgbag", t = "bag"
Output: 5
Why:    Each valid pick is a b, then a later a, then a later g. Counting index triples (b,a,g): (0,1,3), (0,1,6), (0,5,6), (2,5,6), (4,5,6).
```

**Constraints:**
- 1 ≤ m, n ≤ 1000, so m·n ≤ 10⁶.
- The answer fits in 32 bits, **but intermediate values can overflow even 64 bits** (C++).

## Hints
<details><summary>Hint 1</summary>
Walk through s one character at a time. For each one, what are your choices with respect to t?
</details>
<details><summary>Hint 2</summary>
If s's character matches t's next needed character, you may use it or skip it. If it doesn't match, you must skip it. Both choices give smaller prefix problems.
</details>
<details><summary>Hint 3</summary>
dp[i][0] = 1, dp[0][j>0] = 0. dp[i][j] = dp[i-1][j] + (s[i-1] == t[j-1] ? dp[i-1][j-1] : 0). Answer dp[m][n].
</details>

## Clarifying Questions
- Count index sets, not distinct strings? (Index sets; the strings are all t.)
- Empty t? (1 way.)
- Size of the answer? (Fits in int; intermediates may not.)

## Example Walkthrough
`s = "aaa"`, `t = "aa"`: pick any 2 of the 3 a's → 3. The DP: after "a": ways to make "a" = 1. After "aa": "a" = 2, "aa" = 1. After "aaa": "a" = 3, "aa" = 1 + 2 = 3 (skip the new a, or use it on top of the 2 single-a matches).

## Approaches

### 1. Memoized Recursion: O(m·n) time, O(m·n) space
ways(i, j) on suffixes: skip s[i], plus use it if it matches t[j]. Prune when s has fewer chars left than t.

### 2. 2-D Table ⭐ Go-to: O(m·n) time, O(m·n) space
**Why it's the go-to:** the "skip / use" recurrence is the same shape as LCS, so it's easy to derive and draw.

### 3. 1-D Row, Backwards: O(m·n) time, O(n) space
Iterate j from n down to 1 so row[j-1] still holds the previous row's value (the 0/1 knapsack trick).

## Dry Run (Approach 2)
`s = "babgbag"`, `t = "bag"`. Each row is dp[i][0..3] after reading s[i-1].

| i | s[i-1] | "" | b | ba | bag |
|---|--------|----|---|----|-----|
| 0 | | 1 | 0 | 0 | 0 |
| 1 | b | 1 | 1 | 0 | 0 |
| 2 | a | 1 | 1 | 1 | 0 |
| 3 | b | 1 | 2 | 1 | 0 |
| 4 | g | 1 | 2 | 1 | 1 |
| 5 | b | 1 | 3 | 1 | 1 |
| 6 | a | 1 | 3 | **4** | 1 |
| 7 | g | 1 | 3 | 4 | **5** |

i = 6 ('a'): "ba" = 1 (skip) + 3 (b's before it) = 4. i = 7 ('g'): "bag" = 1 + 4 = 5.

## Edge Case Check
- t empty → 1. ✅
- s shorter than t → 0. ✅
- No matching characters → 0. ✅

## ⚠️ Pitfalls
- **Base case:** dp[i][0] = 1 for every i, including i = 0. Setting only dp[0][0] breaks matches that start later.
- **C++ overflow:** intermediate counts blow past `long long`. Use `unsigned long long` (wraparound is well defined) or `double`.
- **1-D row going forward** reuses the current character twice for one match.
- **Confusing with LCS:** this counts, so matches add; LCS takes a max.

## 🎯 What the Interviewer Wants
- The skip/use recurrence and the empty-t base case.
- Awareness of the overflow trap in C++.
- O(n) space by sweeping j backwards.

## Follow-ups
- **Just check t is a subsequence:** [LC 0392 Is Subsequence](../../02-two-pointers/0392-is-subsequence/). Two pointers.
- **Count distinct subsequence strings of s:** LC 0940 Distinct Subsequences II (not added yet).
- **Longest shared subsequence:** [LC 1143 Longest Common Subsequence](../1143-longest-common-subsequence/)
