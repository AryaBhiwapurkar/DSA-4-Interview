---
number: 1004
title: Max Consecutive Ones III
difficulty: Medium
topic: Sliding Window
pattern: Variable window with at most k "bad" elements
link: https://leetcode.com/problems/max-consecutive-ones-iii/
lists: [Interview Extras]
followup_of: []
related: ["0424 Longest Repeating Character Replacement", "0485 Max Consecutive Ones", "2024 Maximize the Confusion of an Exam"]
---

# 1004. Max Consecutive Ones III

## ⚡ 30-Second Summary
**Pattern:** Longest window containing at most k zeros
**Key insight:** Flipping at most k zeros means finding the longest subarray with ≤ k zeros. Grow r. When the zero count goes above k, move l forward until it's back to k. Record `r − l + 1` after each step. Each index enters and leaves the window once.
**Go-to:** Shrinking window, O(n) time, O(1) space

## Problem
Given a binary array and k, return the longest run of consecutive 1s you can get by flipping at most k zeros to ones. [LeetCode](https://leetcode.com/problems/max-consecutive-ones-iii/)

**Examples:**
```
Input:  nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
Output: 6
Why:    Flip the two zeros at indices 4 and 5 to join them with 1,1,1,1: indices 4..9.

Input:  nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
Output: 10
Why:    Indices 2..11 hold exactly three zeros; flipping them gives 10 ones.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵; 0 ≤ k ≤ n, so O(n²) is too slow.

## Hints
<details><summary>Hint 1</summary>
Rephrase: you don't actually need to flip anything. What does a valid final run look like in the original array?
</details>
<details><summary>Hint 2</summary>
It's a subarray with at most k zeros. Which window technique finds the longest such subarray?
</details>
<details><summary>Hint 3</summary>
zeros += (nums[r] == 0); while zeros &gt; k: zeros −= (nums[l] == 0), l++. best = max(best, r − l + 1).
</details>

## Clarifying Questions
- Can k be 0? (Yes → longest run of existing 1s.)
- Only 0s and 1s? (Yes.)
- Return the length only? (Yes.)

## Example Walkthrough
`[1,0,1,0,1], k = 1`: windows up to r = 2 have one zero → length 3. At r = 3 there are two zeros, so drop index 0 (a 1) and index 1 (a 0) → l = 2, window [2,3]. At r = 4 the window [2,4] has one zero → length 3. Best = 3.

## Approaches

### 1. Every Start, Extend: O(n²) time, O(1) space
For each l, extend r until a (k+1)-th zero appears. Too slow for 10⁵.

### 2. Shrinking Window ⭐ Go-to: O(n) time, O(1) space
**Why it's the go-to:** the textbook "longest window with a budget" template.

(Non-shrinking variant: replace the `while` with an `if`. The window never shrinks, only slides, and its final size is the answer. It's the same trick as 0424.)

## Dry Run (Approach 2)
`[1,1,1,0,0,0,1,1,1,1,0], k = 2` (key steps)

| r | nums[r] | zeros | l after shrink | length | best |
|---|---------|-------|----------------|--------|------|
| 4 | 0 | 2 | 0 | 5 | 5 |
| 5 | 0 | 3 → 2 | 4 | 2 | 5 |
| 9 | 1 | 2 | 4 | 6 | 6 |
| 10 | 0 | 3 → 2 | 5 | 6 | **6** |

## Edge Case Check
- k = 0 → longest run of 1s. ✅
- k ≥ number of zeros → n. ✅
- All zeros with k = 0 → 0. ✅

## ⚠️ Pitfalls
- **Shrinking with `if` but recording `r − l + 1` as if the window were valid** is the 0424 trick. It's only correct when you return the final window size, so don't mix the two styles.
- **Decrementing zeros for every element that leaves:** only when the leaving element is a 0.
- **Counting ones instead of zeros:** the budget is on the zeros.

## 🎯 What the Interviewer Wants
- Reframe "flip k" as "window with ≤ k zeros".
- A clean O(n) sliding window.

## Follow-ups
- **Same budget with letters:** [LC 0424 Longest Repeating Character Replacement](../0424-longest-repeating-character-replacement/)
- **Two symbols, both directions:** LC 2024 Maximize the Confusion of an Exam (not added yet). Run this twice.
- **Exactly one deletion:** LC 1493 Longest Subarray of 1's After Deleting One Element (not added yet). k = 1, answer − 1.
