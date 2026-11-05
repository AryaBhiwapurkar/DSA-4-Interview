---
number: 134
title: Gas Station
difficulty: Medium
topic: Greedy
pattern: Reset start on negative tank
link: https://leetcode.com/problems/gas-station/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0053 Maximum Subarray", "0918 Maximum Sum Circular Subarray"]
---

# 0134. Gas Station

## ⚡ 30-Second Summary
**Pattern:** Greedy one pass with a running balance
**Key insight:** (1) If total gas < total cost, no start works. (2) If the tank goes negative going from `start` to i, then no index in [start, i] can be the start, because each of them reaches i with even less gas. So jump the start to i + 1 and reset. When the total is ≥ 0, the last start found is the answer.
**Go-to:** One pass, O(n) time, O(1) space

## Problem
Stations sit on a circular road. At station i you pick up gas[i], and driving on to station i+1 burns cost[i]. With an empty tank at the start, find the station from which you can drive all the way around. The answer is unique if it exists, otherwise return -1. [LeetCode](https://leetcode.com/problems/gas-station/)

**Examples:**
```
Input:  gas = [1,2,3,4,5], cost = [3,4,5,1,2]
Output: 3
Why:    Net gains are [-2,-2,-2,3,3]. Starting at 3 banks +3, +3 before the three -2 legs, and the tank never dips below 0.

Input:  gas = [2,3,4], cost = [3,4,3]
Output: -1
Why:    Total gas is 9 but total cost is 10, so no start can finish.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵, so O(n²) simulation is too slow.
- 0 ≤ gas[i], cost[i] ≤ 10⁴. The answer is unique if it exists.

## Hints
<details><summary>Hint 1</summary>
When is it impossible regardless of the start?
</details>
<details><summary>Hint 2</summary>
Suppose you start at s and run dry just after station i. Could any station between s and i be a valid start?
</details>
<details><summary>Hint 3</summary>
Sum gas[i] - cost[i] into tank. When tank < 0, set start = i + 1 and tank = 0. At the end, return start if the total net is ≥ 0, else -1.
</details>

## Clarifying Questions
- Is the answer unique? (Yes, guaranteed.)
- Does the tank start empty? (Yes.)
- Is there a tank capacity? (No limit.)

## Example Walkthrough
`gas = [3,1,1], cost = [1,2,2]`, nets [2,-1,-1], total 0. From 0: tank 2, 1, 0, never negative → start 0. A total of exactly 0 still works: you arrive back with an empty tank.

## Approaches

### 1. Simulate Every Start: O(n²) time, O(1) space
Try each start, drive n legs, stop at the first negative tank.

### 2. One Pass ⭐ Go-to: O(n) time, O(1) space
**Why it's the go-to:** linear, and both facts behind it (total ≥ 0 suffices, and a failed segment rules out all of its starts) take a sentence each to justify.

## Dry Run (Approach 2)
`gas = [1,2,3,4,5]`, `cost = [3,4,5,1,2]`

| i | net | tank | action | start |
|---|-----|------|--------|-------|
| 0 | -2 | -2 | reset | 1 |
| 1 | -2 | -2 | reset | 2 |
| 2 | -2 | -2 | reset | 3 |
| 3 | 3 | 3 | | 3 |
| 4 | 3 | 6 | | 3 |

The total is 0 ≥ 0 → return **3**. The remaining legs 0..2 cost 6, exactly what was banked.

## Edge Case Check
- One station, gas ≥ cost → 0. ✅
- Total short (example 2) → -1. ✅
- Answer is the last index (`[5,1,2,3,4]`, `[4,4,1,5,1]`) → 4. ✅

## ⚠️ Pitfalls
- **Forgetting the total check:** the pass alone can return a start that fails.
- **Restarting at start + 1 instead of i + 1** turns it back into O(n²).
- **Simulating twice around the array** isn't needed; the total argument covers the wrap-around.

## 🎯 What the Interviewer Wants
- Brute force, then the two-part proof (total, and a failed segment rules out every start inside it).
- O(n) / O(1) code.
- Connect it to Kadane / prefix sums: the answer is the index right after the minimum prefix sum.

## Follow-ups
- **Running-sum restarts in general:** [LC 0053 Maximum Subarray](../0053-maximum-subarray/)
- **Circular arrays:** [LC 0918 Maximum Sum Circular Subarray](../0918-maximum-sum-circular-subarray/)
- **Multiple valid starts / return all:** check each index where the prefix sum hits its minimum.
