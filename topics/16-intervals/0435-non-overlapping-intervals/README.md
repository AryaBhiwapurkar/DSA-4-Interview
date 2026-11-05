---
number: 435
title: Non-overlapping Intervals
difficulty: Medium
topic: Intervals
pattern: Sort by end, greedy
link: https://leetcode.com/problems/non-overlapping-intervals/
lists: [NeetCode 150]
followup_of: []
related: ["0452 Minimum Number of Arrows to Burst Balloons", "0646 Maximum Length of Pair Chain", "0056 Merge Intervals"]
---

# 0435. Non-overlapping Intervals

## ⚡ 30-Second Summary
**Pattern:** Interval scheduling (activity selection)
**Key insight:** Removing the fewest = keeping the most. To keep the most non-overlapping intervals, always keep the one that **ends earliest**: it leaves the most room for the rest. Sort by end, keep an interval if it starts at or after the last kept end, otherwise remove it.
**Go-to:** Sort by end + greedy, O(n log n) time, O(1) extra space

## Problem
Return the minimum number of intervals to delete so that the remaining ones don't overlap. Intervals that only touch ([1,2] and [2,3]) are fine. [LeetCode](https://leetcode.com/problems/non-overlapping-intervals/)

**Examples:**
```
Input:  intervals = [[1,2],[2,3],[3,4],[1,3]]
Output: 1
Why:    Delete [1,3]; the other three line up end to start.

Input:  intervals = [[1,2],[1,2],[1,2]]
Output: 2
Why:    Identical intervals: only one can stay.

Input:  intervals = [[1,2],[2,3]]
Output: 0
Why:    They only touch.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵, so O(n²) DP is too slow.
- Values in [-5·10⁴, 5·10⁴].

## Hints
<details><summary>Hint 1</summary>
Flip it: what's the largest number of intervals you can keep?
</details>
<details><summary>Hint 2</summary>
Among intervals that could come first, which one should you keep so the others have the best chance?
</details>
<details><summary>Hint 3</summary>
Sort by end. Track the end of the last kept interval. If the next starts ≥ that end, keep it and update end; otherwise count a removal.
</details>

## Clarifying Questions
- Touching intervals overlap? (No.)
- Return the count or which to remove? (Count.)
- Negative values? (Yes; the sentinel must be below them.)

## Example Walkthrough
`[[1,100],[11,22],[1,11],[2,12]]` sorted by end: [1,11], [2,12], [11,22], [1,100]. Keep [1,11]; [2,12] overlaps → remove; [11,22] starts at 11 ≥ 11 → keep; [1,100] → remove. Two removals. Sorting by start and keeping the first would pick [1,100] and lose everything else.

## Approaches

### 1. DP (Longest Chain): O(n²) time, O(n) space
Sort by start; keep[i] = 1 + max keep[j] over j with end_j ≤ start_i (LIS-style). Answer n − max(keep).

### 2. Greedy by End ⭐ Go-to: O(n log n) time, O(1) extra
**Why it's the go-to:** the textbook exchange argument (swapping in the earliest-ending interval never hurts) and a five-line loop.

## Dry Run (Approach 2)
`[[1,2],[2,3],[3,4],[1,3]]` sorted by end: [1,2], [2,3], [1,3], [3,4].

| interval | start ≥ end? | action | end | removed |
|----------|--------------|--------|-----|---------|
| [1,2] | yes (−∞) | keep | 2 | 0 |
| [2,3] | 2 ≥ 2 yes | keep | 3 | 0 |
| [1,3] | 1 ≥ 3 no | remove | 3 | 1 |
| [3,4] | 3 ≥ 3 yes | keep | 4 | **1** |

## Edge Case Check
- All identical → n − 1. ✅
- Already disjoint → 0. ✅
- One long interval covering many short ones → remove the long one. ✅

## ⚠️ Pitfalls
- **Sorting by start and keeping greedily** keeps long early intervals; sort by end instead (or, sorting by start, keep the one with the smaller end on overlap).
- **Using `>` instead of `>=`** counts touching intervals as overlaps.
- **Sentinel 0 for the initial end** breaks negative coordinates.
- **C++ comparator with `<=`** is undefined behaviour in `sort`.

## 🎯 What the Interviewer Wants
- Reframe as "max non-overlapping set".
- The earliest-end greedy and why it's optimal.
- Contrast with merge intervals (sort by start).

## Follow-ups
- **Same greedy, overlapping groups share one arrow:** [LC 0452 Minimum Number of Arrows to Burst Balloons](../0452-minimum-number-of-arrows-to-burst-balloons/)
- **Longest chain where b must start strictly after a ends:** LC 0646 Maximum Length of Pair Chain (not added yet)
- **Weighted intervals (maximise total value):** DP + binary search, the greedy no longer works.
