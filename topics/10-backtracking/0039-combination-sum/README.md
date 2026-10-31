---
number: 39
title: Combination Sum
difficulty: Medium
topic: Backtracking
pattern: Backtrack with reuse
link: https://leetcode.com/problems/combination-sum/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0040 Combination Sum II", "0216 Combination Sum III", "0377 Combination Sum IV", "0322 Coin Change"]
---

# 0039. Combination Sum

## ⚡ 30-Second Summary
**Pattern:** Backtracking with a start index, recursing on the same index to allow reuse
**Key insight:** To avoid listing [2,3] and [3,2] separately, only ever pick candidates at index ≥ the last one picked. Reuse is allowed, so recurse with `i`, not `i + 1`. Sorting lets you `break` as soon as a candidate exceeds the remaining target.
**Go-to:** Sorted backtracking with start index + break, O(n^(T/m + 1)) time, O(T/m) space (m = smallest candidate)

## Problem
Given distinct positive integers and a target, return every unique combination (multiset) of candidates that sums to the target. A candidate may be used any number of times. Any order. [LeetCode](https://leetcode.com/problems/combination-sum/)

**Examples:**
```
Input:  candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Why:    2+2+3 and 7 alone are the only multisets that reach 7.

Input:  candidates = [2,3,5], target = 8
Output: [[2,2,2,2],[2,3,3],[3,5]]
Why:    Reuse is allowed, so four 2s count.

Input:  candidates = [2], target = 1
Output: []
Why:    The only candidate is already bigger than the target.
```

**Constraints:**
- 1 ≤ n ≤ 30, 2 ≤ candidates[i] ≤ 40, all distinct; 1 ≤ target ≤ 40.
- Fewer than 150 combinations in the answer, so listing them all is fine.

## Hints
<details><summary>Hint 1</summary>
How do you stop [2,2,3] and [3,2,2] from both showing up?
</details>
<details><summary>Hint 2</summary>
Fix an order: once you move past a candidate, never go back to it. What index does the recursive call start from if reuse is allowed?
</details>
<details><summary>Hint 3</summary>
Sort. `dfs(start, remaining)`: for i from start, if c[i] > remaining break; push c[i], recurse with (i, remaining - c[i]), pop. Save the path when remaining hits 0.
</details>

## Clarifying Questions
- Are candidates distinct and positive? (Yes. Zero or negatives would allow infinite combinations.)
- Can one candidate be used more than once? (Yes, unlimited.)
- Output order, and order inside a combination? (Any.)

## Example Walkthrough
`[2,3,6,7], target 7`: from 2 the path grows 2 → 2,2 → 2,2,2 (remaining 1, nothing fits) → back to 2,2 + 3 = 7 ✓. Starting from 3: 3,3 leaves 1, dead. 6 leaves 1, dead. 7 hits 7 ✓.

## Approaches

### 1. Include / Exclude Recursion: O(2^(n + T/m)) time, O(n + T/m) space
At index i, either use c[i] again (stay at i) or skip it forever (move to i + 1). Same tree as approach 2 written as binary choices; deeper recursion and no early break.

### 2. Sorted Loop from Start Index ⭐ Go-to: O(n^(T/m + 1)) time, O(T/m) space
For each position in the combination, loop over candidates from `start`, recurse with the same `i`. Sorting lets the loop stop at the first candidate that overshoots.
**Why it's the go-to:** the standard combination template; the break is an easy, visible pruning win.

## Dry Run (Approach 2)
`candidates = [2,3,6,7], target = 7`

| path | remaining | start | loop tries | result |
|------|-----------|-------|------------|--------|
| [] | 7 | 0 | 2 | recurse |
| [2] | 5 | 0 | 2 | recurse |
| [2,2] | 3 | 0 | 2 | recurse |
| [2,2,2] | 1 | 0 | 2 > 1 | break |
| [2,2] | 3 | 0 | 3 | remaining 0 → save **[2,2,3]**; then 6 > 3 break |
| [2] | 5 | 0 | 3 → [2,3] rem 2, 3 > 2 break; 6 > 5 break | nothing |
| [] | 7 | 0 | 3 → [3] rem 4 → [3,3] rem 1 dead; 6 → rem 1 dead | nothing |
| [] | 7 | 0 | 7 | save **[7]** |

## Edge Case Check
- Target smaller than every candidate (`[2]`, 1): first loop breaks, result []. ✅
- Target equals a candidate: single-element combination. ✅
- Many small candidates: depth is at most T/m = 20 here. ✅

## ⚠️ Pitfalls
- **Recursing with `i + 1`** forbids reuse (that's 0040). Recursing from 0 creates permutation duplicates.
- **`break` without sorting** skips valid larger-then-smaller candidates; only break on a sorted array (or use `continue`).
- **Saving the path by reference:** C++ `res.push_back(path)` copies (fine); Python must append `path[:]`, Go must copy the slice.
- **Go slice aliasing:** `append(path, x)` passed into recursion can share a backing array between siblings; copy when saving.

## 🎯 What the Interviewer Wants
- Duplicate avoidance via the start index, not a set of sorted tuples.
- The reuse vs no-reuse distinction (`i` vs `i + 1`).
- Pruning with sort + break, and an honest exponential complexity.

## Follow-ups
- **Each candidate once, input has duplicates:** [LC 0040 Combination Sum II](../0040-combination-sum-ii/)
- **Exactly k numbers from 1-9:** LC 0216 Combination Sum III (not added yet)
- **Count ordered ways only:** LC 0377 Combination Sum IV, a DP (not added yet)
- **Fewest coins instead of listing:** [LC 0322 Coin Change](../../13-1d-dp/0322-coin-change/)
