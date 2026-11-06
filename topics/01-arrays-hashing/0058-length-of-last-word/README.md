---
number: 58
title: Length of Last Word
difficulty: Easy
topic: Arrays & Hashing
pattern: Reverse scan
link: https://leetcode.com/problems/length-of-last-word/
lists: [LC Top Interview 150]
followup_of: []
related: ["0151 Reverse Words in a String"]
---

# 0058. Length of Last Word

## ⚡ 30-Second Summary
**Pattern:** Scan from the end
**Key insight:** Only the tail matters. Skip trailing spaces from the right, then count letters until the next space or the start.
**Go-to:** Reverse scan, O(n) time worst case, O(1) space

## Problem
Given a string of words and spaces, return the length of the last word, where a word is a maximal run of non-space characters. [LeetCode](https://leetcode.com/problems/length-of-last-word/)

**Examples:**
```
Input:  s = "Hello World"
Output: 5
Why:    The last word is "World".

Input:  s = "   fly me   to   the moon  "
Output: 4
Why:    Trailing spaces are ignored; the last word is "moon".

Input:  s = "luffy is still joyboy"
Output: 6
Why:    The last word is "joyboy".
```

**Constraints:**
- 1 ≤ |s| ≤ 10⁴.
- Only letters and spaces, and at least one word exists.

## Hints
<details><summary>Hint 1</summary>
Do you need to look at the beginning of the string at all?
</details>
<details><summary>Hint 2</summary>
What could be at the very end of the string that isn't part of a word?
</details>
<details><summary>Hint 3</summary>
Walk from the end: skip spaces, then count non-spaces until you hit a space or index -1.
</details>

## Clarifying Questions
- Can there be trailing or multiple spaces? (Yes.)
- Is at least one word guaranteed? (Yes.)
- Other whitespace like tabs? (Only spaces here.)

## Example Walkthrough
`s = "   fly me   to   the moon  "`
- From the end: two spaces skipped.
- Count n, o, o, m = 4, then a space stops the count.

## Approaches

### 1. Split, Take Last: O(n) time, O(n) space
Split on whitespace, return the length of the last token. Simple but allocates every word.

### 2. Reverse Scan ⭐ Go-to: O(n) time, O(1) space
Index from the end, skip spaces, then count characters until a space.
**Why it's the go-to:** no allocation, and it only touches the tail in the common case.

## Dry Run (Approach 2)
`s = "Hello World "` (one trailing space; indices 0..11)

| i | s[i] | phase | length |
|---|------|-------|--------|
| 11 | ' ' | skip | 0 |
| 10 | d | count | 1 |
| 9 | l | count | 2 |
| 8 | r | count | 3 |
| 7 | o | count | 4 |
| 6 | W | count | 5 |
| 5 | ' ' | stop | 5 |

## Edge Case Check
- Single word, no spaces, `"a"`: loop runs to index -1, answer 1. ✅
- Leading spaces only before the word, `"  ab"`: stops at index -1 or the space. ✅
- Many trailing spaces: skipped first. ✅

## ⚠️ Pitfalls
- **`split(" ")` (single-space separator)** produces empty strings for repeated or trailing spaces; use `split()` / `strings.Fields`.
- **Not bounding the index:** check `i >= 0` before reading `s[i]` in both loops.
- **C++ `size_t i` counting down** never goes below 0 (it wraps); use `int`.

## 🎯 What the Interviewer Wants
- Notice you only need the end of the string.
- O(1) space version without split.
- Correct loop bounds.

## Follow-ups
- **Reverse the order of all words:** [LC 0151 Reverse Words in a String](../0151-reverse-words-in-a-string/)
- **Length of the longest word:** single forward pass with a running counter.
