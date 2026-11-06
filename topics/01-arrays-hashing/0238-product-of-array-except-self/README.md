---
number: 238
title: Product of Array Except Self
difficulty: Medium
topic: Arrays & Hashing
pattern: Prefix & suffix products
link: https://leetcode.com/problems/product-of-array-except-self/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0042 Trapping Rain Water", "0152 Maximum Product Subarray", "0303 Range Sum Query - Immutable"]
---

# 0238. Product of Array Except Self

## ⚡ 30-Second Summary
**Pattern:** Prefix and suffix products
**Key insight:** The product of everything except i = (product of everything left of i) × (product of everything right of i). Build the left products in the output array, then sweep from the right with a running product.
**Go-to:** Output array + running suffix, O(n) time, O(1) extra space

## Problem
Given an integer array, return an array where each position holds the product of all other elements. Division is not allowed, and the solution must be O(n). [LeetCode](https://leetcode.com/problems/product-of-array-except-self/)

**Examples:**
```
Input:  nums = [1,2,3,4]
Output: [24,12,8,6]
Why:    e.g. index 1: 1 × 3 × 4 = 12.

Input:  nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]
Why:    Every position except the zero's includes the 0; index 2 is -1 × 1 × -3 × 3 = 9.
```

**Constraints:**
- 2 ≤ n ≤ 10⁵; -30 ≤ nums[i] ≤ 30.
- Every prefix and suffix product fits in a 32-bit int.
- No division; follow-up: O(1) extra space (the output array doesn't count).

## Hints
<details><summary>Hint 1</summary>
Split "everything except i" into two parts around i.
</details>
<details><summary>Hint 2</summary>
Precompute prefix[i] = product of nums[0..i-1] and suffix[i] = product of nums[i+1..n-1].
</details>
<details><summary>Hint 3</summary>
Store the prefixes directly in the answer array, then walk right-to-left multiplying in a single running suffix variable.
</details>

## Clarifying Questions
- Is division allowed? (No. It also breaks with zeros.)
- Can there be zeros? Negatives? (Yes, both.)
- Does the output array count as extra space? (No.)
- Can products overflow? (Guaranteed to fit in 32 bits.)

## Example Walkthrough
`nums = [1,2,3,4]`
- Left products: [1, 1, 2, 6] (nothing left of index 0, so 1).
- Right products: [24, 12, 4, 1].
- Multiply position-wise: [24, 12, 8, 6].

## Approaches

### 1. Brute Force: O(n²) time, O(1) extra space
For each i, multiply every j ≠ i. Too slow at 10⁵.

### 2. Prefix and Suffix Arrays: O(n) time, O(n) extra space
Build `prefix[]` and `suffix[]` separately, then `ans[i] = prefix[i] * suffix[i]`. The clearest explanation.

### 3. Output Array + Running Suffix ⭐ Go-to: O(n) time, O(1) extra space
Pass 1 writes prefix products into `ans`. Pass 2 goes right to left with `suffix = 1`: `ans[i] *= suffix; suffix *= nums[i]`.
**Why it's the go-to:** same idea as Approach 2 and meets the space follow-up with one variable. Explain with Approach 2, code Approach 3.

## Dry Run (Approach 3)
`nums = [1,2,3,4]`

| pass | i | ans (after) | running |
|------|---|-------------|---------|
| left | 0 | [1,_,_,_] | prefix = 1 |
| left | 1 | [1,1,_,_] | prefix = 2 |
| left | 2 | [1,1,2,_] | prefix = 6 |
| left | 3 | [1,1,2,6] | prefix = 24 |
| right | 3 | [1,1,2,6] | suffix = 4 |
| right | 2 | [1,1,8,6] | suffix = 12 |
| right | 1 | [1,12,8,6] | suffix = 24 |
| right | 0 | [24,12,8,6] | suffix = 24 |

## Edge Case Check
- One zero, `[-1,1,0,-3,3]`: only the zero's index is non-zero (9). ✅
- Two zeros: every product contains a zero, all 0. ✅
- n = 2, `[a,b]`: answer `[b,a]`. ✅

## ⚠️ Pitfalls
- **Division trick fails with zeros** (and is banned anyway).
- **Off-by-one in the prefix:** `ans[i]` is the product strictly left of i; set it *before* multiplying in `nums[i]`.
- **Overflow in other variants:** guaranteed safe here; in general use `long long` / `int64`.

## 🎯 What the Interviewer Wants
- Explain left × right decomposition clearly.
- Reach the O(1)-extra-space version.
- Handle zeros without special cases.

## Follow-ups
- **Division allowed?** Count zeros: 0 zeros → total/nums[i]; 1 zero → only that index gets the product of the rest; 2+ zeros → all 0.
- **Same left/right max idea:** [LC 0042 Trapping Rain Water](../../02-two-pointers/0042-trapping-rain-water/)
- **Range products/sums with many queries:** prefix arrays: LC 0303 Range Sum Query - Immutable (not added yet)
