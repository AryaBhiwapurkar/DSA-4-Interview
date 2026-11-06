---
number: 80
title: Remove Duplicates from Sorted Array II
difficulty: Medium
topic: Two Pointers
pattern: Read/write pointers, compare k back
link: https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/
lists: [LC Top Interview 150]
followup_of: ["0026 Remove Duplicates from Sorted Array"]
related: ["0026 Remove Duplicates from Sorted Array", "0027 Remove Element"]
---

# 0080. Remove Duplicates from Sorted Array II

## ⚡ 30-Second Summary
**Pattern:** Read/write pointers, compare with the element two positions back in the output
**Key insight:** In sorted order, x may be written iff it differs from `nums[k-2]` (the value written two slots ago). If they're equal, the output already has two copies of x.
**Go-to:** Read/write with `nums[k-2]` check, O(n) time, O(1) space

## Problem
Given a sorted array, remove extra duplicates in place so each value appears at most twice, keeping order. Return k; the first k slots must hold the result. [LeetCode](https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/)

**Examples:**
```
Input:  nums = [1,1,1,2,2,3]
Output: 5, nums = [1,1,2,2,3,_]
Why:    The third 1 is dropped; everything else appears at most twice.

Input:  nums = [0,0,1,1,1,1,2,3,3]
Output: 7, nums = [0,0,1,1,2,3,3,_,_]
Why:    Four 1s become two.
```

**Constraints:**
- 1 ≤ n ≤ 3·10⁴; -10⁴ ≤ nums[i] ≤ 10⁴.
- Sorted non-decreasing; O(1) extra space.

## Hints
<details><summary>Hint 1</summary>
How did 0026 decide whether to keep an element? What changes when two copies are allowed?
</details>
<details><summary>Hint 2</summary>
You could count the current run length. Is there a way without a counter?
</details>
<details><summary>Hint 3</summary>
The first two elements always stay. After that, keep nums[i] iff nums[i] != nums[k-2].
</details>

## Clarifying Questions
- At most two copies? (Yes; ask if it might be a general m.)
- Must order be kept? (Yes.)
- What's after index k? (Ignored.)

## Example Walkthrough
`nums = [1,1,1,2,2,3]`
- k = 2 (first two kept). i = 2: nums[2] = 1, nums[k-2] = nums[0] = 1, equal: skip.
- i = 3: 2 vs nums[0] = 1, keep at 2. i = 4: 2 vs nums[1] = 1, keep at 3. i = 5: 3 vs nums[2] = 2, keep at 4.
- k = 5.

## Approaches

### 1. Run Counter: O(n) time, O(1) space
Track how many times the current value has been written; write only while the count is < 2. Works, but more state.

### 2. Compare With nums[k-2] ⭐ Go-to: O(n) time, O(1) space
`k = min(n, 2)`; for i from 2: if `nums[i] != nums[k-2]`, `nums[k++] = nums[i]`.
**Why it's the go-to:** two lines, no counters, and it generalizes to "at most m" by comparing with `nums[k-m]`.

## Dry Run (Approach 2)
`nums = [0,0,1,1,1,1,2,3,3]`

| i | nums[i] | nums[k-2] | keep? | k (after) |
|---|---------|-----------|-------|-----------|
| - | - | - | first two | 2 |
| 2 | 1 | 0 | yes | 3 |
| 3 | 1 | 0 | yes | 4 |
| 4 | 1 | 1 | no | 4 |
| 5 | 1 | 1 | no | 4 |
| 6 | 2 | 1 | yes | 5 |
| 7 | 3 | 1 | yes | 6 |
| 8 | 3 | 2 | yes | 7 |

## Edge Case Check
- n ≤ 2: return n unchanged. ✅
- All equal, `[2,2,2,2]`: k = 2. ✅
- No duplicates: every element kept, k = n. ✅

## ⚠️ Pitfalls
- **Comparing with nums[i-2] instead of nums[k-2]:** slot i-2 may already have been overwritten. On `[1,1,1,2,2,2]` it yields `[1,1,2]` instead of `[1,1,2,2]`. Always compare with the output.
- **Starting k at 2 when n < 2:** use `min(n, 2)`.

## 🎯 What the Interviewer Wants
- Generalize the 0026 template cleanly.
- Explain why `k-2` (output-relative) is the right comparison.

## Follow-ups
- **At most m copies:** compare with `nums[k-m]`, start with k = min(n, m).
- **At most one copy:** [LC 0026 Remove Duplicates from Sorted Array](../0026-remove-duplicates-from-sorted-array/)
- **Unsorted input, at most twice:** hashmap of counts (O(n) space).
