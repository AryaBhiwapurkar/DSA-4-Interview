---
number: 57
title: Insert Interval
difficulty: Medium
topic: Intervals
pattern: Merge on the fly
link: https://leetcode.com/problems/insert-interval/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: ["0056 Merge Intervals"]
related: ["0252 Meeting Rooms", "0715 Range Module"]
---

# 0057. Insert Interval

## ⚡ 30-Second Summary
**Pattern:** Linear merge into an already-sorted list
**Key insight:** The list is sorted and disjoint, so it splits into three runs: intervals that end before the new one starts (copy), intervals that overlap it (absorb into one by widening start/end), and intervals that start after it ends (copy).
**Go-to:** Three-phase scan, O(n) time, O(n) space for the output

## Problem
You have a sorted list of non-overlapping intervals and one new interval. Add the new one, merging anything it overlaps, and return the list, still sorted and non-overlapping. [LeetCode](https://leetcode.com/problems/insert-interval/)

**Examples:**
```
Input:  intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]
Why:    [2,5] overlaps [1,3] and widens it to [1,5]; [6,9] is untouched.

Input:  intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Why:    [4,8] touches [3,5], [6,7] and [8,10], which all collapse into [3,10].
```

**Constraints:**
- 0 ≤ n ≤ 10⁴. **The list can be empty.**
- The input is sorted by start and non-overlapping.

## Hints
<details><summary>Hint 1</summary>
LC 56 would work after appending and sorting. What does the sorted input let you skip?
</details>
<details><summary>Hint 2</summary>
Which intervals can't possibly touch the new one? Where are they in the list?
</details>
<details><summary>Hint 3</summary>
Copy intervals with end < new.start. Then, while start ≤ new.end, absorb: new.start = min, new.end = max. Append the merged new interval, then copy the rest.
</details>

## Clarifying Questions
- Is the input sorted and disjoint? (Yes.)
- Do touching intervals merge? (Yes: [1,5] and [5,7] → [1,7].)
- Empty list? (Return [newInterval].)
- Modify in place or return new? (Return new.)

## Example Walkthrough
`[[3,5]], [1,2]`: phase 1 copies nothing (5 < 1 is false). Phase 2: 3 ≤ 2 is false, so nothing overlaps. Append [1,2], then copy [3,5]. The new interval lands at the front.

## Approaches

### 1. Append + Sort + Merge: O(n log n) time, O(n) space
Reuse LC 56. Correct, but it ignores that the input is already sorted.

### 2. Three Phases ⭐ Go-to: O(n) time, O(n) space
**Why it's the go-to:** linear, and the three loops read exactly like the explanation.

## Dry Run (Approach 2)
`[[1,2],[3,5],[6,7],[8,10],[12,16]]`, new = [4,8]

| phase | interval | test | [s, e] | res |
|-------|----------|------|--------|-----|
| before | [1,2] | 2 < 4 | [4,8] | [[1,2]] |
| overlap | [3,5] | 3 ≤ 8 | [3,8] | |
| overlap | [6,7] | 6 ≤ 8 | [3,8] | |
| overlap | [8,10] | 8 ≤ 8 | [3,10] | |
| stop | [12,16] | 12 ≤ 10? no | | [[1,2],[3,10]] |
| after | [12,16] | | | [[1,2],[3,10],[12,16]] |

## Edge Case Check
- Empty list → [[5,7]]. ✅
- New interval after everything (`[[1,5]], [6,8]`) → appended at the end. ✅
- New interval before everything (`[[3,5]], [1,2]`) → placed first. ✅

## ⚠️ Pitfalls
- **Strict vs non-strict comparisons:** phase 1 uses `end < s`, phase 2 uses `start <= e`, so touching intervals merge.
- **Forgetting to append the merged interval** when nothing overlapped.
- **Erasing/inserting in the input vector mid-loop** costs O(n) per operation and shifts indices; build a new result instead.
- **C++ `new` is a keyword**; name the parameter something else.

## 🎯 What the Interviewer Wants
- Use the sorted input for O(n) instead of re-sorting.
- Clean handling of empty, front and back inserts.
- Explain the three phases before coding.

## Follow-ups
- **Unsorted input, merge everything:** [LC 0056 Merge Intervals](../0056-merge-intervals/)
- **Add/remove/query ranges repeatedly:** LC 0715 Range Module (not added yet). Sorted map of intervals.
- **Insert many intervals:** append all, sort once, merge (LC 56).
