---
number: 152
title: Maximum Product Subarray
difficulty: Medium
topic: 1-D Dynamic Programming
pattern: Track max & min
link: https://leetcode.com/problems/maximum-product-subarray/
lists: [NeetCode 150]
followup_of: []
related: ["0053 Maximum Subarray", "0238 Product of Array Except Self"]
---

# 0152. Maximum Product Subarray

## ⚡ 30-Second Summary
**Pattern:** Kadane's variant tracking both extremes
**Key insight:** A negative number turns the most negative product into the most positive one. So keep both the max **and** the min product of a subarray ending at i. Each new x picks from {x, x·max, x·min}.
**Go-to:** Track max and min ending here, O(n) time, O(1) space

## Problem
Return the largest product you can get from a non-empty contiguous subarray of an integer array. [LeetCode](https://leetcode.com/problems/maximum-product-subarray/)

**Examples:**
```
Input:  nums = [2,3,-2,4]
Output: 6
Why:    [2,3]. Including -2 turns the product negative and 4 alone is smaller.

Input:  nums = [-2,0,-1]
Output: 0
Why:    The 0 splits the array, and each side alone is negative. [-2,-1] isn't contiguous.
```

**Constraints:**
- 1 ≤ n ≤ 2·10⁴, -10 ≤ nums[i] ≤ 10.
- Any subarray product fits in a 32-bit int (guaranteed).

## Hints
<details><summary>Hint 1</summary>
In Maximum Subarray (sum), you keep the best sum ending at i. Why doesn't "best product ending at i" alone work here?
</details>
<details><summary>Hint 2</summary>
Multiplying by a negative flips the order: what was smallest becomes largest. What extra value should you carry?
</details>
<details><summary>Hint 3</summary>
Keep hi and lo, the max and min product ending at i. For each x: candidates = (x, x·hi, x·lo); hi = max, lo = min; best = max(best, hi). Use the old hi and lo for both.
</details>

## Clarifying Questions
- Can the array contain zeros and negatives? (Yes, both.)
- Non-empty subarray? (Yes, so [-2] → -2, not 0 or 1.)
- Overflow? (Guaranteed to fit in 32 bits.)

## Example Walkthrough
`[-2,3,-4]`: ending at -2: hi = lo = -2. At 3: hi = 3, lo = -6. At -4: candidates -4, -12, 24 → hi = 24. The min carried at -6 is what made 24 possible.

## Approaches

### 1. Brute Force: O(n²) time, O(1) space
For each start, extend to the right keeping a running product.

### 2. Track Max and Min ⭐ Go-to: O(n) time, O(1) space
One pass, carrying the max and min product ending at each index.
**Why it's the go-to:** linear, and it's the natural extension of Kadane's that interviewers expect.

(Alternative: the max of all prefix and suffix products, resetting to 1 after a zero, is also O(n). It's neat, but harder to justify on the spot.)

## Dry Run (Approach 2)
`[2,-5,-2,-4,3]`.

| x | candidates (x, x·hi, x·lo) | hi | lo | best |
|---|----------------------------|----|----|------|
| 2 | start | 2 | 2 | 2 |
| -5 | (-5, -10, -10) | -5 | -10 | 2 |
| -2 | (-2, 10, 20) | 20 | -2 | 20 |
| -4 | (-4, -80, 8) | 8 | -80 | 20 |
| 3 | (3, 24, -240) | 24 | -240 | **24** |

The 24 comes from [-2,-4,3]: hi at -4 was 8 = (-2)(-4).

## Edge Case Check
- Single negative `[-2]`: best = -2. ✅
- Zeros `[-2,0,-1]`: x = 0 resets hi and lo to 0 → best 0. ✅
- Even number of negatives: the whole span wins (handled by lo flipping). ✅

## ⚠️ Pitfalls
- **Tracking only the max** misses negative × negative.
- **Updating hi before computing lo** with the new hi: compute both from the old values (tuple, or temps).
- **Initializing best to 0** is wrong for all-negative single elements; start with nums[0].
- **Forgetting x alone** as a candidate, which is how a subarray restarts after a zero.

## 🎯 What the Interviewer Wants
- Explain why sums and products differ (sign flips).
- Kadane-style O(n) with both extremes.
- Handle zeros and single negatives.

## Follow-ups
- **Max sum instead of product:** [LC 0053 Maximum Subarray](../../15-greedy/0053-maximum-subarray/). Plain Kadane.
- **Products of everything except i:** [LC 0238 Product of Array Except Self](../../01-arrays-hashing/0238-product-of-array-except-self/)
- **Count subarrays with product < k:** LC 0713 Subarray Product Less Than K (not added yet). Sliding window, positives only.
