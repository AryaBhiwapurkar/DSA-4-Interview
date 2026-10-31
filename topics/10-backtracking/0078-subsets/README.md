---
number: 78
title: Subsets
difficulty: Medium
topic: Backtracking
pattern: Include/exclude
link: https://leetcode.com/problems/subsets/
lists: [NeetCode 150]
followup_of: []
related: ["0090 Subsets II", "0077 Combinations", "0046 Permutations", "0039 Combination Sum"]
---

# 0078. Subsets

## ⚡ 30-Second Summary
**Pattern:** Backtracking (every node of the recursion tree is an answer)
**Key insight:** Each element is either in or out, so there are 2ⁿ subsets. With the start-index loop, every partial path is itself a valid subset, so you save at *every* call, not just at leaves.
**Go-to:** Start-index backtracking, O(n · 2ⁿ) time, O(n) extra space

## Problem
Given an array of distinct integers, return all of its subsets (the power set), with no duplicate subsets. Any order. [LeetCode](https://leetcode.com/problems/subsets/)

**Examples:**
```
Input:  nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
Why:    Each of the 3 elements is in or out: 2³ = 8 subsets, including the empty one.

Input:  nums = [0]
Output: [[],[0]]
Why:    Take it or leave it.
```

**Constraints:**
- 1 ≤ n ≤ 10, values distinct. 2¹⁰ = 1024 subsets.

## Hints
<details><summary>Hint 1</summary>
For each element, how many choices are there? How many subsets in total?
</details>
<details><summary>Hint 2</summary>
In the combination template you save only at size k. What if you save at every step?
</details>
<details><summary>Hint 3</summary>
`dfs(start)`: save a copy of path first. Then for i from start: push nums[i], dfs(i + 1), pop.
</details>

## Clarifying Questions
- Distinct elements? (Yes. With duplicates it's 0090.)
- Include the empty set? (Yes.)
- Order of subsets / within a subset? (Any.)

## Example Walkthrough
`[1,2,3]` iteratively: start with [[]]. Add 1 to each → [], [1]. Add 2 to each → [], [1], [2], [1,2]. Add 3 → doubles to 8.

## Approaches

### 1. Iterative Doubling: O(n · 2ⁿ) time, O(n · 2ⁿ) space
Start with [[]]; for each element, append a copy of every existing subset with that element added.

### 2. Bitmask: O(n · 2ⁿ) time, O(n) extra
Each mask from 0 to 2ⁿ - 1 is a subset: bit j set means nums[j] is in. Neat, but limited to n ≤ ~30 and less flexible.

### 3. Backtracking ⭐ Go-to: O(n · 2ⁿ) time, O(n) extra space
Start-index loop; record the path on entry to every call.
**Why it's the go-to:** it's the template that adapts to duplicates (0090), sums (0039/0040) and sizes (0077) by changing one line.

## Dry Run (Approach 3)
`nums = [1,2,3]`

| call | start | path (saved on entry) | next picks |
|------|-------|-----------------------|------------|
| 1 | 0 | [] | 1, 2, 3 |
| 2 | 1 | [1] | 2, 3 |
| 3 | 2 | [1,2] | 3 |
| 4 | 3 | [1,2,3] | none |
| 5 | 3 | [1,3] | none |
| 6 | 2 | [2] | 3 |
| 7 | 3 | [2,3] | none |
| 8 | 3 | [3] | none |

8 calls, 8 subsets.

## Edge Case Check
- n = 1: [[], [x]]. ✅
- Negative numbers: values aren't compared, only copied. ✅

## ⚠️ Pitfalls
- **Forgetting the empty subset** (saving only after a push).
- **Python iterative version: `for s in res: res.append(...)`** loops forever; iterate over a snapshot.
- **Bitmask with `1 << n` in C++ for n ≥ 31** overflows int.
- **Not copying the path** when saving (Python/Go).

## 🎯 What the Interviewer Wants
- The 2ⁿ count and why the cost is n · 2ⁿ.
- One clean approach plus a mention of the bitmask alternative.

## Follow-ups
- **Input has duplicates:** [LC 0090 Subsets II](../0090-subsets-ii/)
- **Only subsets of size k:** [LC 0077 Combinations](../0077-combinations/)
- **Subsets summing to a target:** [LC 0040 Combination Sum II](../0040-combination-sum-ii/)
