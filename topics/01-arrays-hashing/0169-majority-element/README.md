---
number: 169
title: Majority Element
difficulty: Easy
topic: Arrays & Hashing
pattern: Boyer-Moore voting
link: https://leetcode.com/problems/majority-element/
lists: [LC Top Interview 150]
followup_of: []
related: ["0229 Majority Element II", "0287 Find the Duplicate Number"]
---

# 0169. Majority Element

## ⚡ 30-Second Summary
**Pattern:** Boyer-Moore voting
**Key insight:** The majority appears more than n/2 times, so if every non-majority element "cancels" one majority element, the majority still has votes left at the end.
**Go-to:** Boyer-Moore, O(n) time, O(1) space

## Problem
Given an array of size n, return the element that appears more than ⌊n/2⌋ times. Such an element is guaranteed to exist.

**Examples:**
```
Input:  nums = [3,2,3]
Output: 3
Why:    3 appears twice out of three, which is more than 1.

Input:  nums = [2,2,1,1,1,2,2]
Output: 2
Why:    2 appears four times out of seven, more than 3.
```

**Constraints:**
- 1 ≤ n ≤ 5·10⁴.
- -10⁹ ≤ nums[i] ≤ 10⁹.
- The majority element always exists (Boyer-Moore relies on this; otherwise verify with a second pass).

## Hints
<details><summary>Hint 1</summary>
Counting with a hashmap is easy. Can you do it without extra space?
</details>
<details><summary>Hint 2</summary>
After sorting, which index is guaranteed to hold the majority?
</details>
<details><summary>Hint 3</summary>
Keep one candidate and a counter: +1 for a match, -1 for a mismatch, switch candidate when the counter hits 0.
</details>

## Clarifying Questions
- Is a majority guaranteed? (Yes; if not, add a verification pass.)
- Strictly more than n/2, or at least? (Strictly more.)
- Can I modify the array? (Affects the sorting approach.)

## Example Walkthrough
`nums = [2,2,1,1,1,2,2]`
- Votes for 2 build to 2, then three 1s knock it down and make 1 the candidate with count 1.
- The final two 2s first cancel 1 (count 0) and then make 2 the candidate again. Answer: 2.

## Approaches

### 1. Hashmap Count: O(n) time, O(n) space
Count occurrences; return the value whose count exceeds n/2 (can return as soon as it does).

### 2. Sort, Take the Middle: O(n log n) time, O(1) extra space
The majority occupies more than half the sorted array, so it must cover index n/2.

### 3. Boyer-Moore Voting ⭐ Go-to: O(n) time, O(1) space
Pairs of different elements cancel; the majority can't be fully cancelled.
**Why it's the go-to:** optimal on both axes and only five lines. It's the answer to the standard "O(1) space?" follow-up, so lead with the hashmap and land here.

## Dry Run (Approach 3)
`nums = [2,2,1,1,1,2,2]`

| i | x | candidate (before) | count (before) | action | count (after) |
|---|---|--------------------|----------------|--------|---------------|
| 0 | 2 | - | 0 | take 2 | 1 |
| 1 | 2 | 2 | 1 | match | 2 |
| 2 | 1 | 2 | 2 | mismatch | 1 |
| 3 | 1 | 2 | 1 | mismatch | 0 |
| 4 | 1 | 2 | 0 | take 1 | 1 |
| 5 | 2 | 1 | 1 | mismatch | 0 |
| 6 | 2 | 1 | 0 | take 2 | 1 |

Final candidate: 2.

## Edge Case Check
- n = 1: that element. ✅
- Majority at the end, `[1,2,2]`: candidate switches to 2. ✅
- All equal: count just grows. ✅

## ⚠️ Pitfalls
- **No guaranteed majority:** Boyer-Moore still returns *a* candidate; verify it with a counting pass.
- **Checking `count == 0` after updating** instead of before swaps the logic; take the new candidate when the counter is 0 *before* processing x.
- **Sorting mutates the input;** sort a copy if needed.

## 🎯 What the Interviewer Wants
- Hashmap first, then the O(1)-space follow-up.
- Explain *why* cancellation works, not just the code.
- Mention the verification pass when no majority is guaranteed.

## Follow-ups
- **Elements appearing more than n/3 times:** two candidates: LC 0229 Majority Element II (not added yet)
- **No guarantee a majority exists:** add a second counting pass.
- **Stream of numbers:** Boyer-Moore works online with O(1) memory.
