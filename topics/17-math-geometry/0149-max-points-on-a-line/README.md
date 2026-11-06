---
number: 149
title: Max Points on a Line
difficulty: Hard
topic: Math & Geometry
pattern: Slope hashmap (gcd)
link: https://leetcode.com/problems/max-points-on-a-line/
lists: [LC Top Interview 150]
followup_of: []
related: ["2013 Detect Squares", "1232 Check If It Is a Straight Line"]
---

# 0149. Max Points on a Line

## ⚡ 30-Second Summary
**Pattern:** Fix an anchor point, group the others by exact slope
**Key insight:** Every line through anchor p is identified by its direction from p. Store the direction as a reduced integer pair (dx/g, dy/g) with a fixed sign, never as a float. Points with the same key are collinear with p. The best line through p has `1 + max group size` points. Take the maximum over all anchors.
**Go-to:** Anchor + gcd-normalised slope map, O(n² log C) time, O(n) space

## Problem
Given distinct points on the plane, return the largest number of them that lie on one straight line. [LeetCode](https://leetcode.com/problems/max-points-on-a-line/)

**Examples:**
```
Input:  points = [[1,1],[2,2],[3,3]]
Output: 3
Why:    All three are on y = x.

Input:  points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
Output: 4
Why:    (3,2), (4,1), (2,3), (1,4) all lie on x + y = 5.
```

**Constraints:**
- 1 ≤ n ≤ 300, so O(n³) is ~2.7·10⁷ (passes); O(n²) is the expected answer.
- Coordinates in [−10⁴, 10⁴]; all points are **distinct**.

## Hints
<details><summary>Hint 1</summary>
If you fix one point that's on the line, what single number describes the line?
</details>
<details><summary>Hint 2</summary>
Floating-point slopes can collide or differ by rounding. How can you represent a slope exactly with integers?
</details>
<details><summary>Hint 3</summary>
For each anchor i, for every j &gt; i: dx, dy = difference; g = gcd(|dx|, |dy|); divide both by g; flip signs so dx &gt; 0 (or dx == 0 and dy &gt; 0). Count keys in a fresh map per anchor. The answer is max(1 + count).
</details>

## Clarifying Questions
- Can points repeat? (Not here; if they could, count duplicates of the anchor separately and add them to every line.)
- Integer coordinates? (Yes, so the gcd representation is exact.)
- n = 1? (Answer 1.)

## Example Walkthrough
Anchor (3,2) in example 2. The directions to (4,1), (2,3) and (1,4) are (1,−1), (−1,1) and (−2,2). Normalised with dx > 0, they all become (1,−1). Group size 3 → 1 + 3 = **4** points on one line.

## Approaches

### 1. Every Pair + Collinearity Check: O(n³) time, O(1) space
For each pair (i, j), count the k with cross product `(xj − xi)(yk − yi) − (yj − yi)(xk − xi) == 0`. Exact and simple, but cubic.

### 2. Anchor + Slope Map ⭐ Go-to: O(n² log C) time, O(n) space
**Why it's the go-to:** quadratic, exact integer keys, and the normalisation rules are a few lines you can state up front.

## Dry Run (Approach 2)
`[[1,1],[2,2],[3,3]]`

| anchor | other | dx, dy | g | key | counts |
|--------|-------|--------|---|-----|--------|
| (1,1) | (2,2) | 1, 1 | 1 | (1,1) | {(1,1):1} |
| (1,1) | (3,3) | 2, 2 | 2 | (1,1) | {(1,1):2} |
| (2,2) | (3,3) | 1, 1 | 1 | (1,1) | {(1,1):1} |

Best = 1 + 2 = **3**, from anchor (1,1).

## Edge Case Check
- One point → 1 (no pairs; the answer starts at 1). ✅
- Vertical line (dx = 0) → key (0, 1) after sign normalisation. ✅
- Horizontal line (dy = 0) → key (1, 0). ✅
- Opposite directions (−2, 2) and (1, −1) → both map to (1, −1). ✅

## ⚠️ Pitfalls
- **Float slopes:** `dy / dx` rounding can merge different lines, and vertical lines divide by zero. In Java, `Double` keys even treat −0.0 and 0.0 as different.
- **No sign normalisation:** (1, −1) and (−1, 1) become different keys for the same line.
- **Reusing one map across anchors:** clear it for each anchor, because lines through different anchors aren't comparable.
- **C++ `std::gcd` with negatives:** it returns a non-negative result, but normalise the signs yourself afterwards anyway.
- **Returning 0 for n = 1:** start the answer at 1.

## 🎯 What the Interviewer Wants
- Anchor + slope grouping in O(n²).
- Exact slope keys (gcd-reduced, sign-normalised), and why floats fail.
- Correct vertical and horizontal handling, plus a word on duplicates.

## Follow-ups
- **Squares instead of lines, with a count map:** [LC 2013 Detect Squares](../2013-detect-squares/)
- **Are all points collinear?** LC 1232 Check If It Is a Straight Line (not added yet). Cross product against the first two points.
- **Duplicate points allowed:** count copies of the anchor and add them to every line through it.
