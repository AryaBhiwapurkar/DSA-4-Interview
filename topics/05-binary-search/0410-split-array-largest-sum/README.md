---
number: 410
title: Split Array Largest Sum
difficulty: Hard
topic: Binary Search
pattern: Binary search on the answer + greedy feasibility check
link: https://leetcode.com/problems/split-array-largest-sum/
lists: [Interview Extras]
followup_of: ["0875 Koko Eating Bananas"]
related: ["1011 Capacity To Ship Packages Within D Days", "0875 Koko Eating Bananas", "1283 Find the Smallest Divisor Given a Threshold", "1231 Divide Chocolate"]
---

# 0410. Split Array Largest Sum

## ⚡ 30-Second Summary
**Pattern:** "Minimise the maximum" → binary search on that maximum
**Key insight:** Fix a cap S. Cut greedily: extend the current piece while its sum stays ≤ S, and start a new piece otherwise. This uses the fewest pieces possible for that cap. Larger caps never need more pieces, so search for the smallest S in [max(nums), sum(nums)] where the greedy count is ≤ k.
**Go-to:** Binary search on the cap + greedy count, O(n log sum) time, O(1) space

## Problem
Split an array of non-negative integers into k non-empty contiguous pieces so that the largest piece sum is as small as possible. Return that smallest possible largest sum. [LeetCode](https://leetcode.com/problems/split-array-largest-sum/)

**Examples:**
```
Input:  nums = [7,2,5,10,8], k = 2
Output: 18
Why:    [7,2,5] | [10,8] gives sums 14 and 18; every other cut has a bigger max.

Input:  nums = [1,2,3,4,5], k = 2
Output: 9
Why:    [1,2,3] | [4,5] gives 6 and 9.
```

**Constraints:**
- 1 ≤ n ≤ 1000, 0 ≤ nums[i] ≤ 10⁶, 1 ≤ k ≤ min(50, n). The total is at most 10⁹, which fits in a 32-bit int but leaves little room.

## Hints
<details><summary>Hint 1</summary>
Flip the question: given a cap S, can you check whether k pieces with every sum ≤ S are possible?
</details>
<details><summary>Hint 2</summary>
Greedy check: keep adding to the current piece and cut only when the next number would push it over S. If that needs ≤ k pieces, S is achievable. Bigger S never needs more pieces.
</details>
<details><summary>Hint 3</summary>
Binary search S over [max(nums), sum(nums)] for the first S where the greedy count is ≤ k. Feasible → hi = mid, otherwise lo = mid + 1.
</details>

## Clarifying Questions
- Pieces must be contiguous and non-empty? (Yes, exactly k of them.)
- Can numbers be negative? (No. Non-negative values make the greedy and the monotonicity work.)
- Is k ≤ n guaranteed? (Yes.)

## Example Walkthrough
`[7,2,5,10,8], k = 2`. The cap lies between 10 (largest element) and 32 (whole array). At cap 17, greedy gives [7,2,5] [10] [8], 3 pieces: too many. At cap 18 it gives [7,2,5] [10,8], 2 pieces: OK. So 18 is the first feasible cap.

## Approaches

### 1. DP over Prefixes: O(k · n²) time, O(k · n) space
`dp[j][i]` is the best largest sum when the first i numbers form j pieces: `min over p < i of max(dp[j−1][p], sum(p..i−1))`. Correct and general, but 50 · 10⁶ steps: slow.

### 2. Binary Search on the Cap ⭐ Go-to: O(n log sum) time, O(1) space
The greedy piece count is monotonic in the cap, so lower-bound search the cap.
**Why it's the go-to:** about 30 × n work, and it's the same template as Koko and ship-packages: the interviewer expects you to see that.

## Dry Run (Approach 2)
`[7,2,5,10,8], k = 2`, lo = 10, hi = 32.

| lo | hi | mid | greedy pieces | ≤ k? | action |
|----|----|-----|---------------|------|--------|
| 10 | 32 | 21 | [7,2,5] [10,8] → 2 | yes | hi = 21 |
| 10 | 21 | 15 | [7,2,5] [10] [8] → 3 | no | lo = 16 |
| 16 | 21 | 18 | [7,2,5] [10,8] → 2 | yes | hi = 18 |
| 16 | 18 | 17 | [7,2,5] [10] [8] → 3 | no | lo = 18 |
| 18 | 18 | | | | return **18** |

## Edge Case Check
- k = 1 → the answer is sum(nums) = hi. ✅
- k = n → the answer is max(nums) = lo. ✅
- Zeros in the array (`[0,0,5]`, k = 3) → greedy can merge pieces, but fewer pieces than k is fine (see pitfalls). ✅

## ⚠️ Pitfalls
- **Requiring exactly k pieces in the check.** Using fewer than k pieces is fine: since k ≤ n you can always split some piece further without raising the max. So check `pieces ≤ k`.
- **lo = 0 or lo = min:** a cap below max(nums) can't hold that element alone. The greedy loop would then cut forever or miscount.
- **Overflow:** the sum fits in 32 bits here, but use 64-bit when values can be larger (Go int is already 64-bit).

## 🎯 What the Interviewer Wants
- Spot "minimise the maximum" → binary search on the answer.
- Prove the greedy check is optimal for a fixed cap, and that it's monotonic.
- Know the DP as the fallback and why it's slower.

## Follow-ups
- **Same problem, different story:** [LC 1011 Capacity To Ship Packages Within D Days](../1011-capacity-to-ship-packages-within-d-days/)
- **Maximise the minimum instead:** LC 1231 Divide Chocolate (not added yet)
- **Simpler binary search on the answer:** [LC 0875 Koko Eating Bananas](../0875-koko-eating-bananas/)
- **Sum of ceilings as the check:** [LC 1283 Find the Smallest Divisor Given a Threshold](../1283-find-the-smallest-divisor-given-a-threshold/)
