---
number: 209
title: Minimum Size Subarray Sum
difficulty: Medium
topic: Sliding Window
pattern: Variable window, shrink while valid
link: https://leetcode.com/problems/minimum-size-subarray-sum/
lists: [LC Top Interview 150]
followup_of: []
related: ["0076 Minimum Window Substring", "0862 Shortest Subarray with Sum at Least K", "0560 Subarray Sum Equals K"]
---

# 0209. Minimum Size Subarray Sum

## ⚡ 30-Second Summary
**Pattern:** Variable window for a "shortest valid" answer
**Key insight:** All numbers are positive, so growing the window only increases the sum and shrinking only decreases it. Extend r until sum ≥ target, then shrink l as far as possible while still valid, recording the length each time.
**Go-to:** Sliding window, O(n) time, O(1) space

## Problem
Given positive integers and a target, return the length of the shortest contiguous subarray whose sum is at least target, or 0 if there is none.

**Examples:**
```
Input:  target = 7, nums = [2,3,1,2,4,3]
Output: 2
Why:    [4,3] sums to 7; no single element reaches 7.

Input:  target = 4, nums = [1,4,4]
Output: 1
Why:    [4] alone reaches 4.

Input:  target = 11, nums = [1,1,1,1,1,1,1,1]
Output: 0
Why:    The whole array only sums to 8.
```

**Constraints:**
- 1 ≤ target ≤ 10⁹; 1 ≤ n ≤ 10⁵; 1 ≤ nums[i] ≤ 10⁴ (all positive, which is what makes the window valid).
- Sums reach at most 10⁹, so 32-bit is fine.
- Follow-up: an O(n log n) solution too.

## Hints
<details><summary>Hint 1</summary>
Because every number is positive, what happens to the sum when you add or drop an element?
</details>
<details><summary>Hint 2</summary>
Once a window is valid, there's no point making it longer; try making it shorter.
</details>
<details><summary>Hint 3</summary>
Add nums[r]; while sum ≥ target, record r - l + 1, subtract nums[l], l++.
</details>

## Clarifying Questions
- Are all numbers positive? (Yes. With negatives, the window doesn't work.)
- "At least" target, or exactly? (At least.)
- Return 0 if impossible? (Yes.)

## Example Walkthrough
`target = 7, nums = [2,3,1,2,4,3]`
- Grow to [2,3,1,2] = 8 ≥ 7 → length 4; drop 2 → 6, stop.
- Add 4 → [3,1,2,4] = 10 → length 4; drop 3 → 7, length 3; drop 1 → 6, stop.
- Add 3 → [2,4,3] = 9 → length 3; drop 2 → 7, length 2; drop 4 → 3, stop. Answer 2.

## Approaches

### 1. Brute Force: O(n²) time, O(1) space
For each start, extend until the sum reaches target.

### 2. Prefix Sums + Binary Search: O(n log n) time, O(n) space
Prefix sums are strictly increasing (positives), so for each i binary search the first j with `P[j] - P[i] ≥ target`. This is the follow-up.

### 3. Sliding Window ⭐ Go-to: O(n) time, O(1) space
Grow r, shrink l while valid, record the minimum.
**Why it's the go-to:** linear, constant space, and it's the template for every "shortest window satisfying X" question.

## Dry Run (Approach 3)
`target = 7, nums = [2,3,1,2,4,3]`

| r | nums[r] | sum after add | shrink steps (length recorded) | l after | best |
|---|---------|---------------|--------------------------------|---------|------|
| 0 | 2 | 2 | - | 0 | ∞ |
| 1 | 3 | 5 | - | 0 | ∞ |
| 2 | 1 | 6 | - | 0 | ∞ |
| 3 | 2 | 8 | 4 | 1 | 4 |
| 4 | 4 | 10 | 4, 3 | 3 | 3 |
| 5 | 3 | 9 | 3, 2 | 5 | 2 |

## Edge Case Check
- No valid window: best stays ∞ → return 0. ✅
- A single element ≥ target: length 1. ✅
- Whole array exactly equals target: length n. ✅

## ⚠️ Pitfalls
- **Using `if` instead of `while` for shrinking** misses shorter windows.
- **Returning the sentinel (∞ / INT_MAX)** instead of 0 when nothing qualifies.
- **Negative numbers break the window** (shrinking could increase the sum); then use prefix sums + monotonic deque (0862).

## 🎯 What the Interviewer Wants
- Explain why positivity makes the window correct.
- Clean grow/shrink loop and the 0 sentinel.
- Mention the O(n log n) prefix-sum version for the follow-up.

## Follow-ups
- **Negatives allowed, sum ≥ k:** prefix sums + monotonic deque: LC 0862 Shortest Subarray with Sum at Least K (not added yet)
- **Count subarrays with sum exactly k (negatives allowed):** prefix sums + hashmap: LC 0560 Subarray Sum Equals K (not added yet)
- **Shortest window covering characters:** [LC 0076 Minimum Window Substring](../0076-minimum-window-substring/)
