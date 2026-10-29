---
number: 28
title: Find the Index of the First Occurrence in a String
difficulty: Easy
topic: Arrays & Hashing
pattern: String matching
link: https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/
lists: [LC Top Interview 150]
followup_of: []
related: ["0459 Repeated Substring Pattern", "0214 Shortest Palindrome"]
---

# 0028. Find the Index of the First Occurrence in a String

## ⚡ 30-Second Summary
**Pattern:** String matching (brute force window, KMP as the follow-up)
**Key insight:** Try every start position and compare the needle character by character. KMP avoids re-checking characters by precomputing how far the needle can "fall back" on a mismatch.
**Go-to:** Brute-force window, O(n·m) time, O(1) space (KMP if asked for linear)

## Problem
Given strings `haystack` and `needle`, return the index of the first place `needle` occurs in `haystack`, or -1 if it doesn't occur.

**Examples:**
```
Input:  haystack = "sadbutsad", needle = "sad"
Output: 0
Why:    "sad" appears at index 0 (and again at 6); the first one counts.

Input:  haystack = "leetcode", needle = "leeto"
Output: -1
Why:    "leet" matches at 0 but the 'o' doesn't, and no other start works.
```

**Constraints:**
- 1 ≤ |haystack|, |needle| ≤ 10⁴, so O(n·m) ≈ 10⁸ char compares in the worst case (fine in practice due to early mismatch).
- Lowercase English letters only.

## Hints
<details><summary>Hint 1</summary>
Which start positions in haystack are even possible?
</details>
<details><summary>Hint 2</summary>
At each start, compare until the first mismatch. Can you skip work after a mismatch?
</details>
<details><summary>Hint 3</summary>
KMP: for each prefix of needle, precompute the length of its longest proper prefix that is also a suffix. On a mismatch, jump j back to that length instead of restarting.
</details>

## Clarifying Questions
- What if needle is empty? (Not possible here; conventionally return 0.)
- Can I use the built-in find? (Usually they want you to implement it.)
- Is linear time required? (Decides brute force vs KMP.)

## Example Walkthrough
`haystack = "leetcode", needle = "leeto"`
- Start 0: l, e, e, t match, then 'c' ≠ 'o'. Fail.
- Starts 1..3: first chars e, e, t ≠ 'l'. Fail. No start beyond 3 fits a length-5 needle. Return -1.

## Approaches

### 1. Brute-Force Window ⭐ Go-to: O(n·m) time, O(1) space
For each start `i` in `[0, n - m]`, compare `needle` with `haystack[i..i+m)` and return `i` on a full match.
**Why it's the go-to:** it's what an Easy expects, it's hard to get wrong, and it passes the limits. Mention KMP as the linear-time upgrade and code it only if asked.

### 2. KMP: O(n + m) time, O(m) space
Build the LPS (longest proper prefix-suffix) array for needle, then scan haystack once; on a mismatch set `j = lps[j-1]` instead of moving i back.

## Dry Run (Approach 1)
`haystack = "sadbutsad", needle = "sad"` (n = 9, m = 3)

| i | window | compare | result |
|---|--------|---------|--------|
| 0 | "sad" | s=s, a=a, d=d | match, return 0 |

LPS for KMP on `needle = "aabaaa"`: `[0,1,0,1,2,2]`.

## Edge Case Check
- Needle longer than haystack: no start positions, -1. ✅
- Needle equals haystack: returns 0. ✅
- Match at the very end, `"abc"`/`"c"`: last start i = n - m = 2. ✅

## ⚠️ Pitfalls
- **Loop bound:** starts go up to `n - m` inclusive. In C++ with size_t, `n - m` underflows when m > n; check that first or use int.
- **KMP LPS build:** on a mismatch, fall back `len = lps[len-1]` without advancing i; only advance i when `len == 0`.
- **Built-ins:** `str.find`, `strings.Index`, `string::find` exist; say so, then implement.

## 🎯 What the Interviewer Wants
- A clean, bounds-correct brute force.
- Awareness of KMP (or Rabin-Karp) and its complexity; coding it is a bonus.

## Follow-ups
- **Linear time guarantee:** KMP (Approach 2) or Rabin-Karp rolling hash.
- **Is the string made of a repeated substring:** KMP's LPS array: LC 0459 Repeated Substring Pattern (not added yet)
- **Shortest palindrome by adding chars in front:** LPS on `s + "#" + reverse(s)`: LC 0214 Shortest Palindrome (not added yet)
