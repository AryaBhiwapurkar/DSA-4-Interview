---
number: 42
title: Trapping Rain Water
difficulty: Hard
topic: Two Pointers
pattern: Two pointers with running max
link: https://leetcode.com/problems/trapping-rain-water/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0011 Container With Most Water", "0238 Product of Array Except Self", "0084 Largest Rectangle in Histogram", "0407 Trapping Rain Water II"]
---

# 0042. Trapping Rain Water

## ⚡ 30-Second Summary
**Pattern:** Two pointers with running left/right max
**Key insight:** Water above bar i = min(maxLeft, maxRight) - h[i]. With pointers at both ends, whichever side has the smaller running max is the bottleneck: its water is fully determined by its own running max, so settle that side and move inward.
**Go-to:** Two pointers, O(n) time, O(1) space

## Problem
Given non-negative bar heights of width 1, return how many units of rain water are trapped between the bars after it rains. [LeetCode](https://leetcode.com/problems/trapping-rain-water/)

**Examples:**
```
Input:  height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Why:    Water sits at indices 2 (1), 4 (1), 5 (2), 6 (1), 9 (1) = 6.

Input:  height = [4,2,0,3,2,5]
Output: 9
Why:    Bounded by 4 on the left and 5 on the right: 2 + 4 + 1 + 2 = 9.
```

**Constraints:**
- 1 ≤ n ≤ 2·10⁴; 0 ≤ height[i] ≤ 10⁵.
- Total water ≤ 2·10⁴ × 10⁵ = 2·10⁹, which is just under INT_MAX (≈2.147·10⁹); fine in 32 bits here, 64-bit is safer in general.

## Hints
<details><summary>Hint 1</summary>
How much water sits on top of a single bar i? What does it depend on?
</details>
<details><summary>Hint 2</summary>
Precompute the max to the left and max to the right of every index.
</details>
<details><summary>Hint 3</summary>
With two pointers, if leftMax < rightMax, the left bar's water is leftMax - h[l] no matter what lies between; add it and move l. Otherwise do the same on the right.
</details>

## Clarifying Questions
- Bars have width 1? (Yes.)
- Can heights be 0? (Yes.)
- Is water lost off the edges? (Yes, the ends hold nothing.)

## Example Walkthrough
`height = [4,2,0,3,2,5]`
- maxLeft:  [4,4,4,4,4,5]; maxRight: [5,5,5,5,5,5].
- water[i] = min(L, R) - h: [0,2,4,1,2,0] → 9.

## Approaches

### 1. Brute Force: O(n²) time, O(1) space
For each i, scan left and right for the tallest bars. Recomputes the same maxima over and over.

### 2. Prefix/Suffix Max Arrays: O(n) time, O(n) space
Precompute `L[i] = max(h[0..i])` and `R[i] = max(h[i..n-1])`; sum `min(L, R) - h`. Clearest explanation (same idea as 0238).

### 3. Monotonic Stack: O(n) time, O(n) space
Keep a decreasing stack of indices; when a taller bar arrives, pop and fill the "basin" layer by layer. Computes water horizontally; good to know, rarely the expected answer.

### 4. Two Pointers ⭐ Go-to: O(n) time, O(1) space
`l, r` at the ends, `leftMax, rightMax` = 0. If `h[l] < h[r]`: update leftMax, add `leftMax - h[l]`, l++. Else mirror on the right.
**Why it's the go-to:** removes the two arrays from Approach 2 with the bottleneck argument. Explain with Approach 2, then optimize.

## Dry Run (Approach 4)
`height = [4,2,0,3,2,5]`

| l | r | h[l] | h[r] | side | leftMax | rightMax | add | total |
|---|---|------|------|------|---------|----------|-----|-------|
| 0 | 5 | 4 | 5 | left | 4 | 0 | 0 | 0 |
| 1 | 5 | 2 | 5 | left | 4 | 0 | 2 | 2 |
| 2 | 5 | 0 | 5 | left | 4 | 0 | 4 | 6 |
| 3 | 5 | 3 | 5 | left | 4 | 0 | 1 | 7 |
| 4 | 5 | 2 | 5 | left | 4 | 0 | 2 | 9 |
| 5 | 5 | | | stop | | | | 9 |

## Edge Case Check
- n < 3: nothing can be trapped, 0. ✅
- Strictly increasing or decreasing: 0. ✅
- Flat plateau, `[3,3,3]`: 0. ✅

## ⚠️ Pitfalls
- **Using `leftMax < rightMax` vs `h[l] < h[r]`:** both work if consistent; mixing the update order (add before updating the max) can produce negatives.
- **Off-by-one with prefix arrays:** include h[i] itself in L[i] and R[i], so min(L, R) - h[i] ≥ 0.
- **Overflow in other variants:** total can approach 2·10⁹; use 64-bit if limits grow.

## 🎯 What the Interviewer Wants
- The per-bar formula `min(maxLeft, maxRight) - h[i]`.
- Progression brute → prefix arrays → two pointers, with the bottleneck argument.
- Bonus: mention the stack approach.

## Follow-ups
- **2-D elevation map:** min-heap from the border inward: LC 0407 Trapping Rain Water II (not added yet)
- **Only two walls count, no bars in between:** [LC 0011 Container With Most Water](../0011-container-with-most-water/)
- **Same prefix/suffix idea with products:** [LC 0238 Product of Array Except Self](../../01-arrays-hashing/0238-product-of-array-except-self/)
