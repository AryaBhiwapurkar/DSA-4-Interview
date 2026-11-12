---
number: 907
title: Sum of Subarray Minimums
difficulty: Medium
topic: Stack
pattern: Monotonic stack, contribution counting
link: https://leetcode.com/problems/sum-of-subarray-minimums/
lists: [Interview Extras]
followup_of: []
related: ["0084 Largest Rectangle in Histogram", "2104 Sum of Subarray Ranges", "0496 Next Greater Element I"]
---

# 0907. Sum of Subarray Minimums

## ⚡ 30-Second Summary
**Pattern:** Count, for each element, how many subarrays have it as their minimum
**Key insight:** Flip the sum around: arr[i] contributes `arr[i] · left[i] · right[i]`. Here left[i] is the number of choices for the start (back to the previous **smaller** element) and right[i] the number of choices for the end (up to the next **smaller-or-equal** element). Using strict on one side and non-strict on the other assigns each subarray with repeated minimums to exactly one index. Both arrays come from monotonic stacks.
**Go-to:** Previous-less / next-less-or-equal via stacks, O(n) time, O(n) space

## Problem
Return the sum of min(sub) over every contiguous subarray of arr, modulo 10⁹ + 7. [LeetCode](https://leetcode.com/problems/sum-of-subarray-minimums/)

**Examples:**
```
Input:  arr = [3,1,2,4]
Output: 17
Why:    The 10 subarrays have minimums 3,1,2,4,1,1,2,1,1,1, which add up to 17.

Input:  arr = [11,81,94,43,3]
Output: 444
Why:    Same rule; 3 is the minimum of every subarray that contains it.
```

**Constraints:**
- 1 ≤ n ≤ 3·10⁴; 1 ≤ arr[i] ≤ 3·10⁴, so there are about 4.5·10⁸ subarrays: don't enumerate them.
- The answer is taken modulo 10⁹ + 7; intermediate products need 64-bit.

## Hints
<details><summary>Hint 1</summary>
Instead of looping over subarrays, ask: for a fixed index i, in how many subarrays is arr[i] the minimum?
</details>
<details><summary>Hint 2</summary>
That subarray can stretch left until a smaller value and right until a smaller value. Which structure finds those boundaries for every i?
</details>
<details><summary>Hint 3</summary>
left[i] = i − (index of previous element &lt; arr[i]); right[i] = (index of next element ≤ arr[i]) − i. Answer = Σ arr[i]·left[i]·right[i] mod 1e9+7.
</details>

## Clarifying Questions
- Duplicates? (Yes, so the tie-break matters.)
- Modulo? (10⁹ + 7.)
- n up to? (3·10⁴, so O(n²) is about 9·10⁸: too slow.)

## Example Walkthrough
`[3,1,2,4]`:
- 3: left 1, right 1 (1 is smaller) → 3·1·1 = 3.
- 1: left 2, right 3 → 1·2·3 = 6.
- 2: left 1, right 2 → 2·1·2 = 4.
- 4: left 1, right 1 → 4.

Total 3 + 6 + 4 + 4 = **17**.

## Approaches

### 1. All Subarrays with Running Min: O(n²) time, O(1) space
For each start, extend and track the min. About 4.5·10⁸ steps at the limit: too slow.

### 2. Contribution with Monotonic Stacks ⭐ Go-to: O(n) time, O(n) space
**Why it's the go-to:** the standard "contribution technique". It's the same boundary search as Largest Rectangle in Histogram, and the tie-breaking rule is the one subtle point.

(A one-pass DP also works: dp[i] = dp[prev smaller] + arr[i]·(i − prev). Same stack, different bookkeeping.)

## Dry Run (Approach 2)
`[3,1,2,4]`

| i | arr[i] | prev < (index) | next ≤ (index) | left | right | contribution |
|---|--------|----------------|----------------|------|-------|--------------|
| 0 | 3 | −1 | 1 | 1 | 1 | 3 |
| 1 | 1 | −1 | 4 (none) | 2 | 3 | 6 |
| 2 | 2 | 1 | 4 (none) | 1 | 2 | 4 |
| 3 | 4 | 2 | 4 (none) | 1 | 1 | 4 |

Sum **17**.

## Edge Case Check
- All equal `[2,2,2]` → each subarray counted once thanks to the strict/non-strict split → 2·6 = 12. ✅
- Strictly increasing → each element is the min of the subarrays starting at it. ✅
- n = 1 → arr[0]. ✅

## ⚠️ Pitfalls
- **Strict on both sides** undercounts and **non-strict on both** double-counts subarrays whose minimum appears twice.
- **Overflow:** arr[i] · left · right can reach about 3·10⁴ · (1.5·10⁴)², roughly 7·10¹². Use 64-bit and reduce mod at each add.
- **Missing boundaries:** no previous smaller → index −1; no next smaller → index n.

## 🎯 What the Interviewer Wants
- The contribution reframing.
- Monotonic stacks for the boundaries, with a correct tie-break.
- Overflow and modulo handling.

## Follow-ups
- **Same boundaries, area instead of a sum:** [LC 0084 Largest Rectangle in Histogram](../0084-largest-rectangle-in-histogram/)
- **Sum of (max − min) over all subarrays:** LC 2104 Sum of Subarray Ranges (not added yet). Run this for max and for min.
