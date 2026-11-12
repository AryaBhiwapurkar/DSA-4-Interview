---
number: 229
title: Majority Element II
difficulty: Medium
topic: Arrays & Hashing
pattern: Boyer-Moore voting with two candidates
link: https://leetcode.com/problems/majority-element-ii/
lists: [Interview Extras]
followup_of: ["0169 Majority Element"]
related: ["0169 Majority Element", "1150 Check If a Number Is Majority Element in a Sorted Array"]
---

# 0229. Majority Element II

## ⚡ 30-Second Summary
**Pattern:** Extended Boyer-Moore: keep two candidates, cancel triples
**Key insight:** At most **two** values can appear more than ⌊n/3⌋ times. Keep two candidates with counts. A match bumps its count. An empty slot adopts the value. Anything else decrements **both** counts, which cancels three distinct values at once, and real majorities survive that. Candidates aren't guaranteed, so do a second pass to verify each one.
**Go-to:** Two-candidate voting + verification pass, O(n) time, O(1) space

## Problem
Return every value that appears more than ⌊n/3⌋ times in an integer array. Follow-up: linear time, O(1) space. [LeetCode](https://leetcode.com/problems/majority-element-ii/)

**Examples:**
```
Input:  nums = [3,2,3]
Output: [3]
Why:    n = 3, threshold 1; 3 appears twice.

Input:  nums = [1]
Output: [1]
Why:    A single element always clears ⌊1/3⌋ = 0.

Input:  nums = [1,2]
Output: [1,2]
Why:    Threshold 0; both appear once.
```

**Constraints:**
- 1 ≤ n ≤ 5·10⁴; values span the 32-bit range.
- Follow-up: O(n) time and O(1) space.

## Hints
<details><summary>Hint 1</summary>
How many different values can each appear more than n/3 times?
</details>
<details><summary>Hint 2</summary>
In 0169 you kept one candidate and cancelled pairs. What do you cancel when you keep two candidates?
</details>
<details><summary>Hint 3</summary>
c1, c2 with counts k1, k2. If x == c1: k1++. Else if x == c2: k2++. Else if k1 == 0: c1 = x, k1 = 1. Else if k2 == 0: c2 = x, k2 = 1. Else k1--, k2--. Then count c1 and c2 in a second pass and keep those &gt; n/3.
</details>

## Clarifying Questions
- Strictly more than ⌊n/3⌋? (Yes.)
- Is a majority guaranteed? (No; the answer can be empty, so verify.)
- Output order? (Any.)

## Example Walkthrough
`[1,2,3,1,2,1]` (n = 6, threshold 2). Voting: 1 → c1; 2 → c2; 3 cancels both (k1 = k2 = 0); 1 → k1 is 0, but `x == c1` is checked first, so k1 = 1. Then 2 → k2 = 1, and 1 → k1 = 2. Candidates are 1 and 2. Verify: 1 appears 3 times (> 2) ✓, 2 appears 2 times ✗. Answer [1].

## Approaches

### 1. Hashmap Counts: O(n) time, O(n) space
Count everything and keep the counts above n/3. Correct and the natural first answer.

### 2. Sort + Runs: O(n log n) time, O(1) extra
Sort, then measure each run's length. No hashmap, but slower.

### 3. Two-candidate Boyer-Moore ⭐ Go-to: O(n) time, O(1) space
**Why it's the go-to:** it meets the follow-up, and it generalises: k − 1 candidates find every element above n/k.

## Dry Run (Approach 3)
`[3,2,3]`

| x | c1, k1 | c2, k2 | rule |
|---|--------|--------|------|
| 3 | 3, 1 | –, 0 | adopt into slot 1 |
| 2 | 3, 1 | 2, 1 | adopt into slot 2 |
| 3 | 3, 2 | 2, 1 | match c1 |

Verify: 3 appears 2 times (> 1) ✓; 2 appears once (not > 1) ✗ → **[3]**.

## Edge Case Check
- No element qualifies `[1,2,3]` → verification removes both candidates → []. ✅
- Same value in both slots: checking `x == c1` and `x == c2` before adopting prevents it. ✅
- n = 1 or 2 → every distinct value qualifies. ✅

## ⚠️ Pitfalls
- **Skipping verification:** the candidates are only "possible" majorities.
- **Wrong branch order:** test both matches before the empty-slot checks, or one value can fill both slots.
- **Equal starting candidates:** start them at different values (e.g. 0 and 1). If both start at 0, `[0]` verifies the same candidate twice and returns [0,0]. Adoption only happens for a value matching neither, so they stay distinct afterwards.
- **Threshold:** strictly greater than n/3 (integer division).

## 🎯 What the Interviewer Wants
- The "at most two answers" argument.
- Generalised voting, with the cancel-three intuition.
- The verification pass and O(1) space.

## Follow-ups
- **Single majority > n/2:** [LC 0169 Majority Element](../0169-majority-element/)
- **Generalisation:** elements above n/k need k − 1 candidates (the Misra-Gries summary).
- **Sorted input:** binary search for the first and last occurrence of a candidate.
