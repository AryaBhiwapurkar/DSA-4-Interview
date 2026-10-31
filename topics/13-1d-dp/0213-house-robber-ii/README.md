---
number: 213
title: House Robber II
difficulty: Medium
topic: 1-D Dynamic Programming
pattern: Two passes of House Robber
link: https://leetcode.com/problems/house-robber-ii/
lists: [NeetCode 150]
followup_of: ["0198 House Robber"]
related: ["0337 House Robber III"]
---

# 0213. House Robber II

## ⚡ 30-Second Summary
**Pattern:** Break the circle into two lines
**Key insight:** In a circle, the first and last houses can't both be robbed. So the answer is the better of "rob houses 0..n-2" and "rob houses 1..n-1", each solved with plain House Robber.
**Go-to:** Two linear House Robber passes, O(n) time, O(1) space

## Problem
Same as House Robber (no two adjacent houses), but the houses are arranged in a circle, so the first and last are also neighbours. Return the maximum you can rob. [LeetCode](https://leetcode.com/problems/house-robber-ii/)

**Examples:**
```
Input:  nums = [2,3,2]
Output: 3
Why:    Both 2s would make 4, but they sit next to each other around the circle. Take the 3.

Input:  nums = [1,2,3,1]
Output: 4
Why:    Houses 0 and 2 (1 + 3), which are not neighbours even in a circle.

Input:  nums = [1,2,3]
Output: 3
Why:    Every pair is adjacent in a 3-circle, so take the single largest.
```

**Constraints:**
- 1 ≤ n ≤ 100, 0 ≤ nums[i] ≤ 1000.

## Hints
<details><summary>Hint 1</summary>
What's the only new constraint compared to House Robber, and which two houses does it involve?
</details>
<details><summary>Hint 2</summary>
Any valid plan leaves out at least one of those two houses. What if you remove one of them up front?
</details>
<details><summary>Hint 3</summary>
Run House Robber on nums[0..n-2] and on nums[1..n-1], and return the max. Handle n = 1 separately (both ranges would be empty).
</details>

## Clarifying Questions
- Is it a true circle (first and last adjacent)? (Yes.)
- n = 1? (That house alone; it isn't its own neighbour.)
- Non-negative values? (Yes.)

## Example Walkthrough
`[2,3,2]`: without the last → [2,3] → 3. Without the first → [3,2] → 3. Max 3.

## Approaches

### 1. Memoized Recursion with a Flag: O(n) time, O(n) space
House Robber recursion plus a flag "did I take house 0?". If set, the last house is off limits. Works, but has twice the states and more edge logic.

### 2. Two Linear Passes ⭐ Go-to: O(n) time, O(1) space
Reuse House Robber I on two ranges.
**Why it's the go-to:** it reduces to a solved problem and is easy to argue correct.

## Dry Run (Approach 2)
`[1,3,1,3,100]`.

| pass | range | rolling best after each house | result |
|------|-------|-------------------------------|--------|
| skip last | [1,3,1,3] | 1, 3, 3, 6 | 6 |
| skip first | [3,1,3,100] | 3, 3, 6, 103 | 103 |

Answer **103** (houses 1 and 4: 3 + 100). Houses 4 and 0 are neighbours in the circle. The skip-last pass leaves out the 100 and the skip-first pass leaves out house 0, so no pass can take both.

## Edge Case Check
- n = 1: early return → 5. ✅
- n = 2: max of the two singles. ✅
- n = 3: every pair adjacent → largest single (example 3). ✅

## ⚠️ Pitfalls
- **n = 1** makes both ranges empty and returns 0 unless you special-case it.
- **Excluding both ends in one pass** (nums[1..n-2]) misses cases where one end is needed.
- **Python slices copy**: fine for n ≤ 100; pass indices for huge inputs.

## 🎯 What the Interviewer Wants
- Spot that the circle only couples house 0 and house n-1.
- Reduce to House Robber I twice, reusing the helper.
- Handle n = 1.

## Follow-ups
- **Line version:** [LC 0198 House Robber](../0198-house-robber/)
- **Tree version:** LC 0337 House Robber III (not added yet)
- **General circular DP trick:** fix the state of one element (taken / not taken), then solve the line.
