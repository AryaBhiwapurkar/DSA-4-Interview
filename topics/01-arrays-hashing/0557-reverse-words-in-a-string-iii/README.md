---
number: 557
title: Reverse Words in a String III
difficulty: Easy
topic: Arrays & Hashing
pattern: Reverse each word in place (two pointers per word)
link: https://leetcode.com/problems/reverse-words-in-a-string-iii/
lists: [Interview Extras]
followup_of: ["0151 Reverse Words in a String"]
related: ["0151 Reverse Words in a String", "0344 Reverse String", "0189 Rotate Array"]
---

# 0557. Reverse Words in a String III

## ⚡ 30-Second Summary
**Pattern:** Find each word's boundaries and reverse that range
**Key insight:** The words stay in place; only their letters flip. Scan with a start pointer. At each space (or the end), reverse `s[start..i−1]` and move start past the space. Single spaces and no leading or trailing spaces make the boundaries trivial.
**Go-to:** In-place per-word reversal, O(n) time, O(1) extra (in C++; Python strings need a list)

## Problem
Reverse the letters of every word in a sentence while keeping the word order and the single spaces. [LeetCode](https://leetcode.com/problems/reverse-words-in-a-string-iii/)

**Examples:**
```
Input:  s = "Let's take LeetCode contest"
Output: "s'teL ekat edoCteeL tsetnoc"
Why:    Each word is mirrored; punctuation inside a word moves with it.

Input:  s = "Mr Ding"
Output: "rM gniD"
Why:    Two words, each reversed, still in the same order.
```

**Constraints:**
- 1 ≤ n ≤ 5·10⁴; printable ASCII.
- Words are separated by **exactly one** space; no leading or trailing spaces.

## Hints
<details><summary>Hint 1</summary>
Which parts of the string move, and which stay put?
</details>
<details><summary>Hint 2</summary>
If you know where a word starts and ends, how do you reverse just that range in place?
</details>
<details><summary>Hint 3</summary>
start = 0; for i in 0..n: if i == n or s[i] == ' ': reverse s[start..i−1], start = i + 1.
</details>

## Clarifying Questions
- Always exactly one space between words? (Yes; otherwise preserve whatever spacing there is.)
- Do punctuation marks count as letters? (Yes, everything between spaces is the word.)
- In place? (Possible in C++; Python strings are immutable.)

## Example Walkthrough
`"Mr Ding"`: at i = 2 (space), reverse [0,1] → "rM Ding", start = 3. At i = 7 (end), reverse [3,6] → "rM gniD".

## Approaches

### 1. Split, Reverse, Join: O(n) time, O(n) space
`" ".join(w[::-1] for w in s.split(" "))`. Perfect in Python, but it allocates new strings.

### 2. In-place Per-word Reversal ⭐ Go-to: O(n) time, O(1) extra
**Why it's the go-to:** it shows you can do the boundary bookkeeping, and it's the building block of LC 151's "reverse all, then reverse each word".

## Dry Run (Approach 2)
`"Let's take"`

| i | s[i] | action | string |
|---|------|--------|--------|
| 5 | ' ' | reverse [0,4] | "s'teL take" |
| 10 | end | reverse [6,9] | "s'teL ekat" |

## Edge Case Check
- Single word → the whole string is reversed. ✅
- One-letter words → unchanged. ✅
- Trailing word handled by the `i == n` check. ✅

## ⚠️ Pitfalls
- **Missing the last word:** the loop must also trigger at i == n, not only at spaces.
- **Python `s.split()`** collapses multiple spaces. Fine here, but `split(" ")` keeps the exact spacing if inputs may vary.
- **Reversing the whole string** reverses the word order too. That's LC 151, not this.

## 🎯 What the Interviewer Wants
- Correct boundary handling, including the final word.
- An in-place O(1)-extra version in a mutable-string language.
- A quick idiomatic one-liner where the language allows it.

## Follow-ups
- **Reverse the word order instead:** [LC 0151 Reverse Words in a String](../0151-reverse-words-in-a-string/)
- **Same "reverse parts" trick on arrays:** [LC 0189 Rotate Array](../0189-rotate-array/)
