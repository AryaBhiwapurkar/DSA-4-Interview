---
number: 27
title: Remove Element
difficulty: Easy
topic: Two Pointers
pattern: Read/write pointers
link: https://leetcode.com/problems/remove-element/
lists: [LC Top Interview 150]
followup_of: []
related: ["0026 Remove Duplicates from Sorted Array", "0283 Move Zeroes"]
---

# 0027. Remove Element

## ⚡ 30-Second Summary
**Pattern:** Read/write pointers (or swap with the end)
**Key insight:** Copy every element that is NOT `val` to the write position. Alternatively, since order doesn't matter, overwrite each `val` with the last element and shrink the array, which writes less when `val` is rare.
**Go-to:** Read/write pointers, O(n) time, O(1) space

## Problem
Remove all occurrences of `val` from the array in place. Return k, the number of remaining elements; the first k slots must hold them in any order. [LeetCode](https://leetcode.com/problems/remove-element/)

**Examples:**
```
Input:  nums = [3,2,2,3], val = 3
Output: 2, nums = [2,2,_,_]
Why:    Both 3s are removed; two 2s remain.

Input:  nums = [0,1,2,2,3,0,4,2], val = 2
Output: 5, nums = [0,1,4,0,3,_,_,_]
Why:    Three 2s removed; the five others remain (any order is accepted).
```

**Constraints:**
- 0 ≤ n ≤ 100; 0 ≤ nums[i] ≤ 50; 0 ≤ val ≤ 100.
- Order of the kept elements doesn't matter.

## Hints
<details><summary>Hint 1</summary>
Think of building the answer at the front of the same array.
</details>
<details><summary>Hint 2</summary>
A second index marks where the next kept element should go.
</details>
<details><summary>Hint 3</summary>
Since order doesn't matter, you could also fill each removed slot with the last element and shrink n.
</details>

## Clarifying Questions
- Must the order of kept elements be preserved? (No.)
- Can the array be empty? (Yes, return 0.)
- What's after index k? (Ignored.)

## Example Walkthrough
`nums = [3,2,2,3], val = 3`
- k = 0. Read 3: skip. Read 2: write at 0, k = 1. Read 2: write at 1, k = 2. Read 3: skip.
- Return 2, front = [2,2].

## Approaches

### 1. Read/Write Pointers ⭐ Go-to: O(n) time, O(1) space
For each x, if `x != val`, write `nums[k++] = x`.
**Why it's the go-to:** simplest correct template, keeps order as a bonus.

### 2. Swap With End: O(n) time, O(1) space
`i = 0, n = len`; while `i < n`: if `nums[i] == val`, set `nums[i] = nums[n-1]` and `n--` (re-check i); else `i++`. Fewer writes when val is rare; order not kept.

## Dry Run (Approach 1)
`nums = [0,1,2,2,3,0,4,2], val = 2`

| i | nums[i] | keep? | k (after) | front |
|---|---------|-------|-----------|-------|
| 0 | 0 | yes | 1 | [0] |
| 1 | 1 | yes | 2 | [0,1] |
| 2 | 2 | no | 2 | [0,1] |
| 3 | 2 | no | 2 | [0,1] |
| 4 | 3 | yes | 3 | [0,1,3] |
| 5 | 0 | yes | 4 | [0,1,3,0] |
| 6 | 4 | yes | 5 | [0,1,3,0,4] |
| 7 | 2 | no | 5 | [0,1,3,0,4] |

## Edge Case Check
- Empty array: k = 0. ✅
- All elements equal val: k = 0. ✅
- val not present: k = n. ✅

## ⚠️ Pitfalls
- **Swap-with-end: advancing i after a swap** skips the element just moved in, which may also be val.
- **Deleting from a vector/list inside the loop** (`erase`, `remove`) is O(n) each, O(n²) total.

## 🎯 What the Interviewer Wants
- In-place read/write pointers.
- Bonus: mention the swap-with-end variant and when it's better.

## Follow-ups
- **Move all zeros to the end, keep order:** LC 0283 Move Zeroes (not added yet)
- **Remove duplicates from a sorted array:** [LC 0026](../0026-remove-duplicates-from-sorted-array/)
- **C++ idiom:** `nums.erase(remove(nums.begin(), nums.end(), val), nums.end())` is exactly Approach 1.
