---
number: 125
title: Valid Palindrome
difficulty: Easy
topic: Two Pointers
pattern: Converging pointers
link: https://leetcode.com/problems/valid-palindrome/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0680 Valid Palindrome II", "0009 Palindrome Number", "0005 Longest Palindromic Substring"]
---

# 0125. Valid Palindrome

## ⚡ 30-Second Summary
**Pattern:** Converging two pointers
**Key insight:** Compare from both ends inward, skipping anything that isn't a letter or digit and comparing case-insensitively. No need to build a cleaned copy.
**Go-to:** Two pointers with skipping, O(n) time, O(1) space

## Problem
Given a string, return true if it reads the same forwards and backwards after lowercasing it and removing every character that isn't a letter or a digit.

**Examples:**
```
Input:  s = "A man, a plan, a canal: Panama"
Output: true
Why:    Cleaned, it's "amanaplanacanalpanama", which is a palindrome.

Input:  s = "race a car"
Output: false
Why:    Cleaned, it's "raceacar"; reversed is "racaecar".

Input:  s = " "
Output: true
Why:    Cleaned, it's the empty string, which counts as a palindrome.
```

**Constraints:**
- 1 ≤ |s| ≤ 2·10⁵.
- Printable ASCII only, so the standard isalnum/tolower helpers are safe.

## Hints
<details><summary>Hint 1</summary>
Building a cleaned string and reversing it works. Can you avoid the extra copy?
</details>
<details><summary>Hint 2</summary>
Start one pointer at each end. What should happen when a pointer lands on a comma or space?
</details>
<details><summary>Hint 3</summary>
Advance each pointer past non-alphanumerics, then compare lowercase versions; move both inward on a match, return false on a mismatch.
</details>

## Clarifying Questions
- Which characters count? (Letters and digits only.)
- Case-sensitive? (No.)
- Is the empty cleaned string a palindrome? (Yes.)
- Unicode? (ASCII only here.)

## Example Walkthrough
`s = "race a car"`
- r vs r ✓, a vs a ✓, c vs c ✓, e vs (skip space) a ✗.
- Mismatch, so false.

## Approaches

### 1. Clean + Reverse: O(n) time, O(n) space
Filter to lowercase alphanumerics, compare with its reverse. One line in Python.

### 2. Two Pointers ⭐ Go-to: O(n) time, O(1) space
`l = 0, r = n-1`; skip non-alphanumerics from each side; compare lowercase; move inward.
**Why it's the go-to:** same time, constant space, and it's the pattern the problem is testing.

## Dry Run (Approach 2)
`s = "A man, a plan, a canal: Panama"` (first few steps)

| l | s[l] | r | s[r] | action |
|---|------|---|------|--------|
| 0 | A | 29 | a | a == a, move both |
| 1 | ' ' → skip to 2 'm' | 28 | m | m == m |
| 3 | a | 27 | a | a == a |
| 4 | n | 26 | n | n == n |
| 5 | ',' → skip to 7 'a' | 25 | a | ... continues until l ≥ r → true |

## Edge Case Check
- Only punctuation/spaces, `" "` or `".,"`: pointers cross without a comparison, true. ✅
- Digits mixed with letters, `"0P"`: '0' vs 'p' differ, false. ✅
- Single character: true. ✅

## ⚠️ Pitfalls
- **Skipping loops without `l < r`** can run past each other or off the string.
- **Digits count:** use isalnum, not isalpha (`"0P"` must be false).
- **C++ `isalnum(char)` with negative chars** is UB; cast to `unsigned char` (safe here, but a good habit).

## 🎯 What the Interviewer Wants
- Two pointers with clean skipping logic.
- O(1) space and correct bounds.

## Follow-ups
- **Allowed to delete at most one character:** on the first mismatch, try skipping either side: LC 0680 Valid Palindrome II (not added yet)
- **Integer palindrome without string conversion:** [LC 0009 Palindrome Number](../../17-math-geometry/0009-palindrome-number/)
- **Longest palindromic substring:** expand around centers: [LC 0005 Longest Palindromic Substring](../../13-1d-dp/0005-longest-palindromic-substring/)
