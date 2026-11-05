---
number: 1851
title: Minimum Interval to Include Each Query
difficulty: Hard
topic: Intervals
pattern: Sort queries + min-heap
link: https://leetcode.com/problems/minimum-interval-to-include-each-query/
lists: [NeetCode 150]
followup_of: []
related: ["0253 Meeting Rooms II", "0218 The Skyline Problem", "2251 Number of Flowers in Full Bloom"]
---

# 1851. Minimum Interval to Include Each Query

## ⚡ 30-Second Summary
**Pattern:** Offline queries + sweep + min-heap
**Key insight:** Answer the queries in **sorted order** (remember their original positions). As q grows, push every interval whose left ≤ q into a min-heap keyed by size. Lazily pop intervals whose right < q: they can't contain this q or any later one. The heap top is the answer.
**Go-to:** Sorted intervals + sorted queries + min-heap, O((n + q) log(n + q)) time

## Problem
Each interval [left, right] has size right − left + 1. For every query value, find the size of the smallest interval that contains it, or −1 if none does. Return answers in the original query order. [LeetCode](https://leetcode.com/problems/minimum-interval-to-include-each-query/)

**Examples:**
```
Input:  intervals = [[1,4],[2,4],[3,6],[4,4]], queries = [2,3,4,5]
Output: [3,3,1,4]
Why:    2 and 3 are best served by [2,4] (size 3); 4 sits in [4,4] (size 1); only [3,6] reaches 5.

Input:  intervals = [[2,3],[2,5],[1,8],[20,25]], queries = [2,19,5,22]
Output: [2,-1,4,6]
Why:    19 falls in the gap between 8 and 20, so it gets -1.
```

**Constraints:**
- 1 ≤ n, q ≤ 10⁵, so O(n·q) = 10¹⁰ is far too slow.
- Values up to 10⁷.

## Hints
<details><summary>Hint 1</summary>
Queries can be answered in any order as long as you put the answers back in place. Which order makes the problem easier?
</details>
<details><summary>Hint 2</summary>
With queries increasing, the set of intervals that have "started" only grows. Intervals that have "ended" stay ended. What structure gives you the smallest valid one quickly?
</details>
<details><summary>Hint 3</summary>
Sort intervals by left and queries by value (keep indices). For each q: push (size, right) for all intervals with left ≤ q; pop while top.right < q; answer = top.size or -1.
</details>

## Clarifying Questions
- Endpoints inclusive? (Yes.)
- Duplicate queries? (Possible; each gets its own answer.)
- Answer order? (Original query order.)

## Example Walkthrough
Example 2, queries sorted: 2, 5, 19, 22. At 2: [1,8] and both [2,·] are pushed; smallest is [2,3] (2). At 5: [2,3] has ended, so pop it; [2,5] (4) is on top. At 19: everything left has ended → −1. At 22: [20,25] (6).

## Approaches

### 1. Brute Force: O(n·q) time, O(1) extra
For each query, scan every interval. Fine for small inputs, a baseline only.

### 2. Offline Sweep + Min-heap ⭐ Go-to: O((n + q) log(n + q)) time, O(n + q) space
Each interval is pushed and popped at most once.
**Why it's the go-to:** it's the standard "offline queries" technique, and the lazy deletion argument (an ended interval is useless for every later query) is short.

## Dry Run (Approach 2)
Example 1. Intervals sorted: [1,4], [2,4], [3,6], [4,4]. Heap entries are (size, right).

| q | pushed | popped (right < q) | heap top | answer |
|---|--------|--------------------|----------|--------|
| 2 | (4,4), (3,4) | none | (3,4) | 3 |
| 3 | (4,6) | none | (3,4) | 3 |
| 4 | (1,4) | none | (1,4) | 1 |
| 5 | none | (1,4), (3,4), (4,4) | (4,6) | 4 |

## Edge Case Check
- Query in a gap → −1. ✅
- Query on an endpoint (`[5,10]`, q = 5 or 10) → 6. ✅
- Query before every interval → −1 (nothing pushed). ✅

## ⚠️ Pitfalls
- **Popping only the top once:** keep popping while the top has ended.
- **Removing ended intervals eagerly** from the middle of the heap is unnecessary; lazy deletion is enough because queries only increase.
- **Losing the original order** of queries; sort indices, not values.
- **Keying the heap by right end** instead of size gives the wrong "smallest".

## 🎯 What the Interviewer Wants
- Recognise offline processing (sort the queries).
- Sweep + heap with lazy deletion, and its O((n + q) log) bound.
- Clean index bookkeeping for the answers.

## Follow-ups
- **Max concurrent intervals, same sweep:** [LC 0253 Meeting Rooms II](../0253-meeting-rooms-ii/)
- **Count intervals covering each query:** LC 2251 Number of Flowers in Full Bloom (not added yet). Binary search on sorted starts/ends.
- **Heap-driven sweep over heights:** LC 0218 The Skyline Problem (not added yet)
- **Online queries:** a segment tree over compressed coordinates storing the min size.
