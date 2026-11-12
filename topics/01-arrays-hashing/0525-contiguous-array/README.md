---
number: 525
title: Contiguous Array
difficulty: Medium
topic: Arrays & Hashing
pattern: Prefix sum + first-seen index map
link: https://leetcode.com/problems/contiguous-array/
lists: [Interview Extras]
followup_of: ["0560 Subarray Sum Equals K"]
related: ["0560 Subarray Sum Equals K", "0974 Subarray Sums Divisible by K", "0325 Maximum Size Subarray Sum Equals k"]
---

# 0525. Contiguous Array

## ⚡ 30-Second Summary
**Pattern:** Map 0 → −1, then find the longest subarray with sum 0
**Key insight:** Equal numbers of 0s and 1s means the sum is 0 once every 0 counts as −1. A zero-sum subarray sits between two equal prefix sums. Store the **first** index where each prefix appeared (seed `{0: −1}`). Each later repeat gives a candidate length `i − first[prefix]`.
**Go-to:** Running balance + first-index map, O(n) time, O(n) space

## Problem
Given a binary array, return the length of the longest contiguous subarray with the same number of 0s and 1s. [LeetCode](https://leetcode.com/problems/contiguous-array/)

**Examples:**
```
Input:  nums = [0,1]
Output: 2
Why:    One 0 and one 1.

Input:  nums = [0,1,0]
Output: 2
Why:    [0,1] or [1,0]; the whole array has two 0s and one 1.

Input:  nums = [0,1,1,1,1,1,0,0,0]
Output: 6
Why:    [1,1,1,0,0,0] at the end has three of each.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵, so O(n²) is too slow.
- Values are only 0 or 1.

## Hints
<details><summary>Hint 1</summary>
Could you turn "equal counts" into "sum equals some fixed number"?
</details>
<details><summary>Hint 2</summary>
Replace each 0 with −1. When do two prefix sums tell you the subarray between them sums to 0?
</details>
<details><summary>Hint 3</summary>
balance += (x == 1 ? 1 : −1). Keep first[balance] = earliest index, seeded with first[0] = −1. If the balance was seen before, best = max(best, i − first[balance]); otherwise record i.
</details>

## Clarifying Questions
- Only 0s and 1s? (Yes.)
- Return the length or the subarray? (Length; 0 if none exists.)
- Can the array be all 0s? (Yes, then the answer is 0.)

## Example Walkthrough
`[0,0,1,0,1,1]` → balances after each index: −1, −2, −1, −2, −1, 0. Balance 0 first appears at −1 (the seed), so at i = 5 the length is 5 − (−1) = 6: the whole array. Balance −1 at i = 0 and again at 4 gives 4, which is shorter.

## Approaches

### 1. All Subarrays with Running Counts: O(n²) time, O(1) space
For each start, extend and track zeros − ones. Correct but too slow for 10⁵.

### 2. Balance + First-Index Map ⭐ Go-to: O(n) time, O(n) space
**Why it's the go-to:** it's the 0560 template with "count" swapped for "longest", and the −1 trick is the one insight to state.

(The balance only ranges over −n..n, so an array of size 2n + 1 can replace the hashmap.)

## Dry Run (Approach 2)
`[0,1,0]`

| i | x | balance | first seen? | length | best | first map |
|---|---|---------|-------------|--------|------|-----------|
| – | | 0 | | | 0 | {0:−1} |
| 0 | 0 | −1 | no | | 0 | {0:−1, −1:0} |
| 1 | 1 | 0 | at −1 | 2 | 2 | |
| 2 | 0 | −1 | at 0 | 2 | **2** | |

## Edge Case Check
- All 0s → balance never repeats → 0. ✅
- Answer starting at index 0 → the {0: −1} seed gives i + 1. ✅
- n = 1 → 0. ✅

## ⚠️ Pitfalls
- **Overwriting the first index** with later ones shrinks the answer. Only store the first occurrence.
- **Seeding `{0: 0}` instead of `{0: −1}`** is off by one for subarrays that start at 0.
- **Counting instead of tracking the longest:** this isn't 0560 exactly. You need indices, not counts.

## 🎯 What the Interviewer Wants
- The 0 → −1 transformation.
- Reduce to "longest subarray with sum 0" using prefix sums.
- Store only the earliest index, and seed correctly.

## Follow-ups
- **Count subarrays with sum k:** [LC 0560 Subarray Sum Equals K](../0560-subarray-sum-equals-k/)
- **Longest subarray with sum exactly k:** LC 0325 Maximum Size Subarray Sum Equals k (not added yet). Same first-index map.
- **Divisibility instead of equality:** [LC 0974 Subarray Sums Divisible by K](../0974-subarray-sums-divisible-by-k/)
