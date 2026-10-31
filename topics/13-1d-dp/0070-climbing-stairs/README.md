---
number: 70
title: Climbing Stairs
difficulty: Easy
topic: 1-D Dynamic Programming
pattern: Fibonacci DP
link: https://leetcode.com/problems/climbing-stairs/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0746 Min Cost Climbing Stairs", "0509 Fibonacci Number", "0091 Decode Ways"]
---

# 0070. Climbing Stairs

## ⚡ 30-Second Summary
**Pattern:** Fibonacci-style DP
**Key insight:** To reach step n, the last move was either 1 step (from n-1) or 2 steps (from n-2). So `ways(n) = ways(n-1) + ways(n-2)`, which is Fibonacci.
**Go-to:** Bottom-up with two variables, O(n) time, O(1) space

## Problem
You climb a staircase of n steps, taking either 1 or 2 steps at a time. Count how many distinct sequences of moves reach the top. [LeetCode](https://leetcode.com/problems/climbing-stairs/)

**Examples:**
```
Input:  n = 2
Output: 2
Why:    1+1 or 2.

Input:  n = 3
Output: 3
Why:    1+1+1, 1+2, 2+1.
```

**Constraints:**
- 1 ≤ n ≤ 45, so the answer (≈1.8·10⁹) still fits in a 32-bit int.

## Hints
<details><summary>Hint 1</summary>
Think about the very last move you make onto step n. What are the options?
</details>
<details><summary>Hint 2</summary>
If you know the number of ways to reach n-1 and n-2, can you get the number for n?
</details>
<details><summary>Hint 3</summary>
ways(n) = ways(n-1) + ways(n-2), with ways(1) = 1, ways(2) = 2. You only ever need the last two values, so keep two variables and roll them forward.
</details>

## Clarifying Questions
- Only 1 or 2 steps? (Yes. If the step set is arbitrary, it becomes a coin-change-style count.)
- Does order matter? (Yes, 1+2 and 2+1 are different.)
- Range of n? (1..45, fits in int.)

## Example Walkthrough
n = 5: ways = 1 (step 1), 2 (step 2), 3, 5, 8. Each value is the sum of the two before it. Answer 8.

## Approaches

### 1. Plain Recursion: O(2ⁿ) time, O(n) space
Direct translation of the recurrence. Recomputes the same subproblems exponentially many times.

### 2. Memoized Recursion: O(n) time, O(n) space
Cache each ways(i). Each subproblem is solved once.

### 3. Two Variables ⭐ Go-to: O(n) time, O(1) space
Iterate up from the base cases, keeping only `prev` and `cur`.
**Why it's the go-to:** optimal, five lines, and it shows the standard DP progression (recursion → memo → table → rolling variables).

## Dry Run (Approach 3)
n = 5. Start prev = ways(0) = 1, cur = ways(1) = 1.

| i | prev (before) | cur (before) | new cur = prev + cur | prev after |
|---|---------------|--------------|----------------------|------------|
| 2 | 1 | 1 | 2 | 1 |
| 3 | 1 | 2 | 3 | 2 |
| 4 | 2 | 3 | 5 | 3 |
| 5 | 3 | 5 | **8** | 5 |

## Edge Case Check
- n = 1: the loop doesn't run, cur = 1. ✅
- n = 2: one iteration → 2. ✅
- n = 45: 1,836,311,903 < INT_MAX. ✅

## ⚠️ Pitfalls
- **Base cases:** ways(0) = 1 (one way to stand still) makes the loop clean; mixing up ways(0) and ways(1) shifts everything by one.
- **Plain recursion** times out around n = 40.
- **Swapping order:** in C++ compute `next` before overwriting `prev`. In Python, the tuple assignment handles it.
- **Python `@cache` on a top-level function** keeps its cache across calls (fine here, but surprising in tests).

## 🎯 What the Interviewer Wants
- Derive the recurrence from "last move", not from memorizing Fibonacci.
- Show the progression recursion → memo → O(1) space.
- State complexities and the int-range check.

## Follow-ups
- **Each step has a cost:** [LC 0746 Min Cost Climbing Stairs](../0746-min-cost-climbing-stairs/)
- **Steps from an arbitrary set {1, 3, 5}:** ways(n) = Σ ways(n - s). That's the counting version of [LC 0322 Coin Change](../0322-coin-change/), with order mattering.
- **n up to 10¹⁸ (mod p):** matrix exponentiation, O(log n).
- **Similar two-term recurrence with conditions:** [LC 0091 Decode Ways](../0091-decode-ways/)
