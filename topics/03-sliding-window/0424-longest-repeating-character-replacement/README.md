---
number: 424
title: Longest Repeating Character Replacement
difficulty: Medium
topic: Sliding Window
pattern: Variable window + max frequency
link: https://leetcode.com/problems/longest-repeating-character-replacement/
lists: [NeetCode 150]
followup_of: []
related: ["0003 Longest Substring Without Repeating Characters", "1004 Max Consecutive Ones III", "2024 Maximize the Confusion of an Exam"]
---

# 0424. Longest Repeating Character Replacement

## ⚡ 30-Second Summary
**Pattern:** Variable window with "window length - max frequency ≤ k"
**Key insight:** A window can be made all one letter with `len - maxFreq` replacements (change everything except the most common letter). Keep the window valid under that rule. maxFreq never needs to decrease, because only a larger maxFreq can produce a longer answer.
**Go-to:** Window + counts + non-decreasing maxFreq, O(n) time, O(26) space

## Problem
Given an uppercase string and an integer k, you may change at most k characters to any other uppercase letter. Return the length of the longest substring that can be made of a single repeated letter. [LeetCode](https://leetcode.com/problems/longest-repeating-character-replacement/)

**Examples:**
```
Input:  s = "ABAB", k = 2
Output: 4
Why:    Change both A's to B (or both B's to A): "BBBB".

Input:  s = "AABABBA", k = 1
Output: 4
Why:    Change the A at index 3 to B: "AABBBBA" contains "BBBB".
```

**Constraints:**
- 1 ≤ |s| ≤ 10⁵; uppercase English letters only (26 counters).
- 0 ≤ k ≤ |s|.

## Hints
<details><summary>Hint 1</summary>
For a fixed window, how many replacements are needed to make it one letter?
</details>
<details><summary>Hint 2</summary>
It's window length minus the count of its most frequent letter. When is the window invalid?
</details>
<details><summary>Hint 3</summary>
Grow r, update counts and maxFreq; if len - maxFreq > k, slide l right by one (decrementing its count). You don't need to recompute maxFreq when shrinking.
</details>

## Clarifying Questions
- Only uppercase letters? (Yes.)
- Is k the maximum number of changes (can use fewer)? (Yes.)
- Return the length only? (Yes.)

## Example Walkthrough
`s = "AABABBA", k = 1`
- Window "AABA": maxFreq 3 (A), len 4, needs 1 change ✓ → 4.
- Adding B gives "AABAB": 5 - 3 = 2 > 1, so slide l by one. The window keeps length 4 from here on.
- Later windows ("BABB", "ABBA") also need 1 change, but no window of length 5 ever needs ≤ 1. Answer 4.

## Approaches

### 1. Brute Force: O(n²) time, O(26) space
For each start, extend while `len - maxFreq ≤ k`, tracking counts.

### 2. Per-Letter Window: O(26·n) time, O(1) space
For each target letter c, find the longest window with at most k non-c characters (classic "at most k zeros" window). Easy to prove correct.

### 3. Window + Max Frequency ⭐ Go-to: O(n) time, O(26) space
`count[s[r]]++; maxf = max(maxf, count[s[r]])`; if `(r - l + 1) - maxf > k`, decrement `count[s[l]]` and l++. Answer = largest window seen (equivalently n - l at the end).
**Why it's the go-to:** single pass. The stale-maxf trick is the key point: the window never shrinks below the best size so far, it just slides.

## Dry Run (Approach 3)
`s = "AABABBA", k = 1`

| r | s[r] | counts (A,B) | maxf | len | len - maxf > k? | l after | best |
|---|------|--------------|------|-----|-----------------|---------|------|
| 0 | A | 1,0 | 1 | 1 | no | 0 | 1 |
| 1 | A | 2,0 | 2 | 2 | no | 0 | 2 |
| 2 | B | 2,1 | 2 | 3 | no | 0 | 3 |
| 3 | A | 3,1 | 3 | 4 | no | 0 | 4 |
| 4 | B | 3,2 | 3 | 5 | yes → drop A | 1 | 4 |
| 5 | B | 2,3 | 3 | 5 | yes → drop A | 2 | 4 |
| 6 | A | 2,3 | 3 | 5 | yes → drop B | 3 | 4 |

## Edge Case Check
- k = 0: longest run of one letter. ✅
- k ≥ |s|: the whole string. ✅
- Single character: 1. ✅

## ⚠️ Pitfalls
- **Recomputing maxf exactly on shrink** is unnecessary (and costs 26 per step); a stale, too-high maxf only keeps the window from shrinking, which never loses the best answer.
- **Using `while` vs `if` to shrink:** with the stale-maxf version, one step is enough since the window only ever grows by one.
- **Index with `c - 'A'`**, not `'a'`.

## 🎯 What the Interviewer Wants
- The validity condition `len - maxFreq ≤ k`.
- A correct explanation of why maxFreq can stay stale.
- Per-letter approach as a safe fallback if you can't justify the trick.

## Follow-ups
- **Binary array, flip at most k zeros:** same window: LC 1004 Max Consecutive Ones III (not added yet)
- **Two letters (T/F), at most k flips:** LC 2024 Maximize the Confusion of an Exam (not added yet)
- **No replacements, all distinct:** [LC 0003](../0003-longest-substring-without-repeating-characters/)
