---
number: 309
title: Best Time to Buy and Sell Stock with Cooldown
difficulty: Medium
topic: 2-D Dynamic Programming
pattern: State machine DP
link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
lists: [NeetCode 150]
followup_of: ["0122 Best Time to Buy and Sell Stock II"]
related: ["0714 Best Time to Buy and Sell Stock with Transaction Fee", "0123 Best Time to Buy and Sell Stock III", "0188 Best Time to Buy and Sell Stock IV"]
---

# 0309. Best Time to Buy and Sell Stock with Cooldown

## ⚡ 30-Second Summary
**Pattern:** State machine DP (the 2-D state is day × what you hold)
**Key insight:** On any day you are in one of three states: **hold** (own a share), **sold** (sold today, so tomorrow is locked), **rest** (no share, free to buy). Each state's best profit comes from yesterday's states: `hold = max(hold, rest - p)`, `sold = hold + p`, `rest = max(rest, sold)`.
**Go-to:** Three rolling variables, O(n) time, O(1) space

## Problem
Given daily stock prices, maximise profit with any number of buy/sell pairs, holding at most one share, where the day after any sale you may not buy. [LeetCode](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/)

**Examples:**
```
Input:  prices = [1,2,3,0,2]
Output: 3
Why:    Buy at 1, sell at 2, sit out the 3 (cooldown), buy at 0, sell at 2: 1 + 2.

Input:  prices = [1]
Output: 0
Why:    One day: nothing to sell.
```

**Constraints:**
- 1 ≤ n ≤ 5000, 0 ≤ prices[i] ≤ 1000.

## Hints
<details><summary>Hint 1</summary>
Without the cooldown, you'd just collect every rising day (LC 122). What does the cooldown break about that?
</details>
<details><summary>Hint 2</summary>
At the end of each day, describe yourself: do you hold a share? If not, did you just sell? That's three states.
</details>
<details><summary>Hint 3</summary>
hold = max(hold, rest - p); sold = hold + p; rest = max(rest, sold), all using yesterday's values. Start hold = -prices[0], sold = rest = 0, answer max(sold, rest).
</details>

## Clarifying Questions
- Hold more than one share? (No.)
- Does the cooldown apply after buying too? (No, only after selling.)
- Any fee per transaction? (No. That's LC 714.)
- Can prices be 0? (Yes.)

## Example Walkthrough
`[1,2,4]`: without a cooldown you could sell at 2 and rebuy at 2 for the same total. With it, you can't rebuy on day 2, but holding from 1 to 4 gives 3 anyway. The state machine never needs that rebuy: hold stays -1 and sold on day 2 is -1 + 4 = 3.

## Approaches

### 1. Memoized Recursion: O(n) time, O(n) space
f(i, holding): if holding, keep or sell and jump to i+2; if not, wait or buy. Mirrors the rules directly.

### 2. State Machine ⭐ Go-to: O(n) time, O(1) space
Three variables updated once per day from yesterday's values.
**Why it's the go-to:** the same template solves every stock variant (fee, k transactions); you just change the states.

## Dry Run (Approach 2)
`[1,2,3,0,2]`, start hold = -1, sold = 0, rest = 0.

| day | p | hold = max(hold, rest-p) | sold = hold+p | rest = max(rest, sold) |
|-----|---|--------------------------|---------------|------------------------|
| 1 | 2 | max(-1, -2) = -1 | 1 | 0 |
| 2 | 3 | max(-1, -3) = -1 | 2 | 1 |
| 3 | 0 | max(-1, 1) = **1** | -1 | 2 |
| 4 | 2 | max(1, 0) = 1 | **3** | 2 |

Day 3: buying at 0 uses rest = 1 (the sale on day 1 has cooled down), not the sale of day 2. Answer max(3, 2) = **3**.

## Edge Case Check
- One day → max(0, 0) = 0. ✅
- Strictly falling `[2,1]` → never buy, 0. ✅
- Cooldown doesn't matter `[1,2,4]` → 3. ✅

## ⚠️ Pitfalls
- **Buying from `sold`** instead of `rest` ignores the cooldown.
- **Updating states in place in C++**: `sold = hold + p` after `hold` already changed uses today's hold. Use temporaries (Python's tuple assignment does this for you).
- **Returning `hold`**: ending with a share is never optimal.
- **Memo jump `i + 2`** must be handled by `i >= n`, not `i == n`.

## 🎯 What the Interviewer Wants
- Name the states and draw the transitions.
- O(1) space with the old-values-first update.
- Show how the same machine adapts to fees or a k-transaction limit.

## Follow-ups
- **No cooldown:** [LC 0122 Best Time to Buy and Sell Stock II](../../15-greedy/0122-best-time-to-buy-and-sell-stock-ii/)
- **Fee per transaction:** LC 0714 Best Time to Buy and Sell Stock with Transaction Fee (not added yet). Two states, subtract the fee on sell.
- **At most 2 / k transactions:** [LC 0123](../0123-best-time-to-buy-and-sell-stock-iii/), [LC 0188](../0188-best-time-to-buy-and-sell-stock-iv/)
