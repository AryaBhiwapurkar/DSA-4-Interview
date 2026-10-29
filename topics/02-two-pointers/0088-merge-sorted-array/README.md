---
number: 88
title: Merge Sorted Array
difficulty: Easy
topic: Two Pointers
pattern: Merge from the back
link: https://leetcode.com/problems/merge-sorted-array/
lists: [LC Top Interview 150]
followup_of: []
related: ["0021 Merge Two Sorted Lists", "0977 Squares of a Sorted Array", "0023 Merge k Sorted Lists"]
---

# 0088. Merge Sorted Array

## ⚡ 30-Second Summary
**Pattern:** Two pointers merging from the back
**Key insight:** The free space in nums1 is at the end. Fill it from the back with the larger of the two current tails, so you never overwrite an nums1 value you still need.
**Go-to:** Backward merge, O(m + n) time, O(1) space

## Problem
`nums1` has m sorted values followed by n empty slots (zeros); `nums2` has n sorted values. Merge nums2 into nums1 in place so nums1 becomes one sorted array of length m + n.

**Examples:**
```
Input:  nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
Output: [1,2,2,3,5,6]
Why:    Interleave [1,2,3] and [2,5,6] in sorted order.

Input:  nums1 = [1], m = 1, nums2 = [], n = 0
Output: [1]
Why:    Nothing to merge.

Input:  nums1 = [0], m = 0, nums2 = [1], n = 1
Output: [1]
Why:    nums1 has no real values; the result is just nums2.
```

**Constraints:**
- nums1 has length m + n; 0 ≤ m, n ≤ 200; 1 ≤ m + n ≤ 200.
- Values in [-10⁹, 10⁹]. Follow-up: O(m + n) time.

## Hints
<details><summary>Hint 1</summary>
Merging from the front would overwrite nums1 values you haven't used yet. Where is the free space?
</details>
<details><summary>Hint 2</summary>
Which element belongs in the very last slot?
</details>
<details><summary>Hint 3</summary>
Pointers i = m-1, j = n-1, write = m+n-1. Place the larger of nums1[i], nums2[j] at write. Stop when nums2 is used up.
</details>

## Clarifying Questions
- Is nums1 guaranteed to have exactly n spare slots at the end? (Yes.)
- Can m or n be 0? (Yes.)
- Return anything? (No, modify nums1 in place.)

## Example Walkthrough
`nums1 = [1,2,3,_,_,_], nums2 = [2,5,6]`
- Compare 3 and 6: put 6 at index 5. Compare 3 and 5: put 5 at 4. Compare 3 and 2: put 3 at 3.
- Compare 2 and 2: put nums2's 2 at 2 (either is fine). nums2 done; nums1's 1, 2 are already in place.

## Approaches

### 1. Copy + Sort: O((m+n) log(m+n)) time, O(1) extra
Copy nums2 into the tail of nums1, sort. Ignores that inputs are sorted.

### 2. Forward Merge With a Copy: O(m + n) time, O(m) space
Copy the first m values of nums1 aside, then do a standard merge from the front.

### 3. Backward Merge ⭐ Go-to: O(m + n) time, O(1) space
Fill from the end with the larger tail; loop while `j ≥ 0`.
**Why it's the go-to:** optimal on both axes, and the "merge from the back" insight is what's being tested.

## Dry Run (Approach 3)
`nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3`

| i | j | w | nums1[i] | nums2[j] | write | nums1 |
|---|---|---|----------|----------|-------|-------|
| 2 | 2 | 5 | 3 | 6 | 6 | [1,2,3,0,0,6] |
| 2 | 1 | 4 | 3 | 5 | 5 | [1,2,3,0,5,6] |
| 2 | 0 | 3 | 3 | 2 | 3 | [1,2,3,3,5,6] |
| 1 | 0 | 2 | 2 | 2 | 2 (nums2) | [1,2,2,3,5,6] |
| 1 | -1 | - | | | stop | [1,2,2,3,5,6] |

## Edge Case Check
- n = 0: loop never runs. ✅
- m = 0: i starts at -1, every element comes from nums2. ✅
- All nums2 smaller than nums1: nums1 values shift to the back first, then nums2 fills the front. ✅

## ⚠️ Pitfalls
- **Looping while i ≥ 0 too:** once nums2 is exhausted, the rest of nums1 is already in place; but if nums1 runs out first you must keep copying nums2. Loop on `j ≥ 0` and guard `i ≥ 0` in the comparison.
- **Merging from the front in place** overwrites unread nums1 values.

## 🎯 What the Interviewer Wants
- Spot the back-to-front trick for O(1) space.
- Correct termination when one array runs out.

## Follow-ups
- **Merge two sorted linked lists:** LC 0021 Merge Two Sorted Lists (not added yet)
- **Merge k sorted arrays/lists:** min-heap of heads: LC 0023 Merge k Sorted Lists (not added yet)
- **Squares of a sorted array (with negatives):** fill from the back with the larger absolute value: LC 0977 Squares of a Sorted Array (not added yet)
