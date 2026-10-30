---
number: 34
title: Find First and Last Position of Element in Sorted Array
difficulty: Medium
topic: Binary Search
pattern: Lower & upper bound
link: https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
lists: [LC Top Interview 150]
followup_of: ["0035 Search Insert Position"]
related: ["0704 Binary Search", "0035 Search Insert Position", "2089 Find Target Indices After Sorting Array"]
---

# 0034. Find First and Last Position of Element in Sorted Array

## ⚡ 30-Second Summary
**Pattern:** Lower bound twice
**Key insight:** The first occurrence is `lowerBound(target)` (first ≥ target). The last occurrence is one before `lowerBound(target + 1)` (first > target). Two O(log n) searches, never a linear expansion.
**Go-to:** Two lower-bound searches, O(log n) time, O(1) space

## Problem
Given a sorted array (with possible duplicates) and a target, return the first and last index of the target, or `[-1, -1]` if it's absent. Must be O(log n).

**Examples:**
```
Input:  nums = [5,7,7,8,8,10], target = 8
Output: [3,4]
Why:    The two 8s occupy indices 3 and 4.

Input:  nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]
Why:    6 isn't in the array.

Input:  nums = [], target = 0
Output: [-1,-1]
Why:    Empty array.
```

**Constraints:**
- 0 ≤ n ≤ 10⁵ (empty input is allowed).
- Values and target in ±10⁹, so target + 1 still fits in a 32-bit int.

## Hints
<details><summary>Hint 1</summary>
Finding any occurrence then walking outward is O(n) when all elements are equal. Can a binary search find a boundary instead of an element?
</details>
<details><summary>Hint 2</summary>
"First index with value ≥ target" is a boundary search. What boundary marks the last occurrence?
</details>
<details><summary>Hint 3</summary>
first = lowerBound(target). If first == n or nums[first] != target, return [-1,-1]. Else last = lowerBound(target + 1) - 1.
</details>

## Clarifying Questions
- Can the array be empty? (Yes.)
- Duplicates? (Yes, that's the point.)
- Must it be O(log n)? (Yes; finding one copy and expanding is O(n) worst case.)

## Example Walkthrough
`[5,7,7,8,8,10], target 8`
- lowerBound(8): first index with value ≥ 8 is 3.
- nums[3] == 8, so it exists.
- lowerBound(9): first index ≥ 9 is 5 (value 10). Last = 5 - 1 = 4. Answer [3,4].

## Approaches

### 1. Linear Scan: O(n) time, O(1) space
First and last index where nums[i] == target.

### 2. Two Lower Bounds ⭐ Go-to: O(log n) time, O(1) space
One helper, called for target and target + 1. (A common middle step, "binary search one copy then expand", is O(n) when the array is all one value; mention it only to reject it.)
**Why it's the go-to:** reuses one well-tested helper; no separate "leftmost" and "rightmost" variants to get wrong.

## Dry Run (Approach 2)
`[2,2,2], target 2`

| call | lo | hi | mid | nums[mid] < x? | action |
|------|----|----|-----|----------------|--------|
| lb(2) | 0 | 3 | 1 | 2 < 2 no | hi = 1 |
| | 0 | 1 | 0 | no | hi = 0 → **first = 0** |
| lb(3) | 0 | 3 | 1 | 2 < 3 yes | lo = 2 |
| | 2 | 3 | 2 | yes | lo = 3 → 3, **last = 2** |

## Edge Case Check
- Empty array: lowerBound returns 0 == n, so [-1,-1]. ✅
- Single matching element `[1]`, target 1: [0,0]. ✅
- All elements equal the target: [0, n-1] in O(log n). ✅
- Target outside the range on either side: [-1,-1]. ✅

## ⚠️ Pitfalls
- **Reading nums[first] without checking first < n**: out of bounds when target > everything.
- **target + 1 overflow** if target could be INT_MAX (here it's ≤ 10⁹). Otherwise write a dedicated upper bound with `<=`.
- **"Find one, then expand"**: O(n) worst case, fails the requirement.
- **C++ `size_t` math**: `upper - 1` on size_t 0 wraps. Keep indices as int.

## 🎯 What the Interviewer Wants
- Boundary search instead of element search.
- Reuse of one helper (lower bound) for both ends.
- The empty and absent cases handled before indexing.

## Follow-ups
- **Count occurrences:** last - first + 1 (= upper bound - lower bound).
- **Insert position:** [LC 0035 Search Insert Position](../0035-search-insert-position/)
- **Library:** C++ `equal_range`, Python `bisect_left`/`bisect_right`, Go `sort.SearchInts` twice.
- **Unsorted input, return indices after sorting:** count less-than and equal: LC 2089 Find Target Indices After Sorting Array (not added yet)
