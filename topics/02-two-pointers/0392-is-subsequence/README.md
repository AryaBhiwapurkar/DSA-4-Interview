---
number: 392
title: Is Subsequence
difficulty: Easy
topic: Two Pointers
pattern: Two pointers on two strings
link: https://leetcode.com/problems/is-subsequence/
lists: [LC Top Interview 150]
followup_of: []
related: ["0792 Number of Matching Subsequences", "1143 Longest Common Subsequence", "0115 Distinct Subsequences"]
---

# 0392. Is Subsequence

## ⚡ 30-Second Summary
**Pattern:** Two pointers, one per string
**Key insight:** Walk t once; every time t's character matches the next unmatched character of s, advance in s. Greedy matching as early as possible is always safe.
**Go-to:** Two pointers, O(|t|) time, O(1) space (binary-search index for the many-queries follow-up)

## Problem
Given strings `s` and `t`, return true if `s` can be obtained by deleting some (possibly zero) characters from `t` without reordering the rest.

**Examples:**
```
Input:  s = "abc", t = "ahbgdc"
Output: true
Why:    a, b, c appear in t in that order (positions 0, 2, 5).

Input:  s = "axc", t = "ahbgdc"
Output: false
Why:    t has no 'x', so s can't be matched.
```

**Constraints:**
- 0 ≤ |s| ≤ 100; 0 ≤ |t| ≤ 10⁴; lowercase letters.
- Follow-up: billions of different s against the same t; preprocess t.

## Hints
<details><summary>Hint 1</summary>
Should you match s[0] to the first occurrence in t, or might a later one be better?
</details>
<details><summary>Hint 2</summary>
Use a pointer into s and scan t once.
</details>
<details><summary>Hint 3</summary>
For many queries: store, for each letter, the sorted positions where it occurs in t, and binary search for the next position after the current one.
</details>

## Clarifying Questions
- Is the empty s a subsequence? (Yes, always.)
- Must characters be contiguous? (No, only in order.)
- One query or many against the same t? (Many changes the best solution.)

## Example Walkthrough
`s = "abc", t = "ahbgdc"`
- t[0] a = s[0] → i = 1. h no. t[2] b = s[1] → i = 2. g, d no. t[5] c = s[2] → i = 3 = |s|. True.

## Approaches

### 1. Two Pointers ⭐ Go-to: O(|t|) time, O(1) space
Pointer i into s; scan t, advance i on a match; answer is `i == |s|`.
**Why it's the go-to:** it's optimal for a single query and trivial to get right.

### 2. Preprocess t + Binary Search: O(|t|) once, then O(|s| log |t|) per query, O(|t|) space
`pos[c]` = sorted indices of c in t. For each char of s, binary search the first index > previous match. This is the answer to the follow-up.

## Dry Run (Approach 1)
`s = "axc", t = "ahbgdc"`

| j | t[j] | i (before) | s[i] | match? | i (after) |
|---|------|------------|------|--------|-----------|
| 0 | a | 0 | a | yes | 1 |
| 1 | h | 1 | x | no | 1 |
| 2 | b | 1 | x | no | 1 |
| 3 | g | 1 | x | no | 1 |
| 4 | d | 1 | x | no | 1 |
| 5 | c | 1 | x | no | 1 |

End: i = 1 ≠ 3, false.

## Edge Case Check
- s empty: i = 0 = |s| immediately, true. ✅
- t empty and s non-empty: false. ✅
- s == t: true. ✅
- s longer than t: false. ✅

## ⚠️ Pitfalls
- **Reading s[i] after i reached |s|:** stop advancing (or bound-check) once s is fully matched.
- **Binary search variant:** search for the first position strictly greater than the previous one (upper_bound, `bisect_right`).

## 🎯 What the Interviewer Wants
- The greedy two-pointer solution and why greedy is safe.
- A good answer to the "many s" follow-up (index + binary search).

## Follow-ups
- **Count how many words are subsequences of s:** bucket words by their next needed char: LC 0792 Number of Matching Subsequences (not added yet)
- **Longest common subsequence of two strings:** 2-D DP: [LC 1143 Longest Common Subsequence](../../14-2d-dp/1143-longest-common-subsequence/)
- **Count distinct ways s appears as a subsequence of t:** [LC 0115 Distinct Subsequences](../../14-2d-dp/0115-distinct-subsequences/)
