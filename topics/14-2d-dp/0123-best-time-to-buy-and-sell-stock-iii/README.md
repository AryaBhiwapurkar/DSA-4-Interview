---
number: 123
title: Best Time to Buy and Sell Stock III
difficulty: Hard
topic: 2-D Dynamic Programming
pattern: State machine DP (2 txns)
link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
lists: [LC Top Interview 150]
followup_of: ["0121 Best Time to Buy and Sell Stock"]
related: ["0188 Best Time to Buy and Sell Stock IV", "0309 Best Time to Buy and Sell Stock with Cooldown"]
---

# 0123. Best Time to Buy and Sell Stock III

## ⚡ 30-Second Summary
**Pattern:** State machine DP with a transaction count
**Key insight:** Track four running bests: after the 1st buy, 1st sell, 2nd buy, 2nd sell. Each one builds on the previous: `b1 = max(b1, -p)`, `s1 = max(s1, b1 + p)`, `b2 = max(b2, s1 - p)`, `s2 = max(s2, b2 + p)`. Answer `s2`.
**Go-to:** Four variables, O(n) time, O(1) space

## Problem
Given daily prices, return the maximum profit using at most two transactions, where you must sell before buying again. [LeetCode](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/)

**Examples:**
```
Input:  prices = [3,3,5,0,0,3,1,4]
Output: 6
Why:    Buy at 0, sell at 3 (+3), then buy at 1, sell at 4 (+3).

Input:  prices = [1,2,3,4,5]
Output: 4
Why:    One trade, 1 → 5. Splitting a steady climb into two trades can't beat it.

Input:  prices = [7,6,4,3,1]
Output: 0
Why:    Prices only fall, so don't trade.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵, so O(n²) split-point brute force is too slow.
- 0 ≤ prices[i] ≤ 10⁵.

## Hints
<details><summary>Hint 1</summary>
With two non-overlapping trades, there is a day that separates them. How would you use LC 121 on each side?
</details>
<details><summary>Hint 2</summary>
Precompute "best single trade ending by day i" from the left and "best single trade starting after day i" from the right. Can you avoid the arrays?
</details>
<details><summary>Hint 3</summary>
Keep b1, s1, b2, s2 as the best balance after each of the four actions so far. For each price: b1 = max(b1, -p), s1 = max(s1, b1 + p), b2 = max(b2, s1 - p), s2 = max(s2, b2 + p). Return s2.
</details>

## Clarifying Questions
- At most two, so zero or one is fine? (Yes.)
- Can a buy and sell happen on the same day? (Allowed, but pointless: it nets 0.)
- Hold two shares at once? (No.)

## Example Walkthrough
`[3,3,5,0,0,3,1,4]`: the best single trade is 0 → 4 = 4. Two trades do better: 0 → 3 and 1 → 4, total 6. The second trade "starts" with the money from the first: b2 = s1 - p.

## Approaches

### 1. Brute Split Point: O(n²) time, O(1) space
For each split k, best single trade in [0, k) plus best in [k, n).

### 2. Prefix / Suffix: O(n) time, O(n) space
left[i] = best trade within days 0..i (running min); a right-to-left pass keeps the best trade after i (running max). Answer max(left[i] + right).

### 3. Four States ⭐ Go-to: O(n) time, O(1) space
**Why it's the go-to:** four lines, constant space, and it generalises straight to k transactions (LC 188).

## Dry Run (Approach 3)
`[3,3,5,0,0,3,1,4]`

| p | b1 | s1 | b2 | s2 |
|---|----|----|----|----|
| 3 | -3 | 0 | -3 | 0 |
| 3 | -3 | 0 | -3 | 0 |
| 5 | -3 | 2 | -3 | 2 |
| 0 | 0 | 2 | **2** | 2 |
| 0 | 0 | 2 | 2 | 2 |
| 3 | 0 | 3 | 2 | 5 |
| 1 | 0 | 3 | 2 | 5 |
| 4 | 0 | 4 | 2 | **6** |

At p = 0, b2 = s1 - 0 = 2: the 3 → 5 trade banked +2, then the second share was bought at 0. Selling it at 4 gives s2 = **6** (3 → 5 plus 0 → 4, which ties with 0 → 3 plus 1 → 4).

## Edge Case Check
- One day → 0. ✅
- Monotonic rise → one trade, s2 = s1 = 4. ✅
- Falling prices → 0. ✅

## ⚠️ Pitfalls
- **Greedy "take the two biggest rises"** fails when rises overlap or merge.
- **C++ `INT_MIN + p` overflow** if you compute b1 + p before raising b1; update in order.
- **Starting b2 at 0** pretends you bought a share for free.
- **Returning max(s1, s2)** is unnecessary: s2 ≥ s1 always (a second trade can be empty).

## 🎯 What the Interviewer Wants
- The split-point idea, then the O(1) state version.
- Explain why the update order within a day is safe.
- Generalise to k transactions.

## Follow-ups
- **One transaction:** [LC 0121 Best Time to Buy and Sell Stock](../../03-sliding-window/0121-best-time-to-buy-and-sell-stock/)
- **k transactions:** [LC 0188 Best Time to Buy and Sell Stock IV](../0188-best-time-to-buy-and-sell-stock-iv/)
- **Unlimited with cooldown:** [LC 0309](../0309-best-time-to-buy-and-sell-stock-with-cooldown/)
