---
number: 35
title: Search Insert Position
difficulty: Easy
topic: Binary Search
pattern: Lower bound
link: https://leetcode.com/problems/search-insert-position/
lists: [LC Top Interview 150]
followup_of: ["0704 Binary Search"]
related: ["0034 Find First and Last Position of Element in Sorted Array", "0278 First Bad Version"]
---

# 0035. Search Insert Position

## ⚡ 30-Second Summary
**Pattern:** Lower bound (first index with nums[i] ≥ target)
**Key insight:** "Index of target, or where it would be inserted" is exactly the first position whose value is ≥ target. Search a half-open window [lo, hi) and never discard a candidate that could be that position.
**Go-to:** Lower-bound binary search, O(log n) time, O(1) space

## Problem
Given a sorted array of distinct integers and a target, return the target's index if present, otherwise the index where it would be inserted to keep the array sorted. Must be O(log n). [LeetCode](https://leetcode.com/problems/search-insert-position/)

**Examples:**
```
Input:  nums = [1,3,5,6], target = 5
Output: 2
Why:    5 is at index 2.

Input:  nums = [1,3,5,6], target = 2
Output: 1
Why:    2 belongs between 1 and 3.

Input:  nums = [1,3,5,6], target = 7
Output: 4
Why:    Larger than everything, so it goes at the end (index n).
```

**Constraints:**
- 1 ≤ n ≤ 10⁴; distinct, sorted ascending.
- The answer can be n, so the search range is [0, n], not [0, n-1].

## Hints
<details><summary>Hint 1</summary>
Rephrase: you want the first index whose value is not less than the target.
</details>
<details><summary>Hint 2</summary>
If nums[mid] ≥ target, mid might be the answer. Don't throw it away.
</details>
<details><summary>Hint 3</summary>
lo = 0, hi = n. While lo < hi: if nums[mid] < target, lo = mid + 1, else hi = mid. Return lo.
</details>

## Clarifying Questions
- Distinct values? (Yes. With duplicates, lower bound still returns the first match.)
- Can the answer be n? (Yes, when target is larger than all.)

## Example Walkthrough
`[1,3,5,6], target 2`
- lo 0, hi 4: mid 2 → 5 ≥ 2, hi = 2.
- mid 1 → 3 ≥ 2, hi = 1.
- mid 0 → 1 < 2, lo = 1. lo == hi, return 1.

## Approaches

### 1. Linear Scan: O(n) time, O(1) space
Return the first i with nums[i] ≥ target, else n.

### 2. Lower Bound ⭐ Go-to: O(log n) time, O(1) space
Half-open [lo, hi) with hi = n; `hi = mid` keeps mid as a candidate.
**Why it's the go-to:** one template that also answers "first ≥", "first >" (upper bound) and "count < x".

## Dry Run (Approach 2)
`[1,3,5,6], target 7`

| lo | hi | mid | nums[mid] | < 7? | action |
|----|----|-----|-----------|------|--------|
| 0 | 4 | 2 | 5 | yes | lo = 3 |
| 3 | 4 | 3 | 6 | yes | lo = 4 |
| 4 | 4 | | | | return **4** |

## Edge Case Check
- Target smaller than all: hi shrinks to 0, return 0. ✅
- Target larger than all: return n (hi starts at n for this). ✅
- Target present: lower bound lands on it. ✅

## ⚠️ Pitfalls
- **hi = n - 1** makes "insert at the end" impossible to return.
- **`lo <= hi` with `hi = mid`** loops forever when lo == hi.
- **Mixing templates**: half-open goes with `lo < hi` and `hi = mid`; inclusive goes with `lo <= hi` and `hi = mid - 1`.

## 🎯 What the Interviewer Wants
- Recognize it as lower bound and say so.
- A clean invariant: everything left of lo is < target, everything at or right of hi is ≥ target.
- Library knowledge: `lower_bound`, `bisect_left`, `sort.SearchInts`.

## Follow-ups
- **Exact match only:** [LC 0704 Binary Search](../0704-binary-search/)
- **First and last occurrence with duplicates:** [LC 0034 Find First and Last Position](../0034-find-first-and-last-position-of-element-in-sorted-array/)
- **Same template on a predicate:** LC 0278 First Bad Version (not added yet)
