---
number: 1283
title: Find the Smallest Divisor Given a Threshold
difficulty: Medium
topic: Binary Search
pattern: Binary search on the answer (sum of ceilings)
link: https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/
lists: [Interview Extras]
followup_of: ["0875 Koko Eating Bananas"]
related: ["0875 Koko Eating Bananas", "1011 Capacity To Ship Packages Within D Days", "0410 Split Array Largest Sum"]
---

# 1283. Find the Smallest Divisor Given a Threshold

## ⚡ 30-Second Summary
**Pattern:** Smallest d whose cost fits a budget → binary search on d
**Key insight:** `f(d) = Σ ceil(x / d)` never increases as d grows. Search d over [1, max(nums)] for the first d with f(d) ≤ threshold. At d = max every term is 1, and threshold ≥ n, so an answer always exists.
**Go-to:** Binary search on the divisor, O(n log max) time, O(1) space

## Problem
Divide every number by a positive integer d, rounding each result up, and add the results. Return the smallest d for which that sum is at most `threshold`. [LeetCode](https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/)

**Examples:**
```
Input:  nums = [1,2,5,9], threshold = 6
Output: 5
Why:    d = 5 gives 1+1+1+2 = 5 ≤ 6; d = 4 gives 1+1+2+3 = 7.

Input:  nums = [44,22,33,11,1], threshold = 5
Output: 44
Why:    The budget equals n, so every term must be 1: d must be at least the max.
```

**Constraints:**
- 1 ≤ n ≤ 5 · 10⁴, 1 ≤ nums[i] ≤ 10⁶, n ≤ threshold ≤ 10⁶ (so d = max(nums) always works).

## Hints
<details><summary>Hint 1</summary>
As d increases, what happens to each ceil(x / d), and to their sum?
</details>
<details><summary>Hint 2</summary>
The sum only goes down (or stays the same). What's the smallest d worth trying, and what d is always good enough?
</details>
<details><summary>Hint 3</summary>
Binary search d in [1, max(nums)]: if the sum of (x + d − 1) / d is ≤ threshold, then hi = d, otherwise lo = d + 1.
</details>

## Clarifying Questions
- Positive integer divisors only? (Yes.)
- Is threshold ≥ n guaranteed? (Yes, so an answer exists.)
- Round each term up, not the total? (Each term.)

## Example Walkthrough
`[1,2,5,9], threshold = 6`: d = 5 → 1+1+1+2 = 5 fits. d = 4 → 1+1+2+3 = 7 doesn't fit. Since the sum is monotonic, 5 is the smallest.

## Approaches

### 1. Try Every Divisor: O(n · max) time, O(1) space
d = 1, 2, … until the sum fits. Up to 10⁶ × 5 · 10⁴: too slow.

### 2. Binary Search on the Divisor ⭐ Go-to: O(n log max) time, O(1) space
Lower-bound search on the monotonic "sum(d) ≤ threshold" predicate.
**Why it's the go-to:** about 20 passes over the array; this is Koko with the hours budget renamed to threshold.

## Dry Run (Approach 2)
`[1,2,5,9], threshold = 6`, lo = 1, hi = 9.

| lo | hi | mid | Σ ceil(x/mid) | ≤ 6? | action |
|----|----|-----|---------------|------|--------|
| 1 | 9 | 5 | 1+1+1+2 = 5 | yes | hi = 5 |
| 1 | 5 | 3 | 1+1+2+3 = 7 | no | lo = 4 |
| 4 | 5 | 4 | 1+1+2+3 = 7 | no | lo = 5 |
| 5 | 5 | | | | return **5** |

## Edge Case Check
- threshold = n → answer max(nums). ✅
- threshold ≥ sum(nums) → answer 1. ✅
- Single element `[x]`, threshold t → ceil(x / t). ✅

## ⚠️ Pitfalls
- **lo = 0** → division by zero.
- **Float ceil** (`ceil(x / d)` with ints in C++ is integer division first, so it rounds down). Use `(x + d − 1) / d`.
- **Sum overflow:** at d = 1 the sum can reach 5 · 10¹⁰. Use 64-bit, or stop adding once the sum passes the threshold.

## 🎯 What the Interviewer Wants
- Same template as Koko: identify the monotonic predicate and the bounds.
- Integer ceiling division, written correctly.
- Overflow awareness at small d.

## Follow-ups
- **Hours per pile with an hour budget:** [LC 0875 Koko Eating Bananas](../0875-koko-eating-bananas/)
- **Contiguous chunks instead of independent items:** [LC 1011 Capacity To Ship Packages Within D Days](../1011-capacity-to-ship-packages-within-d-days/)
- **Minimise the largest of k pieces:** [LC 0410 Split Array Largest Sum](../0410-split-array-largest-sum/)
