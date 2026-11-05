---
number: 97
title: Interleaving String
difficulty: Medium
topic: 2-D Dynamic Programming
pattern: Two-string DP
link: https://leetcode.com/problems/interleaving-string/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["1143 Longest Common Subsequence", "0072 Edit Distance"]
---

# 0097. Interleaving String

## ⚡ 30-Second Summary
**Pattern:** Two-string DP over prefixes, with the third string's index fixed at i + j
**Key insight:** `dp[i][j]` = can `s1[:i]` and `s2[:j]` interleave into `s3[:i+j]`. The last character of that prefix of s3 came from s1 or from s2: `dp[i][j] = (dp[i-1][j] && s1[i-1] == s3[i+j-1]) || (dp[i][j-1] && s2[j-1] == s3[i+j-1])`.
**Go-to:** 2-D boolean table, O(m·n) time, O(m·n) space (1-D row as the follow-up)

## Problem
Decide whether s3 can be built by merging s1 and s2 character by character, keeping the relative order inside each of them. [LeetCode](https://leetcode.com/problems/interleaving-string/)

**Examples:**
```
Input:  s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
Output: true
Why:    "aa" from s1, "dbbc" from s2, "bc" from s1, "a" from s2, "c" from s1.

Input:  s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
Output: false
Why:    The first two a's must come from s1 (s2 starts with d), then d, then the three b's use every b in both strings. s3 now wants an a, but both strings offer c next.

Input:  s1 = "", s2 = "", s3 = ""
Output: true
Why:    Two empty strings merge into the empty string.
```

**Constraints:**
- 0 ≤ m, n ≤ 100, |s3| ≤ 200.
- Follow-up: O(n) extra space.

## Hints
<details><summary>Hint 1</summary>
When both s1 and s2 offer the next character of s3, greedily picking one can fail. What do you need to remember to try both safely?
</details>
<details><summary>Hint 2</summary>
After using i characters of s1 and j of s2, you've matched exactly i + j characters of s3. So (i, j) is the whole state.
</details>
<details><summary>Hint 3</summary>
Check lengths first. dp[0][0] = true. dp[i][j] is true if (dp[i-1][j] and s1[i-1] == s3[i+j-1]) or (dp[i][j-1] and s2[j-1] == s3[i+j-1]). Answer dp[m][n].
</details>

## Clarifying Questions
- Must all of s1 and s2 be used? (Yes: check m + n == |s3| first.)
- Empty strings? (Allowed.)
- The LC "|n − m| ≤ 1" alternation wording? (It doesn't constrain anything: any interleaving can be cut into such pieces.)

## Example Walkthrough
`s1 = "aab"`, `s2 = "axy"`, `s3 = "aaxaby"`. Greedy "prefer s1" takes both a's from s1, then needs x: s1 offers b, s2 offers a. Dead end. The real split is a(s1), a(s2), x(s2), a(s1), b(s1), y(s2), so the first tie had to go to s1 and the second to s2. The table keeps both options alive.

## Approaches

### 1. Memoized Recursion: O(m·n) time, O(m·n) space
ok(i, j): try taking s3[i+j] from s1 or s2. Memo on (i, j); the k index is derived.

### 2. 2-D Table ⭐ Go-to: O(m·n) time, O(m·n) space
Fill dp row by row; row 0 and column 0 are "only one string used so far".
**Why it's the go-to:** the recurrence is easy to state and the table is easy to draw; space can be cut when asked.

### 3. 1-D Row: O(m·n) time, O(n) space
row[j] holds dp[i-1][j] until it's overwritten; row[j-1] is already dp[i][j-1].

## Dry Run (Approach 2)
`s1 = "aab"` (rows), `s2 = "axy"` (columns), `s3 = "aaxaby"`. T = true.

| | "" | a | x | y |
|---|---|---|---|---|
| "" | T | T | F | F |
| a | T | T | T | F |
| a | T | F | T | F |
| b | F | F | T | **T** |

dp[1][2] = T: "a" + "ax" → "aax" (from dp[1][1] with s2's x). dp[3][2] = T via s1's b, then dp[3][3] adds s2's y. The bottom-right T means yes.

## Edge Case Check
- Length mismatch → false immediately. ✅
- One string empty → s3 must equal the other. ✅
- All empty → true. ✅

## ⚠️ Pitfalls
- **Greedy two-pointer** fails when both strings offer the same next character.
- **Skipping the length check**: dp[m][n] would read past s3 or return a partial match.
- **Using a 3-D state (i, j, k)**: k = i + j is redundant.
- **1-D row:** forgetting that row[j] must be recomputed even when false (stale `true` from the previous row).

## 🎯 What the Interviewer Wants
- Show why greedy fails, then define dp on prefixes.
- Notice k = i + j.
- O(n) space if prompted.

## Follow-ups
- **Two-string prefix DP, longest shared subsequence:** [LC 1143 Longest Common Subsequence](../1143-longest-common-subsequence/)
- **Edits between two strings:** [LC 0072 Edit Distance](../0072-edit-distance/)
- **Return one valid interleaving:** walk back from dp[m][n] through true cells.
