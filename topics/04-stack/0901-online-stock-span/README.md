---
number: 901
title: Online Stock Span
difficulty: Medium
topic: Stack
pattern: Monotonic stack of (price, span)
link: https://leetcode.com/problems/online-stock-span/
lists: [Interview Extras]
followup_of: []
related: ["0739 Daily Temperatures", "0496 Next Greater Element I", "0084 Largest Rectangle in Histogram"]
---

# 0901. Online Stock Span

## ⚡ 30-Second Summary
**Pattern:** Previous-greater with a stack that absorbs spans
**Key insight:** A day's span is the number of consecutive days, ending today, with price ≤ today's. Keep a stack of (price, span) pairs with strictly decreasing prices. A new price pops every entry with price ≤ it and adds their spans to its own. Those days are covered now, and a later query that reaches today will also reach them. Each entry is pushed and popped once, so the cost is amortised O(1).
**Go-to:** Stack of (price, span), O(1) amortised per call, O(n) space

## Problem
Design a class that receives one stock price per day. After each price, return the span: the number of consecutive days, counting backwards from today and including today, on which the price was at most today's price. [LeetCode](https://leetcode.com/problems/online-stock-span/)

**Examples:**
```
Input:  ["StockSpanner","next","next","next","next","next","next","next"]
        [[],[100],[80],[60],[70],[60],[75],[85]]
Output: [null,1,1,1,2,1,4,6]
Why:    75 covers 60, 70, 60 and itself (4); 85 covers everything back to 80 (6).
```

**Constraints:**
- Up to 10⁴ calls; prices 1..10⁵.
- Online: each answer is needed before the next price arrives.

## Hints
<details><summary>Hint 1</summary>
The span ends at the most recent earlier day with a strictly higher price. Which classic stack problem finds that?
</details>
<details><summary>Hint 2</summary>
Once today's price absorbs a smaller earlier price, will you ever need that earlier day on its own again?
</details>
<details><summary>Hint 3</summary>
span = 1; while stack and stack.top.price ≤ price: span += pop().span. Push (price, span); return span.
</details>

## Clarifying Questions
- Are prices equal to today's included? (Yes, ≤.)
- Online calls? (Yes, one at a time.)
- Price range? (Positive integers.)

## Example Walkthrough
Prices 100, 80, 60, 70: stack (100,1), (80,1), (60,1). 70 pops (60,1), so its span is 2: [(100,1),(80,1),(70,2)]. Then 60 → span 1. 75 pops (60,1) and (70,2) → 1 + 1 + 2 = 4.

## Approaches

### 1. Scan Back Each Day: O(n) per call, O(n) space
Store all prices and walk backwards while ≤ today. O(n²) total in the worst case (rising prices).

### 2. Monotonic Stack of (price, span) ⭐ Go-to: amortised O(1) per call, O(n) space
**Why it's the go-to:** online-friendly, and the "absorb the popped span" trick is reusable.

## Dry Run (Approach 2)

| price | popped | span | stack after |
|-------|--------|------|-------------|
| 100 | – | 1 | [(100,1)] |
| 80 | – | 1 | [(100,1),(80,1)] |
| 60 | – | 1 | […,(60,1)] |
| 70 | (60,1) | 2 | […,(80,1),(70,2)] |
| 60 | – | 1 | […,(70,2),(60,1)] |
| 75 | (60,1),(70,2) | 4 | […,(80,1),(75,4)] |
| 85 | (75,4),(80,1) | **6** | [(100,1),(85,6)] |

## Edge Case Check
- Strictly rising prices → spans 1, 2, 3, … ✅
- Strictly falling prices → all 1. ✅
- Equal prices → included (≤), so spans grow. ✅

## ⚠️ Pitfalls
- **Using `<` instead of `≤`:** equal prices must be absorbed.
- **Storing only prices:** you lose the days already absorbed. Keep the span (or the day index).
- **Recomputing from scratch per call:** O(n²).

## 🎯 What the Interviewer Wants
- Spot that this is "previous greater element".
- Amortised analysis for the online version.

## Follow-ups
- **Look forward instead of back:** [LC 0739 Daily Temperatures](../0739-daily-temperatures/)
- **Next greater values:** [LC 0496 Next Greater Element I](../0496-next-greater-element-i/)
- **Spans both ways as widths:** [LC 0084 Largest Rectangle in Histogram](../0084-largest-rectangle-in-histogram/)
