---
number: 300
title: Longest Increasing Subsequence
difficulty: Medium
topic: 1-D Dynamic Programming
pattern: DP / patience sort + binary search
link: https://leetcode.com/problems/longest-increasing-subsequence/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0354 Russian Doll Envelopes", "0673 Number of Longest Increasing Subsequence", "1143 Longest Common Subsequence"]
---

# 0300. Longest Increasing Subsequence

## ⚡ 30-Second Summary
**Pattern:** "Longest ending at i" DP, upgraded with binary search
**Key insight:** Keep `tails[k]` = the smallest possible last value of an increasing subsequence of length k+1. `tails` is always sorted, so each new x either extends it (bigger than all) or replaces the first tail ≥ x. The length of `tails` is the answer.
**Go-to:** Tails array + binary search, O(n log n) time, O(n) space

## Problem
Return the length of the longest subsequence (keep the order, skip any elements) whose values are strictly increasing. [LeetCode](https://leetcode.com/problems/longest-increasing-subsequence/)

**Examples:**
```
Input:  nums = [10,9,2,5,3,7,101,18]
Output: 4
Why:    2, 3, 7, 18 (or 2, 5, 7, 101). Nothing of length 5 exists.

Input:  nums = [0,1,0,3,2,3]
Output: 4
Why:    0, 1, 2, 3, taking the 2 and the final 3.

Input:  nums = [7,7,7,7,7,7,7]
Output: 1
Why:    Strictly increasing, so equal values can't follow each other.
```

**Constraints:**
- 1 ≤ n ≤ 2500, so O(n²) ≈ 6·10⁶ passes. The follow-up asks for O(n log n).
- Values in ±10⁴.

## Hints
<details><summary>Hint 1</summary>
Define dp[i] = longest increasing subsequence that ends exactly at index i. How do you compute it from earlier indices?
</details>
<details><summary>Hint 2</summary>
For O(n log n): among all increasing subsequences of the same length, which one is the most useful to keep extending?
</details>
<details><summary>Hint 3</summary>
The one with the smallest last value. Keep a sorted array tails; for each x, binary-search the first tail ≥ x and replace it, or append if none. Return len(tails). Note that tails is not itself a valid subsequence.
</details>

## Clarifying Questions
- Strictly increasing or non-decreasing? (Strict. That decides lower_bound vs upper_bound.)
- Length only, or the subsequence itself? (Length. Reconstruction needs parent pointers.)
- Subsequence, not subarray? (Yes, gaps allowed.)

## Example Walkthrough
`[0,1,0,3,2,3]` with dp[i]: dp = [1, 2, 1, 3, 3, 4]. The last 3 extends the 2 (dp = 3), giving 4.

## Approaches

### 1. DP, Longest Ending at i: O(n²) time, O(n) space
`dp[i] = 1 + max(dp[j])` over j < i with nums[j] < nums[i]. The answer is max(dp). Present this first: it's the standard DP derivation.

### 2. Tails + Binary Search ⭐ Go-to: O(n log n) time, O(n) space
Patience sorting. Each x does one binary search.
**Why it's the go-to:** optimal, and with `lower_bound` / `bisect_left` it's shorter than the O(n²) DP. Lead with the O(n²) idea, then upgrade.

## Dry Run (Approach 2)
`[10,9,2,5,3,7,101,18]`.

| x | first tail ≥ x | action | tails |
|---|----------------|--------|-------|
| 10 | none | append | [10] |
| 9 | 10 at 0 | replace | [9] |
| 2 | 9 at 0 | replace | [2] |
| 5 | none | append | [2, 5] |
| 3 | 5 at 1 | replace | [2, 3] |
| 7 | none | append | [2, 3, 7] |
| 101 | none | append | [2, 3, 7, 101] |
| 18 | 101 at 3 | replace | [2, 3, 7, 18] |

Length **4**.

## Edge Case Check
- All equal: lower_bound finds the existing tail each time → length 1. ✅
- Strictly decreasing: always replace tails[0] → 1. ✅
- n = 1: 1. ✅
- `[4,10,4,3,8,9]`: tails ends as [3, 8, 9] → 3. ✅

## ⚠️ Pitfalls
- **upper_bound vs lower_bound:** upper_bound counts equal values as increasing (non-decreasing LIS).
- **Reading tails as the answer sequence:** it holds the right length, but its values may not form a real subsequence.
- **dp answer is max(dp), not dp[n-1].**

## 🎯 What the Interviewer Wants
- The O(n²) DP with a clear state, then the O(n log n) upgrade when asked.
- Explain why tails stays sorted and why replacing keeps future options open.
- Strict vs non-strict handled correctly.

## Follow-ups
- **2-D version (envelopes):** LC 0354 Russian Doll Envelopes (not added yet). Sort by width ascending and height descending, then run LIS on heights.
- **Count the LIS:** LC 0673 Number of Longest Increasing Subsequence (not added yet). O(n²) DP carrying lengths and counts.
- **Two-sequence version:** [LC 1143 Longest Common Subsequence](../../14-2d-dp/1143-longest-common-subsequence/). 2-D DP.
- **Reconstruct the subsequence:** store for each element the index of its predecessor in tails.
