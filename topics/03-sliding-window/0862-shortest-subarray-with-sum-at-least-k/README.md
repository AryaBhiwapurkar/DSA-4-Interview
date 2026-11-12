---
number: 862
title: Shortest Subarray with Sum at Least K
difficulty: Hard
topic: Sliding Window
pattern: Prefix sums + monotonic increasing deque
link: https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/
lists: [Interview Extras]
followup_of: ["0209 Minimum Size Subarray Sum"]
related: ["0209 Minimum Size Subarray Sum", "0239 Sliding Window Maximum", "0560 Subarray Sum Equals K"]
---

# 0862. Shortest Subarray with Sum at Least K

## ⚡ 30-Second Summary
**Pattern:** Prefix sums, with a deque of candidate start indices whose prefixes increase
**Key insight:** Negatives break the plain window, so look at prefixes P instead. You want the shortest j − i with `P[j] − P[i] ≥ k`. Keep a deque of indices with increasing P. At each j:
1. While `P[j] − P[front] ≥ k`, record j − front and pop the front. It can't give anything shorter later.
2. While `P[back] ≥ P[j]`, pop the back. j is a later start with a smaller-or-equal prefix, so it's strictly better.
3. Push j.
**Go-to:** Monotonic deque over prefix sums, O(n) time, O(n) space

## Problem
Return the length of the shortest non-empty contiguous subarray whose sum is at least k, or −1 if none exists. Values can be negative. [LeetCode](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/)

**Examples:**
```
Input:  nums = [1], k = 1
Output: 1
Why:    The single element reaches 1.

Input:  nums = [1,2], k = 4
Output: -1
Why:    The total is only 3.

Input:  nums = [2,-1,2], k = 3
Output: 3
Why:    Only the whole array reaches 3; the -1 has to be included.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵; −10⁵ ≤ nums[i] ≤ 10⁵; 1 ≤ k ≤ 10⁹.
- Prefix sums reach 10¹⁰ in magnitude: use 64-bit.

## Hints
<details><summary>Hint 1</summary>
With only positives this is LC 209's shrinking window. What exactly breaks with negatives?
</details>
<details><summary>Hint 2</summary>
Use prefix sums: you want j − i minimal with P[j] − P[i] ≥ k. If i₁ &lt; i₂ and P[i₁] ≥ P[i₂], is i₁ ever a useful start?
</details>
<details><summary>Hint 3</summary>
Deque of indices with increasing P. For each j: while P[j] − P[dq.front] ≥ k: best = min(best, j − front), pop front. While P[dq.back] ≥ P[j]: pop back. Push j.
</details>

## Clarifying Questions
- Negatives allowed? (Yes, which is the whole difficulty.)
- At least k (≥)? (Yes.)
- No answer? (Return −1.)

## Example Walkthrough
`[2,-1,2], k = 3` → P = [0,2,1,3]. j = 1: P=2; push → [0,1]. j = 2: P=1 ≤ P[1]=2, so pop 1 → [0,2]. j = 3: P=3, P[3] − P[0] = 3 ≥ 3 → best 3, pop 0. P[3] − P[2] = 2 < 3. Answer 3.

## Approaches

### 1. All Pairs of Prefixes: O(n²) time, O(n) space
For each j, scan every i < j. Correct, but too slow for 10⁵.

### 2. Monotonic Deque ⭐ Go-to: O(n) time, O(n) space
**Why it's the go-to:** each index is pushed and popped at most once, and the two pop rules each have a one-line justification.

## Dry Run (Approach 2)
`[2,-1,2], k = 3`, P = [0,2,1,3]

| j | P[j] | front pops (record) | back pops | deque after | best |
|---|------|---------------------|-----------|-------------|------|
| 0 | 0 | – | – | [0] | ∞ |
| 1 | 2 | 2−0 < 3 | – | [0,1] | ∞ |
| 2 | 1 | 1−0 < 3 | pop 1 (2 ≥ 1) | [0,2] | ∞ |
| 3 | 3 | 3−0 ≥ 3 → len 3, pop 0; 3−1 < 3 | – | [2,3] | **3** |

## Edge Case Check
- No valid subarray → −1. ✅
- One element ≥ k → 1. ✅
- Large negatives in between → step 2 discards dominated starts. ✅

## ⚠️ Pitfalls
- **Using the 209 shrinking window:** it gives wrong answers once negatives appear.
- **int prefix sums:** up to 10¹⁰ overflows 32-bit.
- **Popping the front without recording first,** or recording after popping.
- **Strictness of the back-pop:** pop when `P[back] ≥ P[j]`. Equal prefixes favour the later index.

## 🎯 What the Interviewer Wants
- Explain why the simple window fails.
- The prefix-sum reformulation and both deque invariants.
- Amortised O(n).

## Follow-ups
- **All positive values:** [LC 0209 Minimum Size Subarray Sum](../0209-minimum-size-subarray-sum/)
- **Another monotonic deque:** [LC 0239 Sliding Window Maximum](../0239-sliding-window-maximum/)
- **Exact sum, count instead of shortest:** [LC 0560 Subarray Sum Equals K](../../01-arrays-hashing/0560-subarray-sum-equals-k/)
