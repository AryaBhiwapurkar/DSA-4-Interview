---
number: 56
title: Merge Intervals
difficulty: Medium
topic: Intervals
pattern: Sort by start + merge
link: https://leetcode.com/problems/merge-intervals/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0057 Insert Interval", "0252 Meeting Rooms", "0763 Partition Labels"]
---

# 0056. Merge Intervals

## ⚡ 30-Second Summary
**Pattern:** Sort by start, then sweep and merge
**Key insight:** After sorting by start, an interval can only overlap the **last** merged interval, never an earlier one. So: if `start <= last.end`, extend `last.end = max(last.end, end)`; otherwise start a new block.
**Go-to:** Sort + one pass, O(n log n) time, O(n) space

## Problem
Given a list of [start, end] intervals, combine every group of overlapping intervals into one and return the non-overlapping result. Intervals that only touch (end == start) count as overlapping. [LeetCode](https://leetcode.com/problems/merge-intervals/)

**Examples:**
```
Input:  intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Why:    [1,3] and [2,6] overlap on 2..3; the other two stand alone.

Input:  intervals = [[1,4],[4,5]]
Output: [[1,5]]
Why:    They share the point 4, which counts as overlapping.

Input:  intervals = [[4,7],[1,4]]
Output: [[1,7]]
Why:    The input isn't sorted; after sorting it's the same touching case.
```

**Constraints:**
- 1 ≤ n ≤ 10⁴, 0 ≤ start ≤ end ≤ 10⁴.
- Input order is arbitrary.

## Hints
<details><summary>Hint 1</summary>
Overlaps are hard to find in a random order. What order would put overlapping intervals next to each other?
</details>
<details><summary>Hint 2</summary>
After sorting by start, when does the next interval overlap what you've merged so far?
</details>
<details><summary>Hint 3</summary>
Sort by start. For each interval: if res is non-empty and start ≤ res[-1].end, set res[-1].end = max(res[-1].end, end); otherwise append it.
</details>

## Clarifying Questions
- Do touching intervals merge? (Yes, [1,4] and [4,5] → [1,5].)
- Is the input sorted? (No.)
- Can I modify the input? (Sorting in place is usually fine; ask.)
- Output order? (Any, but sorted falls out naturally.)

## Example Walkthrough
`[[1,4],[2,3]]`: sorted already. [2,3] starts at 2 ≤ 4, so it overlaps. Taking max(4, 3) keeps the end at 4. Writing `end = 3` instead would wrongly shrink the block.

## Approaches

### 1. Repeated Pair Merging: O(n³) time, O(n) space
Find any overlapping pair, merge it, repeat until none remain. Shows the idea but is slow.

### 2. Sort + Merge ⭐ Go-to: O(n log n) time, O(n) space
**Why it's the go-to:** the canonical interval template: short, optimal (sorting dominates), and easy to prove.

## Dry Run (Approach 2)
`[[1,3],[2,6],[8,10],[15,18]]`

| interval | overlaps last? | res |
|----------|----------------|-----|
| [1,3] | (empty) | [[1,3]] |
| [2,6] | 2 ≤ 3 yes | [[1,6]] |
| [8,10] | 8 ≤ 6 no | [[1,6],[8,10]] |
| [15,18] | 15 ≤ 10 no | [[1,6],[8,10],[15,18]] |

## Edge Case Check
- One interval → itself. ✅
- Nested `[[1,4],[2,3]]` → [[1,4]] thanks to max. ✅
- Unsorted input `[[4,7],[1,4]]` → [[1,7]]. ✅

## ⚠️ Pitfalls
- **Assigning `end` instead of `max(end, last.end)`** breaks nested intervals.
- **Using `<` instead of `<=`** leaves touching intervals unmerged.
- **Forgetting to sort** (the example inputs often look sorted).
- **C++ comparator returning `a[0] <= b[0]`** violates strict weak ordering; use the default sort or `<`.

## 🎯 What the Interviewer Wants
- Sort by start and explain why only the last block can overlap.
- Nested and touching cases handled without prompting.
- O(n log n) and the space used by the output/sort.

## Follow-ups
- **Insert one interval into a sorted list:** [LC 0057 Insert Interval](../0057-insert-interval/)
- **Do any overlap at all?** [LC 0252 Meeting Rooms](../0252-meeting-rooms/)
- **Intervals hidden in a string:** [LC 0763 Partition Labels](../../15-greedy/0763-partition-labels/)
- **Intervals arrive as a stream:** LC 0352 Data Stream as Disjoint Intervals (not added yet). Keep a sorted map keyed by start.
