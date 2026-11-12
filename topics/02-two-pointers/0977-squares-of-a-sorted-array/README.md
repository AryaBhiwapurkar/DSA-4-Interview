---
number: 977
title: Squares of a Sorted Array
difficulty: Easy
topic: Two Pointers
pattern: Converging pointers, fill from the back
link: https://leetcode.com/problems/squares-of-a-sorted-array/
lists: [Interview Extras]
followup_of: []
related: ["0088 Merge Sorted Array", "0360 Sort Transformed Array"]
---

# 0977. Squares of a Sorted Array

## ⚡ 30-Second Summary
**Pattern:** The largest square sits at one of the two ends
**Key insight:** In a sorted array with negatives, the squares fall towards the middle and rise towards both ends. So the biggest remaining square is always at `lo` or `hi`. Compare `|nums[lo]|` with `|nums[hi]|`, write the bigger square into the result from the **back**, and move that pointer inward.
**Go-to:** Two pointers filling from the end, O(n) time, O(n) output

## Problem
Given an integer array sorted in non-decreasing order, return the squares of its elements, also sorted in non-decreasing order. [LeetCode](https://leetcode.com/problems/squares-of-a-sorted-array/)

**Examples:**
```
Input:  nums = [-4,-1,0,3,10]
Output: [0,1,9,16,100]
Why:    Squares are [16,1,0,9,100]; sorted they read 0,1,9,16,100.

Input:  nums = [-7,-3,2,3,11]
Output: [4,9,9,49,121]
Why:    -3 and 3 both square to 9.
```

**Constraints:**
- 1 ≤ n ≤ 10⁴; |nums[i]| ≤ 10⁴, so squares fit in an int (10⁸).
- Follow-up: O(n) instead of squaring and sorting.

## Hints
<details><summary>Hint 1</summary>
Where in the array can the largest square be?
</details>
<details><summary>Hint 2</summary>
If you always know where the largest remaining square is, in which order should you fill the result?
</details>
<details><summary>Hint 3</summary>
lo = 0, hi = n − 1, k = n − 1. While lo ≤ hi: put the larger of nums[lo]², nums[hi]² into res[k−−] and move that pointer inward.
</details>

## Clarifying Questions
- Is the input sorted ascending? (Yes, non-decreasing.)
- Return a new array? (Yes.)
- Can squares overflow? (No, 10⁸ max.)

## Example Walkthrough
`[-3,-1,2]`: compare 9 vs 4 → res[2] = 9, lo = 1. Compare 1 vs 4 → res[1] = 4, hi = 1. Only index 1 is left → res[0] = 1. Result [1,4,9].

## Approaches

### 1. Square and Sort: O(n log n) time, O(n) space
One line. Correct, but ignores the sortedness.

### 2. Two Pointers from the Back ⭐ Go-to: O(n) time, O(n) output
**Why it's the go-to:** linear, simple, and it's the classic "merge two sorted runs" trick: the negatives form a descending run of squares and the positives an ascending one.

## Dry Run (Approach 2)
`[-4,-1,0,3,10]`

| lo | hi | compare | write res[k] | res |
|----|----|---------|--------------|-----|
| 0 | 4 | 16 vs 100 | 100 at 4 | [_,_,_,_,100] |
| 0 | 3 | 16 vs 9 | 16 at 3 | [_,_,_,16,100] |
| 1 | 3 | 1 vs 9 | 9 at 2 | [_,_,9,16,100] |
| 1 | 2 | 1 vs 0 | 1 at 1 | [_,1,9,16,100] |
| 2 | 2 | 0 | 0 at 0 | **[0,1,9,16,100]** |

## Edge Case Check
- All non-negative → hi does all the moving. ✅
- All negative → lo does all the moving. ✅
- n = 1 → one square. ✅

## ⚠️ Pitfalls
- **Filling from the front:** the smallest square is somewhere in the middle, not at an end.
- **`lo < hi` instead of `lo ≤ hi`** skips the last element.
- **Comparing raw values** instead of absolute values or squares.

## 🎯 What the Interviewer Wants
- See where the extremes are, and fill from the back.
- O(n) with clean pointer movement.

## Follow-ups
- **Same back-fill idea:** [LC 0088 Merge Sorted Array](../0088-merge-sorted-array/)
- **Any quadratic f(x) = ax² + bx + c:** LC 0360 Sort Transformed Array (not added yet). Fill from the back if a ≥ 0, from the front if a < 0.
