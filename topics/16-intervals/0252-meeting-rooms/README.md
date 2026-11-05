---
number: 252
title: Meeting Rooms
difficulty: Easy
topic: Intervals
pattern: Sort + check overlap
link: https://leetcode.com/problems/meeting-rooms/
lists: [NeetCode 150]
followup_of: []
related: ["0253 Meeting Rooms II", "0056 Merge Intervals"]
---

# 0252. Meeting Rooms

## ⚡ 30-Second Summary
**Pattern:** Sort by start, check adjacent pairs
**Key insight:** After sorting by start, if any meeting overlaps another, it overlaps its **immediate neighbour**. So one pass comparing `cur.start < prev.end` is enough.
**Go-to:** Sort + neighbour check, O(n log n) time, O(1) extra space

## Problem
Meetings are given as [start, end) times. Decide whether a single person can attend every meeting, i.e. no two overlap. A meeting ending at t and another starting at t don't conflict. LC Premium. [LeetCode](https://leetcode.com/problems/meeting-rooms/)

**Examples:**
```
Input:  intervals = [[0,30],[5,10],[15,20]]
Output: false
Why:    [0,30] covers both of the others.

Input:  intervals = [[7,10],[2,4]]
Output: true
Why:    After sorting, [2,4] ends before [7,10] starts.
```

**Constraints:**
- 0 ≤ n ≤ 10⁴, 0 ≤ start < end ≤ 10⁶.
- Touching (end == next start) is **not** a conflict.

## Hints
<details><summary>Hint 1</summary>
Checking every pair works. What ordering would let you check far fewer pairs?
</details>
<details><summary>Hint 2</summary>
If meetings are sorted by start time, which meeting could the next one possibly clash with?
</details>
<details><summary>Hint 3</summary>
Sort by start. For i ≥ 1, if intervals[i].start < intervals[i-1].end, return false. Otherwise true.
</details>

## Clarifying Questions
- Is end exclusive, so [1,2] and [2,3] are fine? (Yes.)
- Empty list? (True.)
- Sorted input? (No.)

## Example Walkthrough
`[[5,8],[6,8]]`: sorted already. 6 < 8, so the second meeting starts before the first ends → false.

## Approaches

### 1. Every Pair: O(n²) time, O(1) space
Two intervals overlap iff `a.start < b.end && b.start < a.end`.

### 2. Sort + Neighbours ⭐ Go-to: O(n log n) time, O(1) extra
**Why it's the go-to:** the standard interval opener; it sets up Meeting Rooms II.

## Dry Run (Approach 2)
`[[0,30],[5,10],[15,20]]` (already sorted)

| i | prev | cur | cur.start < prev.end? |
|---|------|-----|------------------------|
| 1 | [0,30] | [5,10] | 5 < 30 → **false** |

## Edge Case Check
- Empty or single meeting → true. ✅
- Touching `[[1,2],[2,3]]` → 2 < 2 is false → true. ✅
- Same end, overlapping start (`[[5,8],[6,8]]`) → false. ✅

## ⚠️ Pitfalls
- **Using `<=`** marks touching meetings as conflicts.
- **Skipping the sort:** the neighbour check is only valid on input sorted by start.
- **Sorting by end** works here too, but stick to start; it's the setup for LC 56/57.

## 🎯 What the Interviewer Wants
- Sort, then a single adjacent comparison, with the reason it suffices.
- Correct handling of touching intervals.
- A smooth transition to "how many rooms?" (LC 253).

## Follow-ups
- **Minimum rooms needed:** [LC 0253 Meeting Rooms II](../0253-meeting-rooms-ii/)
- **Merge the overlaps instead:** [LC 0056 Merge Intervals](../0056-merge-intervals/)
