---
number: 81
title: Search in Rotated Sorted Array II
difficulty: Medium
topic: Binary Search
pattern: Rotated binary search + shrink both ends on ties
link: https://leetcode.com/problems/search-in-rotated-sorted-array-ii/
lists: [Interview Extras]
followup_of: ["0033 Search in Rotated Sorted Array"]
related: ["0033 Search in Rotated Sorted Array", "0154 Find Minimum in Rotated Sorted Array II", "0153 Find Minimum in Rotated Sorted Array"]
---

# 0081. Search in Rotated Sorted Array II

## ⚡ 30-Second Summary
**Pattern:** LC 33 with duplicates
**Key insight:** As in LC 33, one half around mid is always sorted; search there if the target fits its range, otherwise go to the other half. With duplicates, `nums[lo] == nums[mid] == nums[hi]` doesn't tell you which half is sorted. In that case just drop both ends (lo++, hi−−); neither can be the target, since it ≠ nums[mid].
**Go-to:** Rotated binary search with tie-shrinking, O(log n) typical, O(n) worst, O(1) space

## Problem
A sorted array (it may contain duplicates) was rotated at an unknown pivot. Return whether target is present. [LeetCode](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/)

**Examples:**
```
Input:  nums = [2,5,6,0,0,1,2], target = 0
Output: true
Why:    0 is right after the rotation point.

Input:  nums = [2,5,6,0,0,1,2], target = 3
Output: false
Why:    3 would sit between 2 and 5, and it isn't there.
```

**Constraints:**
- 1 ≤ n ≤ 5000; values in [−10⁴, 10⁴]; duplicates allowed.
- Follow-up: how do duplicates change the runtime?

## Hints
<details><summary>Hint 1</summary>
Start from the LC 33 logic: at least one of [lo, mid] and [mid, hi] is sorted. How do you normally tell which?
</details>
<details><summary>Hint 2</summary>
nums[lo] ≤ nums[mid] means the left half is sorted, except when duplicates fool you, e.g. [1,0,1,1,1]. When exactly does the test fail?
</details>
<details><summary>Hint 3</summary>
When nums[lo] == nums[mid] == nums[hi] you can't tell. Since nums[mid] ≠ target, nums[lo] and nums[hi] aren't the target either: lo++, hi−−. Otherwise use the LC 33 rules.
</details>

## Clarifying Questions
- Duplicates allowed? (Yes: this is the whole difference from LC 33.)
- Return a boolean, not an index? (Boolean.)
- Could the array be not rotated at all? (Yes; the same code handles it.)

## Example Walkthrough
`[2,5,6,0,0,1,2], target = 0`: lo = 0, hi = 6, mid = 3 → nums[3] = 0 is the target. Found on the first probe. The duplicate case is in the dry run below.

## Approaches

### 1. Linear Scan: O(n) time, O(1) space
`target in nums`. Since the worst case of the clever approach is also O(n), say this out loud.

### 2. Rotated Binary Search with Tie-shrinking ⭐ Go-to: O(log n) typical, O(n) worst, O(1) space
LC 33's sorted-half rule, plus "shrink both ends" when all three probes are equal.
**Why it's the go-to:** it's what the interviewer is asking for, and you can explain exactly when it degrades: e.g. all 1s with one 0 hidden.

## Dry Run (Approach 2)
`nums = [1,0,1,1,1], target = 0` (the case that breaks plain LC 33).

| lo | hi | mid | nums[lo], nums[mid], nums[hi] | decision |
|----|----|-----|-------------------------------|----------|
| 0 | 4 | 2 | 1, 1, 1 | all equal → lo = 1, hi = 3 |
| 1 | 3 | 2 | 0, 1, 1 | left [0..1] sorted, 0 ≤ 0 < 1 → hi = 1 |
| 1 | 1 | 1 | nums[1] = 0 | **found** |

Plain LC 33 at step 1 would see nums[lo] ≤ nums[mid], call the left [1,0,1] "sorted", see 0 is outside [1, 1), and go right: missing the 0.

## Edge Case Check
- Single element → one comparison. ✅
- All equal and target absent → shrinks both ends to empty: O(n). ✅
- Not rotated → behaves like normal binary search. ✅

## ⚠️ Pitfalls
- **Copying LC 33 unchanged:** the `nums[lo] ≤ nums[mid]` test lies when lo, mid and hi hold equal values.
- **Shrinking only one end** works but is slower; shrinking both is safe because neither end equals the target.
- **Claiming O(log n):** the worst case is O(n), and that's the follow-up answer.

## 🎯 What the Interviewer Wants
- Reuse LC 33 and pinpoint the exact case duplicates break.
- The tie-shrink fix and why it's safe.
- Honest complexity: O(n) worst case, with an example.

## Follow-ups
- **Without duplicates, return the index:** [LC 0033 Search in Rotated Sorted Array](../0033-search-in-rotated-sorted-array/)
- **Minimum of a rotated array with duplicates:** [LC 0154 Find Minimum in Rotated Sorted Array II](../0154-find-minimum-in-rotated-sorted-array-ii/)
- **Minimum without duplicates:** [LC 0153 Find Minimum in Rotated Sorted Array](../0153-find-minimum-in-rotated-sorted-array/)
