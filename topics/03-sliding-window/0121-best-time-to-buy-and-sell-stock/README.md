---
number: 121
title: Best Time to Buy and Sell Stock
difficulty: Easy
topic: Sliding Window
pattern: Running min
link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0122 Best Time to Buy and Sell Stock II", "0123 Best Time to Buy and Sell Stock III", "0309 Best Time to Buy and Sell Stock with Cooldown", "0053 Maximum Subarray"]
---

# 0121. Best Time to Buy and Sell Stock

## ⚡ 30-Second Summary
**Pattern:** Running minimum (a window whose left edge jumps to each new low)
**Key insight:** The best sale on day i uses the cheapest price seen before day i. Track that minimum while scanning; the answer is the largest `price - minSoFar`.
**Go-to:** One pass with running min, O(n) time, O(1) space

## Problem
Given daily prices, choose one day to buy and a later day to sell to maximize profit. Return the maximum profit, or 0 if no profit is possible. [LeetCode](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)

**Examples:**
```
Input:  prices = [7,1,5,3,6,4]
Output: 5
Why:    Buy at 1 (day 1), sell at 6 (day 4).

Input:  prices = [7,6,4,3,1]
Output: 0
Why:    Prices only fall, so don't trade.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵, so O(n²) is too slow.
- 0 ≤ prices[i] ≤ 10⁴.

## Hints
<details><summary>Hint 1</summary>
If you sell on day i, which buy day is best?
</details>
<details><summary>Hint 2</summary>
You only need one number from the past: the lowest price so far.
</details>
<details><summary>Hint 3</summary>
For each price: profit = price - minSoFar; update best; then update minSoFar.
</details>

## Clarifying Questions
- Exactly one buy and one sell? (At most one transaction.)
- Must sell strictly after buying? (Yes.)
- Return 0 if no profit? (Yes, not negative.)

## Example Walkthrough
`prices = [7,1,5,3,6,4]`
- min 7 → 1 (day 1). Day 2: 5 - 1 = 4. Day 3: 3 - 1 = 2. Day 4: 6 - 1 = 5 (best). Day 5: 4 - 1 = 3.
- Answer 5.

## Approaches

### 1. Brute Force: O(n²) time, O(1) space
Try every (buy, sell) pair with sell > buy.

### 2. Running Min ⭐ Go-to: O(n) time, O(1) space
Keep `minPrice`; at each day, `best = max(best, price - minPrice)`, then `minPrice = min(minPrice, price)`.
**Why it's the go-to:** single pass, two variables. As a sliding window: l = cheapest day, r = today; move l to r whenever today is cheaper.

## Dry Run (Approach 2)
`prices = [7,1,5,3,6,4]`

| day | price | minPrice (before) | profit | best |
|-----|-------|-------------------|--------|------|
| 0 | 7 | ∞ | - | 0 |
| 1 | 1 | 7 | -6 | 0 |
| 2 | 5 | 1 | 4 | 4 |
| 3 | 3 | 1 | 2 | 4 |
| 4 | 6 | 1 | 5 | 5 |
| 5 | 4 | 1 | 3 | 5 |

## Edge Case Check
- n = 1: no sale possible, 0. ✅
- Decreasing prices: every profit ≤ 0, answer 0. ✅
- All equal: 0. ✅

## ⚠️ Pitfalls
- **Updating min before computing profit on the same day** gives profit 0 for that day; harmless here, but compute then update to keep "sell after buy" explicit.
- **Taking max price minus min price overall:** the max might come before the min.
- **Initializing best to a negative number** returns a loss instead of 0.

## 🎯 What the Interviewer Wants
- Recognize that only the minimum so far matters.
- O(n), O(1), and a clean "never negative" answer.

## Follow-ups
- **Unlimited transactions:** sum every positive day-to-day gain: [LC 0122 Best Time to Buy and Sell Stock II](../../15-greedy/0122-best-time-to-buy-and-sell-stock-ii/)
- **At most two / k transactions:** state-machine DP: [LC 0123](../../14-2d-dp/0123-best-time-to-buy-and-sell-stock-iii/) / [LC 0188](../../14-2d-dp/0188-best-time-to-buy-and-sell-stock-iv/)
- **With cooldown:** [LC 0309 Best Time to Buy and Sell Stock with Cooldown](../../14-2d-dp/0309-best-time-to-buy-and-sell-stock-with-cooldown/)
- **Same idea on differences:** max subarray of daily changes (Kadane): [LC 0053 Maximum Subarray](../../15-greedy/0053-maximum-subarray/)
