---
number: 242
title: Valid Anagram
difficulty: Easy
topic: Arrays & Hashing
pattern: Frequency count
link: https://leetcode.com/problems/valid-anagram/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0049 Group Anagrams", "0383 Ransom Note", "0438 Find All Anagrams in a String", "0567 Permutation in String"]
---

# 0242. Valid Anagram

## ⚡ 30-Second Summary
**Pattern:** Frequency count
**Key insight:** Two strings are anagrams iff every character appears the same number of times in both. Count up for `s`, down for `t`, and check everything is zero.
**Go-to:** 26-slot count array, O(n) time, O(1) space

## Problem
Given two strings `s` and `t`, return true if `t` is a rearrangement of the letters of `s` (same letters, same counts), otherwise false. [LeetCode](https://leetcode.com/problems/valid-anagram/)

**Examples:**
```
Input:  s = "anagram", t = "nagaram"
Output: true
Why:    Both have three a's, one each of n, g, r, m.

Input:  s = "rat", t = "car"
Output: false
Why:    s has a 't' that t lacks (and t has a 'c' that s lacks).
```

**Constraints:**
- 1 ≤ |s|, |t| ≤ 5·10⁴.
- Only lowercase English letters, so a fixed array of 26 counts works.

## Hints
<details><summary>Hint 1</summary>
If the lengths differ, can they be anagrams?
</details>
<details><summary>Hint 2</summary>
Sorting both strings and comparing works. Can you avoid the sort?
</details>
<details><summary>Hint 3</summary>
Use one count array: +1 for each char of s, -1 for each char of t. Anagrams leave all zeros.
</details>

## Clarifying Questions
- Only lowercase a–z, or Unicode? (Decides array vs hashmap.)
- Case-sensitive? Do spaces count?
- Can the strings have different lengths? (Then the answer is immediately false.)

## Example Walkthrough
`s = "rat", t = "car"`
- Lengths match (3).
- Counts after s: r=1, a=1, t=1. After subtracting t: r=0, a=0, t=1, c=-1.
- Not all zero, so false.

## Approaches

### 1. Sort Both: O(n log n) time, O(n) space
Sort the characters of each string and compare. Short to write, but slower and needs copies (strings are immutable in Python/Go).

### 2. Count Array ⭐ Go-to: O(n) time, O(1) space
One array of 26 ints: increment for `s[i]`, decrement for `t[i]`, then check all zeros.
**Why it's the go-to:** linear, constant space, and easy to explain. Swap the array for a hashmap if the alphabet is not fixed.

## Dry Run (Approach 2)
`s = "anagram", t = "nagaram"` (showing only letters touched)

| step | s char | t char | a | n | g | r | m |
|------|--------|--------|---|---|---|---|---|
| 0 | a | n | 1 | -1 | 0 | 0 | 0 |
| 1 | n | a | 0 | 0 | 0 | 0 | 0 |
| 2 | a | g | 1 | 0 | -1 | 0 | 0 |
| 3 | g | a | 0 | 0 | 0 | 0 | 0 |
| 4 | r | r | 0 | 0 | 0 | 0 | 0 |
| 5 | a | a | 0 | 0 | 0 | 0 | 0 |
| 6 | m | m | 0 | 0 | 0 | 0 | 0 |

All zeros, so true.

## Edge Case Check
- Different lengths, `"ab"` vs `"a"`: early false. ✅
- Same string: trivially true. ✅
- Single char, `"a"` vs `"b"`: counts a=1, b=-1, false. ✅

## ⚠️ Pitfalls
- **Skipping the length check** lets the single loop over `s` read past the end of `t`.
- **Unicode input** breaks `c - 'a'` indexing; use a hashmap keyed by character (or rune in Go).
- **Go:** indexing a string gives bytes; `range` over a string gives runes. For a–z only, bytes are fine.

## 🎯 What the Interviewer Wants
- Sorting as the quick idea, then the counting improvement.
- Explain why the count array is O(1) space (fixed alphabet).
- Bring up the Unicode follow-up yourself.

## Follow-ups
- **Unicode characters:** hashmap of counts instead of a 26-array.
- **Group many strings by anagram:** [LC 0049 Group Anagrams](../0049-group-anagrams/)
- **Find all anagram windows of p in s:** sliding window: LC 0438 Find All Anagrams in a String (not added yet)
- **Does s contain a permutation of p:** [LC 0567 Permutation in String](../../03-sliding-window/0567-permutation-in-string/)
