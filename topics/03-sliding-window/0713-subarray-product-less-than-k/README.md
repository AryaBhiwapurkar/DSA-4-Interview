---
number: 713
title: Subarray Product Less Than K
difficulty: Medium
topic: Sliding Window
pattern: Shrinking window, count subarrays ending at r
link: https://leetcode.com/problems/subarray-product-less-than-k/
lists: [Interview Extras]
followup_of: []
related: ["0209 Minimum Size Subarray Sum", "0560 Subarray Sum Equals K", "0992 Subarrays with K Different Integers"]
---

# 0713. Subarray Product Less Than K

## ⚡ 30-Second Summary
**Pattern:** Window counting: every valid window [l, r] contributes `r − l + 1` subarrays
**Key insight:** All values are positive, so extending the window only increases the product and shrinking only decreases it. For each r, shrink l until the product is below k. Then every subarray ending at r and starting anywhere in [l, r] is valid: that's `r − l + 1` of them. If k ≤ 1, no product of positive integers can be below it, so return 0.
**Go-to:** Sliding window with counting, O(n) time, O(1) space

## Problem
Count the contiguous subarrays whose product is strictly less than k. All numbers are positive. [LeetCode](https://leetcode.com/problems/subarray-product-less-than-k/)

**Examples:**
```
Input:  nums = [10,5,2,6], k = 100
Output: 8
Why:    [10], [5], [2], [6], [10,5], [5,2], [2,6], [5,2,6]; [10,5,2] is exactly 100, not below.

Input:  nums = [1,2,3], k = 0
Output: 0
Why:    No positive product is below 0.
```

**Constraints:**
- 1 ≤ n ≤ 3·10⁴; 1 ≤ nums[i] ≤ 1000; 0 ≤ k ≤ 10⁶.
- **Positive values** make the window monotone; the running product stays below k·1000 ≤ 10⁹ before shrinking.

## Hints
<details><summary>Hint 1</summary>
If [l, r] has product &lt; k, what about every subarray inside it that also ends at r?
</details>
<details><summary>Hint 2</summary>
For a fixed r, the valid starts form a contiguous range. How do you find its left end as r moves?
</details>
<details><summary>Hint 3</summary>
If k ≤ 1 return 0. prod *= nums[r]; while prod ≥ k: prod /= nums[l++]. count += r − l + 1.
</details>

## Clarifying Questions
- Strictly less than k? (Yes.)
- All positive? (Yes, ≥ 1, so no zeros and no negatives.)
- Can k be 0 or 1? (Yes, then the answer is 0.)

## Example Walkthrough
`[10,5,2,6], k = 100`. r = 0: prod 10 → +1. r = 1: 50 → +2. r = 2: 100 ≥ 100 → drop 10 → 10 → +2 ([5,2], [2]). r = 3: 60 → +3. Total 8.

## Approaches

### 1. All Start/End Pairs: O(n²) time, O(1) space
For each start, multiply forward and stop when the product reaches k. Fine for small n.

### 2. Sliding Window + Count ⭐ Go-to: O(n) time, O(1) space
**Why it's the go-to:** the "count subarrays ending at r" trick turns a longest-window template into a counting one, and it's reused for "at most k" counts (0992).

(Log trick: take logs so products become sums, then binary search over prefix sums. That's O(n log n) and has float issues. Mention it only.)

## Dry Run (Approach 2)
`[10,5,2,6], k = 100`

| r | prod after × | shrink | l | +count | total |
|---|--------------|--------|---|--------|-------|
| 0 | 10 | – | 0 | 1 | 1 |
| 1 | 50 | – | 0 | 2 | 3 |
| 2 | 100 | ÷10 → 10 | 1 | 2 | 5 |
| 3 | 60 | – | 1 | 3 | **8** |

## Edge Case Check
- k ≤ 1 → 0 (and the while loop would otherwise run past r). ✅
- Single element ≥ k → the window empties (l = r + 1), so it adds 0. ✅
- All 1s with k = 2 → n(n+1)/2. ✅

## ⚠️ Pitfalls
- **No k ≤ 1 guard:** `prod ≥ k` stays true even for an empty window, and l runs past r.
- **Counting windows instead of subarrays:** add r − l + 1, not 1.
- **≤ vs <:** the product must be strictly below k, so shrink while `prod ≥ k`.

## 🎯 What the Interviewer Wants
- Spot the monotonicity that comes from positive values.
- The "count subarrays ending at r" idea.
- Handle the k ≤ 1 edge case.

## Follow-ups
- **Sum version, shortest window:** [LC 0209 Minimum Size Subarray Sum](../0209-minimum-size-subarray-sum/)
- **Exactly k via atMost(k) − atMost(k−1):** [LC 0992 Subarrays with K Different Integers](../0992-subarrays-with-k-different-integers/)
- **Negatives allowed (sums):** [LC 0560 Subarray Sum Equals K](../../01-arrays-hashing/0560-subarray-sum-equals-k/)
