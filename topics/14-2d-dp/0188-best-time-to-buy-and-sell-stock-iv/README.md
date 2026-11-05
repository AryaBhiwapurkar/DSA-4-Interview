---
number: 188
title: Best Time to Buy and Sell Stock IV
difficulty: Hard
topic: 2-D Dynamic Programming
pattern: State machine DP (k txns)
link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/
lists: [LC Top Interview 150]
followup_of: ["0123 Best Time to Buy and Sell Stock III"]
related: ["0122 Best Time to Buy and Sell Stock II", "0309 Best Time to Buy and Sell Stock with Cooldown"]
---

# 0188. Best Time to Buy and Sell Stock IV

## ⚡ 30-Second Summary
**Pattern:** State machine DP, one buy/sell pair per allowed transaction
**Key insight:** LC 123's four variables become two arrays: `buy[j] = max(buy[j], sell[j-1] - p)`, `sell[j] = max(sell[j], buy[j] + p)` for j = 1..k. If `2k ≥ n`, the limit can't bind, so just sum every rise.
**Go-to:** buy[]/sell[] arrays, O(n·k) time, O(k) space

## Problem
Same as LC 123, but the cap on the number of transactions is an input k. Return the maximum profit. [LeetCode](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/)

**Examples:**
```
Input:  k = 2, prices = [2,4,1]
Output: 2
Why:    One trade, 2 → 4. Nothing after the 1 to sell into.

Input:  k = 2, prices = [3,2,6,5,0,3]
Output: 7
Why:    2 → 6 (+4) and 0 → 3 (+3).
```

**Constraints:**
- 1 ≤ k ≤ 100, 1 ≤ n ≤ 1000, so n·k ≤ 10⁵.
- 0 ≤ prices[i] ≤ 1000.

## Hints
<details><summary>Hint 1</summary>
Solve k = 2 first (LC 123) with four running values. What would k = 3 add?
</details>
<details><summary>Hint 2</summary>
Index the states by transaction number: the balance after the j-th buy and after the j-th sell. What does the j-th buy depend on?
</details>
<details><summary>Hint 3</summary>
For each price p, for j from 1 to k: buy[j] = max(buy[j], sell[j-1] - p); sell[j] = max(sell[j], buy[j] + p). Start buy = -inf, sell = 0, return sell[k]. Shortcut: if 2k ≥ n, sum all positive day-to-day differences.
</details>

## Clarifying Questions
- k = 0 or empty prices? (Current constraints: k ≥ 1, n ≥ 1. Return 0 if asked.)
- Same-day buy and sell? (Allowed but useless.)
- Can k exceed n / 2? (Yes; then it's unlimited trading.)

## Example Walkthrough
`k = 3, [1,3,2,5,4,8,0,1]`: the rises are +2, +3, +4, +1. With unlimited trades that's 10, but only 3 are allowed, so drop the smallest (+1): **9**. Sometimes merging two neighbouring rises into one trade beats dropping one. Here 1 → 5 = 4 loses to +2 and +3. The DP weighs both options automatically.

## Approaches

### 1. Memoized Recursion: O(n·k) time, O(n·k) space
f(i, left, holding): wait, buy, keep or sell, with `left` dropping on each sale.

### 2. State Arrays ⭐ Go-to: O(n·k) time, O(k) space
k buy/sell pairs, updated per price, plus the 2k ≥ n shortcut.
**Why it's the go-to:** it's LC 123 written for any k, so you can derive it live; the shortcut shows you think about bounds.

## Dry Run (Approach 2)
`k = 2, [3,2,6,5,0,3]` (buy starts at -inf, sell at 0).

| p | buy[1] | sell[1] | buy[2] | sell[2] |
|---|--------|---------|--------|---------|
| 3 | -3 | 0 | -3 | 0 |
| 2 | -2 | 0 | -2 | 0 |
| 6 | -2 | 4 | -2 | 4 |
| 5 | -2 | 4 | -1 | 4 |
| 0 | 0 | 4 | **4** | 4 |
| 3 | 0 | 4 | 4 | **7** |

At p = 0, buy[2] = sell[1] - 0 = 4: the 2 → 6 profit funds the second buy. Then 4 + 3 = 7.

## Edge Case Check
- k ≥ n / 2 (`k = 100, [1,2,3,4,5]`) → shortcut, 4. ✅
- k = 1 → classic single trade, 5 on `[7,1,5,3,6,4]`. ✅
- Falling prices → every sell stays 0. ✅

## ⚠️ Pitfalls
- **No shortcut with huge k:** the O(n·k) table is wasteful (older versions of the problem had k up to 10⁹, which broke memory).
- **Using `sell[j]` instead of `sell[j-1]`** for buy[j] lets one transaction count twice.
- **C++ INT_MIN overflow** if `buy[j] + p` is evaluated before buy[j] is raised.
- **Memo state size** n·k·2 is fine here; say so before choosing it.

## 🎯 What the Interviewer Wants
- Generalise the LC 123 states to arrays indexed by transaction count.
- The 2k ≥ n observation.
- Clear complexity: O(n·k) time, O(k) space.

## Follow-ups
- **k = 2:** [LC 0123 Best Time to Buy and Sell Stock III](../0123-best-time-to-buy-and-sell-stock-iii/)
- **Unlimited:** [LC 0122 Best Time to Buy and Sell Stock II](../../15-greedy/0122-best-time-to-buy-and-sell-stock-ii/)
- **Unlimited with cooldown:** [LC 0309](../0309-best-time-to-buy-and-sell-stock-with-cooldown/)
- **Faster for large k:** a "merge the smallest gains" greedy with a heap runs in O(n log n).
