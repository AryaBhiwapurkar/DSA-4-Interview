---
number: 846
title: Hand of Straights
difficulty: Medium
topic: Greedy
pattern: Sorted counts, build from min
link: https://leetcode.com/problems/hand-of-straights/
lists: [NeetCode 150]
followup_of: []
related: ["1296 Divide Array in Sets of K Consecutive Numbers", "0659 Split Array into Consecutive Subsequences"]
---

# 0846. Hand of Straights

## ⚡ 30-Second Summary
**Pattern:** Greedy on sorted counts
**Key insight:** The smallest remaining card can only be the **first** card of a group, since nothing smaller is left to precede it. So every copy of it starts a group: subtract its count from the next k-1 values. If any of them runs short, it's impossible.
**Go-to:** Ordered count map, smallest first, O(n log n + n·k) time, O(n) space

## Problem
Decide whether the cards can be split into groups of exactly groupSize cards each, where every group is a run of consecutive values. [LeetCode](https://leetcode.com/problems/hand-of-straights/)

**Examples:**
```
Input:  hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
Output: true
Why:    [1,2,3], [2,3,4], [6,7,8].

Input:  hand = [1,2,3,4,5], groupSize = 4
Output: false
Why:    5 cards can't split into groups of 4.
```

**Constraints:**
- 1 ≤ n ≤ 10⁴, values up to 10⁹, so count with a map, not an array indexed by value.
- 1 ≤ groupSize ≤ n.

## Hints
<details><summary>Hint 1</summary>
If n isn't divisible by groupSize, stop. Otherwise, which card's group can you be sure about?
</details>
<details><summary>Hint 2</summary>
The smallest card has nothing below it, so it must start a group. Which cards must that group contain?
</details>
<details><summary>Hint 3</summary>
Count cards in an ordered map. For each value low in ascending order with count c > 0, every one of low..low+k-1 needs at least c copies; subtract c from each, and fail if any falls short.
</details>

## Clarifying Questions
- Groups are exactly groupSize? (Yes.)
- Duplicates? (Yes, very common.)
- Value range? (Up to 10⁹: use a map.)

## Example Walkthrough
`[1,1,2,2,3,3], k = 3`: smallest 1 has count 2, so open two groups 1-2-3. Subtract 2 from counts of 1, 2 and 3 → all zero → true.

## Approaches

### 1. Sort + Remove One Group at a Time: O(n²) with a list, O(n log n) with a multiset
Repeatedly take the smallest card and remove low, low+1, …, low+k-1 (one copy each).

### 2. Sorted Counts ⭐ Go-to: O(n log n + n·k) time, O(n) space
Process distinct values ascending and open all c groups starting at a value in one step.
**Why it's the go-to:** handles duplicates in bulk, short code, and the "smallest must start a group" argument is the whole proof.

## Dry Run (Approach 2)
`[1,2,3,6,2,3,4,7,8], k = 3` → counts {1:1, 2:2, 3:2, 4:1, 6:1, 7:1, 8:1}.

| low | c | subtract c from | counts after |
|-----|---|-----------------|--------------|
| 1 | 1 | 1, 2, 3 | {1:0, 2:1, 3:1, 4:1, 6:1, 7:1, 8:1} |
| 2 | 1 | 2, 3, 4 | {2:0, 3:0, 4:0, 6:1, 7:1, 8:1} |
| 3 | 0 | skip | |
| 4 | 0 | skip | |
| 6 | 1 | 6, 7, 8 | all 0 |

Every subtraction succeeded → **true**.

## Edge Case Check
- n % k ≠ 0 → false at once. ✅
- k = 1 → always true. ✅
- Gap in values (`[1,2,4]`, k = 3) → 3 is missing → false. ✅

## ⚠️ Pitfalls
- **C++ `map[v]` inserts** missing keys while you iterate the map; use `find`.
- **C++ reference to the count:** `auto& [low, c]` and then zeroing count[low] changes c mid-loop; copy it first.
- **`multiset::erase(value)`** removes every copy; erase by iterator.
- **Skipping the divisibility check:** the greedy still fails later, but checking up front costs nothing.

## 🎯 What the Interviewer Wants
- The "smallest card starts a group" greedy argument.
- Correct duplicate handling with counts.
- Complexity, plus awareness of the O(n) "find run starts" variant.

## Follow-ups
- **Identical problem:** LC 1296 Divide Array in Sets of K Consecutive Numbers (not added yet)
- **Runs of length ≥ 3, any length:** LC 0659 Split Array into Consecutive Subsequences (not added yet). Greedy with "groups ending at x" counts.
- **Avoid sorting:** for each value, walk down while value-1 exists to find run starts, then process each run.
