---
number: 33
title: Search in Rotated Sorted Array
difficulty: Medium
topic: Binary Search
pattern: Find the sorted half
link: https://leetcode.com/problems/search-in-rotated-sorted-array/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: ["0153 Find Minimum in Rotated Sorted Array"]
related: ["0153 Find Minimum in Rotated Sorted Array", "0081 Search in Rotated Sorted Array II", "0704 Binary Search"]
---

# 0033. Search in Rotated Sorted Array

## ⚡ 30-Second Summary
**Pattern:** Find the sorted half
**Key insight:** Any mid splits a rotated array into two halves, and at least one of them is sorted. Check whether the target lies inside the sorted half's range; if yes go there, otherwise go to the other half.
**Go-to:** One-pass binary search on the sorted half, O(log n) time, O(1) space

## Problem
A sorted array of distinct integers was rotated at an unknown pivot. Return the index of a target, or -1, in O(log n). [LeetCode](https://leetcode.com/problems/search-in-rotated-sorted-array/)

**Examples:**
```
Input:  nums = [4,5,6,7,0,1,2], target = 0
Output: 4
Why:    0 sits right after the rotation point, at index 4.

Input:  nums = [4,5,6,7,0,1,2], target = 3
Output: -1
Why:    3 isn't in the array.

Input:  nums = [1], target = 0
Output: -1
Why:    Single element, not the target.
```

**Constraints:**
- 1 ≤ n ≤ 5000; values distinct.
- O(log n) required.

## Hints
<details><summary>Hint 1</summary>
At any mid, is it possible for both halves [lo, mid] and [mid, hi] to be unsorted?
</details>
<details><summary>Hint 2</summary>
No: the rotation point is in at most one of them. How do you tell which half is sorted using nums[lo] and nums[mid]?
</details>
<details><summary>Hint 3</summary>
If nums[lo] ≤ nums[mid], the left is sorted: go left iff nums[lo] ≤ target < nums[mid]. Else the right is sorted: go right iff nums[mid] < target ≤ nums[hi].
</details>

## Clarifying Questions
- Distinct values? (Yes. Duplicates break the "which half is sorted" check: LC 0081.)
- Could it be unrotated? (Yes, and the same code handles it.)
- Return the index or a boolean? (Index, -1 if absent.)

## Example Walkthrough
`[4,5,6,7,0,1,2], target 0`
- lo 0, hi 6, mid 3 (7). Left [4..7] is sorted; 0 isn't in [4, 7), so go right: lo = 4.
- mid 5 (1). nums[4] = 0 ≤ 1, so left [0..1] is sorted; 0 is in [0, 1): hi = 4.
- mid 4 (0) → found, return 4.

## Approaches

### 1. Linear Scan: O(n) time, O(1) space
Ignore the structure.

### 2. Find the Pivot, Then Binary Search: O(log n) time, O(1) space
Find the minimum's index with the 0153 search, then run a normal binary search on whichever side could hold the target. Two clean, reusable searches.

### 3. One-Pass Sorted-Half Search ⭐ Go-to: O(log n) time, O(1) space
Decide the sorted half at each step and test the target against its range.
**Why it's the go-to:** one loop, and it's the answer interviewers expect. Approach 2 is a good fallback if the conditions get confusing under pressure.

## Dry Run (Approach 3)
`[5,1,3], target 5`

| lo | hi | mid | nums[mid] | sorted half | target in it? | action |
|----|----|-----|-----------|-------------|---------------|--------|
| 0 | 2 | 1 | 1 | right [1..3] (5 > 1) | 5 in (1, 3]? no | hi = 0 |
| 0 | 0 | 0 | 5 | | found | return **0** |

## Edge Case Check
- Unrotated `[1,3]`, target 3: left sorted, 3 not in [1, 3), go right → found. ✅
- Rotated by one `[3,1]`, target 1: nums[0]=3 ≤ nums[0]=3 so "left sorted" (just mid itself), 1 not in [3,3), go right → found. ✅
- Target absent: loop ends with -1. ✅

## ⚠️ Pitfalls
- **`<` instead of `<=` in nums[lo] ≤ nums[mid]**: when lo == mid the single-element left half is sorted; `<` misclassifies it.
- **Half-open vs closed range tests**: left is `nums[lo] ≤ t < nums[mid]`, right is `nums[mid] < t ≤ nums[hi]` (mid was already checked).
- **Duplicates**: nums[lo] == nums[mid] == nums[hi] tells you nothing; that's 0081.

## 🎯 What the Interviewer Wants
- "One half is always sorted" stated clearly.
- Correct boundary inequalities.
- Ability to fall back to the two-step pivot method.

## Follow-ups
- **Find the minimum / rotation point:** [LC 0153 Find Minimum in Rotated Sorted Array](../0153-find-minimum-in-rotated-sorted-array/)
- **With duplicates:** shrink lo++ and hi-- when the ends equal mid; O(n) worst case: LC 0081 Search in Rotated Sorted Array II (not added yet)
- **Plain sorted array:** [LC 0704 Binary Search](../0704-binary-search/)
