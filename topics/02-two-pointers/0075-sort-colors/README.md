---
number: 75
title: Sort Colors
difficulty: Medium
topic: Two Pointers
pattern: Dutch national flag (three-way partition)
link: https://leetcode.com/problems/sort-colors/
lists: [Interview Extras]
followup_of: []
related: ["0283 Move Zeroes", "0215 Kth Largest Element in an Array", "0905 Sort Array By Parity"]
---

# 0075. Sort Colors

## ⚡ 30-Second Summary
**Pattern:** Dutch national flag: three regions, three pointers
**Key insight:** Keep `[0, lo)` all 0s, `[lo, mid)` all 1s and `(hi, n−1]` all 2s; `[mid, hi]` is still unknown. Look at nums[mid]. A 0 is swapped to lo and both pointers advance. A 1 just advances mid. A 2 is swapped to hi and hi shrinks, but mid **stays**, because the value swapped in hasn't been examined yet.
**Go-to:** One-pass three pointers, O(n) time, O(1) space

## Problem
An array holds only 0, 1 and 2 (red, white, blue). Sort it in place so equal values are grouped in the order 0, 1, 2, without using a library sort. Follow-up: one pass, constant space. [LeetCode](https://leetcode.com/problems/sort-colors/)

**Examples:**
```
Input:  nums = [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]
Why:    Two of each color, grouped in order.

Input:  nums = [2,0,1]
Output: [0,1,2]
Why:    One of each.
```

**Constraints:**
- 1 ≤ n ≤ 300; values only 0, 1, 2.
- In place; follow-up asks for a single pass with O(1) space.

## Hints
<details><summary>Hint 1</summary>
Counting sort works in two passes. Can you instead grow the 0-region from the left and the 2-region from the right?
</details>
<details><summary>Hint 2</summary>
Track three boundaries. What should happen for each of the three values at the scanning pointer?
</details>
<details><summary>Hint 3</summary>
lo = mid = 0, hi = n − 1. While mid ≤ hi: 0 → swap(lo, mid), lo++, mid++. 1 → mid++. 2 → swap(mid, hi), hi−− (mid stays).
</details>

## Clarifying Questions
- Only 0, 1, 2? (Yes.)
- In place, no library sort? (Yes.)
- One pass required? (That's the follow-up; counting sort is the two-pass answer.)

## Example Walkthrough
`[2,0,1]`: mid sees 2 → swap with hi → [1,0,2], hi = 1. mid sees 1 → mid = 1. mid sees 0 → swap with lo → [0,1,2], lo = 1, mid = 2 > hi → stop.

## Approaches

### 1. Counting Sort: O(n) time, O(1) space, two passes
Count the 0s, 1s and 2s, then overwrite. Simple and correct, but two passes.

### 2. Dutch National Flag ⭐ Go-to: O(n) time, O(1) space, one pass
**Why it's the go-to:** it meets the follow-up, and three-way partitioning is reused in quicksort (handling duplicates) and in quickselect.

## Dry Run (Approach 2)
`[2,0,2,1,1,0]`

| lo | mid | hi | nums[mid] | action | array |
|----|-----|----|-----------|--------|-------|
| 0 | 0 | 5 | 2 | swap mid/hi, hi−− | [0,0,2,1,1,2] |
| 0 | 0 | 4 | 0 | swap lo/mid, lo++, mid++ | [0,0,2,1,1,2] |
| 1 | 1 | 4 | 0 | swap lo/mid, lo++, mid++ | [0,0,2,1,1,2] |
| 2 | 2 | 4 | 2 | swap mid/hi, hi−− | [0,0,1,1,2,2] |
| 2 | 2 | 3 | 1 | mid++ | |
| 2 | 3 | 3 | 1 | mid++ | **[0,0,1,1,2,2]** |

## Edge Case Check
- One color only → pointers sweep without swapping (except harmless self-swaps). ✅
- Already sorted → unchanged. ✅
- n = 1 → unchanged. ✅

## ⚠️ Pitfalls
- **Advancing mid after a swap with hi:** the swapped-in value is unexamined and could be a 0 or a 2.
- **Loop condition `mid < hi`:** misses the last unknown element. Use `≤`.
- **Advancing only lo (not mid) on a 0:** mid then falls behind lo, so the region invariants break.

## 🎯 What the Interviewer Wants
- The invariant for the four regions, stated clearly.
- The asymmetry: mid moves after a 0-swap but not after a 2-swap, with the reason.
- One pass, O(1) space.

## Follow-ups
- **Two-way partition:** [LC 0283 Move Zeroes](../0283-move-zeroes/)
- **k colors:** counting sort in O(n + k), or recursive partitioning in O(n log k).
- **Three-way partition inside quickselect:** [LC 0215 Kth Largest Element in an Array](../../09-heap-priority-queue/0215-kth-largest-element-in-an-array/)
