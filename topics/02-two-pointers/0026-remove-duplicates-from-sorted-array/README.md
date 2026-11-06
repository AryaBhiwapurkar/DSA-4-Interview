---
number: 26
title: Remove Duplicates from Sorted Array
difficulty: Easy
topic: Two Pointers
pattern: Read/write pointers
link: https://leetcode.com/problems/remove-duplicates-from-sorted-array/
lists: [LC Top Interview 150]
followup_of: []
related: ["0080 Remove Duplicates from Sorted Array II", "0027 Remove Element", "0083 Remove Duplicates from Sorted List"]
---

# 0026. Remove Duplicates from Sorted Array

## ⚡ 30-Second Summary
**Pattern:** Read/write (slow/fast) pointers
**Key insight:** In a sorted array, a value is new iff it differs from the last value written. A fast pointer reads every element; a slow pointer writes only the new ones.
**Go-to:** Read/write pointers, O(n) time, O(1) space

## Problem
Given an array sorted in non-decreasing order, remove duplicates in place so each value appears once, keeping the original order. Return k, the number of unique values; the first k slots must hold them (anything after k doesn't matter). [LeetCode](https://leetcode.com/problems/remove-duplicates-from-sorted-array/)

**Examples:**
```
Input:  nums = [1,1,2]
Output: 2, nums = [1,2,_]
Why:    Two unique values, 1 and 2, moved to the front.

Input:  nums = [0,0,1,1,1,2,2,3,3,4]
Output: 5, nums = [0,1,2,3,4,_,_,_,_,_]
Why:    Five unique values in their original order.
```

**Constraints:**
- 1 ≤ n ≤ 3·10⁴; -100 ≤ nums[i] ≤ 100.
- Sorted non-decreasing, so duplicates are adjacent.

## Hints
<details><summary>Hint 1</summary>
Because the array is sorted, where are all copies of a value?
</details>
<details><summary>Hint 2</summary>
Keep a "write" index for where the next unique value should go.
</details>
<details><summary>Hint 3</summary>
Scan with i from 1; if nums[i] != nums[k-1], write nums[k] = nums[i] and k++.
</details>

## Clarifying Questions
- Is the array sorted? (Yes; otherwise you'd need a set.)
- Must relative order be kept? (Yes.)
- What's left after index k? (Doesn't matter.)

## Example Walkthrough
`nums = [0,0,1,1,1,2,2,3,3,4]`
- k = 1 (0 kept). Reading: 0 dup, 1 new → write at 1, 1 dup, 1 dup, 2 new → at 2, 2 dup, 3 new → at 3, 3 dup, 4 new → at 4.
- k = 5, front = [0,1,2,3,4].

## Approaches

### 1. Collect Uniques, Copy Back: O(n) time, O(n) space
Build a list of distinct values (or use an ordered set), copy it to the front. Uses extra memory the problem forbids.

### 2. Read/Write Pointers ⭐ Go-to: O(n) time, O(1) space
`k = 1`; for each i ≥ 1, if `nums[i] != nums[k-1]`, set `nums[k++] = nums[i]`.
**Why it's the go-to:** in place, single pass, and the same template generalizes to "at most m copies" (0080).

## Dry Run (Approach 2)
`nums = [1,1,2]`

| i | nums[i] | nums[k-1] | new? | k (after) | array |
|---|---------|-----------|------|-----------|-------|
| - | - | - | - | 1 | [1,1,2] |
| 1 | 1 | 1 | no | 1 | [1,1,2] |
| 2 | 2 | 1 | yes | 2 | [1,2,2] |

Return 2.

## Edge Case Check
- n = 1: k = 1, loop doesn't run. ✅
- All equal, `[5,5,5]`: k stays 1. ✅
- All unique: every element is copied onto itself, k = n. ✅

## ⚠️ Pitfalls
- **Comparing with nums[i-1] instead of nums[k-1]:** works here (sorted) but breaks the generalization; compare with the last *written* value.
- **Returning k but not writing:** the judge checks the first k elements too.
- **Python:** `nums = sorted(set(nums))` rebinds a local name; the caller's list is unchanged.

## 🎯 What the Interviewer Wants
- The in-place read/write pointer template.
- Use of the sorted property (no set needed).

## Follow-ups
- **Allow at most two copies:** compare with nums[k-2]: [LC 0080 Remove Duplicates from Sorted Array II](../0080-remove-duplicates-from-sorted-array-ii/)
- **Remove a given value instead:** [LC 0027 Remove Element](../0027-remove-element/)
- **Same on a sorted linked list:** LC 0083 Remove Duplicates from Sorted List (not added yet)
- **Unsorted input:** needs a hash set to track seen values (O(n) space).
