---
number: 974
title: Subarray Sums Divisible by K
difficulty: Medium
topic: Arrays & Hashing
pattern: Prefix sum mod k + count map
link: https://leetcode.com/problems/subarray-sums-divisible-by-k/
lists: [Interview Extras]
followup_of: ["0560 Subarray Sum Equals K"]
related: ["0560 Subarray Sum Equals K", "0523 Continuous Subarray Sum", "0525 Contiguous Array"]
---

# 0974. Subarray Sums Divisible by K

## ⚡ 30-Second Summary
**Pattern:** Prefix remainders + counting equal remainders
**Key insight:** `sum(i+1..j)` is divisible by k exactly when `P[j] ≡ P[i] (mod k)`. So count pairs of prefixes with the same remainder. For each new prefix, add how many earlier prefixes share its remainder. Normalise negative remainders into 0..k−1 first.
**Go-to:** Remainder count array of size k, O(n) time, O(k) space

## Problem
Count the non-empty contiguous subarrays whose sum is divisible by k. Values can be negative. [LeetCode](https://leetcode.com/problems/subarray-sums-divisible-by-k/)

**Examples:**
```
Input:  nums = [4,5,0,-2,-3,1], k = 5
Output: 7
Why:    [4,5,0,-2,-3,1], [5], [5,0], [5,0,-2,-3], [0], [0,-2,-3], [-2,-3] all sum to a multiple of 5.

Input:  nums = [5], k = 9
Output: 0
Why:    5 isn't a multiple of 9.
```

**Constraints:**
- 1 ≤ n ≤ 3·10⁴; 2 ≤ k ≤ 10⁴.
- −10⁴ ≤ nums[i] ≤ 10⁴, **negatives allowed**, so remainders can be negative in C++/Java.

## Hints
<details><summary>Hint 1</summary>
When is P[j] − P[i] divisible by k, in terms of P[j] mod k and P[i] mod k?
</details>
<details><summary>Hint 2</summary>
So you need pairs of prefixes with equal remainder. How do you count those in one pass?
</details>
<details><summary>Hint 3</summary>
cnt[0] = 1. For each x: r = ((r + x) % k + k) % k; answer += cnt[r]; cnt[r]++.
</details>

## Clarifying Questions
- Can numbers be negative? (Yes, so normalise the remainder.)
- Is k positive? (Yes, k ≥ 2.)
- Does a zero-sum subarray count? (Yes, 0 is divisible by k.)

## Example Walkthrough
`[4,5,0,-2,-3,1], k = 5`. The prefixes 4, 9, 9, 7, 4, 5 have remainders 4, 4, 4, 2, 4, 0, plus the starting 0. Group sizes: remainder 0 → 2 prefixes (the seed and the last) → 1 pair. Remainder 4 → 4 prefixes → 6 pairs. Remainder 2 → 1 → 0. Total 7.

## Approaches

### 1. All Subarrays: O(n²) time, O(1) space
Running sum per start, then test `sum % k == 0`. Too slow at the upper limits, but a fine baseline.

### 2. Remainder Counts ⭐ Go-to: O(n) time, O(k) space
**Why it's the go-to:** the 0560 template with "equal remainder" in place of "difference k", and an array works because remainders are bounded.

## Dry Run (Approach 2)
`[4,5,0,-2,-3,1], k = 5`

| x | r after | cnt[r] before | answer | cnt[r] after |
|---|---------|---------------|--------|--------------|
| – | 0 | | 0 | cnt[0] = 1 |
| 4 | 4 | 0 | 0 | 1 |
| 5 | 4 | 1 | 1 | 2 |
| 0 | 4 | 2 | 3 | 3 |
| −2 | 2 | 0 | 3 | 1 |
| −3 | 4 | 3 | 6 | 4 |
| 1 | 0 | 1 | **7** | 2 |

## Edge Case Check
- `[5], k = 9` → remainder 5 is new → 0. ✅
- All zeros `[0,0], k = 3` → 3 subarrays. ✅
- Negative-only `[-5], k = 5` → remainder 0 → 1. ✅

## ⚠️ Pitfalls
- **C++/Java `%` with negatives** gives a negative remainder (−2 % 5 == −2). Normalise with `(r % k + k) % k`. Python's `%` is already non-negative for positive k.
- **Forgetting `cnt[0] = 1`** misses subarrays that start at index 0.
- **Using the raw prefix as the key** instead of its remainder (that solves 0560, not this).

## 🎯 What the Interviewer Wants
- The modular reduction: equal remainders ⇒ divisible difference.
- Correct negative-remainder handling, called out explicitly.
- O(n) with O(k) space.

## Follow-ups
- **Exact sum instead of divisibility:** [LC 0560 Subarray Sum Equals K](../0560-subarray-sum-equals-k/)
- **Existence with length ≥ 2:** LC 0523 Continuous Subarray Sum (not added yet). Store the first index per remainder.
- **Longest instead of count:** first-index map, as in [LC 0525 Contiguous Array](../0525-contiguous-array/).
