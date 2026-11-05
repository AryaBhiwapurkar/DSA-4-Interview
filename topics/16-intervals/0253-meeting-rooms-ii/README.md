---
number: 253
title: Meeting Rooms II
difficulty: Medium
topic: Intervals
pattern: Sorted starts/ends or min-heap
link: https://leetcode.com/problems/meeting-rooms-ii/
lists: [NeetCode 150]
followup_of: ["0252 Meeting Rooms"]
related: ["1851 Minimum Interval to Include Each Query", "0732 My Calendar III", "1094 Car Pooling"]
---

# 0253. Meeting Rooms II

## ⚡ 30-Second Summary
**Pattern:** Max overlap of intervals (sweep line / min-heap)
**Key insight:** The answer is the largest number of meetings running at the same moment. Process meetings by start time with a min-heap of end times for rooms in use. If the earliest-ending room is free (`end <= start`), reuse it; otherwise open a new room. The heap size at the end is the answer.
**Go-to:** Sort by start + min-heap of ends, O(n log n) time, O(n) space

## Problem
Given [start, end) meeting times, return the fewest conference rooms needed so that no two overlapping meetings share a room. LC Premium. [LeetCode](https://leetcode.com/problems/meeting-rooms-ii/)

**Examples:**
```
Input:  intervals = [[0,30],[5,10],[15,20]]
Output: 2
Why:    [0,30] needs its own room; [5,10] and [15,20] can share the second one.

Input:  intervals = [[7,10],[2,4]]
Output: 1
Why:    They never overlap.
```

**Constraints:**
- 1 ≤ n ≤ 10⁴, 0 ≤ start < end ≤ 10⁶.
- A meeting ending at t frees its room for one starting at t.

## Hints
<details><summary>Hint 1</summary>
Rephrase it: at the busiest moment, how many meetings are in progress?
</details>
<details><summary>Hint 2</summary>
Handle meetings in order of start time. When one starts, which existing room is the best candidate to reuse?
</details>
<details><summary>Hint 3</summary>
Sort by start; keep a min-heap of end times. For each meeting, if heap.top ≤ start, pop it (that room is free). Push the meeting's end. Return heap size.
</details>

## Clarifying Questions
- Does [1,5] then [5,10] need two rooms? (No, one.)
- Do we need the assignment, or just the count? (Count.)
- Is the input sorted? (No.)

## Example Walkthrough
`[[1,5],[5,10]]`: room 1 takes [1,5] (heap [5]). [5,10] starts at 5 ≥ 5, so pop and reuse → heap [10]. One room. With `<` instead of `<=` you'd open a second one.

## Approaches

### 1. Sweep Line: O(n log n) time, O(n) space
Turn each meeting into (start, +1) and (end, −1), sort, and track the running sum's max. Ends sort before starts at the same time.

### 2. Min-heap of Ends ⭐ Go-to: O(n log n) time, O(n) space
**Why it's the go-to:** it models real rooms, extends naturally to "which room does each meeting get", and is easy to justify.

### 3. Two Sorted Arrays: O(n log n) time, O(n) space
Sort starts and ends separately; for each start, retire every end ≤ it, then add a room. Short, but the "why can I decouple starts from ends" argument needs a sentence.

## Dry Run (Approach 2)
`[[1,10],[2,7],[3,19],[8,12],[10,20],[11,30]]` (sorted by start)

| meeting | heap top ≤ start? | action | heap (ends) |
|---------|-------------------|--------|-------------|
| [1,10] | (empty) | new room | [10] |
| [2,7] | 10 ≤ 2 no | new room | [7, 10] |
| [3,19] | 7 ≤ 3 no | new room | [7, 10, 19] |
| [8,12] | 7 ≤ 8 yes | reuse | [10, 12, 19] |
| [10,20] | 10 ≤ 10 yes | reuse | [12, 19, 20] |
| [11,30] | 12 ≤ 11 no | new room | [12, 19, 20, 30] |

Heap size **4**.

## Edge Case Check
- One meeting → 1. ✅
- Touching meetings → 1. ✅
- All overlapping → n. ✅

## ⚠️ Pitfalls
- **`<` instead of `<=`** for reuse double-counts touching meetings.
- **Sweep line tie order:** at the same time, process ends before starts.
- **Checking the heap before sorting by start:** meetings must be processed in start order, or a free room can be missed.
- **C++ `priority_queue` is a max-heap by default**; use `greater<int>`.

## 🎯 What the Interviewer Wants
- Reframe as "max concurrent meetings".
- Heap version with the reuse condition explained.
- Mention the sweep line / two-array alternative.

## Follow-ups
- **Can one person attend all?** [LC 0252 Meeting Rooms](../0252-meeting-rooms/)
- **Return which room each meeting uses:** keep (end, roomId) in the heap.
- **Capacity instead of count:** LC 1094 Car Pooling (not added yet). Sweep line with weights.
- **Online bookings, max overlap so far:** LC 0732 My Calendar III (not added yet). Sorted map of +1/−1 counts.
