---
number: 704
title: Binary Search
difficulty: Easy
topic: Binary Search
pattern: Classic binary search
link: https://leetcode.com/problems/binary-search/
lists: [NeetCode 150]
followup_of: []
related: ["0035 Search Insert Position", "0034 Find First and Last Position of Element in Sorted Array", "0074 Search a 2D Matrix"]
---

# 0704. Binary Search

## ⚡ 30-Second Summary
**Pattern:** Classic binary search on a sorted array
**Key insight:** In a sorted array, one comparison with the middle element rules out half of the remaining range. Keep an inclusive window [lo, hi] that always contains the target if it exists.
**Go-to:** Iterative binary search, O(log n) time, O(1) space

## Problem
Given a sorted array of distinct integers and a target, return the target's index or -1. The solution must be O(log n).

**Examples:**
```
Input:  nums = [-1,0,3,5,9,12], target = 9
Output: 4
Why:    9 sits at index 4.

Input:  nums = [-1,0,3,5,9,12], target = 2
Output: -1
Why:    2 would go between 0 and 3, but it isn't there.
```

**Constraints:**
- 1 ≤ n ≤ 10⁴; values distinct and sorted ascending.
- Values and target in ±10⁴.

## Hints
<details><summary>Hint 1</summary>
Compare the target with the middle element. What does each outcome tell you?
</details>
<details><summary>Hint 2</summary>
If nums[mid] < target, nothing at or left of mid can be the answer. Which bound moves, and to where?
</details>
<details><summary>Hint 3</summary>
Use lo = 0, hi = n - 1, loop while lo ≤ hi; on less move lo = mid + 1, on greater move hi = mid - 1, on equal return mid.
</details>

## Clarifying Questions
- Is the array sorted ascending? Are values distinct? (Yes and yes.)
- What to return if missing? (-1.)
- Empty array possible? (No, n ≥ 1.)

## Example Walkthrough
`nums = [-1,0,3,5,9,12], target = 9`
- lo 0, hi 5, mid 2 → 3 < 9, so lo = 3.
- mid 4 → 9 == 9, return 4.

## Approaches

### 1. Linear Scan: O(n) time, O(1) space
Check every element. Correct but ignores the sorted order.

### 2. Iterative Binary Search ⭐ Go-to: O(log n) time, O(1) space
Inclusive [lo, hi], `while lo <= hi`, shrink past mid on each miss.
**Why it's the go-to:** it's the template for everything else in this topic; iterative avoids recursion overhead.

## Dry Run (Approach 2)
`nums = [-1,0,3,5,9,12], target = 2`

| lo | hi | mid | nums[mid] | compare | action |
|----|----|-----|-----------|---------|--------|
| 0 | 5 | 2 | 3 | 3 > 2 | hi = 1 |
| 0 | 1 | 0 | -1 | -1 < 2 | lo = 1 |
| 1 | 1 | 1 | 0 | 0 < 2 | lo = 2 |
| 2 | 1 | | | lo > hi | return **-1** |

## Edge Case Check
- Single element, found / not found: one iteration either way. ✅
- Target smaller than everything: hi walks below 0, return -1. ✅
- Target larger than everything: lo walks to n, return -1. ✅

## ⚠️ Pitfalls
- **`lo < hi` with inclusive bounds** misses the last candidate (single-element ranges).
- **`hi = mid` or `lo = mid`** with `lo <= hi` can loop forever. With inclusive bounds always move past mid.
- **Overflow in `(lo + hi) / 2`** in C++/Java for large indices. Use `lo + (hi - lo) / 2`.
- **C++ `size_t hi = n - 1`** underflows when `hi = mid - 1` with mid = 0. Use `int`.

## 🎯 What the Interviewer Wants
- Bug-free bounds and a stated loop invariant ("target, if present, is in [lo, hi]").
- The overflow-safe midpoint.
- Knowing the library equivalents: `lower_bound`, `bisect_left`, `sort.SearchInts`.

## Follow-ups
- **Return the insert position if missing:** [LC 0035 Search Insert Position](../0035-search-insert-position/)
- **With duplicates, first and last index:** [LC 0034 Find First and Last Position](../0034-find-first-and-last-position-of-element-in-sorted-array/)
- **Sorted 2-D matrix:** [LC 0074 Search a 2D Matrix](../0074-search-a-2d-matrix/)
- **Unknown size (reader API):** double hi until reader.get(hi) ≥ target, then search: LC 0702 Search in a Sorted Array of Unknown Size (not added yet)
