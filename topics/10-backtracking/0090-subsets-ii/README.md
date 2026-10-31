---
number: 90
title: Subsets II
difficulty: Medium
topic: Backtracking
pattern: Sort + skip duplicates
link: https://leetcode.com/problems/subsets-ii/
lists: [NeetCode 150]
followup_of: ["0078 Subsets"]
related: ["0078 Subsets", "0040 Combination Sum II", "0047 Permutations II"]
---

# 0090. Subsets II

## ⚡ 30-Second Summary
**Pattern:** Subsets backtracking + sort + same-level duplicate skip
**Key insight:** Sort so equal values sit together. At one recursion level, picking the first or the second copy of a value as "the next element" leads to identical subsets, so skip `nums[i]` when `i > start && nums[i] == nums[i-1]`. Deeper levels may still take the next copy, which gives [2,2].
**Go-to:** Sort + skip duplicates, O(n · 2ⁿ) time, O(n) extra space

## Problem
Given an integer array that may contain duplicates, return all distinct subsets (no subset listed twice). Any order. [LeetCode](https://leetcode.com/problems/subsets-ii/)

**Examples:**
```
Input:  nums = [1,2,2]
Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
Why:    The two 2s are interchangeable, so [1,2] and [2] each appear once, not twice.

Input:  nums = [0]
Output: [[],[0]]
Why:    No duplicates: the plain power set.
```

**Constraints:**
- 1 ≤ n ≤ 10, values in [-10, 10].

## Hints
<details><summary>Hint 1</summary>
Run 0078 on [1,2,2]. Which subsets come out twice, and from which branches?
</details>
<details><summary>Hint 2</summary>
The duplicates come from choosing a different copy of 2 at the same position in the subset. How does sorting make those choices easy to spot?
</details>
<details><summary>Hint 3</summary>
Sort. In `dfs(start)`, save the path, then loop i from start, `continue` if `i > start and nums[i] == nums[i-1]`, else push, `dfs(i+1)`, pop.
</details>

## Clarifying Questions
- Is [1,2] the same subset as [2,1]? (Yes, sets.)
- Output order? (Any.)

## Example Walkthrough
Sorted `[1,2,2]`: from [], pick 1 → [1], then [1,2], then [1,2,2]. Back at [1], the second 2 is skipped (it would give [1,2] again). From [], pick the first 2 → [2], [2,2]; the second 2 at depth 0 is skipped.

## Approaches

### 1. Power Set + Set of Sorted Tuples: O(n² · 2ⁿ) time, O(n · 2ⁿ) space
Sort, generate all 2ⁿ subsets, dedupe with a set (each insert compares O(n)-length subsets, log 2ⁿ = n times). Works but creates every duplicate first.

### 2. Sort + Skip Duplicates ⭐ Go-to: O(n · 2ⁿ) time, O(n) extra space
Never generate a duplicate: the skip rule prunes repeated branches at the level where they would start.
**Why it's the go-to:** structural dedupe, same rule as 0040, no extra set.

## Dry Run (Approach 2)
Sorted `[1,2,2]`

| call | start | path (saved) | i | decision |
|------|-------|--------------|---|----------|
| A | 0 | [] | 0 (1) | pick → B |
| B | 1 | [1] | 1 (2) | i == start, pick → C |
| C | 2 | [1,2] | 2 (2) | i == start, pick → D |
| D | 3 | [1,2,2] | | no loop |
| B | 1 | | 2 (2) | i > start, equals nums[1] → **skip** |
| A | 0 | | 1 (2) | pick → E |
| E | 2 | [2] | 2 (2) | i == start, pick → F |
| F | 3 | [2,2] | | no loop |
| A | 0 | | 2 (2) | i > start, equals nums[1] → **skip** |

6 subsets saved.

## Edge Case Check
- All equal `[2,2,2]`: [], [2], [2,2], [2,2,2]. ✅
- No duplicates: behaves exactly like 0078. ✅
- Duplicates not adjacent in input (`[4,1,4]`): sorting groups them first. ✅

## ⚠️ Pitfalls
- **Forgetting to sort**: the adjacent-equal check misses split duplicates.
- **`i > 0` instead of `i > start`**: drops [2,2] and [1,2,2].
- **Using a set of lists in Python**: lists aren't hashable; use tuples (approach 1 only).

## 🎯 What the Interviewer Wants
- Spot where duplicates come from and prune there, not after.
- Explain `i > start` precisely.

## Follow-ups
- **No duplicates:** [LC 0078 Subsets](../0078-subsets/)
- **Same skip with a target sum:** [LC 0040 Combination Sum II](../0040-combination-sum-ii/)
- **Unique permutations:** LC 0047 Permutations II (not added yet)
