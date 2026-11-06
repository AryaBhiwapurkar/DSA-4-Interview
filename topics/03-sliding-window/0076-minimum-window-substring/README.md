---
number: 76
title: Minimum Window Substring
difficulty: Hard
topic: Sliding Window
pattern: Variable window + need/have counts
link: https://leetcode.com/problems/minimum-window-substring/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0567 Permutation in String", "0209 Minimum Size Subarray Sum", "0438 Find All Anagrams in a String", "0030 Substring with Concatenation of All Words"]
---

# 0076. Minimum Window Substring

## ⚡ 30-Second Summary
**Pattern:** Variable window, "shortest valid" flavour, with a satisfied-counter
**Key insight:** Track how many distinct characters of t are currently covered with enough copies (`have` vs `need`). Expand r until `have == need`, then shrink l while still valid, recording the smallest window. Each index enters and leaves once.
**Go-to:** Sliding window with counts, O(|s| + |t|) time, O(alphabet) space

## Problem
Given strings s and t, return the shortest substring of s that contains every character of t (with multiplicity). Return "" if none exists; the answer is unique when it exists. [LeetCode](https://leetcode.com/problems/minimum-window-substring/)

**Examples:**
```
Input:  s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Why:    It's the shortest window containing an A, a B, and a C.

Input:  s = "a", t = "a"
Output: "a"
Why:    The whole string.

Input:  s = "a", t = "aa"
Output: ""
Why:    t needs two a's; s has only one.
```

**Constraints:**
- 1 ≤ |s|, |t| ≤ 10⁵; upper- and lowercase letters (use a 128 array or hashmap).
- Follow-up: O(m + n) time.

## Hints
<details><summary>Hint 1</summary>
If a window is valid, extending it keeps it valid. So for each right edge, you want the largest valid left edge.
</details>
<details><summary>Hint 2</summary>
Comparing full count arrays on every step is slow. Can you track how many required characters are already satisfied?
</details>
<details><summary>Hint 3</summary>
need = number of distinct chars in t. When window[c] reaches tCount[c], have++. While have == need, record the window, then remove s[l]; if that drops window[s[l]] below tCount, have--.
</details>

## Clarifying Questions
- Case-sensitive? (Yes.)
- Duplicates in t must be matched with multiplicity? (Yes.)
- If several minimum windows exist? (Guaranteed unique here; otherwise return any/first.)

## Example Walkthrough
`s = "ADOBECODEBANC", t = "ABC"`
- Expand to "ADOBEC" (first time all three covered) → record 6. Shrinking drops A → invalid.
- Expand to index 10 (the second A): valid again; shrinking stops at "CODEBA" (length 6, not better), then dropping C breaks it.
- Expand to index 12 (the last C): valid again; shrink to "BANC" → record 4.

## Approaches

### 1. Brute Force: O(|s|²·σ) time, O(σ) space
Check every substring's counts against t.

### 2. Sliding Window, Compare Full Counts: O(σ·|s|) time, O(σ) space
Same expand/shrink, but check validity by comparing all σ counts each step. Fine for small alphabets.

### 3. Sliding Window With have/need ⭐ Go-to: O(|s| + |t|) time, O(σ) space
Maintain `have` (satisfied distinct chars); validity is `have == need` in O(1).
**Why it's the go-to:** it's the optimal answer to the follow-up and the general template for "shortest window covering a multiset".

## Dry Run (Approach 3)
`s = "ADOBECODEBANC", t = "ABC"` (need = 3), key moments only

| r | s[r] | have | action | best |
|---|------|------|--------|------|
| 0 | A | 1 | | - |
| 3 | B | 2 | | - |
| 5 | C | 3 | valid [0,5] "ADOBEC" (6); drop A → have 2, l=1 | ADOBEC |
| 10 | A | 3 | valid [1,10]; shrink l to 5 ("CODEBA", 6); drop C → have 2, l=6 | ADOBEC |
| 12 | C | 3 | valid [6,12]; shrink l to 9 ("BANC", 4); drop B → have 2 | BANC |

## Edge Case Check
- |t| > |s|: never valid, "". ✅
- t has duplicates, `t = "aa"`: need counts, not just presence. ✅
- s == t: whole string. ✅

## ⚠️ Pitfalls
- **Incrementing `have` on every matching char** instead of only when the count *reaches* the requirement.
- **Decrementing `have` only when the count drops *below* the requirement**, not on every removal of a needed char.
- **Storing the substring on every update** costs O(n) each; store (start, length) and slice once at the end.
- **Case:** 'A' and 'a' are different; use a 128 array, not 26.

## 🎯 What the Interviewer Wants
- Expand-then-shrink with a clear validity invariant.
- O(1) validity check via have/need.
- Clean index bookkeeping and the empty-result case.

## Follow-ups
- **Fixed-size window, exact multiset:** [LC 0567 Permutation in String](../0567-permutation-in-string/)
- **Numeric version (sum ≥ target):** [LC 0209 Minimum Size Subarray Sum](../0209-minimum-size-subarray-sum/)
- **Window must be made of whole words:** [LC 0030 Substring with Concatenation of All Words](../0030-substring-with-concatenation-of-all-words/)
- **t's characters must appear in order (subsequence):** LC 0727 Minimum Window Subsequence (not added yet)
