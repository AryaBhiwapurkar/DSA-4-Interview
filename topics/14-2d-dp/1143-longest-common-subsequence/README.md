---
number: 1143
title: Longest Common Subsequence
difficulty: Medium
topic: 2-D Dynamic Programming
pattern: Two-string DP
link: https://leetcode.com/problems/longest-common-subsequence/
lists: [NeetCode 150]
followup_of: []
related: ["0072 Edit Distance", "0583 Delete Operation for Two Strings", "1092 Shortest Common Supersequence"]
---

# 1143. Longest Common Subsequence

## ⚡ 30-Second Summary
**Pattern:** Two-string DP over prefixes
**Key insight:** `dp[i][j]` = LCS of `a[:i]` and `b[:j]`. If the last characters match, they pair up: `dp[i-1][j-1] + 1`. Otherwise drop one of them: `max(dp[i-1][j], dp[i][j-1])`.
**Go-to:** (m+1)×(n+1) table, O(m·n) time, O(m·n) space (two rows for O(n))

## Problem
Given two strings, return the length of the longest sequence of characters that appears in both, in the same order but not necessarily contiguous. [LeetCode](https://leetcode.com/problems/longest-common-subsequence/)

**Examples:**
```
Input:  text1 = "abcde", text2 = "ace"
Output: 3
Why:    "ace" itself is a subsequence of "abcde" (skip b and d).

Input:  text1 = "abc", text2 = "abc"
Output: 3
Why:    Identical strings share all of their characters.

Input:  text1 = "abc", text2 = "def"
Output: 0
Why:    No character appears in both.
```

**Constraints:**
- 1 ≤ m, n ≤ 1000, so m·n ≤ 10⁶.
- Lowercase English letters only.

## Hints
<details><summary>Hint 1</summary>
Compare the last characters of the two strings. What are the possibilities when they're equal, and when they differ?
</details>
<details><summary>Hint 2</summary>
If they differ, at least one of them isn't in the LCS. Which two smaller problems does that give you?
</details>
<details><summary>Hint 3</summary>
dp[i][j] over prefix lengths, row and column 0 are 0. Match: dp[i-1][j-1] + 1. No match: max(dp[i-1][j], dp[i][j-1]). Answer dp[m][n].
</details>

## Clarifying Questions
- Subsequence (gaps allowed) or substring (contiguous)? (Subsequence.)
- Return the length or the sequence? (Length. Reconstruction is a follow-up.)
- Empty strings? (Lengths ≥ 1, but the table handles 0 naturally.)

## Example Walkthrough
`"abcde"` vs `"ace"`: the a's match (1). Next, "bcde" vs "ce": b doesn't match, so skip it; c matches (2). Then "de" vs "e": skip d, e matches (3). The DP tries every "skip which side" choice, keeping the best.

## Approaches

### 1. Memoized Recursion: O(m·n) time, O(m·n) space
lcs(i, j) on suffixes, with the same match/skip choices. Recursion depth up to m+n (2000): fine in C++, raise the limit in Python.

### 2. 2-D Table ⭐ Go-to: O(m·n) time, O(m·n) space
Fill dp[i][j] over prefix lengths with row/column 0 as the empty-prefix base.
**Why it's the go-to:** the template for every two-string DP (edit distance, distinct subsequences, interleaving), and it supports reconstructing the actual subsequence.

### 3. Two Rows: O(m·n) time, O(min(m, n)) space
dp[i] only reads row i-1, so keep `prev` and `cur`. Loses easy reconstruction.

## Dry Run (Approach 2)
`a = "abcde"` (rows), `b = "ace"` (columns).

| | "" | a | c | e |
|---|---|---|---|---|
| "" | 0 | 0 | 0 | 0 |
| a | 0 | **1** | 1 | 1 |
| b | 0 | 1 | 1 | 1 |
| c | 0 | 1 | **2** | 2 |
| d | 0 | 1 | 2 | 2 |
| e | 0 | 1 | 2 | **3** |

Bold cells are matches (diagonal + 1); every other cell copies the bigger of top/left.

## Edge Case Check
- No common character (example 3) → all zeros. ✅
- One string inside the other ("abcde", "ace") → the shorter length. ✅
- Repeated letters ("aaaa", "aa") → 2, the table never reuses a character. ✅

## ⚠️ Pitfalls
- **Confusing it with longest common substring**, where a mismatch resets to 0.
- **Off-by-one between dp indices and string indices:** dp[i][j] reads a[i-1], b[j-1].
- **Python recursion limit** for the memo version at m + n = 2000.
- **Python two-row version:** `prev = cur` and then writing into `cur` changes both lists. Build a fresh `cur` per row (C++ `swap` is fine).

## 🎯 What the Interviewer Wants
- The match / skip-one-side recurrence and the empty-prefix base case.
- Clean table fill, then O(n) space when asked.
- Reconstruction: walk back from dp[m][n], take diagonals on matches.

## Follow-ups
- **Min edits (insert, delete, replace):** [LC 0072 Edit Distance](../0072-edit-distance/)
- **Min deletions to make two strings equal:** LC 0583 Delete Operation for Two Strings (not added yet). m + n - 2·LCS.
- **Shortest string containing both:** LC 1092 Shortest Common Supersequence (not added yet). Reconstruct via the LCS table.
- **Count the ways one string appears in the other:** [LC 0115 Distinct Subsequences](../0115-distinct-subsequences/)
- **LIS as LCS with the sorted array:** [LC 0300 Longest Increasing Subsequence](../../13-1d-dp/0300-longest-increasing-subsequence/)
