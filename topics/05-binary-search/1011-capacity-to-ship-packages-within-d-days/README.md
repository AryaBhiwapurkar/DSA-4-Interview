---
number: 1011
title: Capacity To Ship Packages Within D Days
difficulty: Medium
topic: Binary Search
pattern: Binary search on the answer + greedy day count
link: https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/
lists: [Interview Extras]
followup_of: ["0875 Koko Eating Bananas"]
related: ["0410 Split Array Largest Sum", "0875 Koko Eating Bananas", "1283 Find the Smallest Divisor Given a Threshold"]
---

# 1011. Capacity To Ship Packages Within D Days

## ⚡ 30-Second Summary
**Pattern:** Smallest capacity that works → binary search on capacity
**Key insight:** For a fixed capacity, load packages in order and start a new day only when the next one doesn't fit. That gives the fewest days possible for that capacity. More capacity never needs more days, so search [max(weights), sum(weights)] for the first capacity that needs ≤ `days` days.
**Go-to:** Binary search on capacity + greedy day count, O(n log sum) time, O(1) space

## Problem
Packages must ship in the given order, one ship per day, and each day's load can't exceed the ship's capacity. Return the smallest capacity that ships everything within `days` days. [LeetCode](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/)

**Examples:**
```
Input:  weights = [1,2,3,4,5,6,7,8,9,10], days = 5
Output: 15
Why:    [1..5] [6,7] [8] [9] [10] works at 15; at 14 the loads need 6 days.

Input:  weights = [3,2,2,4,1,4], days = 3
Output: 6
Why:    [3,2] [2,4] [1,4]; at 5 you need [3,2] [2] [4,1] [4] = 4 days.

Input:  weights = [1,2,3,1,1], days = 4
Output: 3
Why:    Capacity 3 ships [1,2] [3] [1,1] in 3 days; nothing smaller can carry the 3-weight package.
```

**Constraints:**
- 1 ≤ days ≤ n ≤ 5 · 10⁴, 1 ≤ weights[i] ≤ 500. The sum is at most 2.5 · 10⁷, so ints are safe.

## Hints
<details><summary>Hint 1</summary>
If capacity C works, does C + 1 work? What does that say about the set of good capacities?
</details>
<details><summary>Hint 2</summary>
For a given C, the fewest days comes from greedily filling each day before moving on. What are the smallest and largest capacities worth trying?
</details>
<details><summary>Hint 3</summary>
Search C over [max(weights), sum(weights)]. If greedy days(C) ≤ days, then hi = C, otherwise lo = C + 1.
</details>

## Clarifying Questions
- Must packages keep their order? (Yes, which makes each day a contiguous chunk.)
- Can a package be split across days? (No.)
- Is days ≤ n? (Yes, so the empty-day question doesn't come up.)

## Example Walkthrough
`[3,2,2,4,1,4], days = 3`: the capacity lies in [4, 16]. Capacity 5 gives [3,2] [2] [4,1] [4], 4 days: too many. Capacity 6 gives [3,2] [2,4] [1,4], 3 days. Answer 6.

## Approaches

### 1. Try Every Capacity: O(n · (sum − max)) time, O(1) space
Walk C up from max(weights) until the greedy fits. Up to 2.5 · 10⁷ capacities × n: too slow.

### 2. Binary Search on Capacity ⭐ Go-to: O(n log sum) time, O(1) space
Lower-bound search on the monotonic "days(C) ≤ days" predicate.
**Why it's the go-to:** about 25 greedy passes. It's word-for-word LC 410 with "pieces" renamed to "days".

## Dry Run (Approach 2)
`[3,2,2,4,1,4], days = 3`, lo = 4, hi = 16.

| lo | hi | mid | greedy loads | days | ≤ 3? | action |
|----|----|-----|--------------|------|------|--------|
| 4 | 16 | 10 | [3,2,2] [4,1,4] | 2 | yes | hi = 10 |
| 4 | 10 | 7 | [3,2,2] [4,1] [4] | 3 | yes | hi = 7 |
| 4 | 7 | 5 | [3,2] [2] [4,1] [4] | 4 | no | lo = 6 |
| 6 | 7 | 6 | [3,2] [2,4] [1,4] | 3 | yes | hi = 6 |
| 6 | 6 | | | | | return **6** |

## Edge Case Check
- days = 1 → sum(weights). ✅
- days = n → max(weights). ✅
- Single package → its weight. ✅

## ⚠️ Pitfalls
- **lo = 1 instead of max(weights):** a capacity below the heaviest package can never ship it. The greedy then miscounts, because that package forms its own over-full "day".
- **Counting days off by one:** start at 1 day, not 0, and add a day when you cut.
- **`days(C) == days` as the check:** fewer days is also fine; use ≤.

## 🎯 What the Interviewer Wants
- Recognise LC 410 / Koko in disguise.
- Justify the bounds [max, sum] and the greedy.
- O(n log sum) with clean code.

## Follow-ups
- **The same problem stated abstractly:** [LC 0410 Split Array Largest Sum](../0410-split-array-largest-sum/)
- **Per-item hours instead of contiguous loads:** [LC 0875 Koko Eating Bananas](../0875-koko-eating-bananas/)
- **Sum of ceilings check:** [LC 1283 Find the Smallest Divisor Given a Threshold](../1283-find-the-smallest-divisor-given-a-threshold/)
