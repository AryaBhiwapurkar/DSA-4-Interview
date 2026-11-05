---
number: 322
title: Coin Change
difficulty: Medium
topic: 1-D Dynamic Programming
pattern: Unbounded knapsack (min)
link: https://leetcode.com/problems/coin-change/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0518 Coin Change II", "0279 Perfect Squares", "0039 Combination Sum"]
---

# 0322. Coin Change

## ⚡ 30-Second Summary
**Pattern:** Unbounded knapsack, minimizing the count
**Key insight:** `dp[a]` = fewest coins summing to a. The last coin is some c, so `dp[a] = 1 + min(dp[a - c])`. Greedy (largest coin first) fails for coin sets like [1,3,4].
**Go-to:** Bottom-up DP over amounts, O(amount · coins) time, O(amount) space

## Problem
Given coin denominations (unlimited supply of each) and a target amount, return the fewest coins that add up to exactly the amount, or -1 if no combination works. [LeetCode](https://leetcode.com/problems/coin-change/)

**Examples:**
```
Input:  coins = [1,2,5], amount = 11
Output: 3
Why:    5 + 5 + 1.

Input:  coins = [2], amount = 3
Output: -1
Why:    Only even totals are reachable with 2s.

Input:  coins = [1], amount = 0
Output: 0
Why:    Zero coins already make zero.
```

**Constraints:**
- Up to 12 coins, amount ≤ 10⁴, so amount × coins ≈ 1.2·10⁵ steps.
- Coin values go up to 2³¹-1, so in C++ write `c <= amount - a`, not `a + c <= amount` (that sum can overflow).

## Hints
<details><summary>Hint 1</summary>
Try greedy on coins [1,3,4], amount 6. Why does it fail?
</details>
<details><summary>Hint 2</summary>
If you knew the fewest coins for every smaller amount, how would you get the answer for this one?
</details>
<details><summary>Hint 3</summary>
dp[0] = 0, everything else "infinity" (amount + 1 works). For a = 1..amount and each coin c ≤ a: dp[a] = min(dp[a], dp[a - c] + 1). Return -1 if dp[amount] is still infinity.
</details>

## Clarifying Questions
- Unlimited coins of each type? (Yes.)
- amount = 0? (0 coins.)
- Return the count or the coins used? (Count.)
- Are coin values positive and distinct? (Positive, distinct.)

## Example Walkthrough
`[1,3,4]`, amount 6: greedy takes 4, then 1, 1 → 3 coins. But 3 + 3 = 2 coins. DP finds it because dp[6] considers last coin 3 → dp[3] + 1 = 2.

## Approaches

### 1. Memoized Recursion: O(amount · coins) time, O(amount) space
fewest(a) = 1 + min over coins of fewest(a - c). Recursion depth can reach the amount (with coin 1), which is risky in Python.

### 2. BFS over Amounts: O(amount · coins) time, O(amount) space
Nodes are amounts 0..amount, an edge adds one coin. The first level that reaches the amount is the minimum coin count. A nice alternate framing.

### 3. Bottom-up DP ⭐ Go-to: O(amount · coins) time, O(amount) space
Fill dp from 0 to amount.
**Why it's the go-to:** the canonical unbounded-knapsack loop, iterative, with one sentinel to explain.

## Dry Run (Approach 3)
`[1,3,4]`, amount 6. Candidates are dp[a - c] + 1 for each coin c ≤ a.

| a | c = 1 | c = 3 | c = 4 | dp[a] |
|---|-------|-------|-------|-------|
| 0 | | | | 0 |
| 1 | dp0+1 = 1 | | | 1 |
| 2 | dp1+1 = 2 | | | 2 |
| 3 | dp2+1 = 3 | dp0+1 = 1 | | 1 |
| 4 | dp3+1 = 2 | dp1+1 = 2 | dp0+1 = 1 | 1 |
| 5 | dp4+1 = 2 | dp2+1 = 3 | dp1+1 = 2 | 2 |
| 6 | dp5+1 = 3 | dp3+1 = 2 | dp2+1 = 3 | **2** |

## Edge Case Check
- amount = 0 → dp[0] = 0. ✅
- Unreachable (`[2]`, 3): dp[3] stays 4 > 3 → -1. ✅
- Large coins mixed (`[186,419,83,408]`, 6249) → 20. ✅

## ⚠️ Pitfalls
- **Greedy** fails on non-canonical coin systems.
- **C++ `INT_MAX + 1` overflow** if you use INT_MAX as infinity; amount + 1 is safe.
- **Forgetting the -1 conversion** for unreachable amounts.
- **C++ `a + c` overflow** in the BFS when a coin is near INT_MAX: compare `c <= amount - a`.
- **Python memo recursion** hits the recursion limit for amount 10⁴ with coin 1.

## 🎯 What the Interviewer Wants
- Show why greedy fails with a concrete counterexample.
- A clean recurrence and base case, bottom-up.
- Contrast with Coin Change II (count combinations: loop over coins outside, amounts inside).

## Follow-ups
- **Count combinations instead of min:** [LC 0518 Coin Change II](../../14-2d-dp/0518-coin-change-ii/). The coin loop goes outside so order doesn't matter.
- **Fewest perfect squares summing to n:** LC 0279 Perfect Squares (not added yet). Same DP with squares as coins.
- **List all combinations:** [LC 0039 Combination Sum](../../10-backtracking/0039-combination-sum/)
- **Each coin usable once:** 0/1 knapsack, as in [LC 0416 Partition Equal Subset Sum](../0416-partition-equal-subset-sum/)
