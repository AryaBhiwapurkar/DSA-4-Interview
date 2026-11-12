---
number: 560
title: Subarray Sum Equals K
difficulty: Medium
topic: Arrays & Hashing
pattern: Prefix sum + hashmap of counts
link: https://leetcode.com/problems/subarray-sum-equals-k/
lists: [Interview Extras]
followup_of: ["0001 Two Sum"]
related: ["0974 Subarray Sums Divisible by K", "0525 Contiguous Array", "0437 Path Sum III", "0209 Minimum Size Subarray Sum"]
---

# 0560. Subarray Sum Equals K

## ⚡ 30-Second Summary
**Pattern:** Prefix sums + hashmap counting earlier prefixes
**Key insight:** A subarray sum is a difference of two prefix sums: `sum(i+1..j) = P[j] − P[i]`. So for each j, count the earlier prefixes equal to `P[j] − k`. That's Two Sum on prefix sums. Seed the map with `{0: 1}` so subarrays starting at index 0 are counted.
**Go-to:** Running prefix + count map, O(n) time, O(n) space

## Problem
Count the contiguous, non-empty subarrays whose elements add up to exactly k. Values can be negative. [LeetCode](https://leetcode.com/problems/subarray-sum-equals-k/)

**Examples:**
```
Input:  nums = [1,1,1], k = 2
Output: 2
Why:    The first two 1s and the last two 1s.

Input:  nums = [1,2,3], k = 3
Output: 2
Why:    [1,2] and [3] both sum to 3.
```

**Constraints:**
- 1 ≤ n ≤ 2·10⁴, so O(n²) is about 4·10⁸ and borderline; O(n) is expected.
- −1000 ≤ nums[i] ≤ 1000, **negatives allowed**, so a sliding window doesn't work.
- −10⁷ ≤ k ≤ 10⁷.

## Hints
<details><summary>Hint 1</summary>
Why does a shrinking sliding window fail when numbers can be negative?
</details>
<details><summary>Hint 2</summary>
Write the sum of nums[i..j] using prefix sums. What do you need to know about earlier prefixes when you stand at j?
</details>
<details><summary>Hint 3</summary>
Keep count[prefix] for prefixes seen so far, starting with count[0] = 1. At each j: prefix += nums[j]; answer += count[prefix − k]; then count[prefix]++.
</details>

## Clarifying Questions
- Can values be negative or zero? (Yes, both.)
- Count subarrays, or return them? (Count.)
- Can the count be large? (Up to n(n+1)/2 for all-zero input with k = 0; that still fits in an int for n ≤ 2·10⁴.)

## Example Walkthrough
`[3, 4, -7, 3], k = 3`. The prefixes are 0, 3, 7, 0, 3. At P = 3 (j = 0), the earlier prefix 0 appears once → [3]. At P = 0 (j = 2), we need −3: none. At P = 3 (j = 3), we need 0, which has appeared twice (before the start and after index 2) → [3,4,−7,3] and [3]. Total 3. Negatives make a window approach miss these.

## Approaches

### 1. All Start/End Pairs: O(n²) time, O(1) space
For every start, extend the end and keep a running sum. Correct, and the natural first answer.

### 2. Prefix Sum + Count Map ⭐ Go-to: O(n) time, O(n) space
**Why it's the go-to:** one pass, it's Two Sum in disguise, and the same template solves Contiguous Array, Path Sum III and Subarray Sums Divisible by K.

## Dry Run (Approach 2)
`[1, 2, 3], k = 3`

| j | nums[j] | prefix | need prefix − k | count[need] | answer | count after |
|---|---------|--------|-----------------|-------------|--------|-------------|
| – | | 0 | | | 0 | {0:1} |
| 0 | 1 | 1 | −2 | 0 | 0 | {0:1, 1:1} |
| 1 | 2 | 3 | 0 | 1 | 1 | {0:1, 1:1, 3:1} |
| 2 | 3 | 6 | 3 | 1 | **2** | {…, 6:1} |

## Edge Case Check
- `k = 0` with zeros `[0,0,0]` → 6 (every subarray). The {0:1} seed handles it. ✅
- A single element equal to k → 1. ✅
- Negatives (`[1,-1,0], k = 0`) → 3: [1,-1], [0], [1,-1,0]. ✅

## ⚠️ Pitfalls
- **Sliding window:** only valid when all numbers are positive (that's LC 209). Negatives break the "shrink when too big" logic.
- **Forgetting `count[0] = 1`** misses every subarray that starts at index 0.
- **Updating the map before the lookup** counts the empty subarray when k = 0.
- **C++ `count[prefix - k]` with `operator[]`** inserts zeros; use `find` (or accept the extra entries knowingly).

## 🎯 What the Interviewer Wants
- Say why the window fails (negatives), then switch to prefix sums.
- The "Two Sum on prefixes" reduction and the `{0: 1}` seed.
- O(n) time, O(n) space.

## Follow-ups
- **Divisible by k instead of equal:** [LC 0974 Subarray Sums Divisible by K](../0974-subarray-sums-divisible-by-k/)
- **Longest instead of count (equal 0s and 1s):** [LC 0525 Contiguous Array](../0525-contiguous-array/)
- **Same idea on tree paths:** LC 0437 Path Sum III (not added yet)
- **All positive numbers, shortest window:** [LC 0209 Minimum Size Subarray Sum](../../03-sliding-window/0209-minimum-size-subarray-sum/)
