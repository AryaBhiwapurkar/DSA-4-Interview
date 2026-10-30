---
number: 853
title: Car Fleet
difficulty: Medium
topic: Stack
pattern: Sort by position + stack of arrival times
link: https://leetcode.com/problems/car-fleet/
lists: [NeetCode 150]
followup_of: []
related: ["1776 Car Fleet II", "0739 Daily Temperatures"]
---

# 0853. Car Fleet

## ⚡ 30-Second Summary
**Pattern:** Sort by position, compare arrival times
**Key insight:** Process cars from closest-to-target to farthest. A car catches the fleet ahead iff its solo arrival time is ≤ that fleet's arrival time (it would pass, but can't, so it merges). Otherwise it starts a new, slower fleet.
**Go-to:** Sort descending by position + track the slowest fleet time, O(n log n) time, O(n) space

## Problem
Cars on a one-lane road drive toward `target`, each with a start position and speed. A faster car can't pass: when it catches up it joins that car and they move at the slower speed as one fleet. Count how many fleets reach the target (catching up exactly at the target counts as one fleet).

**Examples:**
```
Input:  target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
Output: 3
Why:    Cars at 10 and 8 both arrive at time 1, so they're one fleet. The car at 0
        arrives alone at time 12. Cars at 5 (time 7) and 3 (time 3, caught up
        behind 5) merge into one fleet.

Input:  target = 10, position = [3], speed = [3]
Output: 1
Why:    One car is one fleet.

Input:  target = 100, position = [0,2,4], speed = [4,2,1]
Output: 1
Why:    The car at 4 is slowest (time 96). Both cars behind would arrive sooner,
        so they catch it and everything merges into one fleet.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵; positions are distinct and < target ≤ 10⁶.
- 1 ≤ speed ≤ 10⁶.

## Hints
<details><summary>Hint 1</summary>
Ignore the merging for a moment: when would each car arrive if alone?
</details>
<details><summary>Hint 2</summary>
A car can only be blocked by cars ahead of it. Process cars in which order so that the fleet ahead is always known?
</details>
<details><summary>Hint 3</summary>
Sort by position descending. Keep the arrival time of the last fleet. If a car's time ≤ that time, it merges (skip it); else it forms a new fleet and becomes the new "last fleet time".
</details>

## Clarifying Questions
- Are positions distinct? (Yes.)
- Does meeting exactly at the target count as one fleet? (Yes.)
- Can a merged fleet speed up later? (No: it moves at the slowest member's speed.)

## Example Walkthrough
target 12. Sorted by position descending, with time = (12 - pos) / speed:
- pos 10, time 1 → new fleet (last = 1).
- pos 8, time 1 → 1 ≤ 1, merges.
- pos 5, time 7 → new fleet (last = 7).
- pos 3, time 3 → 3 ≤ 7, merges.
- pos 0, time 12 → new fleet. Total 3.

## Approaches

### 1. Sort + Stack of Fleet Times: O(n log n) time, O(n) space
Push each car's time; if it's ≤ the top, pop it (it merged). The stack size at the end is the number of fleets. This is the NeetCode framing and makes the "fleets ahead" visible.

### 2. Sort + Slowest Fleet Time ⭐ Go-to: O(n log n) time, O(n) space for the sort
Only the top of that stack is ever compared, so keep one variable and a counter.
**Why it's the go-to:** same idea, fewer moving parts. Mention the stack version to show where it comes from.

## Dry Run (Approach 2)
`target = 100, position = [0,2,4], speed = [4,2,1]`

| car (pos, speed) | time = (100-pos)/speed | last fleet time | new fleet? | fleets |
|------------------|------------------------|-----------------|------------|--------|
| (4, 1) | 96 | 0 | yes | 1 |
| (2, 2) | 49 | 96 | no (49 ≤ 96) | 1 |
| (0, 4) | 25 | 96 | no (25 ≤ 96) | 1 |

Note: we compare against 96, not 49. The car at 2 merged, so the fleet ahead is still the 96 one.

## Edge Case Check
- One car: 1 fleet. ✅
- Equal arrival times (first example, 10 and 8): `≤` merges them. ✅
- All cars same speed: no one catches up, n fleets. ✅

## ⚠️ Pitfalls
- **Sorting ascending**: you must start from the car closest to the target.
- **Integer division for time**: (12-3)/3 = 3 is fine, but (12-0)/5 truncates. Use floating point, or compare `(t - p1) * s2` vs `(t - p2) * s1` with 64-bit ints.
- **`<` instead of `≤`**: equal times are one fleet (they meet at the target).
- **Updating the last time on a merge**: a merged car doesn't change the fleet's time.

## 🎯 What the Interviewer Wants
- The reduction to arrival times, and why sorting by position is needed.
- A clean argument for why only the fleet directly ahead matters.
- Awareness of the float vs cross-multiplication choice.

## Follow-ups
- **When does each car collide?** Monotonic stack over times: LC 1776 Car Fleet II (not added yet)
- **Similar "next blocking element" logic:** [LC 0739 Daily Temperatures](../0739-daily-temperatures/)
- **Avoid sorting:** positions < target ≤ 10⁶, so bucket by position in an array of size target, O(n + target).
