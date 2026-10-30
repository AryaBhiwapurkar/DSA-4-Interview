---
number: 4
title: Median of Two Sorted Arrays
difficulty: Hard
topic: Binary Search
pattern: Binary search on partition
link: https://leetcode.com/problems/median-of-two-sorted-arrays/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0088 Merge Sorted Array", "0295 Find Median from Data Stream", "0215 Kth Largest Element in an Array"]
---

# 0004. Median of Two Sorted Arrays

## ⚡ 30-Second Summary
**Pattern:** Binary search on the partition of the smaller array
**Key insight:** The median splits the merged array into a left half and a right half of equal size (left gets the extra one if odd). Choose i elements from A for the left half; then j = half - i come from B. The split is correct iff A[i-1] ≤ B[j] and B[j-1] ≤ A[i]. Binary search i over the smaller array.
**Go-to:** Partition binary search on the shorter array, O(log min(m, n)) time, O(1) space

## Problem
Given two sorted arrays of sizes m and n, return the median of all m + n numbers combined. Required: O(log(m + n)).

**Examples:**
```
Input:  nums1 = [1,3], nums2 = [2]
Output: 2.00000
Why:    Merged [1,2,3]; the middle element is 2.

Input:  nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Why:    Merged [1,2,3,4]; the average of the middle two is (2 + 3) / 2.
```

**Constraints:**
- 0 ≤ m, n ≤ 1000 and m + n ≥ 1 (one array can be empty).
- Values in ±10⁶, so ±∞ sentinels can be INT_MIN / INT_MAX.

## Hints
<details><summary>Hint 1</summary>
Merging gives O(m + n). To get a log, what single number could you binary search on?
</details>
<details><summary>Hint 2</summary>
If you knew how many elements of A are in the left half of the merged array, you'd know how many of B are too. How do you check whether that guess is right, too big, or too small?
</details>
<details><summary>Hint 3</summary>
For i from A and j = (m+n+1)/2 - i from B: if A[i-1] > B[j], take fewer from A (hi = i-1); if B[j-1] > A[i], take more (lo = i+1). Otherwise the median comes from max(A[i-1], B[j-1]) and min(A[i], B[j]). Use ±∞ at the edges.
</details>

## Clarifying Questions
- Can one array be empty? (Yes; both can't be.)
- Return type for an even total? (Average of the two middle values, as a double.)
- Duplicates across arrays? (Yes, fine.)

## Example Walkthrough
`A = [1,2], B = [3,4]`, total 4, half = 2.
- i = 1, j = 1: A[0]=1 ≤ B[1]=4 ✓, but B[0]=3 > A[1]=2 ✗ → take more from A: lo = 2.
- i = 2, j = 0: left = {1,2}, right = {3,4}. A[1]=2 ≤ B[0]=3 ✓ and B[-1] = -∞ ≤ A[2] = +∞ ✓.
- Even total: (max(2, -∞) + min(+∞, 3)) / 2 = 2.5.

## Approaches

### 1. Merge, Then Pick the Middle: O(m + n) time, O(m + n) space
Merge like 0088 and index the middle. (Stopping two pointers at the middle gets O(1) space but is still linear.) Safe fallback and a good opener.

### 2. Partition Binary Search ⭐ Go-to: O(log min(m, n)) time, O(1) space
Search i in [0, m] on the shorter array A.
**Why it's the go-to:** it's the only approach that meets the stated complexity; it's the reason this is a Hard.

## Dry Run (Approach 2)
`nums1 = [1,3], nums2 = [2]`: nums2 is shorter, so A = [2], B = [1,3]; total 3, half = 2

| lo | hi | i | j | A[i-1] | A[i] | B[j-1] | B[j] | check | action |
|----|----|---|---|--------|------|--------|------|-------|--------|
| 0 | 1 | 0 | 2 | -∞ | 2 | 3 | +∞ | B[j-1]=3 > A[i]=2 | lo = 1 |
| 1 | 1 | 1 | 1 | 2 | +∞ | 1 | 3 | 2 ≤ 3 ✓, 1 ≤ +∞ ✓ | odd → max(2, 1) = **2** |

## Edge Case Check
- One array empty `[] , [1]`: m = 0, i = 0, j = 1; answer B[0] = 1. ✅
- All of A belongs on the left/right: i hits 0 or m; sentinels handle it. ✅
- Equal values `[0,0], [0,0]`: any valid split, median 0. ✅
- Interleaved `[1,3,5], [2,4,6]`: 3.5. ✅

## ⚠️ Pitfalls
- **Searching the longer array**: j = half - i can go negative or exceed n. Always swap so A is the shorter one.
- **half = (m + n + 1) / 2** (not / 2) so the left side gets the extra element when odd; then the odd answer is max of the left side.
- **Integer division for the even case**: divide by 2.0.
- **Sentinels**: INT_MIN/INT_MAX are safe because values are ≤ 10⁶ in magnitude; in Python use `float("-inf")`.

## 🎯 What the Interviewer Wants
- Start with the O(m + n) merge, then explain why the partition gives a log.
- The two cross conditions and which way to move.
- Careful handling of empty arrays and edge partitions with ±∞.

## Follow-ups
- **Kth smallest of two sorted arrays:** same idea with half = k, or eliminate k/2 per step.
- **Merge two sorted arrays:** [LC 0088 Merge Sorted Array](../../02-two-pointers/0088-merge-sorted-array/)
- **Median of a stream:** two heaps: LC 0295 Find Median from Data Stream (not added yet)
- **Kth largest in one unsorted array:** quickselect or heap: LC 0215 Kth Largest Element in an Array (not added yet)
