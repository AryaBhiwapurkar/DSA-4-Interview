---
number: 268
title: Missing Number
difficulty: Easy
topic: Bit Manipulation
pattern: XOR / sum formula
link: https://leetcode.com/problems/missing-number/
lists: [NeetCode 150]
followup_of: []
related: ["0136 Single Number", "0041 First Missing Positive", "0287 Find the Duplicate Number"]
---

# 0268. Missing Number

## ⚡ 30-Second Summary
**Pattern:** XOR pairing (or the Gauss sum)
**Key insight:** XOR every index 0..n−1, the value n, and every element. Each present value pairs with its matching index and cancels, so only the missing number survives. The sum version `n(n+1)/2 − sum(nums)` works too, but can overflow in fixed-width languages.
**Go-to:** XOR of indices and values, O(n) time, O(1) space

## Problem
An array of length n contains distinct numbers from 0 to n, so exactly one of them is absent. Return it. [LeetCode](https://leetcode.com/problems/missing-number/)

**Examples:**
```
Input:  nums = [3,0,1]
Output: 2
Why:    The range is 0..3; 2 is the gap.

Input:  nums = [0,1]
Output: 2
Why:    n = 2 itself is the missing one.

Input:  nums = [9,6,4,2,3,5,7,0,1]
Output: 8
Why:    n = 9, so the range is 0..9; every value except 8 is present.
```

**Constraints:**
- 1 ≤ n ≤ 10⁴, values distinct in [0, n].
- Follow-up: O(1) extra space and O(n) time.

## Hints
<details><summary>Hint 1</summary>
If nothing were missing, what would the full set 0..n look like? How does nums differ from it?
</details>
<details><summary>Hint 2</summary>
Combine the full range with the array so that every number appearing in both disappears. Which operation makes equal values disappear?
</details>
<details><summary>Hint 3</summary>
x = n; for each i: x ^= i ^ nums[i]. Return x. (Or n(n+1)/2 − sum.)
</details>

## Clarifying Questions
- Exactly one missing? (Yes, values distinct.)
- Can the missing one be n? (Yes, as in [0,1].)
- Can I modify the array? (Not needed.)

## Example Walkthrough
`[3,0,1]`: start x = 3. XOR in (0, 3), (1, 0), (2, 1): the indices give 0, 1, 2; the values give 3, 0, 1; plus the starting 3. Everything appears twice except 2.

## Approaches

### 1. Sort: O(n log n) time, O(1) extra
After sorting, the first index where a[i] ≠ i is the answer; if none, it's n.

### 2. Hash Set: O(n) time, O(n) space
Insert everything, probe 0..n.

### 3. Gauss Sum: O(n) time, O(1) space
Expected sum minus actual sum. Fine in Python; in C++ widen to long long for safety.

### 4. XOR ⭐ Go-to: O(n) time, O(1) space
**Why it's the go-to:** O(1) space, no overflow concerns at all, and it reuses the LC 136 idea.

## Dry Run (Approach 4)
`[3,0,1]`, start x = n = 3

| i | nums[i] | i ^ nums[i] | x |
|---|---------|-------------|---|
| | | | 3 (011) |
| 0 | 3 | 3 | 0 (000) |
| 1 | 0 | 1 | 1 (001) |
| 2 | 1 | 3 | **2** (010) |

## Edge Case Check
- Missing n (`[0,1]`) → 2. ✅
- Missing 0 (`[1]`) → 0. ✅
- Single `[0]` → 1. ✅

## ⚠️ Pitfalls
- **Forgetting to XOR in n** (start x at n, not 0): the result becomes missing ^ n, which is wrong every time.
- **Sum overflow** in C++/Java for large n with 32-bit ints.
- **Sort version** must return n when every index matches.

## 🎯 What the Interviewer Wants
- Several approaches with trade-offs (sort, set, sum, XOR).
- XOR or sum for O(1) space, and the overflow argument for XOR.

## Follow-ups
- **Every number twice except one:** [LC 0136 Single Number](../0136-single-number/)
- **Smallest missing positive, unsorted with junk:** LC 0041 First Missing Positive (not added yet). In-place index marking.
- **One duplicate instead of one missing:** [LC 0287 Find the Duplicate Number](../../06-linked-list/0287-find-the-duplicate-number/)
