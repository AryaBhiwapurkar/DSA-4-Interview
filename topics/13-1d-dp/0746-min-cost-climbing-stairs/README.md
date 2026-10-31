---
number: 746
title: Min Cost Climbing Stairs
difficulty: Easy
topic: 1-D Dynamic Programming
pattern: Linear DP
link: https://leetcode.com/problems/min-cost-climbing-stairs/
lists: [NeetCode 150]
followup_of: ["0070 Climbing Stairs"]
related: ["0198 House Robber"]
---

# 0746. Min Cost Climbing Stairs

## ⚡ 30-Second Summary
**Pattern:** Linear DP, min over the last move
**Key insight:** Let `reach(i)` = cheapest way to stand on step i. You got there from i-1 (paying cost[i-1]) or from i-2 (paying cost[i-2]). The top is index n, one past the last stair, and steps 0 and 1 are free starts.
**Go-to:** Two rolling variables, O(n) time, O(1) space

## Problem
`cost[i]` is what you pay to step off stair i, after which you climb 1 or 2 stairs. You may start on stair 0 or stair 1. Return the minimum total cost to get beyond the last stair. [LeetCode](https://leetcode.com/problems/min-cost-climbing-stairs/)

**Examples:**
```
Input:  cost = [10,15,20]
Output: 15
Why:    Start on stair 1, pay 15, jump 2 straight past the end.

Input:  cost = [1,100,1,1,1,100,1,1,100,1]
Output: 6
Why:    Step only on the 1s: indices 0, 2, 4, 6, 7, 9. That's six 1s, skipping every 100.
```

**Constraints:**
- 2 ≤ n ≤ 1000, 0 ≤ cost[i] ≤ 999: sums fit easily in an int.

## Hints
<details><summary>Hint 1</summary>
Where is "the top"? It's not the last stair, it's one step beyond it.
</details>
<details><summary>Hint 2</summary>
Define the cheapest cost to arrive at step i. Which two earlier steps can you come from, and what do you pay?
</details>
<details><summary>Hint 3</summary>
reach(0) = reach(1) = 0; reach(i) = min(reach(i-1) + cost[i-1], reach(i-2) + cost[i-2]). Answer reach(n). Only the last two values are needed.
</details>

## Clarifying Questions
- Is the top index n (past the end)? (Yes.)
- Is starting free? (Yes, on 0 or 1.)
- Can costs be zero? (Yes, 0 ≤ cost[i].)

## Example Walkthrough
`[10,15,20]`: reach(0) = 0, reach(1) = 0. reach(2) = min(0+15, 0+10) = 10. reach(3) = min(10+20, 0+15) = 15 → answer 15.

## Approaches

### 1. Memoized Recursion: O(n) time, O(n) space
Recurse from the top with the reach(i) recurrence, caching results.

### 2. Two Variables ⭐ Go-to: O(n) time, O(1) space
Iterate i = 2..n, keeping only reach(i-2) and reach(i-1).
**Why it's the go-to:** same recurrence, no recursion, constant space.

## Dry Run (Approach 2)
Example 2: `cost = [1,100,1,1,1,100,1,1,100,1]`. a = reach(i-2), b = reach(i-1).

| i | b + cost[i-1] | a + cost[i-2] | reach(i) |
|---|---------------|---------------|----------|
| 2 | 0+100 | 0+1 | 1 |
| 3 | 1+1 | 0+100 | 2 |
| 4 | 2+1 | 1+1 | 2 |
| 5 | 2+1 | 2+1 | 3 |
| 6 | 3+100 | 2+1 | 3 |
| 7 | 3+1 | 3+100 | 4 |
| 8 | 4+1 | 3+1 | 4 |
| 9 | 4+100 | 4+1 | 5 |
| 10 | 5+1 | 4+100 | **6** |

## Edge Case Check
- n = 2: one iteration, min(cost[0], cost[1]) → `[5,3]` gives 3. ✅
- All zeros: 0. ✅

## ⚠️ Pitfalls
- **Returning reach(n-1)** (the last stair) instead of reach(n) (the top).
- **Charging cost[i] on arrival** instead of on departure shifts the indices; pick one definition and stick to it.
- **Memo sentinel 0** is ambiguous when costs can be 0; use -1 in C++.

## 🎯 What the Interviewer Wants
- A clear state definition (what exactly does dp[i] mean?).
- Correct base cases from "start on 0 or 1".
- O(1) space after showing the recurrence.

## Follow-ups
- **Count ways instead of min cost:** [LC 0070 Climbing Stairs](../0070-climbing-stairs/)
- **Can't take two adjacent items, maximize:** [LC 0198 House Robber](../0198-house-robber/)
- **Jumps of up to k stairs:** min over a window; use a monotonic deque for O(n).
