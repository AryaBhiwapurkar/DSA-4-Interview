---
number: 518
title: Coin Change II
difficulty: Medium
topic: 2-D Dynamic Programming
pattern: Unbounded knapsack (count)
link: https://leetcode.com/problems/coin-change-ii/
lists: [NeetCode 150]
followup_of: ["0322 Coin Change"]
related: ["0377 Combination Sum IV", "0039 Combination Sum"]
---

# 0518. Coin Change II

## ⚡ 30-Second Summary
**Pattern:** Unbounded knapsack, counting combinations
**Key insight:** `dp[a]` = ways to make a. Put the **coin loop outside** and the amount loop inside: each combination is then built in a fixed coin order and counted once. Swapping the loops counts orderings instead (LC 377).
**Go-to:** 1-D DP, coins outer, amounts ascending, O(n·amount) time, O(amount) space

## Problem
Given coin denominations (unlimited supply) and an amount, count the distinct multisets of coins that add up to the amount. Order doesn't matter. [LeetCode](https://leetcode.com/problems/coin-change-ii/)

**Examples:**
```
Input:  amount = 5, coins = [1,2,5]
Output: 4
Why:    {5}, {2,2,1}, {2,1,1,1}, {1,1,1,1,1}.

Input:  amount = 3, coins = [2]
Output: 0
Why:    2s only make even totals.

Input:  amount = 10, coins = [10]
Output: 1
Why:    A single 10.
```

**Constraints:**
- Up to 300 coins, amount ≤ 5000, so n·amount ≤ 1.5·10⁶.
- Coins are distinct. The answer fits in a signed 32-bit int, **but intermediate dp values may not** (C++).
- amount = 0 → 1 (the empty combination).

## Hints
<details><summary>Hint 1</summary>
Counting "1+2" and "2+1" separately is the trap. How can you force every combination to be built in one canonical order?
</details>
<details><summary>Hint 2</summary>
Decide coin by coin: how many of coin 0, then how many of coin 1, ... That's a 2-D state (coins considered, amount).
</details>
<details><summary>Hint 3</summary>
dp[0] = 1. For each coin c (outer loop), for a from c up to amount: dp[a] += dp[a - c]. Ascending a lets c be reused; coins-outer means each multiset is counted once.
</details>

## Clarifying Questions
- Combinations or permutations? (Combinations: {1,2} = {2,1}.)
- amount = 0? (1 way.)
- Distinct coins? (Yes.)
- Answer size? (Fits in int; intermediates might not.)

## Example Walkthrough
`amount = 3, coins = [1,2]`. Coins-outer: after coin 1, dp = [1,1,1,1]; after coin 2, dp[2] += dp[0] → 2, dp[3] += dp[1] → 2. Answer 2 ({1,1,1}, {1,2}). Amounts-outer would give 3, because it counts 1+2 and 2+1 separately.

## Approaches

### 1. Memoized Recursion: O(n·amount) time, O(n·amount) space
ways(i, a) = ways(i, a - coins[i]) (use coin i again) + ways(i+1, a) (move on).

### 2. 2-D Table: O(n·amount) time, O(n·amount) space
dp[i][a] = dp[i-1][a] + dp[i][a - c]. Makes the "first i coins" state explicit.

### 3. 1-D, Coins Outer ⭐ Go-to: O(n·amount) time, O(amount) space
The 2-D table with the coin dimension rolled away.
**Why it's the go-to:** four lines, and the loop order is the whole insight, which is exactly what interviewers probe.

## Dry Run (Approach 3)
`amount = 5, coins = [1,2,5]`, dp starts [1,0,0,0,0,0].

| after coin | dp[0..5] |
|------------|----------|
| 1 | [1, 1, 1, 1, 1, 1] |
| 2 | [1, 1, 2, 2, 3, 3] |
| 5 | [1, 1, 2, 2, 3, **4**] |

Coin 2, a = 4: dp[4] = 1 + dp[2] (already 2 after this coin's pass) = 3, i.e. {1111, 211, 22}.

## Edge Case Check
- amount = 0 → 1. ✅
- Unreachable (`3, [2]`) → 0. ✅
- Single coin equal to amount → 1. ✅

## ⚠️ Pitfalls
- **Amount loop outside** counts permutations (that's LC 377).
- **Descending inner loop** turns it into 0/1 knapsack (each coin at most once).
- **C++ int overflow in intermediates:** dp values for unused amounts can exceed 2³¹ on some tests. Use `unsigned long long` (wraps safely); the final answer is still exact.
- **dp[0] = 0** gives 0 for everything.
- **Python memo recursion** goes up to amount + n deep (5300), well past the default limit of 1000.

## 🎯 What the Interviewer Wants
- Combinations vs permutations, and how loop order controls it.
- Compare with LC 322 (min instead of count) and 0/1 knapsack (descending).
- O(amount) space.

## Follow-ups
- **Fewest coins:** [LC 0322 Coin Change](../../13-1d-dp/0322-coin-change/)
- **Count orderings:** LC 0377 Combination Sum IV (not added yet). Amount loop outside.
- **List the combinations:** [LC 0039 Combination Sum](../../10-backtracking/0039-combination-sum/)
- **Each coin once:** descending loop, as in [LC 0416 Partition Equal Subset Sum](../../13-1d-dp/0416-partition-equal-subset-sum/)
