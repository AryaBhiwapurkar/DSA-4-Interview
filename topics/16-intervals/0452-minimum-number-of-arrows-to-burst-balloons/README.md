---
number: 452
title: Minimum Number of Arrows to Burst Balloons
difficulty: Medium
topic: Intervals
pattern: Sort by end, greedy
link: https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/
lists: [LC Top Interview 150]
followup_of: []
related: ["0435 Non-overlapping Intervals", "0056 Merge Intervals"]
---

# 0452. Minimum Number of Arrows to Burst Balloons

## ⚡ 30-Second Summary
**Pattern:** Greedy on intervals sorted by end (a "stabbing points" problem)
**Key insight:** Some arrow must hit the balloon that ends first. Shooting it at that balloon's **end** hits every balloon that starts by then, and as many others as possible. Sort by end; whenever a balloon starts after the last arrow, shoot a new arrow at its end.
**Go-to:** Sort by end, O(n log n) time, O(1) extra space

## Problem
Balloons are horizontal ranges [start, end] on the x-axis. A vertical arrow shot at x pops every balloon whose range contains x (endpoints included). Return the fewest arrows that pop all balloons. [LeetCode](https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/)

**Examples:**
```
Input:  points = [[10,16],[2,8],[1,6],[7,12]]
Output: 2
Why:    An arrow at 6 pops [1,6] and [2,8]; one at 12 pops [7,12] and [10,16].

Input:  points = [[1,2],[3,4],[5,6],[7,8]]
Output: 4
Why:    No two balloons share a point.

Input:  points = [[1,2],[2,3],[3,4],[4,5]]
Output: 2
Why:    Arrows at 2 and 4: touching endpoints count as shared.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵, coordinates span the **full 32-bit range** (−2³¹ to 2³¹−1).

## Hints
<details><summary>Hint 1</summary>
Look at the balloon that ends first. Some arrow has to pop it. Where is the best place for that arrow?
</details>
<details><summary>Hint 2</summary>
Moving that arrow to the balloon's end can only hit more balloons, never fewer. Which balloons does it pop?
</details>
<details><summary>Hint 3</summary>
Sort by end. arrows = 1, x = first end. For each balloon, if start > x, arrows++ and x = its end. Return arrows.
</details>

## Clarifying Questions
- Do endpoints count? (Yes, [1,2] and [2,3] share x = 2.)
- Coordinate range? (Full int range: watch comparator overflow.)
- n ≥ 1? (Yes.)

## Example Walkthrough
`[[1,10],[2,3],[4,5]]`: sorted by end: [2,3], [4,5], [1,10]. Arrow at 3 pops [2,3] and [1,10]. [4,5] starts at 4 > 3, so a second arrow goes at 5. Two arrows. Sorting by start and shooting at the first end (10) would miss both short ones.

## Approaches

### 1. Sort by Start, Shrink the Window: O(n log n) time, O(1) extra
Keep the common window of the current group; its right edge is min(end). A balloon starting past it begins a new group.

### 2. Sort by End ⭐ Go-to: O(n log n) time, O(1) extra
**Why it's the go-to:** same proof as LC 435 (earliest end first), and there's no window to maintain.

## Dry Run (Approach 2)
`[[10,16],[2,8],[1,6],[7,12]]` sorted by end: [1,6], [2,8], [7,12], [10,16].

| balloon | start > arrow? | arrows | arrow x |
|---------|----------------|--------|---------|
| [1,6] | first | 1 | 6 |
| [2,8] | 2 > 6 no | 1 | 6 |
| [7,12] | 7 > 6 yes | 2 | 12 |
| [10,16] | 10 > 12 no | **2** | 12 |

## Edge Case Check
- All disjoint → n. ✅
- Chain of touching balloons → ⌈n / 2⌉ here (`[[1,2],[2,3],[3,4],[4,5]]` → 2). ✅
- Extreme coordinates → 2, no overflow. ✅

## ⚠️ Pitfalls
- **Comparator `a[1] - b[1]`** overflows for values near ±2³¹ (common in Java/C++ solutions).
- **Using `>=` instead of `>`**: touching balloons share an arrow.
- **Sentinel like INT_MIN for "no arrow yet"** fails when a balloon starts at INT_MIN; seed with the first balloon instead.
- **Confusing it with LC 435:** there, touching is *not* an overlap; here it *is*.

## 🎯 What the Interviewer Wants
- The "shoot at the earliest end" argument.
- Overflow-safe comparisons.
- The connection to LC 435 (number of arrows = max number of pairwise-disjoint balloons).

## Follow-ups
- **Remove intervals to make them disjoint:** [LC 0435 Non-overlapping Intervals](../0435-non-overlapping-intervals/)
- **Merge overlapping groups instead:** [LC 0056 Merge Intervals](../0056-merge-intervals/)
- **Return the arrow positions:** record arrow x each time a new arrow is shot.
