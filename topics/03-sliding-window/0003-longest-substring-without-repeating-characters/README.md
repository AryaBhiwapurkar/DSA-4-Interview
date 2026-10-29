---
number: 3
title: Longest Substring Without Repeating Characters
difficulty: Medium
topic: Sliding Window
pattern: Variable window + set / last-seen map
link: https://leetcode.com/problems/longest-substring-without-repeating-characters/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0159 Longest Substring with At Most Two Distinct Characters", "0340 Longest Substring with At Most K Distinct Characters", "0424 Longest Repeating Character Replacement", "0076 Minimum Window Substring"]
---

# 0003. Longest Substring Without Repeating Characters

## ⚡ 30-Second Summary
**Pattern:** Variable-size sliding window
**Key insight:** Keep a window [l, r] with no repeated characters. Extend r; if s[r] is already inside, shrink from the left until it isn't. The window is always valid, so its largest size is the answer.
**Go-to:** Window + set, O(n) time, O(min(n, alphabet)) space

## Problem
Given a string, return the length of the longest substring (contiguous) that contains no repeated characters.

**Examples:**
```
Input:  s = "abcabcbb"
Output: 3
Why:    "abc" is the longest run with all-distinct characters.

Input:  s = "bbbbb"
Output: 1
Why:    Any longer substring repeats 'b'.

Input:  s = "pwwkew"
Output: 3
Why:    "wke"; note "pwke" is a subsequence, not a substring.
```

**Constraints:**
- 0 ≤ |s| ≤ 5·10⁴ (empty string → 0).
- Letters, digits, symbols, and spaces (ASCII), so a 128-slot array also works.

## Hints
<details><summary>Hint 1</summary>
Checking every substring is O(n²) or worse. When you extend a valid window by one character, what can go wrong?
</details>
<details><summary>Hint 2</summary>
If the new character already appears in the window, which characters must leave?
</details>
<details><summary>Hint 3</summary>
Move l forward (removing chars from a set) until s[r] is no longer in the window, then add s[r] and record r - l + 1.
</details>

## Clarifying Questions
- Substring (contiguous) or subsequence? (Substring.)
- Character set? Case-sensitive? Spaces count? (ASCII, case-sensitive, spaces count.)
- Empty string? (Return 0.)

## Example Walkthrough
`s = "pwwkew"`
- [p], [p,w] (2). Next w repeats: drop p, drop w → [w]. Add k → [w,k], add e → [w,k,e] (3).
- Next w repeats: drop w → [k,e,w] (3). Best 3.

## Approaches

### 1. Brute Force: O(n²) time, O(alphabet) space
For each start, extend while characters stay unique (fresh set per start).

### 2. Window + Set ⭐ Go-to: O(n) time, O(min(n, alphabet)) space
Extend r; while s[r] is in the set, remove s[l] and l++; add s[r]; update best.
**Why it's the go-to:** it's the canonical variable-window template (grow right, shrink left while invalid), easy to explain and hard to get wrong.

### 3. Window + Last-Seen Index: O(n) time, O(alphabet) space
Store each char's last index; on a repeat, jump `l = max(l, last[c] + 1)` in one step. Single pass, slightly trickier (the `max` matters).

## Dry Run (Approach 2)
`s = "abcabcbb"`

| r | s[r] | removed while shrinking | window | best |
|---|------|-------------------------|--------|------|
| 0 | a | - | a | 1 |
| 1 | b | - | ab | 2 |
| 2 | c | - | abc | 3 |
| 3 | a | a | bca | 3 |
| 4 | b | b | cab | 3 |
| 5 | c | c | abc | 3 |
| 6 | b | a, b | cb | 3 |
| 7 | b | c, b | b | 3 |

## Edge Case Check
- Empty string: loop doesn't run, 0. ✅
- All the same char: window size stays 1. ✅
- All distinct: window grows to n. ✅
- Spaces and symbols: just more characters. ✅

## ⚠️ Pitfalls
- **Last-seen jump without `max`:** `l = last[c] + 1` can move l backwards (e.g. "abba"); use `max(l, last[c] + 1)`.
- **Recording best before shrinking** counts an invalid window.
- **C++ `char` as array index:** use a 128/256 array with `(unsigned char)`.

## 🎯 What the Interviewer Wants
- The variable window template, with a crisp invariant ("window has no repeats").
- O(n) argument: each index enters and leaves the window at most once.
- Bonus: the last-index jump and the "abba" trap.

## Follow-ups
- **At most two / k distinct characters:** same window, track counts per char: LC 0159 / LC 0340 (not added yet)
- **Allow up to k replacements:** [LC 0424 Longest Repeating Character Replacement](../0424-longest-repeating-character-replacement/)
- **Shortest window covering a pattern:** [LC 0076 Minimum Window Substring](../0076-minimum-window-substring/)
