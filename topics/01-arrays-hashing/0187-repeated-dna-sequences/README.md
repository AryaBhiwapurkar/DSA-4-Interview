---
number: 187
title: Repeated DNA Sequences
difficulty: Medium
topic: Arrays & Hashing
pattern: Fixed-length window + hash set (rolling hash / 2-bit encoding)
link: https://leetcode.com/problems/repeated-dna-sequences/
lists: [Interview Extras]
followup_of: []
related: ["0028 Find the Index of the First Occurrence in a String", "1044 Longest Duplicate Substring", "0459 Repeated Substring Pattern"]
---

# 0187. Repeated DNA Sequences

## ⚡ 30-Second Summary
**Pattern:** Slide a length-10 window and remember what you've seen
**Key insight:** There are only n − 9 windows. Put each one in a `seen` set, and add it to `repeated` the second time it shows up. Using a set for `repeated` means each sequence is reported once. Strings cost O(10) per window to hash. The upgrade encodes A/C/G/T as 2 bits, so a window becomes a 20-bit integer that's updated in O(1) with a shift and a mask.
**Go-to:** Substring set, O(n·L) time with L = 10; mention the 2-bit rolling version as the O(n) upgrade

## Problem
Given a DNA string over A, C, G, T, return every 10-letter substring that occurs more than once, in any order. [LeetCode](https://leetcode.com/problems/repeated-dna-sequences/)

**Examples:**
```
Input:  s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
Output: ["AAAAACCCCC","CCCCCAAAAA"]
Why:    Each of those two 10-letter blocks appears twice; nothing else repeats.

Input:  s = "AAAAAAAAAAAAA"
Output: ["AAAAAAAAAA"]
Why:    The 4 overlapping windows are all the same string; report it once.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵; letters are only A, C, G, T.
- Windows may **overlap**; output order doesn't matter.

## Hints
<details><summary>Hint 1</summary>
How many 10-letter substrings does a string of length n have?
</details>
<details><summary>Hint 2</summary>
How do you know a window has been seen before, and how do you avoid reporting it three times?
</details>
<details><summary>Hint 3</summary>
Two sets: seen and repeated. For each window w: if w is in seen, add it to repeated; else add it to seen. (Faster: map A,C,G,T → 0..3 and keep code = ((code &lt;&lt; 2) | v) &amp; 0xFFFFF.)
</details>

## Clarifying Questions
- Overlapping occurrences count? (Yes.)
- Report each sequence once even if it appears 3+ times? (Yes.)
- n < 10? (Return an empty list.)

## Example Walkthrough
`"AAAAAAAAAAAAA"` (n = 13) has windows at 0..3, all "AAAAAAAAAA". Window 0 goes into seen. Window 1 is in seen, so add it to repeated. Windows 2 and 3 are already in repeated, so nothing changes. Output one string.

## Approaches

### 1. Substring Hash Set ⭐ Go-to: O(n·L) time, O(n·L) space
**Why it's the go-to:** obvious, correct and short. L = 10 is a constant, so it's effectively linear.

### 2. 2-Bit Rolling Encoding: O(n) time, O(n) space
A = 0, C = 1, G = 2, T = 3. Each new letter: `code = ((code << 2) | v) & ((1 << 20) − 1)`. Store integers instead of strings. That means less memory and no per-window hashing of 10 characters. It's the general rolling-hash idea (Rabin-Karp) with a perfect, collision-free hash.

## Dry Run (Approach 1)
`"AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"`, key windows only:

| start | window | in seen? | repeated |
|-------|--------|----------|----------|
| 0 | AAAAACCCCC | no | {} |
| 5 | CCCCCAAAAA | no | {} |
| 10 | AAAAACCCCC | **yes** | {AAAAACCCCC} |
| 15 | CCCCCCAAAA | no | |
| 16 | CCCCCAAAAA | **yes** | {AAAAACCCCC, CCCCCAAAAA} |

## Edge Case Check
- n < 10 → []. ✅
- One sequence repeated many times → reported once. ✅
- Overlapping repeats → found, since every start index is a window. ✅

## ⚠️ Pitfalls
- **A list for `repeated`** reports a sequence once per extra occurrence. Use a set (or a count == 2 check).
- **Loop bound:** windows start at 0..n−10 inclusive; with n < 10 the range is empty. In C++ watch `s.size() - 10` underflowing as size_t.
- **Rolling mask:** forget `& 0xFFFFF` and old letters pile up in the high bits.

## 🎯 What the Interviewer Wants
- The simple set solution quickly.
- The bit-encoding / rolling-hash optimisation and why it's collision-free here.
- Overlap and de-duplication handled.

## Follow-ups
- **Substring search with rolling hash or KMP:** [LC 0028 Find the Index of the First Occurrence](../0028-find-the-index-of-the-first-occurrence-in-a-string/)
- **Longest repeated substring of any length:** LC 1044 Longest Duplicate Substring (not added yet). Binary search on length + Rabin-Karp.
- **Is the whole string a repeated block?** [LC 0459 Repeated Substring Pattern](../0459-repeated-substring-pattern/)
