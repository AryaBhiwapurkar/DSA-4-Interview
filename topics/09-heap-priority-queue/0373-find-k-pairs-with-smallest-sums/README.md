---
number: 373
title: Find K Pairs with Smallest Sums
difficulty: Medium
topic: Heap / Priority Queue
pattern: Min-heap frontier
link: https://leetcode.com/problems/find-k-pairs-with-smallest-sums/
lists: [LC Top Interview 150]
followup_of: []
related: ["0378 Kth Smallest Element in a Sorted Matrix", "0023 Merge k Sorted Lists", "0719 Find K-th Smallest Pair Distance"]
---

# 0373. Find K Pairs with Smallest Sums

## ⚡ 30-Second Summary
**Pattern:** Min-heap over a sorted "matrix" of sums (frontier expansion)
**Key insight:** With both arrays sorted, row i of the sum matrix (nums1[i] + nums2[j] for all j) is sorted. It's merging k sorted rows: seed the heap with (i, 0) for the first k rows, then each pop (i, j) pushes its right neighbour (i, j + 1).
**Go-to:** Heap of k row heads, O(k log k) time, O(k) space

## Problem
Given two ascending arrays and k, return the k pairs (u from nums1, v from nums2) with the smallest sums u + v. [LeetCode](https://leetcode.com/problems/find-k-pairs-with-smallest-sums/)

**Examples:**
```
Input:  nums1 = [1,7,11], nums2 = [2,4,6], k = 3
Output: [[1,2],[1,4],[1,6]]
Why:    Sums 3, 5, 7 are the three smallest; the next smallest is 7 + 2 = 9.

Input:  nums1 = [1,1,2], nums2 = [1,2,3], k = 2
Output: [[1,1],[1,1]]
Why:    Each 1 in nums1 pairs with the 1 in nums2: two different pairs, both sum 2.
```

**Constraints:**
- Lengths up to 10⁵ each, so m·n pairs (10¹⁰) can't all be generated.
- 1 ≤ k ≤ 10⁴; k may exceed m·n in small cases.

## Hints
<details><summary>Hint 1</summary>
Picture all sums as an m × n grid. What's sorted in it?
</details>
<details><summary>Hint 2</summary>
Each row is sorted (nums2 ascending). Choosing the global smallest repeatedly is a k-way merge.
</details>
<details><summary>Hint 3</summary>
Heap of (sum, i, j), seeded with j = 0 for i < min(k, m). Pop k times; after popping (i, j), push (i, j + 1) if j + 1 < n.
</details>

## Clarifying Questions
- Are both arrays sorted? (Yes, ascending.)
- Duplicates? (Yes; equal values at different indices are different pairs.)
- k larger than m·n? (Return all pairs.)

## Example Walkthrough
Example 1: seed (3: 1+2), (9: 7+2), (13: 11+2). Pop 3 → push (1,4)=5. Pop 5 → push (1,6)=7. Pop 7 → done: [1,2],[1,4],[1,6].

## Approaches

### 1. All Pairs, Sort: O(m·n log(m·n)) time, O(m·n) space
Fine for tiny inputs only.

### 2. Min-Heap Frontier ⭐ Go-to: O(k log k) time, O(k) space
Only ever holds one candidate per row (at most k rows).
**Why it's the go-to:** independent of m·n; the 0023 merge pattern on an implicit matrix.

## Dry Run (Approach 2)
`[1,1,2]`, `[1,2,3]`, k = 2

| pop (sum, i, j) | output | push |
|-----------------|--------|------|
| (2, 0, 0) | [1,1] | (3, 0, 1) |
| (2, 1, 0) | [1,1] | (3, 1, 1) |
| stop (k = 2) | **[[1,1],[1,1]]** | |

## Edge Case Check
- k > m·n: the heap empties first; return everything. ✅
- One array of length 1: a single row, popped in order. ✅

## ⚠️ Pitfalls
- **Seeding all m rows**: only min(k, m) can matter.
- **Pushing both (i+1, j) and (i, j+1)** from every pop: creates duplicates unless you track visited cells.
- **Python heap ties**: tuples (sum, i, j) compare by sum first, then indices, which is fine.

## 🎯 What the Interviewer Wants
- See the implicit sorted matrix and the k-way merge.
- Avoid duplicates with the "seed column 0, move right" scheme.

## Follow-ups
- **Kth smallest in a sorted matrix:** the same frontier, or binary search on value: LC 0378 Kth Smallest Element in a Sorted Matrix (not added yet)
- **Merge k sorted lists:** [LC 0023 Merge k Sorted Lists](../../06-linked-list/0023-merge-k-sorted-lists/)
- **k-th smallest pair distance:** binary search on the answer + two pointers: LC 0719 Find K-th Smallest Pair Distance (not added yet)
