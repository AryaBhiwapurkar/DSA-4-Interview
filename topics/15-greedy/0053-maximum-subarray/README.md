---
number: 53
title: Maximum Subarray
difficulty: Medium
topic: Greedy
pattern: Kadane
link: https://leetcode.com/problems/maximum-subarray/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0918 Maximum Sum Circular Subarray", "0152 Maximum Product Subarray", "0121 Best Time to Buy and Sell Stock"]
---

# 0053. Maximum Subarray

## ⚡ 30-Second Summary
**Pattern:** Kadane's algorithm (greedy, or 1-D DP on "best sum ending here")
**Key insight:** The best subarray ending at i either extends the one ending at i-1 or starts fresh at i: `cur = max(x, cur + x)`. A negative running sum can only drag down whatever comes next, so drop it.
**Go-to:** Kadane, O(n) time, O(1) space

## Problem
Return the largest sum of any non-empty run of consecutive elements in an integer array. [LeetCode](https://leetcode.com/problems/maximum-subarray/)

**Examples:**
```
Input:  nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Why:    [4,-1,2,1]. The -1 is worth keeping because 2 and 1 come right after it.

Input:  nums = [1]
Output: 1
Why:    The only subarray.

Input:  nums = [5,4,-1,7,8]
Output: 23
Why:    The whole array: the single -1 is outweighed by both sides.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵, values in [-10⁴, 10⁴]: sums stay within ±10⁹, fine for int.
- Non-empty, so an all-negative array returns its largest element, not 0.

## Hints
<details><summary>Hint 1</summary>
For each index, what's the best subarray that must end exactly there?
</details>
<details><summary>Hint 2</summary>
If the best sum ending at i-1 is negative, is it ever worth attaching it to element i?
</details>
<details><summary>Hint 3</summary>
cur = max(x, cur + x); best = max(best, cur). Seed both with nums[0] so all-negative arrays work.
</details>

## Clarifying Questions
- Non-empty subarray? (Yes. All negatives → the max element.)
- Return the sum or the indices? (Sum. For indices, record where cur restarts.)
- Value range / overflow? (≤ 10⁹ in magnitude, int is fine.)

## Example Walkthrough
`[-2,1,-3,4]`: start cur = -2. At 1: max(1, -1) → restart at 1. At -3: max(-3, -2) = -2, keep going. At 4: max(4, 2) → restart at 4. The best so far is 4.

## Approaches

### 1. Brute Force: O(n²) time, O(1) space
Fix a start, extend to every end with a running sum.

### 2. Divide and Conquer: O(n log n) time, O(log n) space
The best subarray lies in the left half, the right half, or crosses the middle (best suffix of left + best prefix of right). The classic follow-up the problem itself mentions.

### 3. Kadane ⭐ Go-to: O(n) time, O(1) space
**Why it's the go-to:** optimal, three lines, and the "drop a negative prefix" argument is easy to justify.

## Dry Run (Approach 3)
`[-2,1,-3,4,-1,2,1,-5,4]`

| x | cur = max(x, cur + x) | best |
|---|-----------------------|------|
| -2 | -2 (seed) | -2 |
| 1 | max(1, -1) = 1 (restart) | 1 |
| -3 | max(-3, -2) = -2 | 1 |
| 4 | max(4, 2) = 4 (restart) | 4 |
| -1 | 3 | 4 |
| 2 | 5 | 5 |
| 1 | 6 | **6** |
| -5 | 1 | 6 |
| 4 | 5 | 6 |

## Edge Case Check
- All negative `[-3,-1,-2]` → -1. ✅
- Single element → itself. ✅
- All positive → the whole array (cur never restarts). ✅

## ⚠️ Pitfalls
- **Seeding with 0** returns 0 for all-negative input.
- **Resetting cur to 0 before comparing** (`if cur < 0: cur = 0` placed wrong) can skip the single-element case; `max(x, cur + x)` avoids it.
- **Divide and conquer cross sum:** both halves of the crossing part must be non-empty (start at mid and mid+1).

## 🎯 What the Interviewer Wants
- Brute force, then Kadane with the "negative prefix" justification.
- Correct all-negative handling.
- Often asked: return the indices, or do divide and conquer.

## Follow-ups
- **Circular array:** [LC 0918 Maximum Sum Circular Subarray](../0918-maximum-sum-circular-subarray/)
- **Product instead of sum:** [LC 0152 Maximum Product Subarray](../../13-1d-dp/0152-maximum-product-subarray/)
- **Same idea on price differences:** [LC 0121 Best Time to Buy and Sell Stock](../../03-sliding-window/0121-best-time-to-buy-and-sell-stock/)
- **Best rectangle in a 2-D matrix:** fix two rows, run Kadane on the column sums (O(n³)).
