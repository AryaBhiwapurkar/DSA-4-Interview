---
number: 340
title: Longest Substring with At Most K Distinct Characters
difficulty: Medium
topic: Sliding Window
pattern: Variable window + character counts
link: https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/
lists: [Interview Extras]
followup_of: ["0003 Longest Substring Without Repeating Characters"]
related: ["0904 Fruit Into Baskets", "0159 Longest Substring with At Most Two Distinct Characters", "0992 Subarrays with K Different Integers"]
---

# 0340. Longest Substring with At Most K Distinct Characters

## ⚡ 30-Second Summary
**Pattern:** Longest window whose count map has at most k keys
**Key insight:** Add s[r] to a count map. While the map has more than k distinct keys, decrement s[l] and erase it when it hits 0, then move l forward. After that the window is valid, so record its length. Erasing zero-count keys is what keeps "number of keys" equal to "number of distinct characters".
**Go-to:** Shrinking window + hashmap, O(n) time, O(k) space

## Problem
Return the length of the longest substring of s that contains at most k distinct characters. LeetCode Premium. [LeetCode](https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/)

**Examples:**
```
Input:  s = "eceba", k = 2
Output: 3
Why:    "ece" uses only e and c.

Input:  s = "aa", k = 1
Output: 2
Why:    The whole string is one distinct letter.
```

**Constraints:**
- 1 ≤ n ≤ 5·10⁴; 0 ≤ k ≤ 50; any ASCII characters.

## Hints
<details><summary>Hint 1</summary>
Is a substring with ≤ k distinct characters still valid after you remove its first character?
</details>
<details><summary>Hint 2</summary>
So you can grow from the right and shrink from the left. What do you need to track to know the number of distinct characters?
</details>
<details><summary>Hint 3</summary>
cnt[s[r]]++. While len(cnt) &gt; k: cnt[s[l]]−−, erase it at 0, l++. best = max(best, r − l + 1).
</details>

## Clarifying Questions
- k = 0? (Answer 0.)
- Character set? (Any ASCII; use a map or a 128-slot array plus a distinct counter.)
- Length only? (Yes.)

## Example Walkthrough
`"eceba", k = 2`. Windows: "e", "ec", "ece" (len 3). Adding 'b' makes 3 distinct, so shrink: drop e (cnt e = 1), drop c (c gone) → "eb". Adding 'a' makes 3 distinct again, so drop e → "ba". Best = 3.

## Approaches

### 1. Every Start, Extend: O(n²) time, O(k) space
Extend from each l until a (k+1)-th distinct character appears.

### 2. Shrinking Window + Map ⭐ Go-to: O(n) time, O(k) space
**Why it's the go-to:** the standard "at most K of something" window, and it doubles as the `atMost` helper for "exactly K" counting (0992).

(Follow-up for a stream: keep the last index of each char in an ordered map, LRU-style, and jump l past the smallest last index when you overflow.)

## Dry Run (Approach 2)
`"eceba", k = 2`

| r | char | counts after add | shrink | l | len | best |
|---|------|------------------|--------|---|-----|------|
| 0 | e | {e:1} | | 0 | 1 | 1 |
| 1 | c | {e:1,c:1} | | 0 | 2 | 2 |
| 2 | e | {e:2,c:1} | | 0 | 3 | 3 |
| 3 | b | {e:2,c:1,b:1} | drop e, c | 2 | 2 | 3 |
| 4 | a | {e:1,b:1,a:1} | drop e | 3 | 2 | **3** |

## Edge Case Check
- k = 0 → 0 (every char forces a full shrink). ✅
- k ≥ distinct letters in s → n. ✅
- Single character → 1 if k ≥ 1. ✅

## ⚠️ Pitfalls
- **Not erasing zero counts:** the map size stops matching the distinct count.
- **Recording before shrinking:** you'd record an invalid window.
- **Fixed 26-letter array:** the input may contain any ASCII, so use 128 slots or a map.

## 🎯 What the Interviewer Wants
- The at-most-K window template, cleanly.
- Correct distinct-count bookkeeping.
- Optional: the streaming / LRU follow-up.

## Follow-ups
- **k = 2 on integers:** [LC 0904 Fruit Into Baskets](../0904-fruit-into-baskets/)
- **Exactly k distinct (count):** [LC 0992 Subarrays with K Different Integers](../0992-subarrays-with-k-different-integers/)
- **No repeats at all:** [LC 0003 Longest Substring Without Repeating Characters](../0003-longest-substring-without-repeating-characters/)
