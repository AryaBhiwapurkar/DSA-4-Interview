---
number: 890
title: Find and Replace Pattern
difficulty: Medium
topic: Arrays & Hashing
pattern: Bijection check (two maps) / first-occurrence signature
link: https://leetcode.com/problems/find-and-replace-pattern/
lists: [Interview Extras]
followup_of: ["0205 Isomorphic Strings"]
related: ["0205 Isomorphic Strings", "0290 Word Pattern", "0249 Group Shifted Strings"]
---

# 0890. Find and Replace Pattern

## ⚡ 30-Second Summary
**Pattern:** Isomorphic-strings check, applied to each word
**Key insight:** A word matches when there's a **one-to-one** letter mapping between it and the pattern. Check with two maps (pattern→word and word→pattern), or give both a signature built from the index of each letter's first occurrence ("abb" → [0,1,1]) and compare.
**Go-to:** Two-map bijection check per word, O(total characters) time, O(1) space per word (26 letters)

## Problem
Return every word that matches the pattern, meaning some permutation of the alphabet turns the pattern into that word. Each pattern letter maps to exactly one letter, and no two pattern letters map to the same one. [LeetCode](https://leetcode.com/problems/find-and-replace-pattern/)

**Examples:**
```
Input:  words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
Output: ["mee","aqq"]
Why:    "abb" needs letter1, then letter2 twice, with letter1 ≠ letter2. "ccc" fails (two pattern letters → c).

Input:  words = ["a","b","c"], pattern = "a"
Output: ["a","b","c"]
Why:    Any single letter matches a one-letter pattern.
```

**Constraints:**
- 1 ≤ pattern length ≤ 20; up to 50 words, each the same length as the pattern; lowercase letters.

## Hints
<details><summary>Hint 1</summary>
This is the isomorphic-strings check. What two things can go wrong with a letter mapping?
</details>
<details><summary>Hint 2</summary>
One pattern letter can't map to two different word letters, and two pattern letters can't share one word letter. How do you catch both?
</details>
<details><summary>Hint 3</summary>
For each word, keep p2w and w2p. For every position: if p2w[p] is set and ≠ w, fail; if w2p[w] is set and ≠ p, fail; otherwise set both. Keep the words that never fail.
</details>

## Clarifying Questions
- Same length guaranteed? (Yes.)
- Must the mapping be one-to-one? (Yes, a bijection.)
- Output order? (Any; keep the input order to be safe.)

## Example Walkthrough
"dkd" vs "abb": a→d, b→k, then b→d? b is already mapped to k, so it fails. "ccc": a→c, then b→c, but c is already the image of a (w2p[c] = a), so it fails.

## Approaches

### 1. Two-map Bijection ⭐ Go-to: O(N) time, O(1) space per word
**Why it's the go-to:** reuses 0205/0290 directly; both failure modes are explicit.

### 2. First-occurrence Signature: O(N) time, O(L) space
Map each string to a list of "index of this letter's first occurrence" and keep the words whose list equals the pattern's. Neat, and it doubles as a grouping key.

## Dry Run (Approach 1)
pattern "abb", word "mee"

| i | p | w | p2w | w2p | ok? |
|---|---|---|-----|-----|-----|
| 0 | a | m | {a:m} | {m:a} | ✓ |
| 1 | b | e | {a:m, b:e} | {m:a, e:b} | ✓ |
| 2 | b | e | same | same | ✓ |

**Match.**

## Edge Case Check
- One-letter pattern → every word matches. ✅
- Pattern with all-distinct letters → only words with all-distinct letters match. ✅
- Word with all-equal letters vs a pattern with distinct letters → w2p catches it. ✅

## ⚠️ Pitfalls
- **Only one map:** misses "ccc" vs "abb" (many-to-one).
- **Python `dict.setdefault` tricks** that check one direction only.
- **Signature as a joined string without separators**: indices ≥ 10 can collide ("1,11" vs "11,1"). Use lists or tuples.

## 🎯 What the Interviewer Wants
- Recognise isomorphism and enforce a bijection.
- Clean per-word check in linear total time.

## Follow-ups
- **Same check on two strings:** [LC 0205 Isomorphic Strings](../0205-isomorphic-strings/)
- **Pattern vs words of a sentence:** [LC 0290 Word Pattern](../0290-word-pattern/)
- **Group by shift instead:** [LC 0249 Group Shifted Strings](../0249-group-shifted-strings/)
