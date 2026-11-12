---
number: 438
title: Find All Anagrams in a String
difficulty: Medium
topic: Sliding Window
pattern: Fixed-size window + count match
link: https://leetcode.com/problems/find-all-anagrams-in-a-string/
lists: [Interview Extras]
followup_of: ["0567 Permutation in String"]
related: ["0567 Permutation in String", "0242 Valid Anagram", "0076 Minimum Window Substring"]
---

# 0438. Find All Anagrams in a String

## ⚡ 30-Second Summary
**Pattern:** Slide a window of length |p| and compare letter counts
**Key insight:** An anagram of p is any window of length |p| with the same 26 letter counts. Move the window one step at a time by adding the new right letter and dropping the old left one. Track `matches`, the number of letters whose counts agree, so each step is O(1) instead of comparing all 26 counts.
**Go-to:** Fixed window + matches counter, O(n) time, O(1) space

## Problem
Return every start index in s where a substring is an anagram of p (same letters, any order). [LeetCode](https://leetcode.com/problems/find-all-anagrams-in-a-string/)

**Examples:**
```
Input:  s = "cbaebabacd", p = "abc"
Output: [0,6]
Why:    "cba" at 0 and "bac" at 6 use exactly one a, one b and one c.

Input:  s = "abab", p = "ab"
Output: [0,1,2]
Why:    "ab", "ba", "ab": every length-2 window works.
```

**Constraints:**
- 1 ≤ |s|, |p| ≤ 3·10⁴; lowercase letters, so counts fit in 26-slot arrays.

## Hints
<details><summary>Hint 1</summary>
How long is every candidate substring? Does that suggest a fixed or a variable window?
</details>
<details><summary>Hint 2</summary>
When the window slides by one, only two counts change. How can you avoid rebuilding the whole count?
</details>
<details><summary>Hint 3</summary>
need = counts of p, have = counts of the window. Add s[r]; once r ≥ |p| remove s[r − |p|]; when r ≥ |p| − 1 and have == need (or matches == 26), record r − |p| + 1.
</details>

## Clarifying Questions
- Lowercase only? (Yes.)
- Overlapping windows count? (Yes.)
- |p| > |s|? (Return [].)

## Example Walkthrough
`s = "abab", p = "ab"`. Window [0,1] = "ab" ✓ → 0. Slide: drop 'a', add 'a' → "ba" ✓ → 1. Slide again → "ab" ✓ → 2.

## Approaches

### 1. Sort or Count Each Window: O(n · |p|) time
Rebuild the counts for every start index. Correct, but repeats work.

### 2. Sliding Count Arrays: O(26 · n) time, O(1) space
Update two counts per step, then compare 26 entries. Simple and fast enough.

### 3. Sliding Window + Matches Counter ⭐ Go-to: O(n) time, O(1) space
**Why it's the go-to:** the same window as approach 2, but `matches` makes every step O(1), and that trick is reused in 0567 and 0076.

## Dry Run (Approach 3)
`s = "cbaebabacd", p = "abc"` (window size 3)

| r | add | drop | window | anagram? | out |
|---|-----|------|--------|----------|-----|
| 2 | a | – | cba | yes | [0] |
| 3 | e | c | bae | no | |
| 4 | b | b | aeb | no | |
| 5 | a | a | eba | no | |
| 6 | b | e | bab | no | |
| 7 | a | b | aba | no | |
| 8 | c | a | bac | yes | [0,6] |
| 9 | d | b | acd | no | **[0,6]** |

## Edge Case Check
- |p| > |s| → []. ✅
- s == p → [0]. ✅
- Repeated letters in p (`"aab"`) → counts handle multiplicity. ✅

## ⚠️ Pitfalls
- **Recording before the window is full** (r < |p| − 1).
- **Off-by-one on the drop index:** remove s[r − |p|] when adding s[r].
- **Updating `matches` wrongly:** check equality before and after each count change, in both directions.

## 🎯 What the Interviewer Wants
- Fixed-size window with incremental counts.
- O(n) or O(26n), with an explanation of why sorting each window is wasteful.

## Follow-ups
- **Just "does one exist":** [LC 0567 Permutation in String](../0567-permutation-in-string/)
- **Variable window covering p:** [LC 0076 Minimum Window Substring](../0076-minimum-window-substring/)
- **Anagram check of two strings:** [LC 0242 Valid Anagram](../../01-arrays-hashing/0242-valid-anagram/)
