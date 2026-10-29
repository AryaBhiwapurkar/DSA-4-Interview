---
number: 15
title: 3Sum
difficulty: Medium
topic: Two Pointers
pattern: Sort + fix one + two pointers
link: https://leetcode.com/problems/3sum/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: ["0167 Two Sum II - Input Array Is Sorted"]
related: ["0001 Two Sum", "0167 Two Sum II - Input Array Is Sorted", "0016 3Sum Closest", "0018 4Sum"]
---

# 0015. 3Sum

## ⚡ 30-Second Summary
**Pattern:** Sort, fix one element, two-pointer Two Sum on the rest
**Key insight:** After sorting, for each a[i] you need a pair in the suffix summing to -a[i], which is Two Sum II. Sorting also makes duplicates adjacent, so skipping equal neighbours removes duplicate triplets without a set.
**Go-to:** Sort + two pointers, O(n²) time, O(1) extra space (besides sort/output)

## Problem
Given an integer array, return all unique triplets `[a, b, c]` of values at three different indices with `a + b + c = 0`. No duplicate triplets in the output; order doesn't matter.

**Examples:**
```
Input:  nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Why:    Those are the only distinct value-triplets that sum to 0.

Input:  nums = [0,1,1]
Output: []
Why:    The only triplet sums to 2.

Input:  nums = [0,0,0]
Output: [[0,0,0]]
Why:    The single triplet sums to 0.
```

**Constraints:**
- 3 ≤ n ≤ 3000, so O(n²) ≈ 9·10⁶ is fine and O(n³) is not.
- -10⁵ ≤ nums[i] ≤ 10⁵, so sums fit easily in 32 bits.

## Hints
<details><summary>Hint 1</summary>
Fix the first number. What problem is left for the other two?
</details>
<details><summary>Hint 2</summary>
If the array is sorted, that leftover problem is Two Sum II (two pointers).
</details>
<details><summary>Hint 3</summary>
Skip a[i] if it equals a[i-1]. After finding a triplet, move both pointers and skip over equal values on each side.
</details>

## Clarifying Questions
- Return values or indices? (Values.)
- Unique triplets by value? (Yes: [-1,0,1] once even if several index combinations make it.)
- Order of output? (Any.)

## Example Walkthrough
`nums = [-1,0,1,2,-1,-4]` → sorted `[-4,-1,-1,0,1,2]`
- i = 0 (-4): need 4 from [-1..2]; max pair is 1+2 = 3. None.
- i = 1 (-1): need 1: pairs (-1,2) ✓ and (0,1) ✓.
- i = 2 (-1): same as previous value, skip.
- i = 3 (0): need 0 from [1,2]: none. Done.

## Approaches

### 1. Brute Force + Set: O(n³) time, O(k) space
Try all triples, sort each, store in a set to dedupe. Too slow at n = 3000.

### 2. Hash Set per Fixed Element: O(n²) time, O(n) space
Fix i, run hashmap Two Sum on the rest, dedupe with a set of sorted triplets. Works but dedup is messy.

### 3. Sort + Two Pointers ⭐ Go-to: O(n²) time, O(1) extra space
Sort; for each i (skipping duplicates, stop once a[i] > 0), run l = i+1, r = n-1 inward; on a hit, record, then skip duplicates on both sides.
**Why it's the go-to:** optimal for this problem, no hashing, and duplicate handling falls out of the sort.

## Dry Run (Approach 3)
sorted = `[-4,-1,-1,0,1,2]`, i = 1 (a[i] = -1, need sum 0)

| l | r | a[l] | a[r] | total | action |
|---|---|------|------|-------|--------|
| 2 | 5 | -1 | 2 | 0 | record [-1,-1,2]; l=3, r=4 |
| 3 | 4 | 0 | 1 | 0 | record [-1,0,1]; l=4, r=3 → stop |

## Edge Case Check
- All zeros, `[0,0,0,0]`: one triplet [0,0,0]; skips prevent repeats. ✅
- No solution, `[0,1,1]`: empty. ✅
- All positive: the a[i] > 0 early exit fires at once. ✅

## ⚠️ Pitfalls
- **Skipping duplicates of a[i] with `a[i] == a[i+1]`** (looking ahead) skips valid triplets like [-1,-1,2]; compare with a[i-1].
- **Not skipping duplicates after a hit** produces repeated triplets.
- **Forgetting to move both pointers after a hit** loops forever.
- **4Sum variant overflows 32-bit** sums; use 64-bit there.

## 🎯 What the Interviewer Wants
- Reduce to Two Sum II after sorting.
- Clean duplicate handling without a set.
- Correct O(n²) analysis (the sort is dominated).

## Follow-ups
- **Closest sum to a target:** same loop, track the best |sum - target|: LC 0016 3Sum Closest (not added yet)
- **Four numbers:** add one more fixed index (O(n³)), use 64-bit sums: LC 0018 4Sum (not added yet)
- **Count triplets with sum < target:** when sum < target, add r - l and move l.
- **Base problem:** [LC 0167 Two Sum II](../0167-two-sum-ii-input-array-is-sorted/)
