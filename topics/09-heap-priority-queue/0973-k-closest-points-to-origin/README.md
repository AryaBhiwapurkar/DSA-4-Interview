---
number: 973
title: K Closest Points to Origin
difficulty: Medium
topic: Heap / Priority Queue
pattern: Max-heap of size k
link: https://leetcode.com/problems/k-closest-points-to-origin/
lists: [NeetCode 150]
followup_of: []
related: ["0215 Kth Largest Element in an Array", "0347 Top K Frequent Elements", "0658 Find K Closest Elements"]
---

# 0973. K Closest Points to Origin

## ⚡ 30-Second Summary
**Pattern:** Max-heap of size k keyed by squared distance
**Key insight:** To keep the k **smallest** distances, use a **max**-heap: its top is the worst of the current best k, so any closer point replaces it. Compare x² + y² directly (no square roots).
**Go-to:** Max-heap of size k, O(n log k) time, O(k) space

## Problem
Return the k points closest to the origin (Euclidean distance). Any order; the answer is unique apart from order. [LeetCode](https://leetcode.com/problems/k-closest-points-to-origin/)

**Examples:**
```
Input:  points = [[1,3],[-2,2]], k = 1
Output: [[-2,2]]
Why:    Squared distances are 10 and 8; 8 is closer.

Input:  points = [[3,3],[5,-1],[-2,4]], k = 2
Output: [[3,3],[-2,4]]
Why:    Squared distances 18, 26, 20: the two smallest are 18 and 20.
```

**Constraints:**
- 1 ≤ k ≤ n ≤ 10⁴; coordinates in ±10⁴, so x² + y² ≤ 2·10⁸ fits in 32-bit.

## Hints
<details><summary>Hint 1</summary>
Do you need actual distances, or just a way to compare them?
</details>
<details><summary>Hint 2</summary>
To keep the k smallest values while scanning, which element must you be able to evict quickly?
</details>
<details><summary>Hint 3</summary>
Max-heap on x² + y²: push each point; if size > k, pop the farthest. Remaining heap = answer.
</details>

## Clarifying Questions
- Any output order? (Yes.)
- Ties at the boundary? (The answer is guaranteed unique.)

## Example Walkthrough
k = 2, distances 18 ([3,3]), 26 ([5,-1]), 20 ([-2,4]): heap {18}, {18,26}, push 20 → {18,20,26} → pop 26 → {18,20}.

## Approaches

### 1. Sort by Distance: O(n log n) time, O(n) space
Sort all points by x² + y², take the first k.

### 2. Max-Heap of Size k ⭐ Go-to: O(n log k) time, O(k) space
**Why it's the go-to:** better when k ≪ n, works on streams; quickselect (O(n) average) is the follow-up.

## Dry Run (Approach 2)
`[[3,3],[5,-1],[-2,4]], k = 2`

| point | d² | heap (max on top) after | popped |
|-------|----|-------------------------|--------|
| [3,3] | 18 | 18 | - |
| [5,-1] | 26 | 26, 18 | - |
| [-2,4] | 20 | 26, 20, 18 → pop | 26 |
| result | | **[3,3], [-2,4]** | |

## Edge Case Check
- k = n: all points. ✅
- Point at the origin: distance 0, always kept. ✅

## ⚠️ Pitfalls
- **Min-heap of all points**: O(n log n) and O(n) space; fine but not the k-sized trick.
- **sqrt / floating point**: unnecessary; compare squared distances.
- **Python**: heapq is a min-heap, so push (-d², x, y).

## 🎯 What the Interviewer Wants
- Explain the "max-heap to keep the k smallest" inversion.
- Avoid sqrt; state O(n log k).
- Mention quickselect for O(n) average.

## Follow-ups
- **Quickselect on distances:** partition until the first k are the closest, O(n) average.
- **k-th largest number:** [LC 0215 Kth Largest Element in an Array](../0215-kth-largest-element-in-an-array/)
- **Closest to a value in a sorted array:** binary search + window: LC 0658 Find K Closest Elements (not added yet)
