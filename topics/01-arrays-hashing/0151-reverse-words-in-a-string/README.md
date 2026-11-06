---
number: 151
title: Reverse Words in a String
difficulty: Medium
topic: Arrays & Hashing
pattern: Split + reverse / in-place reversal
link: https://leetcode.com/problems/reverse-words-in-a-string/
lists: [LC Top Interview 150]
followup_of: []
related: ["0186 Reverse Words in a String II", "0557 Reverse Words in a String III", "0189 Rotate Array"]
---

# 0151. Reverse Words in a String

## ⚡ 30-Second Summary
**Pattern:** Split, reverse, join (in-place follow-up: reverse all, then reverse each word)
**Key insight:** Splitting on whitespace both finds the words and throws away the messy spacing. For O(1) space on a mutable buffer: reverse the whole thing, then reverse each word back, compacting spaces as you go.
**Go-to:** Split + reverse + join, O(n) time, O(n) space

## Problem
Given a string, return its words in reverse order joined by single spaces. The input may have leading, trailing, or repeated spaces, which must not appear in the output. [LeetCode](https://leetcode.com/problems/reverse-words-in-a-string/)

**Examples:**
```
Input:  s = "the sky is blue"
Output: "blue is sky the"
Why:    Same four words, opposite order.

Input:  s = "  hello world  "
Output: "world hello"
Why:    Leading and trailing spaces are dropped.

Input:  s = "a good   example"
Output: "example good a"
Why:    The triple space collapses to a single space.
```

**Constraints:**
- 1 ≤ |s| ≤ 10⁴; letters, digits, and spaces; at least one word.
- Follow-up: if the string is mutable, solve it in place with O(1) extra space.

## Hints
<details><summary>Hint 1</summary>
Which library call gives you the words while ignoring extra spaces?
</details>
<details><summary>Hint 2</summary>
For in place: what happens to the word order if you reverse the entire string?
</details>
<details><summary>Hint 3</summary>
After reversing everything, each word is backwards but in the right position. Reverse each word, and shift words left to squeeze out extra spaces.
</details>

## Clarifying Questions
- What counts as a word separator? (Spaces only.)
- Should extra spaces be collapsed? (Yes, single spaces, no leading/trailing.)
- Is the string mutable / is O(1) space required? (Language-dependent follow-up.)

## Example Walkthrough
`s = "a good   example"`
- Split on whitespace: ["a", "good", "example"].
- Reverse: ["example", "good", "a"]. Join with " ": "example good a".

## Approaches

### 1. Split + Reverse + Join ⭐ Go-to: O(n) time, O(n) space
One line in Python/Go, a short `stringstream` loop in C++.
**Why it's the go-to:** correct by construction for all the spacing cases, and fast to write. Offer the in-place version when asked.

### 2. In-Place Reversal + Compaction: O(n) time, O(1) extra space
Reverse the whole buffer; then walk it with a write pointer, copying each word (with one separating space), reversing that word in place, and finally truncate. Only truly O(1) where strings are mutable (C++); Python/Go need a byte/char copy first.

## Dry Run (Approach 2)
`s = "  hello world  "`

| step | buffer |
|------|--------|
| reverse all | "  dlrow olleh  " |
| copy "dlrow" to front, reverse it | "world..." (write = 5) |
| add space, copy "olleh", reverse it | "world hello..." (write = 11) |
| truncate to write | "world hello" |

## Edge Case Check
- Single word with spaces around it: "  hi  " → "hi". ✅
- Only one word, no spaces: unchanged. ✅
- Multiple spaces between every word: collapsed. ✅

## ⚠️ Pitfalls
- **`split(" ")` / `strings.Split(s, " ")`** keeps empty strings for repeated spaces; use `split()` / `strings.Fields`.
- **In place: forgetting to truncate** leaves leftover characters at the end.
- **In place: adding a space before the first word** gives a leading space.

## 🎯 What the Interviewer Wants
- Correct whitespace handling with the simple approach.
- Ability to do the in-place reverse-all-then-each-word version on request.

## Follow-ups
- **Words are already single-spaced in a char array, do it in place:** LC 0186 Reverse Words in a String II (not added yet)
- **Reverse the letters of each word, keep word order:** LC 0557 Reverse Words in a String III (not added yet)
- **Same reversal trick on numbers:** [LC 0189 Rotate Array](../0189-rotate-array/)
