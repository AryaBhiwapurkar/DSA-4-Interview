---
number: 2013
title: Detect Squares
difficulty: Medium
topic: Math & Geometry
pattern: Point counts + diagonal
link: https://leetcode.com/problems/detect-squares/
lists: [NeetCode 150]
followup_of: []
related: ["0149 Max Points on a Line", "0939 Minimum Area Rectangle"]
---

# 2013. Detect Squares

## ⚡ 30-Second Summary
**Pattern:** Hash map of point counts; fix the diagonal corner
**Key insight:** An axis-aligned square is fixed by the query point (qx, qy) and its **diagonal** corner (x, y), where |x − qx| = |y − qy| ≠ 0. The other two corners are then (qx, y) and (x, qy). For each stored diagonal candidate, add `cnt[diag] · cnt[(qx, y)] · cnt[(x, qy)]`. Duplicates multiply naturally.
**Go-to:** Count map + scan diagonal candidates, add O(1), count O(distinct points)

## Problem
Design a structure with two operations. `add(point)` stores a point; duplicates are allowed and each copy counts separately. `count(query)` returns how many ways three stored points can form an axis-aligned square of positive area together with the query point. [LeetCode](https://leetcode.com/problems/detect-squares/)

**Examples:**
```
Input:  ["DetectSquares","add","add","add","count","count","add","count"]
        [[],[[3,10]],[[11,2]],[[3,2]],[[11,10]],[[14,8]],[[11,2]],[[11,10]]]
Output: [null,null,null,null,1,0,null,2]
Why:    (3,10), (11,2), (3,2) close one 8×8 square with (11,10). Nothing fits around (14,8).
        After a second (11,2) is added, the same square can be formed with either copy → 2.
```

**Constraints:**
- 0 ≤ x, y ≤ 1000; at most 3000 calls in total, so O(distinct points) per count is fine.
- Squares must have positive area and sides parallel to the axes.

## Hints
<details><summary>Hint 1</summary>
Given the query point, how many of the other three corners do you need to pick before the square is fixed?
</details>
<details><summary>Hint 2</summary>
Pick the corner diagonally opposite the query. What must be true about it, and where are the other two corners?
</details>
<details><summary>Hint 3</summary>
Keep cnt[(x, y)]. In count(qx, qy): for each stored (x, y) with |x − qx| == |y − qy| and x ≠ qx, add cnt[(x, y)] · cnt[(qx, y)] · cnt[(x, qy)].
</details>

## Clarifying Questions
- Do duplicate points count separately? (Yes, so multiply counts.)
- Does the query point itself get added? (No.)
- Only axis-aligned squares? (Yes, no rotated ones.)
- Zero-area squares? (Excluded.)

## Example Walkthrough
Stored: (3,10), (11,2) ×2, (3,2). Query (11,10). The diagonal candidate (3,2) has |3 − 11| = 8 = |2 − 10|. The other corners are (11,2) with count 2 and (3,10) with count 1. That gives 1 · 2 · 1 = 2. The candidates (3,10) and (11,2) fail the diagonal test (one difference is 0).

## Approaches

### 1. Scan Diagonal Candidates ⭐ Go-to: add O(1), count O(P) where P = distinct points
**Why it's the go-to:** one loop with one condition. Choosing the diagonal corner means each square is counted exactly once.

### 2. Scan the Query's Column: add O(1), count O(points sharing x = qx)
For each stored y ≠ qy in column qx, the side is d = y − qy. Check both squares, to the right (qx + |d|) and to the left (qx − |d|). That's faster when points are spread out, at the cost of a nested map plus two corner lookups per candidate.

## Dry Run (Approach 1)
After all four adds, count(11, 10):

| diagonal (x, y) | cnt | \|dx\|, \|dy\| | valid? | cnt(qx, y) | cnt(x, qy) | adds |
|-----------------|-----|----------------|--------|------------|------------|------|
| (3,10) | 1 | 8, 0 | no | | | 0 |
| (11,2) | 2 | 0, 8 | no | | | 0 |
| (3,2) | 1 | 8, 8 | yes | (11,2) → 2 | (3,10) → 1 | 2 |

Total **2**.

## Edge Case Check
- Query on a stored point → the diagonal candidate has dx = 0 and is skipped. ✅
- Only three of four corners stored → a missing corner has count 0, so it adds 0. ✅
- Squares on both sides of the query → each diagonal is checked separately. ✅

## ⚠️ Pitfalls
- **Not multiplying counts:** duplicates are separate points.
- **C++ `cnt[{x, y}]` with `operator[]`** inserts zero entries, which grow the map you're iterating. Use `find`/`count`, or a lookup helper.
- **Forgetting dx ≠ 0** counts degenerate "squares".
- **Iterating raw added points** instead of distinct points with counts multiplies duplicates twice.

## 🎯 What the Interviewer Wants
- Reduce a square to "query + diagonal corner".
- Correct duplicate handling with a count map.
- Complexity per operation, and the column-based optimisation.

## Follow-ups
- **Collinear points instead of squares:** [LC 0149 Max Points on a Line](../0149-max-points-on-a-line/)
- **Rectangles, minimum area:** LC 0939 Minimum Area Rectangle (not added yet). Fix the diagonal, look up the other two corners in a set.
- **Rotated squares:** fix a side (two points) and compute the other two corners with a 90° rotation of the side vector.
