---
number: 198
title: House Robber
difficulty: Medium
topic: 1-D Dynamic Programming
pattern: Take/skip DP
link: https://leetcode.com/problems/house-robber/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0213 House Robber II", "0337 House Robber III", "0740 Delete and Earn"]
---

# 0198. House Robber

## ⚡ 30-Second Summary
**Pattern:** Take or skip each item, no two adjacent
**Key insight:** For house i, either skip it (keep the best up to i-1) or rob it (its money plus the best up to i-2). `dp[i] = max(dp[i-1], dp[i-2] + nums[i])`.
**Go-to:** Two rolling variables, O(n) time, O(1) space

## Problem
Houses stand in a row, each with some money. Robbing two neighbouring houses triggers an alarm. Return the maximum total you can rob. [LeetCode](https://leetcode.com/problems/house-robber/)

**Examples:**
```
Input:  nums = [1,2,3,1]
Output: 4
Why:    Houses 0 and 2: 1 + 3.

Input:  nums = [2,7,9,3,1]
Output: 12
Why:    Houses 0, 2 and 4: 2 + 9 + 1. Taking 7 blocks both 2 and 9, which costs more.
```

**Constraints:**
- 1 ≤ n ≤ 100, 0 ≤ nums[i] ≤ 400.

## Hints
<details><summary>Hint 1</summary>
Greedy (take every other house, or always the biggest) fails. Try [2,1,1,2]. What decision do you face at each house?
</details>
<details><summary>Hint 2</summary>
If you rob house i, which house's best answer can you build on? If you skip it?
</details>
<details><summary>Hint 3</summary>
best(i) = max(best(i-1), best(i-2) + nums[i]). Start with two zeros and roll forward, keeping only the last two values.
</details>

## Clarifying Questions
- Can values be zero? Negative? (0..400, never negative, so skipping is never forced.)
- Is the street a line or a circle? (Line. The circle is LC 213.)
- Only one house? (Take it.)

## Example Walkthrough
`[2,1,1,2]`: alternating picks give 2+1 = 3, but houses 0 and 3 give 4. DP: 2, max(2,1)=2, max(2,2+1)=3, max(3,2+2)=4 → 4.

## Approaches

### 1. Memoized Recursion: O(n) time, O(n) space
best(i) from the right: max(skip, take + best(i+2)), cached.

### 2. Two Variables ⭐ Go-to: O(n) time, O(1) space
Roll `prev2` (best up to i-2) and `prev1` (best up to i-1).
**Why it's the go-to:** the standard take/skip template in four lines.

## Dry Run (Approach 2)
`[2,7,9,3,1]`.

| x | prev2 | prev1 | cur = max(prev1, prev2 + x) |
|---|-------|-------|-----------------------------|
| 2 | 0 | 0 | max(0, 2) = 2 |
| 7 | 0 | 2 | max(2, 7) = 7 |
| 9 | 2 | 7 | max(7, 11) = 11 |
| 3 | 7 | 11 | max(11, 10) = 11 |
| 1 | 11 | 11 | max(11, 12) = **12** |

## Edge Case Check
- One house: max(0, 0 + x) = x. ✅
- Two houses: the larger one. ✅
- Gap of two skipped houses (`[2,1,1,2]`) → 4. ✅

## ⚠️ Pitfalls
- **Alternating greedy** (even indices vs odd indices) fails on `[2,1,1,2]`.
- **Updating prev2 before computing cur** in C++ uses the wrong value; compute first, then shift.
- **Index out of bounds** with a dp array when n = 1 (dp[1] = max(nums[0], nums[1])). Rolling variables avoid it.

## 🎯 What the Interviewer Wants
- A clear take/skip recurrence with a stated meaning for dp[i].
- A counterexample to greedy.
- O(1) space.

## Follow-ups
- **Houses in a circle:** [LC 0213 House Robber II](../0213-house-robber-ii/)
- **Houses in a binary tree:** LC 0337 House Robber III (not added yet). Return (rob, skip) pairs from a DFS.
- **Taking x deletes x-1 and x+1:** LC 0740 Delete and Earn (not added yet). Bucket by value, then House Robber.
- **Return which houses:** keep parent choices, or backtrack through the dp array.
