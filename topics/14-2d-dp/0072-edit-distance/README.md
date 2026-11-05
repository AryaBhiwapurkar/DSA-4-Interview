---
number: 72
title: Edit Distance
difficulty: Medium
topic: 2-D Dynamic Programming
pattern: Two-string DP
link: https://leetcode.com/problems/edit-distance/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["1143 Longest Common Subsequence", "0583 Delete Operation for Two Strings", "0161 One Edit Distance"]
---

# 0072. Edit Distance

## ⚡ 30-Second Summary
**Pattern:** Two-string DP over prefixes (Levenshtein distance)
**Key insight:** `dp[i][j]` = edits to turn `a[:i]` into `b[:j]`. Equal last chars cost nothing: `dp[i-1][j-1]`. Otherwise 1 + the best of replace (`dp[i-1][j-1]`), delete from a (`dp[i-1][j]`), insert into a (`dp[i][j-1]`). Base: `dp[i][0] = i`, `dp[0][j] = j`.
**Go-to:** (m+1)×(n+1) table, O(m·n) time, O(m·n) space

## Problem
Return the minimum number of single-character inserts, deletes and replacements needed to turn one string into another. [LeetCode](https://leetcode.com/problems/edit-distance/)

**Examples:**
```
Input:  word1 = "horse", word2 = "ros"
Output: 3
Why:    Replace h with r ("rorse"), delete the middle r ("rose"), delete e ("ros").

Input:  word1 = "intention", word2 = "execution"
Output: 5
Why:    Five operations: delete i, replace n→e, t→x, n→c, then insert u. No 4-step version exists.
```

**Constraints:**
- 0 ≤ m, n ≤ 500. **Either string can be empty.**
- Lowercase English letters.

## Hints
<details><summary>Hint 1</summary>
How many edits does it take to turn a string into the empty string? The empty string into a string?
</details>
<details><summary>Hint 2</summary>
Look at the last characters. If they're equal, what's left? If not, each of the three operations fixes the last position in a different way. What subproblem does each leave?
</details>
<details><summary>Hint 3</summary>
dp[i][0] = i, dp[0][j] = j. If a[i-1] == b[j-1]: dp[i][j] = dp[i-1][j-1]. Else 1 + min(dp[i-1][j-1] (replace), dp[i-1][j] (delete), dp[i][j-1] (insert)).
</details>

## Clarifying Questions
- Which operations, all cost 1? (Insert, delete, replace, cost 1 each.)
- Empty strings allowed? (Yes: the answer is the other length.)
- Is a swap of adjacent characters allowed? (No. That's Damerau distance.)

## Example Walkthrough
`"horse"` → `"ros"`: the last chars e/s differ. Deleting e leaves "hors" → "ros", whose last chars s/s match, leaving "hor" → "ro". The table takes the cheapest route through all such choices: 3.

## Approaches

### 1. Memoized Recursion: O(m·n) time, O(m·n) space
ed(i, j) on suffixes with the same four cases. Good for deriving the recurrence out loud.

### 2. 2-D Table ⭐ Go-to: O(m·n) time, O(m·n) space
Fill the table with the base row/column set to i and j.
**Why it's the go-to:** the canonical answer; each cell's three neighbours map one-to-one to the three operations, which is easy to explain.

### 3. Two Rows: O(m·n) time, O(n) space
Keep the previous row plus the current one; the diagonal is `prev[j-1]`.

## Dry Run (Approach 2)
`a = "horse"` (rows), `b = "ros"` (columns).

| | "" | r | o | s |
|---|---|---|---|---|
| "" | 0 | 1 | 2 | 3 |
| h | 1 | 1 | 2 | 3 |
| o | 2 | 2 | **1** | 2 |
| r | 3 | **2** | 2 | 2 |
| s | 4 | 3 | 3 | **2** |
| e | 5 | 4 | 4 | **3** |

(o, o) matches → copies the diagonal 1. (s, s) matches → copies diagonal dp[r][o] = 2. (e, s): 1 + min(replace 3, delete 2, insert 4) = 3. The cheapest choice is to delete the e.

## Edge Case Check
- `""` → `"abc"`: dp[0][3] = 3 inserts. ✅
- `"abc"` → `""`: 3 deletes. ✅
- Equal strings → 0. ✅

## ⚠️ Pitfalls
- **Forgetting the base row/column** (i and j, not 0): empty → "abc" costs 3.
- **Adding 1 on a match:** matching characters are free.
- **Mixing up insert/delete directions:** it doesn't change the answer (both cost 1), but explain them consistently.
- **Empty input with the memo version:** the memo table has 0 rows, so the "string exhausted" base cases must run before any `memo[i][j]` read.

## 🎯 What the Interviewer Wants
- Derive the three-way recurrence from the last characters.
- Correct base cases for empty prefixes.
- O(n) space and, optionally, recovering the edit script.

## Follow-ups
- **Only insert/delete allowed:** LC 0583 Delete Operation for Two Strings (not added yet). m + n - 2·LCS.
- **The LCS view of the same table:** [LC 1143 Longest Common Subsequence](../1143-longest-common-subsequence/)
- **Exactly one edit apart?** LC 0161 One Edit Distance (not added yet). O(n) two-pointer check, no table.
- **Different costs per operation:** same recurrence with weights.
