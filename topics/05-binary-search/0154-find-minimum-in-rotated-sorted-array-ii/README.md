---
number: 154
title: Find Minimum in Rotated Sorted Array II
difficulty: Hard
topic: Binary Search
pattern: Compare mid with hi; shrink hi on ties
link: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/
lists: [Interview Extras]
followup_of: ["0153 Find Minimum in Rotated Sorted Array"]
related: ["0153 Find Minimum in Rotated Sorted Array", "0081 Search in Rotated Sorted Array II", "0033 Search in Rotated Sorted Array"]
---

# 0154. Find Minimum in Rotated Sorted Array II

## ⚡ 30-Second Summary
**Pattern:** LC 153 with duplicates
**Key insight:** Compare `nums[mid]` with `nums[hi]`.
- Smaller: the minimum is at mid or to its left (`hi = mid`).
- Bigger: the drop is to the right of mid (`lo = mid + 1`).
- Equal: you can't tell which side, but removing `hi` is safe, because `nums[mid]` holds the same value and stays in range. So `hi−−`.
**Go-to:** Binary search against hi with `hi−−` on ties, O(log n) typical, O(n) worst, O(1) space

## Problem
A sorted array that may contain duplicates was rotated at an unknown pivot. Return its minimum value. [LeetCode](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/)

**Examples:**
```
Input:  nums = [1,3,5]
Output: 1
Why:    Not rotated: the first element is the smallest.

Input:  nums = [2,2,2,0,1]
Output: 0
Why:    The values drop from 2 to 0 at index 3.
```

**Constraints:**
- 1 ≤ n ≤ 5000; values in [−5000, 5000]; duplicates allowed.
- Follow-up: how do duplicates affect the runtime?

## Hints
<details><summary>Hint 1</summary>
In LC 153 you compared nums[mid] with nums[hi]. Which of the three outcomes (<, >, ==) is new here?
</details>
<details><summary>Hint 2</summary>
When nums[mid] == nums[hi], the minimum might be on either side, e.g. [3,3,1,3] vs [3,1,3,3,3]. What can you safely drop?
</details>
<details><summary>Hint 3</summary>
Drop hi: its value is still in range at mid, so you can't lose the minimum value. Otherwise: < → hi = mid, > → lo = mid + 1. Return nums[lo].
</details>

## Clarifying Questions
- Return the value, not the index? (Value: with duplicates the index is ambiguous anyway.)
- Could it be unrotated? (Yes.)
- Duplicates anywhere, including across the rotation point? (Yes.)

## Example Walkthrough
`[2,2,2,0,1]`: lo = 0, hi = 4, mid = 2: 2 > 1 → lo = 3. mid = 3: 0 < 1 → hi = 3. lo == hi → nums[3] = 0.

## Approaches

### 1. Linear Scan: O(n) time, O(1) space
`min(nums)`. Same worst case as the clever version, so mention it.

### 2. Binary Search with hi−− on Ties ⭐ Go-to: O(log n) typical, O(n) worst, O(1) space
LC 153 with one extra branch.
**Why it's the go-to:** a one-line change to the solution you already know, with a clear safety argument.

## Dry Run (Approach 2)
`nums = [10,1,10,10,10]` (comparing with nums[lo] would go wrong here).

| lo | hi | mid | nums[mid] vs nums[hi] | action |
|----|----|-----|-----------------------|--------|
| 0 | 4 | 2 | 10 == 10 | hi = 3 |
| 0 | 3 | 1 | 1 < 10 | hi = 1 |
| 0 | 1 | 0 | 10 > 1 | lo = 1 |
| 1 | 1 | | | return nums[1] = **1** |

## Edge Case Check
- All equal `[2,2,2]` → hi walks down to lo: O(n), returns 2. ✅
- n = 1 → returns it. ✅
- Unrotated with duplicates `[1,1,2,3]` → hi shrinks toward 0. ✅

## ⚠️ Pitfalls
- **Comparing mid with lo:** with an unrotated array, `nums[mid] > nums[lo]` doesn't mean the minimum is to the right. Compare with hi.
- **`hi = mid − 1` when nums[mid] < nums[hi]:** mid itself may be the minimum. Use `hi = mid`.
- **Returning lo instead of nums[lo].**

## 🎯 What the Interviewer Wants
- Know LC 153 and add exactly one branch.
- Explain why `hi−−` can't lose the minimum.
- Worst case O(n) with an example (all equal but one).

## Follow-ups
- **No duplicates:** [LC 0153 Find Minimum in Rotated Sorted Array](../0153-find-minimum-in-rotated-sorted-array/)
- **Search a target with duplicates:** [LC 0081 Search in Rotated Sorted Array II](../0081-search-in-rotated-sorted-array-ii/)
- **Search a target without duplicates:** [LC 0033 Search in Rotated Sorted Array](../0033-search-in-rotated-sorted-array/)
