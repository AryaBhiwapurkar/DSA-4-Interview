---
number: 18
title: 4Sum
difficulty: Medium
topic: Two Pointers
pattern: Sort + fix two + converging pointers (k-Sum)
link: https://leetcode.com/problems/4sum/
lists: [Interview Extras]
followup_of: ["0015 3Sum"]
related: ["0015 3Sum", "0016 3Sum Closest", "0454 4Sum II", "0001 Two Sum"]
---

# 0018. 4Sum

## ⚡ 30-Second Summary
**Pattern:** k-Sum: fix elements in loops until two are left, then use two pointers
**Key insight:** Sort. Fix i, then j > i, then run lo/hi for the remaining pair: O(n³). Skip duplicate values at **every** level (i, j, lo, hi) so each quadruplet appears once. Values reach ±10⁹, so four of them can overflow a 32-bit int. Sum in `long long`.
**Go-to:** Sort + two nested loops + two pointers, O(n³) time, O(1) extra (output aside)

## Problem
Return every unique quadruplet of values at four different indices that adds up to target. [LeetCode](https://leetcode.com/problems/4sum/)

**Examples:**
```
Input:  nums = [1,0,-1,0,-2,2], target = 0
Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
Why:    The three distinct value-combinations of four numbers that sum to 0.

Input:  nums = [2,2,2,2,2], target = 8
Output: [[2,2,2,2]]
Why:    Many index choices, but only one distinct quadruplet of values.
```

**Constraints:**
- 1 ≤ n ≤ 200, so O(n³) = 8·10⁶ is fine.
- **−10⁹ ≤ nums[i], target ≤ 10⁹**: a sum of four overflows `int`.

## Hints
<details><summary>Hint 1</summary>
How did 3Sum reduce to 2Sum? Can you peel one more level?
</details>
<details><summary>Hint 2</summary>
After sorting, how do you skip duplicates at each of the four positions?
</details>
<details><summary>Hint 3</summary>
for i: skip if nums[i] == nums[i−1]. for j &gt; i: skip if j &gt; i+1 and nums[j] == nums[j−1]. Two pointers on (j+1, n−1) with a long long sum; on a hit, record it, move both pointers and skip equal values.
</details>

## Clarifying Questions
- Unique by value, not by index? (Yes.)
- Output order? (Any.)
- Overflow? (Yes, up to 4·10⁹, so use 64-bit sums.)

## Example Walkthrough
Sorted `[-2,-1,0,0,1,2]`, target 0. i = −2, j = −1 → need 3 from [0,0,1,2] → (1,2) ✓. i = −2, j = 0 → need 2 → (0,2) ✓. i = −2, the second 0 is a duplicate j, so skip it. i = −1, j = 0 → need 1 → (0,1) ✓. Three quadruplets.

## Approaches

### 1. Four Loops + Set: O(n⁴) time
Try every quadruple of indices and de-duplicate sorted tuples in a set. Too slow beyond tiny n.

### 2. Sort + Two Loops + Two Pointers ⭐ Go-to: O(n³) time, O(1) extra
**Why it's the go-to:** the standard extension of 3Sum. Interviewers often ask you to generalise it into a recursive k-Sum.

(General k-Sum: recurse `kSum(start, k, target)` down to the 2Sum base case. It's O(n^(k−1)).)

## Dry Run (Approach 2)
`[2,2,2,2,2], target 8` (sorted already)

| i | j | lo | hi | sum | action |
|---|---|----|----|-----|--------|
| 0 | 1 | 2 | 4 | 8 | record [2,2,2,2]; dup-skips push lo past hi → stop |
| 0 | 2 | | | | skip: nums[2] == nums[1] |
| 1 | | | | | skip: nums[1] == nums[0] |

**[[2,2,2,2]]**

## Edge Case Check
- n < 4 → []. ✅
- Huge values `[10⁹,10⁹,10⁹,10⁹], target −294967296` → 64-bit sum 4·10⁹ ≠ target → [] (a 32-bit sum would wrap to −294967296 and match wrongly). ✅
- All equal → one quadruplet. ✅

## ⚠️ Pitfalls
- **int overflow in C++/Java:** use `(long long)nums[i] + nums[j] + nums[lo] + nums[hi]`.
- **Duplicate skipping for j** must compare with j − 1 only when j > i + 1, or you skip valid first choices.
- **Early-break pruning on `nums[i] > target`** is wrong for negative targets. Prune with the min/max sums instead, or skip pruning.

## 🎯 What the Interviewer Wants
- Reuse 3Sum and explain the k-Sum generalisation.
- Correct de-duplication at all levels.
- The overflow catch.

## Follow-ups
- **Three numbers:** [LC 0015 3Sum](../0015-3sum/)
- **Four separate arrays, count only:** LC 0454 4Sum II (not added yet). Hash all a+b sums, then look up −(c+d): O(n²).
- **Closest instead of exact:** [LC 0016 3Sum Closest](../0016-3sum-closest/)
