---
number: 274
title: H-Index
difficulty: Medium
topic: Arrays & Hashing
pattern: Sort / counting
link: https://leetcode.com/problems/h-index/
lists: [LC Top Interview 150]
followup_of: []
related: ["0275 H-Index II"]
---

# 0274. H-Index

## ⚡ 30-Second Summary
**Pattern:** Counting sort (capped at n)
**Key insight:** h can never exceed n, so any citation count above n can be treated as n. Bucket papers by citations (0..n), then scan from n down, accumulating "papers with ≥ h citations" until that count reaches h.
**Go-to:** Counting buckets, O(n) time, O(n) space

## Problem
Given each paper's citation count, return the researcher's h-index: the largest h such that at least h papers have at least h citations each. [LeetCode](https://leetcode.com/problems/h-index/)

**Examples:**
```
Input:  citations = [3,0,6,1,5]
Output: 3
Why:    Three papers (3, 6, 5) have at least 3 citations; there aren't four with at least 4.

Input:  citations = [1,3,1]
Output: 1
Why:    Only one paper has at least 2 citations, so h = 2 fails; h = 1 works.
```

**Constraints:**
- 1 ≤ n ≤ 5000; 0 ≤ citations[i] ≤ 1000.

## Hints
<details><summary>Hint 1</summary>
If the papers are sorted by citations descending, what does position i tell you?
</details>
<details><summary>Hint 2</summary>
What's the largest h possible for n papers?
</details>
<details><summary>Hint 3</summary>
Count papers per citation value, capping values at n. Walk h from n down to 0, keeping a running total of papers with at least h citations.
</details>

## Clarifying Questions
- Can citations be 0? (Yes.)
- Is the input sorted? (No; if it were, see H-Index II with binary search.)
- Can I modify the array? (Affects sorting in place.)

## Example Walkthrough
`citations = [3,0,6,1,5]`, n = 5
- Sorted descending: [6,5,3,1,0].
- Position 1 (1-based): 6 ≥ 1 ✓. Position 2: 5 ≥ 2 ✓. Position 3: 3 ≥ 3 ✓. Position 4: 1 ≥ 4 ✗.
- h = 3.

## Approaches

### 1. Try Every h: O(n²) time, O(1) space
For h = n down to 0, count papers with ≥ h citations; return the first h that works.

### 2. Sort Descending: O(n log n) time, O(1) extra space
After sorting descending, h is the number of positions i (0-based) with `c[i] ≥ i + 1`.

### 3. Counting Buckets ⭐ Go-to: O(n) time, O(n) space
`bucket[min(c, n)]++`, then for h = n..0 add `bucket[h]` to a running total; return the first h with `total ≥ h`.
**Why it's the go-to:** linear and still short. Explain with the sorted picture, then cap at n to bucket.

## Dry Run (Approach 3)
`citations = [3,0,6,1,5]`, n = 5 → buckets (index = min(c, 5)): b[0]=1, b[1]=1, b[3]=1, b[5]=2

| h | bucket[h] | total (papers with ≥ h) | total ≥ h? |
|---|-----------|-------------------------|------------|
| 5 | 2 | 2 | no |
| 4 | 0 | 2 | no |
| 3 | 1 | 3 | yes, return 3 |

## Edge Case Check
- All zeros, `[0,0]`: total reaches h only at h = 0. Answer 0. ✅
- One paper with many citations, `[100]`: capped to bucket 1, h = 1. ✅
- All equal to n, `[3,3,3]`: h = 3. ✅

## ⚠️ Pitfalls
- **Not capping at n:** citations up to 1000 with n = 5 would index past the bucket array.
- **Off-by-one in the sorted version:** compare with `i + 1` (1-based count), not `i`.
- **Returning the citation value instead of h:** h is a count of papers.

## 🎯 What the Interviewer Wants
- Translate the definition into the sorted-array condition.
- Notice h ≤ n and use it for a linear counting solution.

## Follow-ups
- **Citations already sorted ascending, need O(log n):** binary search for the first i with `c[i] ≥ n - i`: LC 0275 H-Index II (not added yet)
- **Citations arrive as a stream:** keep counts, update h incrementally (h only increases).
