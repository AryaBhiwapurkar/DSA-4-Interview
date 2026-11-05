---
number: 763
title: Partition Labels
difficulty: Medium
topic: Greedy
pattern: Last occurrence + window end
link: https://leetcode.com/problems/partition-labels/
lists: [NeetCode 150]
followup_of: []
related: ["0056 Merge Intervals", "0055 Jump Game"]
---

# 0763. Partition Labels

## ⚡ 30-Second Summary
**Pattern:** Greedy with a running "must reach" boundary
**Key insight:** Record each letter's last index. Sweep left to right, stretching `end = max(end, last[ch])`: the current piece can't close before every letter in it has appeared for the last time. When `i == end`, cut. Cutting as early as possible maximises the number of pieces.
**Go-to:** Last occurrence + window end, O(n) time, O(1) space (26 letters)

## Problem
Split a lowercase string into as many contiguous pieces as possible such that no letter shows up in more than one piece. Return the lengths of the pieces in order. [LeetCode](https://leetcode.com/problems/partition-labels/)

**Examples:**
```
Input:  s = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Why:    "ababcbaca" holds every a, b and c; "defegde" every d, e, f and g; "hijhklij" the rest.

Input:  s = "eccbbbbdec"
Output: [10]
Why:    The e at both ends forces the whole string into one piece.
```

**Constraints:**
- 1 ≤ n ≤ 500, lowercase letters only.

## Hints
<details><summary>Hint 1</summary>
If a piece contains the letter 'a', where is the earliest it can end?
</details>
<details><summary>Hint 2</summary>
Precompute the last index of each letter. As you extend a piece, how does its required end change?
</details>
<details><summary>Hint 3</summary>
end = max(end, last[s[i]]) for each i; when i == end, record end - start + 1 and set start = i + 1.
</details>

## Clarifying Questions
- Pieces must be contiguous and cover the whole string? (Yes.)
- Lowercase only? (Yes, so a 26-slot array works.)
- Return sizes, not strings? (Sizes.)

## Example Walkthrough
`"abac"`: last = {a: 2, b: 1, c: 3}. i = 0 → end 2; i = 1 → end stays 2; i = 2 → cut, size 3. i = 3 → end 3, cut, size 1. Result [3, 1].

## Approaches

### 1. Merge Letter Intervals: O(n) time, O(1) space
Each letter spans [first, last]. Overlapping spans must share a piece, so merge them (LC 56) and output the merged lengths.

### 2. Last Occurrence ⭐ Go-to: O(n) time, O(1) space
The same merge, done implicitly in one sweep.
**Why it's the go-to:** two short loops, no sorting, and the cut condition `i == end` is easy to justify.

## Dry Run (Approach 2)
`"ababcbacadefegdehijhklij"` (key steps only).

| i | ch | last[ch] | end | action |
|---|----|----------|-----|--------|
| 0 | a | 8 | 8 | |
| 1 | b | 5 | 8 | |
| 4 | c | 7 | 8 | |
| 8 | a | 8 | 8 | cut → **9** |
| 9 | d | 14 | 14 | |
| 10 | e | 15 | 15 | |
| 15 | e | 15 | 15 | cut → **7** |
| 16 | h | 19 | 19 | |
| 17 | i | 22 | 22 | |
| 18 | j | 23 | 23 | |
| 23 | j | 23 | 23 | cut → **8** |

## Edge Case Check
- Single character → [1]. ✅
- All distinct `"abc"` → [1,1,1]. ✅
- First letter repeated at the end → one piece. ✅

## ⚠️ Pitfalls
- **Cutting when a letter's last index is reached**, instead of when the max end is reached, splits letters seen earlier.
- **Forgetting to move `start`** after a cut gives cumulative sizes.
- **Storing first occurrences** in the map instead of last.

## 🎯 What the Interviewer Wants
- The interval view (each letter is an interval), then the one-pass version.
- A short argument for why cutting as early as possible is optimal.
- O(n) time, O(1) space.

## Follow-ups
- **Explicit interval merging:** [LC 0056 Merge Intervals](../../16-intervals/0056-merge-intervals/)
- **Same "extend the reach" sweep:** [LC 0055 Jump Game](../0055-jump-game/)
- **Return the substrings:** slice with the recorded start/end indices.
