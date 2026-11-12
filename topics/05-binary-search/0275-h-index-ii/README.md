---
number: 275
title: H-Index II
difficulty: Medium
topic: Binary Search
pattern: First index where citations[i] ≥ n − i
link: https://leetcode.com/problems/h-index-ii/
lists: [Interview Extras]
followup_of: ["0274 H-Index"]
related: ["0274 H-Index", "0278 First Bad Version", "0035 Search Insert Position"]
---

# 0275. H-Index II

## ⚡ 30-Second Summary
**Pattern:** Lower-bound search on a predicate that mixes the value and the index
**Key insight:** In ascending order, the papers from index i to the end number `n − i`, and all have at least `citations[i]` citations. So h = n − i works exactly when `citations[i] ≥ n − i`. That predicate is false...false, true...true over i, so the first true index i gives the answer `n − i`. If there is none, the answer is 0.
**Go-to:** Binary search for the first i with citations[i] ≥ n − i, O(log n) time, O(1) space

## Problem
Given a researcher's citation counts sorted in ascending order, return their h-index: the largest h such that at least h papers have at least h citations each. Do it in logarithmic time. [LeetCode](https://leetcode.com/problems/h-index-ii/)

**Examples:**
```
Input:  citations = [0,1,3,5,6]
Output: 3
Why:    The last three papers (3, 5, 6) each have ≥ 3 citations; there aren't four with ≥ 4.

Input:  citations = [1,2,100]
Output: 2
Why:    Two papers have ≥ 2 citations; there aren't three with ≥ 3.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵; 0 ≤ citations[i] ≤ 1000; sorted ascending.

## Hints
<details><summary>Hint 1</summary>
Pick index i. How many papers have at least citations[i] citations?
</details>
<details><summary>Hint 2</summary>
n − i of them (index i through the end). So "h = n − i is achievable" is the same as citations[i] ≥ n − i. How does that behave as i grows?
</details>
<details><summary>Hint 3</summary>
Left side shrinks, right side grows, so it flips from false to true once. Binary search lo in [0, n] for the first true; return n − lo.
</details>

## Clarifying Questions
- Sorted ascending? (Yes, that's what makes O(log n) possible.)
- Can every paper have 0 citations? (Yes → h = 0.)
- Is h bounded by n? (Yes.)

## Example Walkthrough
`[0,1,3,5,6]`, n = 5. Check i = 2: citations 3 ≥ 5 − 2 = 3 ✓. Check i = 1: 1 ≥ 4 ✗. So i = 2 is the first true index → h = 3.

## Approaches

### 1. Linear Scan: O(n) time, O(1) space
Walk i from 0 and return n − i at the first `citations[i] ≥ n − i`; return 0 if none. Correct but ignores the log-time requirement.

### 2. Binary Search on the Index ⭐ Go-to: O(log n) time, O(1) space
Lower-bound search over [0, n] (n means "none true").
**Why it's the go-to:** once you see the predicate, it's the First Bad Version template.

## Dry Run (Approach 2)
`citations = [1,2,100]`, n = 3, search lo = 0, hi = 3.

| lo | hi | mid | citations[mid] ≥ n − mid? | action |
|----|----|-----|---------------------------|--------|
| 0 | 3 | 1 | 2 ≥ 2: yes | hi = 1 |
| 0 | 1 | 0 | 1 ≥ 3: no | lo = 1 |
| 1 | 1 | | | return n − 1 = **2** |

## Edge Case Check
- `[0]` → never true, lo = n = 1 → h = 0. ✅
- `[100]` → 100 ≥ 1 at i = 0 → h = 1. ✅
- `[0,0,0]` → h = 0. ✅
- All large `[11,15]` → h = n = 2. ✅

## ⚠️ Pitfalls
- **Searching for citations[i] == n − i:** equality may never happen. `[0,3,3]` has h = 2, but no index has citations[i] == n − i. Search for the first ≥.
- **hi = n − 1:** then "no index works" can't be represented; use hi = n.
- **Returning citations[i]** instead of n − i.

## 🎯 What the Interviewer Wants
- Derive the predicate `citations[i] ≥ n − i` from the definition.
- Lower-bound search with the "none" case handled.
- Contrast with LC 274 (unsorted: counting sort in O(n)).

## Follow-ups
- **Unsorted input:** bucket counts in O(n): [LC 0274 H-Index](../../01-arrays-hashing/0274-h-index/)
- **The plain first-true template:** [LC 0278 First Bad Version](../0278-first-bad-version/)
- **Insertion point search:** [LC 0035 Search Insert Position](../0035-search-insert-position/)
