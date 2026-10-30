---
number: 162
title: Find Peak Element
difficulty: Medium
topic: Binary Search
pattern: Binary search on slope
link: https://leetcode.com/problems/find-peak-element/
lists: [LC Top Interview 150]
followup_of: []
related: ["0852 Peak Index in a Mountain Array", "1901 Find a Peak Element II", "0153 Find Minimum in Rotated Sorted Array"]
---

# 0162. Find Peak Element

## ⚡ 30-Second Summary
**Pattern:** Binary search on slope (not on sorted values)
**Key insight:** If nums[mid] < nums[mid+1], you're on an uphill slope, and since nums[n] = -∞, there must be a peak to the right. Otherwise there's a peak at mid or to the left. Either way half the range can be discarded.
**Go-to:** Binary search comparing mid with mid+1, O(log n) time, O(1) space

## Problem
Return the index of any peak: an element strictly greater than its neighbours. Imagine nums[-1] = nums[n] = -∞, and adjacent elements are never equal. Must be O(log n).

**Examples:**
```
Input:  nums = [1,2,3,1]
Output: 2
Why:    3 is bigger than both neighbours.

Input:  nums = [1,2,1,3,5,6,4]
Output: 5 (or 1)
Why:    Both 2 (index 1) and 6 (index 5) are peaks; either is accepted.
```

**Constraints:**
- 1 ≤ n ≤ 1000; nums[i] ≠ nums[i+1].
- Values are full 32-bit range, so "-∞" means "outside the array", not INT_MIN.

## Hints
<details><summary>Hint 1</summary>
The array isn't sorted. What local information at mid tells you which side definitely has a peak?
</details>
<details><summary>Hint 2</summary>
Compare nums[mid] with nums[mid+1]. If you walk uphill forever you'll eventually hit the -∞ edge, so there's a peak on the uphill side.
</details>
<details><summary>Hint 3</summary>
lo = 0, hi = n-1; while lo < hi: if nums[mid] > nums[mid+1], hi = mid, else lo = mid + 1. Return lo.
</details>

## Clarifying Questions
- Any peak or a specific one? (Any.)
- Can neighbours be equal? (No. With plateaus the log n guarantee breaks.)
- Are the edges -∞? (Yes, so index 0 or n-1 can be a peak.)

## Example Walkthrough
`[1,2,1,3,5,6,4]`
- lo 0, hi 6, mid 3: 3 < 5 uphill, so lo = 4.
- mid 5: 6 > 4 downhill, so hi = 5.
- mid 4: 5 < 6 uphill, so lo = 5. lo == hi → 5.

## Approaches

### 1. Linear Scan: O(n) time, O(1) space
Return the first i with nums[i] > nums[i+1] (the first downhill step), else n-1. Correct, since everything before i was rising.

### 2. Binary Search on Slope ⭐ Go-to: O(log n) time, O(1) space
Move toward the uphill side; the range always contains a peak.
**Why it's the go-to:** meets the O(log n) requirement and shows you can binary search on a property, not just on sorted values.

## Dry Run (Approach 2)
`[1,2,3,1]`

| lo | hi | mid | nums[mid] vs nums[mid+1] | action |
|----|----|-----|--------------------------|--------|
| 0 | 3 | 1 | 2 < 3 (uphill) | lo = 2 |
| 2 | 3 | 2 | 3 > 1 (downhill) | hi = 2 |
| 2 | 2 | | | return **2** |

## Edge Case Check
- Single element: index 0 (both sides are -∞). ✅
- Strictly increasing `[1,2,3]`: always uphill, ends at n-1. ✅
- Strictly decreasing `[3,2,1]`: always downhill, ends at 0. ✅
- mid+1 is always valid because lo < hi means mid < hi ≤ n-1. ✅

## ⚠️ Pitfalls
- **`while lo <= hi`** lets mid = n-1, then nums[mid+1] is out of bounds.
- **Using INT_MIN as a sentinel**: values can equal INT_MIN; reason about indices instead.
- **Thinking it needs sorting**: the invariant is "a peak exists in [lo, hi]", not order.

## 🎯 What the Interviewer Wants
- The uphill argument for why a peak exists on that side.
- An invariant-based proof that the search terminates on a peak.
- Correct bounds so mid+1 never overflows the array.

## Follow-ups
- **Exactly one peak (mountain array):** same code: LC 0852 Peak Index in a Mountain Array (not added yet)
- **2-D grid peak:** binary search on columns, take the max of each column: LC 1901 Find a Peak Element II (not added yet)
- **Same "compare with a neighbour/edge" trick:** [LC 0153 Find Minimum in Rotated Sorted Array](../0153-find-minimum-in-rotated-sorted-array/)
