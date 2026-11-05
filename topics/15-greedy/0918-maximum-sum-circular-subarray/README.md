---
number: 918
title: Maximum Sum Circular Subarray
difficulty: Medium
topic: Greedy
pattern: Kadane on max & min
link: https://leetcode.com/problems/maximum-sum-circular-subarray/
lists: [LC Top Interview 150]
followup_of: ["0053 Maximum Subarray"]
related: ["0134 Gas Station", "0213 House Robber II"]
---

# 0918. Maximum Sum Circular Subarray

## ⚡ 30-Second Summary
**Pattern:** Kadane twice: maximum and minimum subarray
**Key insight:** The best subarray either doesn't wrap (plain Kadane max) or wraps around the end. A wrapping subarray is the whole array minus a contiguous middle block, so the best one is `total - (minimum subarray)`. Answer `max(bestMax, total - bestMin)`, except when every number is negative: then the "wrap" would be empty, so return bestMax.
**Go-to:** One pass computing max and min Kadane, O(n) time, O(1) space

## Problem
Treat the array as circular (the end connects back to the start). Return the largest sum of a non-empty contiguous piece, where a piece may wrap around but can't use any element twice. [LeetCode](https://leetcode.com/problems/maximum-sum-circular-subarray/)

**Examples:**
```
Input:  nums = [1,-2,3,-2]
Output: 3
Why:    Just [3]. Wrapping only adds negatives.

Input:  nums = [5,-3,5]
Output: 10
Why:    Wrap from the last 5 to the first 5, skipping the -3.

Input:  nums = [-3,-2,-3]
Output: -2
Why:    All negative: the best is the single largest element.
```

**Constraints:**
- 1 ≤ n ≤ 3·10⁴, values in [-3·10⁴, 3·10⁴]: sums fit in int.
- Non-empty subarray.

## Hints
<details><summary>Hint 1</summary>
Split into two cases: the answer wraps around the end, or it doesn't. The second case is LC 53.
</details>
<details><summary>Hint 2</summary>
If the answer wraps, what's left out is a contiguous block in the middle. Which block should you leave out?
</details>
<details><summary>Hint 3</summary>
Run Kadane for the max and, in the same loop, for the min. Answer max(bestMax, total - bestMin), but if bestMax < 0, return bestMax.
</details>

## Clarifying Questions
- Can the subarray be the whole array? (Yes, but not more than once around.)
- Non-empty? (Yes.)
- Overflow? (|sum| ≤ 9·10⁸, int is fine.)

## Example Walkthrough
`[3,-1,2,-1]`: total 3, max subarray [3,-1,2] = 4, min subarray [-1] = -1, so the wrap gives 3 - (-1) = 4. Either way, 4.

## Approaches

### 1. Brute Force: O(n²) time, O(1) space
For each start, extend through all n lengths with wrap-around indexing.

### 2. Kadane on Max and Min ⭐ Go-to: O(n) time, O(1) space
**Why it's the go-to:** it reuses LC 53 and adds one clever observation (wrap = total − min block) plus one edge case.

## Dry Run (Approach 2)
`[5,-3,5]`

| x | curMax | bestMax | curMin | bestMin | total |
|---|--------|---------|--------|---------|-------|
| 5 | 5 | 5 | 5 | 5 | 5 |
| -3 | 2 | 5 | -3 | -3 | 2 |
| 5 | 7 | 7 | 2 | -3 | 7 |

bestMax = 7 ≥ 0, so the answer is max(7, 7 − (−3)) = **10**.

## Edge Case Check
- All negative → bestMin = total, the wrap would be empty → return bestMax (-2). ✅
- Single element → that element. ✅
- Wrap and non-wrap tie (`[3,-1,2,-1]`) → 4. ✅

## ⚠️ Pitfalls
- **Missing the all-negative case:** total − bestMin = 0 is the empty subarray, which isn't allowed.
- **Running Kadane on the doubled array** without capping the length at n counts elements twice.
- **Seeding bestMin/bestMax with 0:** use nums[0] so single-element and all-negative inputs work.

## 🎯 What the Interviewer Wants
- The two-case split and the "total − min block" insight.
- The all-negative edge case, unprompted.
- One pass, O(1) space.

## Follow-ups
- **Non-circular version:** [LC 0053 Maximum Subarray](../0053-maximum-subarray/)
- **Another circular trick, split into two linear runs:** [LC 0213 House Robber II](../../13-1d-dp/0213-house-robber-ii/)
- **Prefix-sum + monotonic deque version:** works on the doubled array with a window of size ≤ n; useful if the length is also bounded.
