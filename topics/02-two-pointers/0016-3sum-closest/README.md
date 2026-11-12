---
number: 16
title: 3Sum Closest
difficulty: Medium
topic: Two Pointers
pattern: Sort + fix one + converging pointers
link: https://leetcode.com/problems/3sum-closest/
lists: [Interview Extras]
followup_of: ["0015 3Sum"]
related: ["0015 3Sum", "0018 4Sum", "0259 3Sum Smaller"]
---

# 0016. 3Sum Closest

## ⚡ 30-Second Summary
**Pattern:** 3Sum, but track the best distance instead of exact hits
**Key insight:** Sort. Fix i, then run lo/hi over the rest. If the sum is too small, move lo right; if too big, move hi left. That's the only move that can bring the sum closer. Keep the sum with the smallest `|sum − target|`, and return immediately on an exact match.
**Go-to:** Sort + two pointers, O(n²) time, O(1) extra (ignoring the sort)

## Problem
Pick three numbers at different indices whose sum is as close as possible to target, and return that sum. Exactly one closest answer is guaranteed. [LeetCode](https://leetcode.com/problems/3sum-closest/)

**Examples:**
```
Input:  nums = [-1,2,1,-4], target = 1
Output: 2
Why:    -1 + 2 + 1 = 2 is off by 1; no triple hits 1 exactly.

Input:  nums = [0,0,0], target = 1
Output: 0
Why:    The only triple sums to 0.
```

**Constraints:**
- 3 ≤ n ≤ 500, so O(n²) = 2.5·10⁵ and O(n³) = 1.25·10⁸ (too slow in Python).
- |nums[i]| ≤ 1000, |target| ≤ 10⁴, so sums fit in an int.

## Hints
<details><summary>Hint 1</summary>
How did you solve 3Sum in O(n²)? What changes when you want "closest" instead of "equal"?
</details>
<details><summary>Hint 2</summary>
After sorting and fixing nums[i], moving lo right increases the sum and moving hi left decreases it. Which one moves you towards target?
</details>
<details><summary>Hint 3</summary>
best = sum of the first three. For each i, lo = i+1, hi = n−1: s = nums[i]+nums[lo]+nums[hi]; if |s − t| &lt; |best − t|: best = s. If s &lt; t: lo++; elif s &gt; t: hi−−; else return s.
</details>

## Clarifying Questions
- Return the sum, not the triple? (The sum.)
- Is the closest answer unique? (Yes, guaranteed.)
- Any overflow risk? (No, small values.)

## Example Walkthrough
Sorted `[-4,-1,1,2]`, target 1. i = 0 (−4): lo/hi sums are −4−1+2 = −3, then −4+1+2 = −1, so best = −1. i = 1 (−1): −1+1+2 = 2, |2−1| = 1 < 2, so best = 2. Answer 2.

## Approaches

### 1. All Triples: O(n³) time, O(1) space
Three loops tracking the best. Fine for tiny n.

### 2. Sort + Two Pointers ⭐ Go-to: O(n²) time, O(1) extra
**Why it's the go-to:** the 3Sum skeleton with a different update, quadratic, plus an early exit on an exact match.

## Dry Run (Approach 2)
Sorted `[-4,-1,1,2]`, target 1

| i | lo | hi | sum | best | move |
|---|----|----|-----|------|------|
| 0 | 1 | 3 | −3 | −3 | lo++ |
| 0 | 2 | 3 | −1 | −1 | lo++ |
| 1 | 2 | 3 | 2 | **2** | hi−− |

## Edge Case Check
- n = 3 → the only triple. ✅
- Exact match → returned at once. ✅
- All equal values → any triple. ✅

## ⚠️ Pitfalls
- **Initialising `best` with INT_MAX:** `best − target` then overflows in C++. Start from the first triple.
- **Moving both pointers** on a non-match skips candidates.
- **Duplicate skipping** isn't needed for correctness here, only as an optimisation.

## 🎯 What the Interviewer Wants
- Adapting the 3Sum template.
- Why each pointer move is safe.
- O(n²) with an early exit.

## Follow-ups
- **Exact zero, all unique triples:** [LC 0015 3Sum](../0015-3sum/)
- **Four numbers:** [LC 0018 4Sum](../0018-4sum/)
- **Count triples below target:** LC 0259 3Sum Smaller (not added yet). When the sum is too small, add hi − lo pairs at once.
