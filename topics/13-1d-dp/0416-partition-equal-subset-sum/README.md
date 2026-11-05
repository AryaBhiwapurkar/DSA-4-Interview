---
number: 416
title: Partition Equal Subset Sum
difficulty: Medium
topic: 1-D Dynamic Programming
pattern: 0/1 knapsack subset sum
link: https://leetcode.com/problems/partition-equal-subset-sum/
lists: [NeetCode 150]
followup_of: []
related: ["0494 Target Sum", "0698 Partition to K Equal Sum Subsets", "1049 Last Stone Weight II"]
---

# 0416. Partition Equal Subset Sum

## ⚡ 30-Second Summary
**Pattern:** 0/1 knapsack, reachable subset sums
**Key insight:** Two equal halves means one subset sums to `total / 2`. That's subset sum: `dp[s]` = "some subset hits s". Process each number once and sweep s **downwards**, so a number can't be reused within its own pass.
**Go-to:** 1-D boolean DP iterated backwards, O(n·S) time, O(S) space (S = total / 2)

## Problem
Decide whether an array of positive integers can be split into two groups with the same sum. [LeetCode](https://leetcode.com/problems/partition-equal-subset-sum/)

**Examples:**
```
Input:  nums = [1,5,11,5]
Output: true
Why:    {1,5,5} and {11} both sum to 11.

Input:  nums = [1,2,3,5]
Output: false
Why:    The total is 11, which is odd, so no even split exists.
```

**Constraints:**
- 1 ≤ n ≤ 200, 1 ≤ nums[i] ≤ 100, so total ≤ 2·10⁴ and S ≤ 10⁴.
- n·S ≤ 2·10⁶, which is easy.

## Hints
<details><summary>Hint 1</summary>
If both halves are equal, what must each half sum to? When can you answer immediately?
</details>
<details><summary>Hint 2</summary>
Now it's "is there a subset with sum S?". The sums are small. What can you track for every value 0..S?
</details>
<details><summary>Hint 3</summary>
dp[0] = true. For each x, for s from S down to x: dp[s] |= dp[s - x]. Going down ensures dp[s - x] still reflects subsets without x. Return dp[S].
</details>

## Clarifying Questions
- Positive integers only? (Yes, which makes the sum-indexed DP valid.)
- Must every element be used? (Yes, it's a partition. Equivalent to one subset hitting total / 2.)
- Empty subsets? (n ≥ 1, and with positives a half can't be empty if the answer is true.)

## Example Walkthrough
`[1,2,5]`: total 8 is even, S = 4. Reachable sums: {0} → {0,1} → {0,1,2,3} → 5 is bigger than 4, so it adds nothing. 4 is never reached → false. The even total wasn't enough.

## Approaches

### 1. Memoized Recursion: O(n·S) time, O(n·S) space
can(i, rem): take nums[i] or skip it. Caching on (i, rem) collapses the 2ⁿ tree.

### 2. 1-D Boolean DP ⭐ Go-to: O(n·S) time, O(S) space
The classic 0/1 knapsack with one rolling row, iterated backwards.
**Why it's the go-to:** it's the template for every 0/1 knapsack, it's short, and the backwards loop is the one insight to explain.

### 3. Bitset: O(n·S/64) time, O(S) space
`bits |= bits << x` adds x to every reachable sum at once. A good bonus to mention, and very fast in C++.

## Dry Run (Approach 2)
`[1,5,11,5]`, S = 11. Reachable sums ≤ 11 after each number.

| x | new sums from s - x | reachable |
|---|---------------------|-----------|
| start | | {0} |
| 1 | 1 | {0, 1} |
| 5 | 5, 6 | {0, 1, 5, 6} |
| 11 | 11 (from 0) | {0, 1, 5, 6, 11} |
| 5 | 10 (from 5); 11 again via 6 | {0, 1, 5, 6, 10, 11} |

dp[11] = **true**. On the first 5, sweeping down reads dp[1] and dp[0] from before that 5 was added. Sweeping up would set dp[5] and then use it for dp[10], counting that one 5 twice.

## Edge Case Check
- Odd total (example 2): return false immediately. ✅
- Single element `[100]`: total even but S = 50 unreachable → false. ✅
- `[1,1]`: S = 1, reachable → true. ✅

## ⚠️ Pitfalls
- **Iterating s upwards** reuses the same number, which turns it into unbounded knapsack. On `[1,2,5]` (S = 4), sweeping up with x = 1 marks every sum reachable and wrongly returns true.
- **Missing the odd-total early exit.**
- **C++ bitset size** must be a compile-time constant ≥ S + 1 (10001 here).
- **Python memo on (i, rem)** with n = 200 and S = 10⁴ can be 2·10⁶ cache entries; the 1-D DP is lighter.

## 🎯 What the Interviewer Wants
- Reduce to subset sum with target total / 2.
- 0/1 knapsack DP, and why the loop runs backwards.
- Complexity in terms of the sum (pseudo-polynomial), plus the bitset trick.

## Follow-ups
- **Assign + / - signs to hit a target:** [LC 0494 Target Sum](../../14-2d-dp/0494-target-sum/). Subset sum with target (total + T) / 2.
- **k equal subsets:** LC 0698 Partition to K Equal Sum Subsets (not added yet). Backtracking or bitmask DP.
- **Minimize the difference between halves:** LC 1049 Last Stone Weight II (not added yet). Largest reachable sum ≤ total / 2.
- **Unlimited copies of each number:** iterate upwards, as in [LC 0322 Coin Change](../0322-coin-change/)
