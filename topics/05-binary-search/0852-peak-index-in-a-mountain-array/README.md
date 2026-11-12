---
number: 852
title: Peak Index in a Mountain Array
difficulty: Medium
topic: Binary Search
pattern: Binary search on the slope (compare mid with mid + 1)
link: https://leetcode.com/problems/peak-index-in-a-mountain-array/
lists: [Interview Extras]
followup_of: []
related: ["0162 Find Peak Element", "1095 Find in Mountain Array", "0278 First Bad Version"]
---

# 0852. Peak Index in a Mountain Array

## ⚡ 30-Second Summary
**Pattern:** Binary search on "am I still climbing?"
**Key insight:** `arr[i] < arr[i+1]` is true on the way up and false from the peak on. That is a true...true, false...false predicate, so binary search finds the first index where it turns false: the peak.
**Go-to:** Binary search comparing `arr[mid]` with `arr[mid+1]`, O(log n) time, O(1) space

## Problem
The array strictly increases up to one peak, then strictly decreases. Return the index of the peak in O(log n) time. [LeetCode](https://leetcode.com/problems/peak-index-in-a-mountain-array/)

**Examples:**
```
Input:  arr = [0,1,0]
Output: 1
Why:    1 is bigger than both neighbours.

Input:  arr = [0,2,1,0]
Output: 1
Why:    It rises to 2 at index 1, then only falls.

Input:  arr = [0,10,5,2]
Output: 1
Why:    10 is the top; everything after it is smaller.
```

**Constraints:**
- 3 ≤ n ≤ 10⁵; the array is guaranteed to be a mountain (the peak is never at either end).

## Hints
<details><summary>Hint 1</summary>
Pick any index mid. Looking only at arr[mid] and arr[mid+1], can you tell which side of the peak you're on?
</details>
<details><summary>Hint 2</summary>
If arr[mid] < arr[mid+1] you're still climbing, so the peak is to the right of mid. Otherwise you're at the peak or past it.
</details>
<details><summary>Hint 3</summary>
Climbing → lo = mid + 1. Not climbing → hi = mid (mid could be the peak). Loop while lo < hi; lo is the peak.
</details>

## Clarifying Questions
- Is the input guaranteed to be a valid mountain? (Yes.)
- Strictly increasing and decreasing, no plateaus? (Yes; plateaus would break the O(log n) argument.)
- Return the index, not the value? (The index.)

## Example Walkthrough
`[0,2,1,0]`: lo = 0, hi = 3. mid = 1: 2 < 1? No, not climbing → hi = 1. mid = 0: 0 < 2? Yes, climbing → lo = 1. lo == hi = 1.

## Approaches

### 1. Linear Scan: O(n) time, O(1) space
Return the first i with `arr[i] > arr[i+1]`. Fine, but misses the required O(log n).

### 2. Binary Search on the Slope ⭐ Go-to: O(log n) time, O(1) space
Compare `arr[mid]` with its right neighbour and keep the half that contains the peak.
**Why it's the go-to:** five lines, and the same code solves LC 162 (any peak, not just a mountain).

## Dry Run (Approach 2)
`arr = [24,69,100,99,79,78,67,36,26,19]`

| lo | hi | mid | arr[mid] < arr[mid+1]? | action |
|----|----|-----|------------------------|--------|
| 0 | 9 | 4 | 79 < 78: no | hi = 4 |
| 0 | 4 | 2 | 100 < 99: no | hi = 2 |
| 0 | 2 | 1 | 69 < 100: yes | lo = 2 |
| 2 | 2 | | | return **2** |

## Edge Case Check
- n = 3 → one or two steps, returns 1. ✅
- Peak at index n − 2 → lo keeps climbing; mid + 1 ≤ hi is always in bounds. ✅
- Peak at index 1 → hi drops to 1. ✅

## ⚠️ Pitfalls
- **Comparing with `arr[mid-1]`** combined with `lo = mid + 1` makes the update rules asymmetric and easy to get wrong. Comparing with `mid + 1` is safe because mid < hi always holds inside `while (lo < hi)`.
- **`hi = mid - 1` when not climbing** skips the peak if mid is the peak.
- **Returning `arr[lo]`** instead of `lo`.

## 🎯 What the Interviewer Wants
- See that the slope is a monotonic predicate even though the values aren't sorted.
- A loop that keeps mid + 1 in bounds and terminates.
- Mention that the same code finds a peak in LC 162.

## Follow-ups
- **Any peak in an arbitrary array:** [LC 0162 Find Peak Element](../0162-find-peak-element/)
- **Find a target in a mountain array:** find the peak, then binary search each side: LC 1095 Find in Mountain Array (not added yet)
- **Plain first-true search:** [LC 0278 First Bad Version](../0278-first-bad-version/)
