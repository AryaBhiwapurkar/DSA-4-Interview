---
number: 992
title: Subarrays with K Different Integers
difficulty: Hard
topic: Sliding Window
pattern: exactly(k) = atMost(k) − atMost(k − 1)
link: https://leetcode.com/problems/subarrays-with-k-different-integers/
lists: [Interview Extras]
followup_of: ["0340 Longest Substring with At Most K Distinct Characters"]
related: ["0340 Longest Substring with At Most K Distinct Characters", "0713 Subarray Product Less Than K", "1248 Count Number of Nice Subarrays", "0930 Binary Subarrays With Sum"]
---

# 0992. Subarrays with K Different Integers

## ⚡ 30-Second Summary
**Pattern:** Count "at most k" with a window, then subtract
**Key insight:** "Exactly k distinct" isn't monotone: shrinking can drop below k, and growing can go above it. "At most k" is monotone, so a window counts it directly by adding `r − l + 1` subarrays ending at each r. Every subarray with exactly k distinct values is counted by atMost(k) but not by atMost(k−1), so the answer is their difference.
**Go-to:** Two at-most windows, O(n) time, O(n) space

## Problem
Count the contiguous subarrays that contain exactly k different integers. [LeetCode](https://leetcode.com/problems/subarrays-with-k-different-integers/)

**Examples:**
```
Input:  nums = [1,2,1,2,3], k = 2
Output: 7
Why:    [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2] each have exactly two distinct values.

Input:  nums = [1,2,1,3,4], k = 3
Output: 3
Why:    [1,2,1,3], [2,1,3], [1,3,4].
```

**Constraints:**
- 1 ≤ n ≤ 2·10⁴; 1 ≤ nums[i], k ≤ n, so a count array of size n + 1 works.

## Hints
<details><summary>Hint 1</summary>
Why doesn't a single shrinking window count "exactly k" subarrays correctly?
</details>
<details><summary>Hint 2</summary>
Counting subarrays with at most k distinct values is easy with a window. How do "exactly" and "at most" relate?
</details>
<details><summary>Hint 3</summary>
atMost(k): standard window; for each r, shrink while distinct &gt; k, then add r − l + 1. Answer = atMost(k) − atMost(k − 1).
</details>

## Clarifying Questions
- Contiguous subarrays? (Yes.)
- Value range? (1..n, so an array can replace the hashmap.)
- Can the count be large? (Up to about n²/2 = 2·10⁸, which fits in an int.)

## Example Walkthrough
`[1,2,1,2,3], k = 2`. atMost(2) = 1+2+3+4+2 = 12, because at r = 4 the window shrinks to [2,3]. atMost(1) = 5 (every single element). 12 − 5 = 7. ✓

## Approaches

### 1. All Subarrays with a Set: O(n²) time, O(n) space
Extend from every start, track distinct values, count when exactly k, and stop once it passes k.

### 2. atMost(k) − atMost(k−1) ⭐ Go-to: O(n) time, O(n) space
**Why it's the go-to:** two calls to one simple helper. The same trick solves "exactly k odd numbers" (1248) and "sum exactly goal" on binary arrays (930).

(A one-pass "three pointers" version keeps two left boundaries at once. Same complexity, harder to explain.)

## Dry Run (Approach 2)
atMost(2) on `[1,2,1,2,3]`

| r | value | distinct | l after shrink | + (r − l + 1) | total |
|---|-------|----------|----------------|---------------|-------|
| 0 | 1 | 1 | 0 | 1 | 1 |
| 1 | 2 | 2 | 0 | 2 | 3 |
| 2 | 1 | 2 | 0 | 3 | 6 |
| 3 | 2 | 2 | 0 | 4 | 10 |
| 4 | 3 | 3 → 2 | 3 | 2 | 12 |

atMost(1) = 5 → **12 − 5 = 7**.

## Edge Case Check
- k = 1 → atMost(0) = 0, so the result is the number of subarrays with one distinct value. ✅
- k > number of distinct values in nums → atMost(k) == atMost(k − 1) → 0. ✅
- All equal, k = 1 → n(n+1)/2. ✅

## ⚠️ Pitfalls
- **A single "exactly k" window:** it misses subarrays because the valid left boundaries for each r form a range, not one point.
- **atMost(0):** must return 0. The window shrinks to empty every time, adding r − (r+1) + 1 = 0.
- **Not decrementing the distinct count** when a value's count falls to 0.

## 🎯 What the Interviewer Wants
- Explain why exactly-k isn't window-friendly.
- The subtraction trick, plus a correct atMost helper.
- O(n) overall.

## Follow-ups
- **The at-most window itself:** [LC 0340 Longest Substring with At Most K Distinct Characters](../0340-longest-substring-with-at-most-k-distinct-characters/)
- **Same trick, odd counts:** LC 1248 Count Number of Nice Subarrays (not added yet)
- **Same trick, binary sums:** LC 0930 Binary Subarrays With Sum (not added yet)
