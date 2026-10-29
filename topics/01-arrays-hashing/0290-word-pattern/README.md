---
number: 290
title: Word Pattern
difficulty: Easy
topic: Arrays & Hashing
pattern: Two-way mapping
link: https://leetcode.com/problems/word-pattern/
lists: [LC Top Interview 150]
followup_of: ["0205 Isomorphic Strings"]
related: ["0205 Isomorphic Strings", "0291 Word Pattern II"]
---

# 0290. Word Pattern

## ⚡ 30-Second Summary
**Pattern:** Two-way (bijective) mapping
**Key insight:** Same as Isomorphic Strings, but letters map to words. Split the sentence, check counts match, then enforce letter→word and word→letter consistency.
**Go-to:** Split + two hashmaps, O(n + m) time, O(k) space

## Problem
Given a `pattern` of letters and a string `s` of space-separated words, return true if `s` follows the pattern: each letter maps to exactly one word, each word maps to exactly one letter, and the sequence matches position by position.

**Examples:**
```
Input:  pattern = "abba", s = "dog cat cat dog"
Output: true
Why:    a↔dog, b↔cat, and the order a b b a matches.

Input:  pattern = "abba", s = "dog cat cat fish"
Output: false
Why:    The last 'a' would need to be "dog", but it's "fish".

Input:  pattern = "aaaa", s = "dog cat cat dog"
Output: false
Why:    'a' can't map to both "dog" and "cat".
```

**Constraints:**
- 1 ≤ |pattern| ≤ 300; 1 ≤ |s| ≤ 3000.
- Words are lowercase, separated by single spaces, no leading/trailing spaces.

## Hints
<details><summary>Hint 1</summary>
Turn s into a list of words first. What must be true about the two lengths?
</details>
<details><summary>Hint 2</summary>
This is Isomorphic Strings with words on one side.
</details>
<details><summary>Hint 3</summary>
Keep letter→word and word→letter maps; any disagreement on either side means false.
</details>

## Clarifying Questions
- Can there be extra spaces? (Not on LeetCode; in real life, split on whitespace.)
- Must the mapping be one-to-one both ways? (Yes: "abba" vs "dog dog dog dog" is false.)
- What if the word count differs from the pattern length? (False.)

## Example Walkthrough
`pattern = "abba", s = "dog dog dog dog"`
- a↔dog. Then b→dog: forward is new, but reverse says dog already belongs to a. False.

## Approaches

### 1. First-Occurrence Signature: O(n + m) time, O(n + m) space
Map each letter to the index of its first occurrence in the pattern, and each word likewise in the word list; compare the two index sequences.

### 2. Two Hashmaps ⭐ Go-to: O(n + m) time, O(k) space
Split, compare lengths, then for each i check/record `p[i]→w[i]` and `w[i]→p[i]`.
**Why it's the go-to:** direct, early exit, and it reuses the exact reasoning from Isomorphic Strings.

## Dry Run (Approach 2)
`pattern = "abba", s = "dog cat cat fish"`

| i | p[i] | w[i] | p→w (before) | w→p (before) | ok? |
|---|------|------|--------------|--------------|-----|
| 0 | a | dog | {} | {} | add |
| 1 | b | cat | {a:dog} | {dog:a} | add |
| 2 | b | cat | {a:dog, b:cat} | {dog:a, cat:b} | consistent |
| 3 | a | fish | same | same | a maps to dog, not fish: false |

## Edge Case Check
- Word count ≠ pattern length, `"aaa"` vs `"dog dog"`: false. ✅
- Many letters to one word, `"ab"` vs `"dog dog"`: reverse map catches it. ✅
- Single letter and word: true. ✅

## ⚠️ Pitfalls
- **Forgetting the length check:** zip/indexing silently stops at the shorter one.
- **Only one direction checked:** `"abba"` vs `"dog dog dog dog"` slips through.
- **C++ splitting:** `stringstream ss(s); while (ss >> w)` handles any whitespace.

## 🎯 What the Interviewer Wants
- Spot the link to Isomorphic Strings.
- Handle the length mismatch and both mapping directions.
- Clean string splitting in your language.

## Follow-ups
- **Characters instead of words:** [LC 0205 Isomorphic Strings](../0205-isomorphic-strings/)
- **No spaces in s (you choose the split):** backtracking: LC 0291 Word Pattern II (not added yet)
