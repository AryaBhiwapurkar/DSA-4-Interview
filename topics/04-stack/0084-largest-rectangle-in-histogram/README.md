---
number: 84
title: Largest Rectangle in Histogram
difficulty: Hard
topic: Stack
pattern: Monotonic increasing stack
link: https://leetcode.com/problems/largest-rectangle-in-histogram/
lists: [NeetCode 150]
followup_of: []
related: ["0085 Maximal Rectangle", "0739 Daily Temperatures", "0042 Trapping Rain Water", "1793 Maximum Score of a Good Subarray"]
---

# 0084. Largest Rectangle in Histogram

## ⚡ 30-Second Summary
**Pattern:** Monotonic increasing stack (previous/next smaller)
**Key insight:** The best rectangle that uses bar i at full height stretches from just after the previous shorter bar to just before the next shorter bar. An increasing stack finds both: when a bar is popped, the bar that pops it is its next-smaller and the bar below it on the stack is its previous-smaller.
**Go-to:** One-pass increasing stack with a 0-height sentinel, O(n) time, O(n) space

## Problem
Given bar heights of a histogram (each bar width 1), return the area of the largest rectangle that fits entirely inside the bars. [LeetCode](https://leetcode.com/problems/largest-rectangle-in-histogram/)

**Examples:**
```
Input:  heights = [2,1,5,6,2,3]
Output: 10
Why:    Bars 5 and 6 together give height 5 × width 2.

Input:  heights = [2,4]
Output: 4
Why:    Either the 4 alone (4×1) or both at height 2 (2×2); both are 4.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵, so O(n²) is too slow.
- 0 ≤ heights[i] ≤ 10⁴; the max area 10⁹ fits in a 32-bit int.

## Hints
<details><summary>Hint 1</summary>
Every optimal rectangle has some bar that is its shortest. Fix that bar: how wide can the rectangle go?
</details>
<details><summary>Hint 2</summary>
It extends left and right until it hits a strictly shorter bar on each side. So you need the previous-smaller and next-smaller index for each bar.
</details>
<details><summary>Hint 3</summary>
Keep a stack of indices with increasing heights. When the current bar is shorter than the top, pop: the popped bar's width is i - (new top) - 1. Append a height-0 bar at the end to flush the stack.
</details>

## Clarifying Questions
- Can heights be 0? (Yes: a 0 splits the histogram.)
- Are all widths 1? (Yes.)
- Max area range? (≤ 10⁴ · 10⁵ = 10⁹, fits in int.)

## Example Walkthrough
`[2,1,5,6,2,3]`
- The 1 at index 1 pops the 2: width 1, area 2.
- 5 and 6 push. The 2 at index 4 pops 6 (width 1, area 6) then 5 (left boundary is index 1, width 4-1-1 = 2, area 10).
- The sentinel 0 at the end pops 3 (area 3), 2 (left boundary 1, width 4, area 8), 1 (empty stack, width 6, area 6). Best is 10.

## Approaches

### 1. Brute Force, Expand With Running Min: O(n²) time, O(1) space
For each left i, extend j rightward keeping min height; area = min × (j - i + 1).

### 2. Monotonic Increasing Stack ⭐ Go-to: O(n) time, O(n) space
One pass; each bar's area is computed when it's popped. A two-pass version (compute prevSmaller and nextSmaller arrays first, then max over bars) is equally valid and sometimes easier to explain.
**Why it's the go-to:** linear, and the sentinel trick removes the cleanup loop.

## Dry Run (Approach 2)
`heights = [2,1,5,6,2,3]`, then sentinel 0 at i = 6 (stack shows indices)

| i | h | popped (height × width) | stack after | best |
|---|---|-------------------------|-------------|------|
| 0 | 2 | - | 0 | 0 |
| 1 | 1 | idx 0: 2 × (1 - (-1) - 1) = 2 | 1 | 2 |
| 2 | 5 | - | 1, 2 | 2 |
| 3 | 6 | - | 1, 2, 3 | 2 |
| 4 | 2 | idx 3: 6 × (4-2-1) = 6; idx 2: 5 × (4-1-1) = 10 | 1, 4 | 10 |
| 5 | 3 | - | 1, 4, 5 | 10 |
| 6 | 0 | idx 5: 3×1 = 3; idx 4: 2×4 = 8; idx 1: 1×6 = 6 | 6 | 10 |

## Edge Case Check
- Single bar `[5]`: 5. ✅
- Increasing `[1,2,3,4,5]`: everything pops at the sentinel; best 3×3 = 9. ✅
- All equal `[2,2,2]`: popping on ≥ computes partial widths early, but the last 2 popped (by the sentinel) has an empty stack below → width 3, area 6. ✅
- Zeros: a 0 pops everything and acts as a wall. ✅

## ⚠️ Pitfalls
- **Width after pop**: it's `i - st.top() - 1` (using the NEW top), or `i` if the stack is empty. Using the popped index is wrong.
- **Forgetting to flush the stack**: append a 0 height or loop to i = n with h = 0.
- **Python: mutating the input** with `heights.append(0)` changes the caller's list. Use a local copy or the `i == n` trick.
- **Two-pass version with ties**: use "strictly smaller" on one side and "smaller or equal" on the other, or both strict; just be consistent.

## 🎯 What the Interviewer Wants
- The "fix the shortest bar" reduction to previous/next smaller.
- Correct width formula after popping, and a sentinel to avoid duplicate code.
- Amortized O(n) argument.

## Follow-ups
- **Largest rectangle of 1s in a binary matrix:** run this on each row's histogram: LC 0085 Maximal Rectangle (not added yet)
- **Next greater/smaller template:** [LC 0739 Daily Temperatures](../0739-daily-temperatures/)
- **Water between bars (a different combination of left/right info):** [LC 0042 Trapping Rain Water](../../02-two-pointers/0042-trapping-rain-water/)
- **Rectangle must contain index k:** two pointers expanding greedily: LC 1793 Maximum Score of a Good Subarray (not added yet)
