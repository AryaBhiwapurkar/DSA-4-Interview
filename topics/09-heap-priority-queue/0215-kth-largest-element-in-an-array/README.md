---
number: 215
title: Kth Largest Element in an Array
difficulty: Medium
topic: Heap / Priority Queue
pattern: Min-heap of size k / quickselect
link: https://leetcode.com/problems/kth-largest-element-in-an-array/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0703 Kth Largest Element in a Stream", "0973 K Closest Points to Origin", "0347 Top K Frequent Elements"]
---

# 0215. Kth Largest Element in an Array

## ⚡ 30-Second Summary
**Pattern:** Min-heap of size k (or quickselect)
**Key insight:** The k-th largest is the smallest of the k largest values. Keep a min-heap of at most k values; its top is the answer. Quickselect finds the element at sorted index n - k in O(n) average by partitioning only the side that contains it.
**Go-to:** Min-heap of size k, O(n log k) time, O(k) space; quickselect as the follow-up

## Problem
Return the k-th largest element of an unsorted array (k-th in sorted order, not k-th distinct). Can you do it without sorting? [LeetCode](https://leetcode.com/problems/kth-largest-element-in-an-array/)

**Examples:**
```
Input:  nums = [3,2,1,5,6,4], k = 2
Output: 5
Why:    Sorted descending: 6,5,4,... so the 2nd is 5.

Input:  nums = [3,2,3,1,2,4,5,5,6], k = 4
Output: 4
Why:    Descending 6,5,5,4,...: duplicates count separately.
```

**Constraints:**
- 1 ≤ k ≤ n ≤ 10⁵; values in ±10⁴.

## Hints
<details><summary>Hint 1</summary>
Sorting is O(n log n). Do you need the whole order?
</details>
<details><summary>Hint 2</summary>
Only the k largest matter. Which heap keeps them with the answer on top?
</details>
<details><summary>Hint 3</summary>
Min-heap: push each value, pop when size > k; answer = top. Or quickselect for index n - k with three-way partitioning.
</details>

## Clarifying Questions
- k-th distinct or k-th in order? (In order: duplicates count.)
- Can I modify the array? (Quickselect does; the heap doesn't.)

## Example Walkthrough
`[3,2,1,5,6,4], k = 2` with a min-heap: 3 → {3}; 2 → {2,3}; 1 → push, pop 1; 5 → pop 2 → {3,5}; 6 → pop 3 → {5,6}; 4 → pop 4 → {5,6}. Top 5.

## Approaches

### 1. Sort: O(n log n) time, O(1)-O(n) space
Sort and index n - k.

### 2. Min-Heap of Size k ⭐ Go-to: O(n log k) time, O(k) space
**Why it's the go-to:** simple, no worst-case surprises, works on streams.

### 3. Quickselect (Three-Way Partition): O(n) average, O(n²) worst, O(1) space
Partition around a pivot into < , =, > parts; recurse only into the part containing index n - k. A random pivot avoids the worst case in practice.

## Dry Run (Approach 3)
`[3,2,3,1,2,4,5,5,6], k = 4` → target index 5 (ascending)

| range | pivot (middle) | after partition | "=" block | target 5 is | next range |
|-------|----------------|-----------------|-----------|-------------|------------|
| 0..8 | 2 | 1, 2,2, 3,4,5,5,6,3 | indices 1..2 | right of it | 3..8 |
| 3..8 | 5 | 3,4,3, 5,5, 6 | indices 6..7 | left of it | 3..5 |
| 3..5 | 4 | 3,3, 4 | index 5 | inside | **4** |

## Edge Case Check
- k = 1: maximum; k = n: minimum. ✅
- All equal values: three-way partition finishes in one pass. ✅

## ⚠️ Pitfalls
- **Max-heap of all n then popping k times**: O(n + k log n), fine but not what's usually asked.
- **Two-way quickselect on many duplicates**: degrades to O(n²); use three-way partitioning.
- **Off-by-one target**: k-th largest is index n - k in ascending order.

## 🎯 What the Interviewer Wants
- Heap solution with the size-k reasoning.
- Quickselect with average/worst complexity and how to avoid the worst case.

## Follow-ups
- **Streaming version:** [LC 0703 Kth Largest Element in a Stream](../0703-kth-largest-element-in-a-stream/)
- **k closest points (same tools):** [LC 0973 K Closest Points to Origin](../0973-k-closest-points-to-origin/)
- **Guaranteed O(n):** median of medians (rarely expected).
