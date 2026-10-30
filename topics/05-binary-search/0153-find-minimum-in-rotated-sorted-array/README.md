---
number: 153
title: Find Minimum in Rotated Sorted Array
difficulty: Medium
topic: Binary Search
pattern: Compare mid with right
link: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0033 Search in Rotated Sorted Array", "0154 Find Minimum in Rotated Sorted Array II", "0162 Find Peak Element"]
---

# 0153. Find Minimum in Rotated Sorted Array

## ⚡ 30-Second Summary
**Pattern:** Binary search comparing mid with the right end
**Key insight:** If nums[mid] > nums[hi], the drop (where the minimum lives) is strictly to the right of mid. Otherwise mid..hi is sorted, so the minimum is at mid or to its left. Keep mid in the range in that case.
**Go-to:** Binary search with `nums[mid] > nums[hi]`, O(log n) time, O(1) space

## Problem
A sorted array of distinct integers was rotated some number of times (possibly 0 or n). Return its minimum element in O(log n).

**Examples:**
```
Input:  nums = [3,4,5,1,2]
Output: 1
Why:    The original [1,2,3,4,5] was rotated 3 times.

Input:  nums = [4,5,6,7,0,1,2]
Output: 0
Why:    The drop from 7 to 0 marks the start of the original array.

Input:  nums = [11,13,15,17]
Output: 11
Why:    Rotated n times, it's sorted again, so the minimum is first.
```

**Constraints:**
- 1 ≤ n ≤ 5000; all values distinct.
- O(log n) required.

## Hints
<details><summary>Hint 1</summary>
A rotated sorted array is two sorted runs. Where is the minimum relative to them?
</details>
<details><summary>Hint 2</summary>
Compare nums[mid] with nums[hi]. Which outcome means the drop is on the right?
</details>
<details><summary>Hint 3</summary>
lo = 0, hi = n-1, while lo < hi: if nums[mid] > nums[hi], lo = mid + 1, else hi = mid. Return nums[lo].
</details>

## Clarifying Questions
- Distinct values? (Yes. With duplicates it's LC 0154 and worst case O(n).)
- Can it be unrotated? (Yes, then the answer is nums[0].)
- Return the value or the index? (Value; the index is the rotation count.)

## Example Walkthrough
`[4,5,6,7,0,1,2]`
- lo 0, hi 6, mid 3: 7 > 2, so the drop is right: lo = 4.
- mid 5: 1 > 2? No, so mid..hi is sorted: hi = 5.
- mid 4: 0 > 1? No: hi = 4. lo == hi → nums[4] = 0.

## Approaches

### 1. Linear Scan: O(n) time, O(1) space
min(nums), or find the one index where nums[i] > nums[i+1].

### 2. Binary Search vs Right End ⭐ Go-to: O(log n) time, O(1) space
Compare with nums[hi], keep mid when it might be the minimum.
**Why it's the go-to:** comparing with hi has no special case for the unrotated array (comparing with lo does).

## Dry Run (Approach 2)
`[3,4,5,1,2]`

| lo | hi | mid | nums[mid] | nums[hi] | mid > hi? | action |
|----|----|-----|-----------|----------|-----------|--------|
| 0 | 4 | 2 | 5 | 2 | yes | lo = 3 |
| 3 | 4 | 3 | 1 | 2 | no | hi = 3 |
| 3 | 3 | | | | | return **1** |

## Edge Case Check
- Not rotated `[11,13,15,17]`: never nums[mid] > nums[hi], hi walks to 0. ✅
- Two elements `[2,1]`: mid 0, 2 > 1 → lo = 1 → 1. ✅
- Single element: loop skipped. ✅

## ⚠️ Pitfalls
- **Comparing with nums[lo]**: for an unrotated array, nums[mid] ≥ nums[lo] would push you right, away from the minimum at index 0.
- **hi = mid - 1 when nums[mid] ≤ nums[hi]**: mid itself might be the minimum.
- **`lo <= hi` with `hi = mid`**: infinite loop.

## 🎯 What the Interviewer Wants
- The "which half contains the drop" argument.
- Why comparing with the right end avoids the unrotated special case.
- Know that duplicates (0154) degrade it to O(n) worst case (`hi--` when equal).

## Follow-ups
- **Search a target in the rotated array:** [LC 0033 Search in Rotated Sorted Array](../0033-search-in-rotated-sorted-array/)
- **With duplicates:** when nums[mid] == nums[hi], do hi--: LC 0154 Find Minimum in Rotated Sorted Array II (not added yet)
- **How many times was it rotated?** The index of the minimum.
- **Same "compare with a neighbour" idea:** [LC 0162 Find Peak Element](../0162-find-peak-element/)
