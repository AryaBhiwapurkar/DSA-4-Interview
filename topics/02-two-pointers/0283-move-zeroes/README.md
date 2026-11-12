---
number: 283
title: Move Zeroes
difficulty: Easy
topic: Two Pointers
pattern: Read/write pointers (stable partition)
link: https://leetcode.com/problems/move-zeroes/
lists: [Interview Extras]
followup_of: []
related: ["0027 Remove Element", "0026 Remove Duplicates from Sorted Array", "0075 Sort Colors"]
---

# 0283. Move Zeroes

## ⚡ 30-Second Summary
**Pattern:** A write pointer marks where the next non-zero goes
**Key insight:** Walk with a read pointer. Each non-zero gets swapped into position `w`, then `w` moves forward. Everything before `w` is the non-zeros in their original order, and everything from `w` up to the read pointer is zeros. Swapping, instead of copying then zero-filling, finishes in one pass.
**Go-to:** Swap-based read/write pointers, O(n) time, O(1) space

## Problem
Move all zeros in an array to the end, in place, keeping the non-zero elements in their original order. [LeetCode](https://leetcode.com/problems/move-zeroes/)

**Examples:**
```
Input:  nums = [0,1,0,3,12]
Output: [1,3,12,0,0]
Why:    Non-zeros keep their order 1,3,12; both zeros go to the back.

Input:  nums = [0]
Output: [0]
Why:    Nothing to move.
```

**Constraints:**
- 1 ≤ n ≤ 10⁴; in place, no copy of the array.
- Follow-up: minimise the total number of writes.

## Hints
<details><summary>Hint 1</summary>
This is "Remove Element" with val = 0, except the removed values must reappear at the end.
</details>
<details><summary>Hint 2</summary>
Keep a pointer to where the next non-zero should go. What do you do when you read a non-zero?
</details>
<details><summary>Hint 3</summary>
w = 0; for r in 0..n−1: if nums[r] ≠ 0: swap(nums[w], nums[r]); w++.
</details>

## Clarifying Questions
- In place? (Yes.)
- Must non-zeros keep their relative order? (Yes, stable.)
- Do zeros need to stay "the same zeros"? (No, they're indistinguishable.)

## Example Walkthrough
`[1,0,2]`: r = 0 → swap with itself, w = 1. r = 1 is zero, skip. r = 2 → swap nums[1] and nums[2] → [1,2,0]. Done.

## Approaches

### 1. Copy Non-zeros, Then Fill Zeros: O(n) time, O(1) space
Write each non-zero to nums[w++], then set nums[w..] = 0. Two passes, and it writes every slot.

### 2. Swap Read/Write ⭐ Go-to: O(n) time, O(1) space
**Why it's the go-to:** one pass, stable, and when there are few zeros it writes only where needed. Add `if r ≠ w` to skip the self-swaps.

## Dry Run (Approach 2)
`[0,1,0,3,12]`

| r | nums[r] | action | w after | array |
|---|---------|--------|---------|-------|
| 0 | 0 | skip | 0 | [0,1,0,3,12] |
| 1 | 1 | swap w=0, r=1 | 1 | [1,0,0,3,12] |
| 2 | 0 | skip | 1 | |
| 3 | 3 | swap w=1, r=3 | 2 | [1,3,0,0,12] |
| 4 | 12 | swap w=2, r=4 | 3 | **[1,3,12,0,0]** |

## Edge Case Check
- No zeros → only self-swaps. ✅
- All zeros → no swaps. ✅
- Zeros already at the end → unchanged. ✅

## ⚠️ Pitfalls
- **`erase` + `push_back(0)` in a loop:** each erase is O(n), so the whole thing is O(n²).
- **Two pointers from both ends** (swap a zero at the front with a non-zero at the back) breaks the order.
- **Python `nums = [...]`** rebinds the name; the caller's list doesn't change. Mutate in place.

## 🎯 What the Interviewer Wants
- In-place, stable, O(n).
- The read/write pointer template, and the "fewer writes" follow-up.

## Follow-ups
- **Remove instead of move:** [LC 0027 Remove Element](../0027-remove-element/)
- **Three-way partition:** [LC 0075 Sort Colors](../0075-sort-colors/)
- **Deduplicate sorted data:** [LC 0026 Remove Duplicates from Sorted Array](../0026-remove-duplicates-from-sorted-array/)
