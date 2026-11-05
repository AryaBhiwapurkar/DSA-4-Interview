---
number: 122
title: Best Time to Buy and Sell Stock II
difficulty: Medium
topic: Greedy
pattern: Sum positive deltas
link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
lists: [LC Top Interview 150]
followup_of: ["0121 Best Time to Buy and Sell Stock"]
related: ["0309 Best Time to Buy and Sell Stock with Cooldown", "0714 Best Time to Buy and Sell Stock with Transaction Fee", "0188 Best Time to Buy and Sell Stock IV"]
---

# 0122. Best Time to Buy and Sell Stock II

## ⚡ 30-Second Summary
**Pattern:** Greedy, collect every upward step
**Key insight:** Any rise from day a to day b equals the sum of the daily changes in between. With unlimited trades, take every positive daily change and skip every negative one. That's exactly the sum of all rises.
**Go-to:** Sum of positive day-to-day gains, O(n) time, O(1) space

## Problem
Given daily prices, you may buy and sell as many times as you like, but hold at most one share at a time. Return the maximum profit. [LeetCode](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/)

**Examples:**
```
Input:  prices = [7,1,5,3,6,4]
Output: 7
Why:    Buy 1 sell 5 (+4), buy 3 sell 6 (+3).

Input:  prices = [1,2,3,4,5]
Output: 4
Why:    One long trade 1 → 5, the same as four +1 day trades.

Input:  prices = [7,6,4,3,1]
Output: 0
Why:    Never a rise, so never trade.
```

**Constraints:**
- 1 ≤ n ≤ 3·10⁴, 0 ≤ prices[i] ≤ 10⁴.

## Hints
<details><summary>Hint 1</summary>
Draw the price chart. With unlimited trades, which segments of it do you want to "own"?
</details>
<details><summary>Hint 2</summary>
A long rise from day a to day b is the same profit as buying and selling every day along the way.
</details>
<details><summary>Hint 3</summary>
Sum max(0, prices[i] - prices[i-1]) over all i.
</details>

## Clarifying Questions
- Hold more than one share? (No.)
- Same-day sell and buy? (Allowed; it's what makes the daily-gain view legal.)
- Fees or cooldowns? (No. Those are LC 714 and LC 309.)

## Example Walkthrough
`[2,1,2,0,1]`: daily changes −1, +1, −2, +1. Keep the positives: 1 + 1 = 2 (buy 1 sell 2, buy 0 sell 1).

## Approaches

### 1. State Machine DP: O(n) time, O(1) space
hold = max(hold, free − p), free = max(free, hold + p). The general template that survives fees and cooldowns.

### 2. Sum of Gains ⭐ Go-to: O(n) time, O(1) space
**Why it's the go-to:** one line, and the telescoping argument (a long rise = sum of daily rises) is a clean proof. Mention the DP as the version that generalises.

## Dry Run (Approach 2)
`[7,1,5,3,6,4]`

| day | change | taken | total |
|-----|--------|-------|-------|
| 1 | 1 − 7 = −6 | 0 | 0 |
| 2 | 5 − 1 = 4 | 4 | 4 |
| 3 | 3 − 5 = −2 | 0 | 4 |
| 4 | 6 − 3 = 3 | 3 | **7** |
| 5 | 4 − 6 = −2 | 0 | 7 |

## Edge Case Check
- One day → 0. ✅
- Strictly falling → 0. ✅
- Strictly rising → last − first. ✅

## ⚠️ Pitfalls
- **Looking for local min/max pairs** works, but it's easy to get the plateaus and end of array wrong; the delta sum avoids that.
- **Applying this greedy to LC 123/188/309/714:** it breaks once there's a cap, fee or cooldown.
- **C++ `free` as a variable name** shadows the C library function; harmless but confusing.

## 🎯 What the Interviewer Wants
- The telescoping argument for the greedy.
- O(n), O(1).
- Awareness that the DP version handles the variants.

## Follow-ups
- **One transaction:** [LC 0121 Best Time to Buy and Sell Stock](../../03-sliding-window/0121-best-time-to-buy-and-sell-stock/)
- **Cooldown after selling:** [LC 0309](../../14-2d-dp/0309-best-time-to-buy-and-sell-stock-with-cooldown/)
- **Fee per trade:** LC 0714 Best Time to Buy and Sell Stock with Transaction Fee (not added yet). DP, since small rises may not cover the fee.
- **At most k trades:** [LC 0188 Best Time to Buy and Sell Stock IV](../../14-2d-dp/0188-best-time-to-buy-and-sell-stock-iv/)
