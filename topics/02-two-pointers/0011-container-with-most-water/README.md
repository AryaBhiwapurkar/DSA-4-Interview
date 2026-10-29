---
number: 11
title: Container With Most Water
difficulty: Medium
topic: Two Pointers
pattern: Converging, move the shorter side
link: https://leetcode.com/problems/container-with-most-water/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0042 Trapping Rain Water", "0084 Largest Rectangle in Histogram"]
---

# 0011. Container With Most Water

## ⚡ 30-Second Summary
**Pattern:** Converging two pointers, always move the shorter wall
**Key insight:** Area = min(h[l], h[r]) × (r - l). Moving the taller wall inward can only shrink the width and never raises the min, so it can't help. Moving the shorter wall is the only move that might find a bigger area.
**Go-to:** Two pointers, O(n) time, O(1) space

## Problem
Given heights of vertical lines at positions 0..n-1, pick two lines that, together with the x-axis, hold the most water. Return that maximum amount (the container can't be tilted).

**Examples:**
```
Input:  height = [1,8,6,2,5,4,8,3,7]
Output: 49
Why:    Lines at 1 (height 8) and 8 (height 7): min 7 × width 7 = 49.

Input:  height = [1,1]
Output: 1
Why:    min 1 × width 1.
```

**Constraints:**
- 2 ≤ n ≤ 10⁵, so O(n²) is too slow.
- 0 ≤ height[i] ≤ 10⁴; max area ≤ 10⁹, fits in 32 bits.

## Hints
<details><summary>Hint 1</summary>
Start with the widest container. How can you possibly do better from there?
</details>
<details><summary>Hint 2</summary>
If you move the taller line inward, can the area ever increase?
</details>
<details><summary>Hint 3</summary>
Always move the pointer at the shorter line; track the max area as you go.
</details>

## Clarifying Questions
- Lines have zero width? (Yes; width is the index difference.)
- Can heights be 0? (Yes.)
- Return the area, or the indices? (Area.)

## Example Walkthrough
`height = [1,8,6,2,5,4,8,3,7]`
- l = 0 (1), r = 8 (7): area 1 × 8 = 8. Move l (shorter).
- l = 1 (8), r = 8 (7): area 7 × 7 = 49. Move r.
- Remaining pairs are narrower and never beat 49.

## Approaches

### 1. Brute Force: O(n²) time, O(1) space
Check every pair. 5·10⁹ pairs at n = 10⁵: too slow.

### 2. Two Pointers ⭐ Go-to: O(n) time, O(1) space
`l = 0, r = n-1`; record the area; move whichever side is shorter (either on a tie).
**Why it's the go-to:** linear, tiny code, and the "shorter side is the bottleneck" argument is the expected explanation.

## Dry Run (Approach 2)
`height = [1,8,6,2,5,4,8,3,7]`

| l | r | h[l] | h[r] | area | best | move |
|---|---|------|------|------|------|------|
| 0 | 8 | 1 | 7 | 8 | 8 | l |
| 1 | 8 | 8 | 7 | 49 | 49 | r |
| 1 | 7 | 8 | 3 | 18 | 49 | r |
| 1 | 6 | 8 | 8 | 40 | 49 | r (tie) |
| 1 | 5 | 8 | 4 | 16 | 49 | r |
| 1 | 4 | 8 | 5 | 15 | 49 | r |
| 1 | 3 | 8 | 2 | 4 | 49 | r |
| 1 | 2 | 8 | 6 | 6 | 49 | r → stop |

## Edge Case Check
- n = 2: one area computed. ✅
- All zeros: answer 0. ✅
- Strictly increasing heights: l moves right each time; still O(n). ✅

## ⚠️ Pitfalls
- **Moving the taller side** can skip the optimum.
- **Confusing with Trapping Rain Water:** here only two lines matter and lines in between are ignored.
- **Using `height[i]` as width:** width is `r - l`.

## 🎯 What the Interviewer Wants
- The greedy argument for moving the shorter wall (proof sketch, not just code).
- O(n) with constant space.

## Follow-ups
- **Water trapped by all bars together:** [LC 0042 Trapping Rain Water](../0042-trapping-rain-water/)
- **Largest rectangle under a histogram (contiguous bars):** monotonic stack: LC 0084 Largest Rectangle in Histogram (not added yet)
- **Return the indices too:** store l, r when best updates.
