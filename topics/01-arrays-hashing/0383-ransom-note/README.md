---
number: 383
title: Ransom Note
difficulty: Easy
topic: Arrays & Hashing
pattern: Frequency count
link: https://leetcode.com/problems/ransom-note/
lists: [LC Top Interview 150]
followup_of: []
related: ["0242 Valid Anagram", "0049 Group Anagrams"]
---

# 0383. Ransom Note

## ⚡ 30-Second Summary
**Pattern:** Frequency count
**Key insight:** The note can be built iff, for every letter, the magazine has at least as many copies as the note needs. Count the magazine, then spend from it.
**Go-to:** 26-slot count array, O(m + n) time, O(1) space

## Problem
Given two strings `ransomNote` and `magazine`, return true if the note can be written using letters cut from the magazine, where each magazine letter can be used at most once. [LeetCode](https://leetcode.com/problems/ransom-note/)

**Examples:**
```
Input:  ransomNote = "a", magazine = "b"
Output: false
Why:    The magazine has no 'a'.

Input:  ransomNote = "aa", magazine = "ab"
Output: false
Why:    The note needs two a's, the magazine only has one.

Input:  ransomNote = "aa", magazine = "aab"
Output: true
Why:    Two a's are available; the extra 'b' is just unused.
```

**Constraints:**
- 1 ≤ |ransomNote|, |magazine| ≤ 10⁵.
- Only lowercase English letters, so 26 counters suffice.

## Hints
<details><summary>Hint 1</summary>
Order doesn't matter at all. What information about the magazine do you actually need?
</details>
<details><summary>Hint 2</summary>
How many of each letter does the magazine supply?
</details>
<details><summary>Hint 3</summary>
Count magazine letters, then decrement for each note letter. If any count goes negative, fail.
</details>

## Clarifying Questions
- Can a magazine letter be reused? (No, each once.)
- Only lowercase letters? (Decides array vs hashmap.)
- Case-sensitive?

## Example Walkthrough
`note = "aa", magazine = "aab"`
- Magazine counts: a=2, b=1.
- Note 'a': a=1. Note 'a': a=0. Nothing went negative, so true.

## Approaches

### 1. Brute Force (remove as you go): O(m·n) time, O(n) space
For each note letter, search the magazine for an unused copy and mark it used. Correct but quadratic.

### 2. Count Array ⭐ Go-to: O(m + n) time, O(1) space
Count magazine letters into 26 slots, then decrement per note letter; a negative count means the note needs more than the magazine has.
**Why it's the go-to:** single pass over each string and constant space.

## Dry Run (Approach 2)
`note = "aa", magazine = "ab"`

| step | char | a | b | negative? |
|------|------|---|---|-----------|
| count mag | a, b | 1 | 1 | |
| note[0] | a | 0 | 1 | no |
| note[1] | a | -1 | 1 | yes, return false |

## Edge Case Check
- Note longer than magazine: some count must go negative (early length check is an optional shortcut). ✅
- Identical strings: all counts end at 0, true. ✅
- Magazine has extra letters: leftovers are fine. ✅

## ⚠️ Pitfalls
- **Counting the note instead of the magazine first** works too, but then you must compare counts at the end; decrementing gives early exit.
- **Python:** `Counter(note) - Counter(mag)` drops non-positive counts, so `not (Counter(note) - Counter(mag))` is a valid one-liner; know why it works.
- **Go:** `s[i]` is a byte, `range s` yields runes; for a–z either works.

## 🎯 What the Interviewer Wants
- Realize order is irrelevant: it's a counting problem.
- Choose array vs hashmap based on the alphabet.
- Clean early exit.

## Follow-ups
- **Exact same multiset (not just ⊆):** [LC 0242 Valid Anagram](../0242-valid-anagram/)
- **Unicode / case-insensitive:** hashmap of counts, normalize case first.
- **Many notes against one magazine:** precompute the magazine counts once.
