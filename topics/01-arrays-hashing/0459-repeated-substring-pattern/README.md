---
number: 459
title: Repeated Substring Pattern
difficulty: Easy
topic: Arrays & Hashing
pattern: Divisor-length check / doubled string / KMP period
link: https://leetcode.com/problems/repeated-substring-pattern/
lists: [Interview Extras]
followup_of: []
related: ["0028 Find the Index of the First Occurrence in a String", "0214 Shortest Palindrome", "0187 Repeated DNA Sequences"]
---

# 0459. Repeated Substring Pattern

## ⚡ 30-Second Summary
**Pattern:** A block can only repeat to fill s if its length divides n
**Key insight:** Try each proper divisor `len` of n (only up to n/2) and check `s == s[:len] * (n/len)`. Two shortcuts exist. **Doubled string:** s is periodic iff s appears in `(s + s)` with its first and last characters removed. **KMP:** with `p = n − lps[n−1]`, s is periodic iff `lps[n−1] > 0` and `n % p == 0`.
**Go-to:** Divisor-length check, O(n · d(n)) time, where d(n) is the number of divisors (tiny); mention both shortcuts

## Problem
Decide whether a string can be built by writing one of its substrings two or more times in a row. [LeetCode](https://leetcode.com/problems/repeated-substring-pattern/)

**Examples:**
```
Input:  s = "abab"
Output: true
Why:    "ab" written twice.

Input:  s = "aba"
Output: false
Why:    No block repeats to give exactly "aba".

Input:  s = "abcabcabcabc"
Output: true
Why:    "abc" four times (or "abcabc" twice).
```

**Constraints:**
- 1 ≤ n ≤ 10⁴, lowercase letters.
- The block must repeat **at least twice**, so a block of length n doesn't count.

## Hints
<details><summary>Hint 1</summary>
If s is k copies of a block, what must be true about the block's length?
</details>
<details><summary>Hint 2</summary>
The block must also be a prefix of s. How many candidate lengths are there?
</details>
<details><summary>Hint 3</summary>
For len in 1..n/2 with n % len == 0: if s[:len] repeated n/len times equals s, return true. Return false at the end.
</details>

## Clarifying Questions
- Must the block repeat at least twice? (Yes; n = 1 → false.)
- Character set? (Lowercase letters.)
- Is O(n·d(n)) acceptable? (Yes; n ≤ 10⁴ has at most 64 divisors.)

## Example Walkthrough
`"abcabcabcabc"` (n = 12). Divisors ≤ 6: 1, 2, 3, 4, 6. len 1: "a"×12 ✗. len 2: "ab"×6 ✗. len 3: "abc"×4 = s ✓ → true.

## Approaches

### 1. Divisor-length Check ⭐ Go-to: O(n · d(n)) time, O(n) space
**Why it's the go-to:** obviously correct, easy to explain, and fast because few lengths divide n.

### 2. Doubled String: O(n) average with a good search, O(n) space
`s in (s + s)[1:-1]`. If s = BB…B, then s + s contains s at offset |B|, which survives the trimming. The reverse direction (an occurrence implies a period) is a classic lemma. Elegant, but the proof is harder to give on the spot, and naive substring search can be O(n²).

### 3. KMP Prefix Function: O(n) time, O(n) space
Compute `lps`. The smallest period is `p = n − lps[n−1]`. Periodic iff `lps[n−1] > 0` and `n % p == 0`. The guaranteed linear version.

## Dry Run (Approach 3, KMP)
`"abab"`

| i | char | lps[i] |
|---|------|--------|
| 0 | a | 0 |
| 1 | b | 0 |
| 2 | a | 1 |
| 3 | b | 2 |

lps[3] = 2 > 0, p = 4 − 2 = 2, and 4 % 2 == 0 → **true**. For `"aba"`: lps = [0,0,1], p = 2, 3 % 2 ≠ 0 → false.

## Edge Case Check
- n = 1 → false (no proper divisor). ✅
- All same letters `"aaaa"` → true (len 1). ✅
- `"abac"` → lps[3] = 0 → false. ✅

## ⚠️ Pitfalls
- **Including len = n** in the divisor loop makes every string "true".
- **Doubled string without trimming:** s is always found at offset 0. You must drop the first and last characters.
- **KMP with lps[n−1] = 0:** then p = n and n % n == 0. Check lps > 0 too.

## 🎯 What the Interviewer Wants
- The divisor observation and a clean check.
- Awareness of the s+s trick and the KMP period formula.
- Complexity: why few lengths need testing.

## Follow-ups
- **Prefix function in general:** [LC 0028 Find the Index of the First Occurrence in a String](../0028-find-the-index-of-the-first-occurrence-in-a-string/)
- **Same prefix function, palindrome twist:** [LC 0214 Shortest Palindrome](../0214-shortest-palindrome/)
- **Smallest period of any string:** n − lps[n−1], even when it doesn't divide n.
