---
number: 494
title: Target Sum
difficulty: Medium
topic: 2-D Dynamic Programming
pattern: Subset-sum DP / memo
link: https://leetcode.com/problems/target-sum/
lists: [NeetCode 150]
followup_of: []
related: ["0416 Partition Equal Subset Sum", "0518 Coin Change II", "1049 Last Stone Weight II"]
---

# 0494. Target Sum

## ⚡ 30-Second Summary
**Pattern:** Count subsets with a given sum (0/1 knapsack, counting)
**Key insight:** Split the numbers into a plus group P and a minus group N. Then `P - N = target` and `P + N = total`, so `P = (total + target) / 2`. The answer is the number of subsets summing to P. If that's not a non-negative integer, the answer is 0.
**Go-to:** 1-D subset-count DP, sums iterated backwards, O(n·P) time, O(P) space

## Problem
Give every number in the array a + or − sign. Count how many of the 2ⁿ sign assignments make the expression equal to target. [LeetCode](https://leetcode.com/problems/target-sum/)

**Examples:**
```
Input:  nums = [1,1,1,1,1], target = 3
Output: 5
Why:    Exactly one of the five 1s must be negative, and it can be any of them.

Input:  nums = [1], target = 1
Output: 1
Why:    Only +1 works.
```

**Constraints:**
- 1 ≤ n ≤ 20, 0 ≤ nums[i] ≤ 1000, total ≤ 1000, |target| ≤ 1000.
- n ≤ 20 means 2ⁿ ≈ 10⁶, so brute force passes; the DP is the expected answer.
- **Zeros are allowed** and each doubles the count.

## Hints
<details><summary>Hint 1</summary>
Brute force tries both signs per number. What's the state of a partial assignment that actually matters for the rest?
</details>
<details><summary>Hint 2</summary>
Call the sum of the plus numbers P and the sum of the minus numbers N. You know P + N and P − N. Solve for P.
</details>
<details><summary>Hint 3</summary>
P = (total + target) / 2; return 0 if |target| > total or the sum is odd. Then count subsets summing to P: dp[0] = 1, for each x, for s from P down to x, dp[s] += dp[s − x].
</details>

## Clarifying Questions
- Must every number get a sign? (Yes.)
- Zeros? (Yes: +0 and −0 count as different assignments.)
- Negative target? (Yes, |target| ≤ 1000.)
- Count or list? (Count.)

## Example Walkthrough
`[1,2,1], target 0`: total 4, so P = (4 + 0) / 2 = 2. The subsets summing to 2 are {2} and {1,1} (the two 1s at index 0 and 2). Those give −1+2−1 and +1−2+1, so the answer is 2.

## Approaches

### 1. Brute Force: O(2ⁿ) time, O(n) space
Recurse with + and − for each number. Passes at n = 20, but it's the baseline.

### 2. Memo on (index, running sum): O(n·total) time, O(n·total) space
Running sums lie in [−total, total]; shift by total for an array memo (or use a hashmap).

### 3. Subset-Sum Count ⭐ Go-to: O(n·P) time, O(P) space
The algebra reduces it to counting subsets, the counting version of LC 416.
**Why it's the go-to:** the reduction is the "aha" interviewers look for, and the DP is the 0/1 knapsack template.

## Dry Run (Approach 3)
`[1,1,1,1,1], target 3` → total 5, P = 4. dp starts [1,0,0,0,0].

| x | dp[0..4] after the backward sweep |
|---|-----------------------------------|
| 1 | [1, 1, 0, 0, 0] |
| 1 | [1, 2, 1, 0, 0] |
| 1 | [1, 3, 3, 1, 0] |
| 1 | [1, 4, 6, 4, 1] |
| 1 | [1, 5, 10, 10, **5**] |

Binomial coefficients appear because every number is 1: dp[4] = C(5, 4) = 5.

## Edge Case Check
- `|target| > total` (`[100], −200`) → 0 before any DP. ✅
- Odd `total + target` → 0. ✅
- Zeros (`[0×8, 1], 1`) → each 0 doubles the count: 2⁸ = 256. ✅

## ⚠️ Pitfalls
- **Missing the parity / range checks**: (total + target) / 2 then truncates or goes negative.
- **Forward sweep** reuses a number (unbounded knapsack) and overcounts.
- **Skipping zeros** or starting the loop at s ≥ 1: zeros must double dp[0] too.
- **C++ memo with negative sums** needs an offset; indexing `memo[i][s]` directly is out of bounds.

## 🎯 What the Interviewer Wants
- Start with the 2ⁿ recursion, memoize on (i, sum).
- The P = (total + target) / 2 reduction.
- Handle zeros and impossible targets explicitly.

## Follow-ups
- **Is an equal split possible?** [LC 0416 Partition Equal Subset Sum](../../13-1d-dp/0416-partition-equal-subset-sum/)
- **Minimise |P − N|:** LC 1049 Last Stone Weight II (not added yet). Largest reachable sum ≤ total / 2.
- **Unlimited use of each number:** forward sweep, as in [LC 0518 Coin Change II](../0518-coin-change-ii/)
