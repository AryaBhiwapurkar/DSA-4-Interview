---
number: 303
title: Range Sum Query - Immutable
difficulty: Easy
topic: Arrays & Hashing
pattern: Prefix sums
link: https://leetcode.com/problems/range-sum-query-immutable/
lists: [Interview Extras]
followup_of: []
related: ["0304 Range Sum Query 2D - Immutable", "0307 Range Sum Query - Mutable", "0560 Subarray Sum Equals K", "0238 Product of Array Except Self"]
---

# 0303. Range Sum Query - Immutable

## ⚡ 30-Second Summary
**Pattern:** Precompute prefix sums once, answer each query in O(1)
**Key insight:** Store `P[i]` = sum of the first i elements, with `P[0] = 0`. Then `sum(l..r) = P[r+1] − P[l]`. The extra leading zero removes every special case for l = 0.
**Go-to:** Prefix array of length n + 1, O(n) build, O(1) per query, O(n) space

## Problem
Build a class over a fixed integer array that answers many "sum of elements from index left to right, inclusive" queries. [LeetCode](https://leetcode.com/problems/range-sum-query-immutable/)

**Examples:**
```
Input:  ["NumArray","sumRange","sumRange","sumRange"]
        [[[-2,0,3,-5,2,-1]],[0,2],[2,5],[0,5]]
Output: [null,1,-1,-3]
Why:    -2+0+3 = 1; 3-5+2-1 = -1; the whole array sums to -3.
```

**Constraints:**
- 1 ≤ n ≤ 10⁴; up to 10⁴ queries, so O(n) per query is 10⁸ total (too slow in spirit); O(1) per query is the point.
- The array never changes.

## Hints
<details><summary>Hint 1</summary>
The array never changes, but there are many queries. What could you compute once up front?
</details>
<details><summary>Hint 2</summary>
If you knew the sum of everything before index r + 1 and everything before l, how would you get the range sum?
</details>
<details><summary>Hint 3</summary>
P has n + 1 entries, P[0] = 0, P[i+1] = P[i] + nums[i]. sumRange(l, r) = P[r+1] − P[l].
</details>

## Clarifying Questions
- Is the array ever updated? (No; with updates it becomes a Fenwick or segment tree problem.)
- Are l and r inclusive and always valid? (Yes, 0 ≤ l ≤ r < n.)
- Can sums overflow? (No: at most 10⁴ · 10⁵ = 10⁹ in magnitude.)

## Example Walkthrough
nums = [-2, 0, 3, -5, 2, -1] → P = [0, -2, -2, 1, -4, -2, -3]. sumRange(2, 5) = P[6] − P[2] = −3 − (−2) = −1.

## Approaches

### 1. Sum on Every Query: O(1) build, O(n) per query
Loop from l to r each time. Fine for a handful of queries.

### 2. Prefix Sums ⭐ Go-to: O(n) build, O(1) per query, O(n) space
**Why it's the go-to:** it's the canonical precompute-then-query trick, and the n + 1 layout is the habit to build.

## Dry Run (Approach 2)
P = [0, -2, -2, 1, -4, -2, -3]

| query | P[r+1] | P[l] | answer |
|-------|--------|------|--------|
| (0, 2) | P[3] = 1 | P[0] = 0 | **1** |
| (2, 5) | P[6] = −3 | P[2] = −2 | **−1** |
| (0, 5) | P[6] = −3 | P[0] = 0 | **−3** |

## Edge Case Check
- l == r → a single element. ✅
- l = 0 → P[0] = 0, so no special case. ✅
- n = 1 → P = [0, x]. ✅

## ⚠️ Pitfalls
- **Length-n prefix array** forces an `if l == 0` branch and invites off-by-one errors; use n + 1.
- **`P[r] − P[l]`** misses nums[r]. Inclusive r means P[r + 1].
- **Recomputing per query** defeats the purpose when queries are many.

## 🎯 What the Interviewer Wants
- Precompute once, O(1) per query.
- Clean indexing with the leading zero.
- Know the follow-up: updates need a Fenwick or segment tree.

## Follow-ups
- **2-D version:** [LC 0304 Range Sum Query 2D - Immutable](../0304-range-sum-query-2d-immutable/)
- **With point updates:** LC 0307 Range Sum Query - Mutable (not added yet). Fenwick tree, O(log n) both ways.
- **Count subarrays with a given sum:** [LC 0560 Subarray Sum Equals K](../0560-subarray-sum-equals-k/)
