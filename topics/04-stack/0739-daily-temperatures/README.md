---
number: 739
title: Daily Temperatures
difficulty: Medium
topic: Stack
pattern: Monotonic decreasing stack
link: https://leetcode.com/problems/daily-temperatures/
lists: [NeetCode 150]
followup_of: []
related: ["0496 Next Greater Element I", "0503 Next Greater Element II", "0084 Largest Rectangle in Histogram", "0901 Online Stock Span"]
---

# 0739. Daily Temperatures

## ⚡ 30-Second Summary
**Pattern:** Monotonic decreasing stack (next greater element)
**Key insight:** Keep the indices of days that are still waiting for a warmer day. Their temperatures are decreasing from bottom to top (a warmer day would have resolved the cooler ones). A new day resolves every waiting day it beats, popping from the top.
**Go-to:** Monotonic stack of indices, O(n) time, O(n) space

## Problem
For each day, return how many days you must wait for a strictly warmer temperature, or 0 if none comes.

**Examples:**
```
Input:  temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]
Why:    For 75 (day 2) the next warmer day is 76 on day 6, four days later.
        76 and the last 73 never see anything warmer.

Input:  temperatures = [30,40,50,60]
Output: [1,1,1,0]
Why:    Strictly rising: each day's answer is the next day.

Input:  temperatures = [30,60,90]
Output: [1,1,0]
Why:    Same idea, the last day has no future.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵, so O(n²) is too slow in the worst case.
- 30 ≤ temperature ≤ 100 (small range: enables a backward-jump trick).

## Hints
<details><summary>Hint 1</summary>
Brute force scans forward from every day. Which days are "unresolved" at any moment while you scan left to right?
</details>
<details><summary>Hint 2</summary>
Take two unresolved days j < k. If temp[k] > temp[j], day k would already have resolved j. So the unresolved days have non-increasing temperatures, and a new day resolves them starting from the most recent one.
</details>
<details><summary>Hint 3</summary>
Stack of indices. For each day i, while temp[i] > temp[top], pop top and set answer[top] = i - top. Then push i.
</details>

## Clarifying Questions
- Strictly warmer or warmer-or-equal? (Strictly.)
- What if no warmer day exists? (0.)
- Range of n and temperatures? (n up to 10⁵; temperatures 30..100.)

## Example Walkthrough
`[73,74,75,71,69,72,76,73]`
- 73 waits; 74 resolves it (1). 75 resolves 74 (1).
- 71, 69 wait under 75. 72 resolves 69 (1) and 71 (2), but not 75.
- 76 resolves 72 and 75 (6 - 2 = 4). 73 waits. Leftovers 76 and 73 get 0.

## Approaches

### 1. Brute Force: O(n²) time, O(1) extra space
For each day, scan forward to the first warmer day.

### 2. Monotonic Stack ⭐ Go-to: O(n) time, O(n) space
Each index is pushed and popped once; the answer is filled at pop time.
**Why it's the go-to:** the standard "next greater element" template; linear and short.

## Dry Run (Approach 2)
`temperatures = [73,74,75,71,69,72,76,73]` (stack shows index:temp)

| i | temp | pops (answer set) | stack after |
|---|------|-------------------|-------------|
| 0 | 73 | - | 0:73 |
| 1 | 74 | 0 → 1 | 1:74 |
| 2 | 75 | 1 → 1 | 2:75 |
| 3 | 71 | - | 2:75, 3:71 |
| 4 | 69 | - | 2:75, 3:71, 4:69 |
| 5 | 72 | 4 → 1, 3 → 2 | 2:75, 5:72 |
| 6 | 76 | 5 → 1, 2 → 4 | 6:76 |
| 7 | 73 | - | 6:76, 7:73 |
| end | | leftovers stay 0 | |

## Edge Case Check
- Strictly decreasing `[5,4,3]`: nothing pops, all 0. ✅
- Equal temps `[70,70]`: equal does not resolve (strictly warmer), both 0. ✅
- Single day: [0]. ✅

## ⚠️ Pitfalls
- **Storing temperatures instead of indices**: you need the index to compute the distance.
- **`>=` instead of `>` when popping**: treats equal as warmer.
- **Forgetting the initial zeros**: unresolved days must end as 0, so initialize the answer with 0.
- **Python: `while st and ...`**: check non-empty before reading `st[-1]`.

## 🎯 What the Interviewer Wants
- Name it as "next greater element" and explain the decreasing invariant.
- Amortized O(n): each index pushed once, popped at most once.
- Optional: the O(1)-space backward pass that jumps using already-computed answers.

## Follow-ups
- **Next greater in a second array:** LC 0496 Next Greater Element I (not added yet)
- **Circular array:** loop twice (i mod n): LC 0503 Next Greater Element II (not added yet)
- **Previous smaller on both sides:** [LC 0084 Largest Rectangle in Histogram](../0084-largest-rectangle-in-histogram/)
- **Streaming version (span of past days):** LC 0901 Online Stock Span (not added yet)
- **O(1) extra space:** go right to left; from day i jump j = i+1, then j += ans[j] until temp[j] > temp[i].
