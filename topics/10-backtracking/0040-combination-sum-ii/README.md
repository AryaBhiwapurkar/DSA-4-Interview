---
number: 40
title: Combination Sum II
difficulty: Medium
topic: Backtracking
pattern: Sort + skip duplicates, no reuse
link: https://leetcode.com/problems/combination-sum-ii/
lists: [NeetCode 150]
followup_of: ["0039 Combination Sum"]
related: ["0039 Combination Sum", "0090 Subsets II", "0047 Permutations II"]
---

# 0040. Combination Sum II

## ⚡ 30-Second Summary
**Pattern:** Sorted backtracking, each element used once, skip equal values at the same depth
**Key insight:** Duplicates in the input create duplicate combinations only when two equal values are tried *as the same position* of the combination. After sorting, skip `c[i]` when `i > start && c[i] == c[i-1]`; picking equal values at *different* depths ([1,1,6]) stays allowed.
**Go-to:** Sort + skip duplicates + break, O(2ⁿ · n) time, O(n) space

## Problem
Given a list of positive integers (may contain duplicates) and a target, return every unique combination that sums to the target, using each list element at most once. Any order. [LeetCode](https://leetcode.com/problems/combination-sum-ii/)

**Examples:**
```
Input:  candidates = [10,1,2,7,6,1,5], target = 8
Output: [[1,1,6],[1,2,5],[1,7],[2,6]]
Why:    The two 1s can both appear in one combination, but [1,7] must not appear twice.

Input:  candidates = [2,5,2,1,2], target = 5
Output: [[1,2,2],[5]]
Why:    Three 2s exist, but only two are needed, and the result lists [1,2,2] once.
```

**Constraints:**
- 1 ≤ n ≤ 100, 1 ≤ candidates[i] ≤ 50, 1 ≤ target ≤ 30.
- Small target keeps the search shallow, so pruning by sum matters more than n.

## Hints
<details><summary>Hint 1</summary>
Start from 0039 and change one index so nothing is reused. What new problem shows up?
</details>
<details><summary>Hint 2</summary>
With [1,1,7], picking "the first 1" or "the second 1" as the first element gives the same [1,7]. Where in the recursion do these two branches meet?
</details>
<details><summary>Hint 3</summary>
Sort. In the loop `for i in start..n`, skip when `i > start and c[i] == c[i-1]`; break when `c[i] > remaining`; recurse with `i + 1`.
</details>

## Clarifying Questions
- Can the input have duplicates? (Yes, that's the point of this variant.)
- Each element at most once? (Yes, by position.)
- Are values positive? (Yes, which makes the break prune valid.)

## Example Walkthrough
Sorted `[1,1,2,5,6,7,10]`, target 8. Start with the first 1: the second 1 is allowed next (different depth), giving [1,1,6]; then [1,2,5] and [1,7]. Back at depth 0, the second 1 is skipped because the first 1 already explored every combination starting with 1. Then 2 gives [2,6].

## Approaches

### 1. All Subsets + Set: O(2ⁿ · n log n) time, O(2ⁿ · n) space
Generate every subset with the right sum, sort it, insert into a set of tuples. Correct but wasteful: explores every duplicate branch and stores them.

### 2. Sort + Skip Duplicates ⭐ Go-to: O(2ⁿ · n) time, O(n) space
Loop-from-start backtracking with `i + 1` (no reuse), the same-level skip, and a break on overshoot.
**Why it's the go-to:** no extra set, and the skip rule is the same one used in 0090 and 0015, so it's worth knowing cold.

## Dry Run (Approach 2)
Sorted `[1,1,2,5,6,7,10]`, target 8

| path | rem | start | i / value | action |
|------|-----|-------|-----------|--------|
| [] | 8 | 0 | 0 / 1 | pick |
| [1] | 7 | 1 | 1 / 1 | i == start → allowed, pick |
| [1,1] | 6 | 2 | 2 / 2 | pick → [1,1,2] rem 4; next 5 > 4, break |
| [1,1] | 6 | 2 | 3 / 5, then 4 / 6 | 5 leaves 1 (dead); 6 → save **[1,1,6]**; 7 > 6 break |
| [1] | 7 | 1 | 2 / 2 | [1,2] rem 5 → 5 fits, save **[1,2,5]** |
| [1] | 7 | 1 | 3 / 5, 4 / 6, 5 / 7 | 5 and 6 dead ends; 7 → save **[1,7]**; 10 break |
| [] | 8 | 0 | 1 / 1 | i > start and equals c[0] → **skip** |
| [] | 8 | 0 | 2 / 2 | [2] rem 6 → 5 dead, 6 → save **[2,6]** |
| [] | 8 | 0 | 3..6 / 5, 6, 7, 10 | 5, 6, 7 dead ends; 10 > 8 break, done |

## Edge Case Check
- All equal (`[2,2,2]`, 4): only [2,2] once. ✅
- Nothing fits: []. ✅
- Single element equal to target: one result. ✅

## ⚠️ Pitfalls
- **`i > 0` instead of `i > start`** in the skip also kills [1,1,6], since the second 1 at depth 1 gets skipped.
- **Skipping without sorting** misses duplicates that aren't adjacent.
- **Recursing with `i`** (0039's rule) reuses elements.
- **Copying the path:** Python `path[:]`, Go `slices.Clone(path)`.

## 🎯 What the Interviewer Wants
- Explain *why* the skip is per level (same position in the combination), not global.
- Contrast with 0039 (reuse) in one sentence.
- Avoid a result set; dedupe structurally.

## Follow-ups
- **Reuse allowed, distinct input:** [LC 0039 Combination Sum](../0039-combination-sum/)
- **All unique subsets, no target:** [LC 0090 Subsets II](../0090-subsets-ii/)
- **Unique permutations with duplicates:** LC 0047 Permutations II (not added yet)
