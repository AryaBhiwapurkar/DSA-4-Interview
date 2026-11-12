---
number: 214
title: Shortest Palindrome
difficulty: Hard
topic: Arrays & Hashing
pattern: Longest palindromic prefix via KMP on s + '#' + reverse(s)
link: https://leetcode.com/problems/shortest-palindrome/
lists: [Interview Extras]
followup_of: []
related: ["0028 Find the Index of the First Occurrence in a String", "0459 Repeated Substring Pattern", "0005 Longest Palindromic Substring"]
---

# 0214. Shortest Palindrome

## ⚡ 30-Second Summary
**Pattern:** Find the longest prefix that's already a palindrome, then mirror the rest in front
**Key insight:** If `s[:k]` is the longest palindromic prefix, the answer is `reverse(s[k:]) + s`. A palindromic prefix of s is a prefix that equals a suffix of `rev(s)`. Build `t = s + "#" + rev(s)` and compute KMP's prefix function. `lps[last]` is exactly k. The `#` keeps the match from spilling across the two halves.
**Go-to:** KMP prefix function, O(n) time, O(n) space

## Problem
You may only add characters to the **front** of a string. Return the shortest palindrome you can make this way. [LeetCode](https://leetcode.com/problems/shortest-palindrome/)

**Examples:**
```
Input:  s = "aacecaaa"
Output: "aaacecaaa"
Why:    "aacecaa" is already a palindrome; mirror the leftover "a" in front.

Input:  s = "abcd"
Output: "dcbabcd"
Why:    Only "a" is a palindromic prefix, so "dcb" has to go in front.
```

**Constraints:**
- 0 ≤ n ≤ 5·10⁴, lowercase letters, so O(n²) on adversarial input like "aaa…ab" is too slow.

## Hints
<details><summary>Hint 1</summary>
Whatever you add in front must mirror some suffix of s. Which part of s can you leave alone?
</details>
<details><summary>Hint 2</summary>
The part you keep is the longest prefix of s that's a palindrome. How do you find it quickly?
</details>
<details><summary>Hint 3</summary>
A palindromic prefix of s equals a suffix of reverse(s). Compute the KMP prefix function of s + "#" + reverse(s); its last value k is the length of the longest palindromic prefix. Answer = reverse(s[k:]) + s.
</details>

## Clarifying Questions
- Only add at the front? (Yes.)
- Empty string? (Return "".)
- Character set? (Lowercase, so "#" is a safe separator.)

## Example Walkthrough
`s = "abcd"`. t = "abcd#dcba". The prefix function ends at 1 (the final "a" matches the first "a"), so k = 1. reverse("bcd") = "dcb" → "dcb" + "abcd" = **"dcbabcd"**.

## Approaches

### 1. Check Prefixes from Longest: O(n²) time, O(n) space
For k = n down to 1, test whether s[:k] is a palindrome; the first hit wins. Fine on random strings, quadratic on "aaa…ab".

### 2. KMP on s + "#" + rev(s) ⭐ Go-to: O(n) time, O(n) space
**Why it's the go-to:** guaranteed linear, and it reuses the standard prefix-function code from 0028.

(Rolling hash also works: compare forward and backward hashes of each prefix. It's O(n), with a tiny collision risk.)

## Dry Run (Approach 2)
`s = "aacecaaa"`, t = "aacecaaa#aaacecaa" (length 17). Last few lps values:

| i | t[i] | lps[i] |
|---|------|--------|
| 9 | a | 1 |
| 10 | a | 2 |
| 11 | a | 2 |
| 12 | c | 3 |
| 13 | e | 4 |
| 14 | c | 5 |
| 15 | a | 6 |
| 16 | a | **7** |

k = 7 ("aacecaa"). reverse(s[7:]) = "a" → **"aaacecaaa"**.

## Edge Case Check
- `""` → `""`. ✅
- Already a palindrome `"aba"` → k = n → unchanged. ✅
- `"aaaab"`-style input → k = 4, so prepend "b" in O(n). ✅

## ⚠️ Pitfalls
- **No separator:** for `"aaa"`, t = "aaaaaa" gives lps = 5 > n. The `#` caps the match at n.
- **Prepending the wrong part:** it's reverse(s[k:]), not reverse(s[:k]).
- **Assuming you can add at both ends:** that's a different problem.

## 🎯 What the Interviewer Wants
- The reduction to "longest palindromic prefix".
- A linear method (KMP or rolling hash), with the separator explained.
- Mention the O(n²) baseline and why it fails.

## Follow-ups
- **The prefix function itself:** [LC 0028 Find the Index of the First Occurrence in a String](../0028-find-the-index-of-the-first-occurrence-in-a-string/)
- **Periodicity from the same lps array:** [LC 0459 Repeated Substring Pattern](../0459-repeated-substring-pattern/)
- **Longest palindrome anywhere:** [LC 0005 Longest Palindromic Substring](../../13-1d-dp/0005-longest-palindromic-substring/)
