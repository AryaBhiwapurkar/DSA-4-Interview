---
number: 567
title: Permutation in String
difficulty: Medium
topic: Sliding Window
pattern: Fixed window + counts
link: https://leetcode.com/problems/permutation-in-string/
lists: [NeetCode 150]
followup_of: ["0242 Valid Anagram"]
related: ["0438 Find All Anagrams in a String", "0242 Valid Anagram", "0076 Minimum Window Substring"]
---

# 0567. Permutation in String

## ⚡ 30-Second Summary
**Pattern:** Fixed-size sliding window with letter counts
**Key insight:** A permutation of s1 is a substring of s2 iff some window of length |s1| in s2 has the same 26 letter counts as s1. Slide the window one step at a time: add the new char, remove the old one, compare counts.
**Go-to:** Fixed window + count arrays, O(26·n) time, O(1) space

## Problem
Given strings s1 and s2, return true if some permutation of s1 appears as a contiguous substring of s2.

**Examples:**
```
Input:  s1 = "ab", s2 = "eidbaooo"
Output: true
Why:    "ba" (a permutation of "ab") appears at index 3.

Input:  s1 = "ab", s2 = "eidboaoo"
Output: false
Why:    'b' and 'a' are never adjacent in s2.
```

**Constraints:**
- 1 ≤ |s1|, |s2| ≤ 10⁴.
- Lowercase English letters only (26 counters).

## Hints
<details><summary>Hint 1</summary>
How do you check if two strings are permutations of each other? (See Valid Anagram.)
</details>
<details><summary>Hint 2</summary>
Only windows of length |s1| in s2 can match. How do you go from one window to the next cheaply?
</details>
<details><summary>Hint 3</summary>
Keep counts for the current window: add s2[r], remove s2[r - |s1|], and compare with s1's counts.
</details>

## Clarifying Questions
- Contiguous substring of s2? (Yes.)
- Lowercase only? (Yes.)
- What if |s1| > |s2|? (False.)

## Example Walkthrough
`s1 = "ab", s2 = "eidbaooo"`, window size 2
- "ei", "id", "db": counts differ from {a:1, b:1}.
- "ba": counts match → true.

## Approaches

### 1. Sort Every Window: O(n·m log m) time, O(m) space
Sort s1; for each window of s2, sort and compare. Simple, slow.

### 2. Fixed Window + Count Arrays ⭐ Go-to: O(26·n) time, O(1) space
Build counts for s1 and for the first window; slide, updating two entries per step; compare the 26-arrays each time.
**Why it's the go-to:** linear in n (26 is a constant), short, and obviously correct.

### 3. Window + Matches Counter: O(n) time, O(1) space
Track how many of the 26 letters currently have equal counts; update it only for the two letters that change. Avoids the 26-compare per step; mention as the optimization.

## Dry Run (Approach 2)
`s1 = "ab", s2 = "eidbaooo"`, need = {a:1, b:1}

| window | index range | counts | equal? |
|--------|-------------|--------|--------|
| ei | 0-1 | e:1, i:1 | no |
| id | 1-2 | i:1, d:1 | no |
| db | 2-3 | d:1, b:1 | no |
| ba | 3-4 | b:1, a:1 | yes → true |

## Edge Case Check
- |s1| > |s2|: return false immediately. ✅
- s1 equals s2: first window matches. ✅
- Match at the very end of s2: last window checked after the final slide. ✅

## ⚠️ Pitfalls
- **Checking only inside the loop** can miss the first or last window; compare after building the first window and after every slide.
- **Off-by-one on the outgoing index:** remove `s2[r - m]` when adding `s2[r]` (r ≥ m).
- **Matches counter:** update `matches` before and after each count change, carefully (a common source of bugs).

## 🎯 What the Interviewer Wants
- Translate "permutation" into "same letter counts".
- Fixed-size window with O(1) updates per step.

## Follow-ups
- **Return all start indices of anagrams:** same window, collect indices: LC 0438 Find All Anagrams in a String (not added yet)
- **Variable-size window covering all chars of t:** [LC 0076 Minimum Window Substring](../0076-minimum-window-substring/)
- **Unicode:** hashmap counts instead of a 26-array.
