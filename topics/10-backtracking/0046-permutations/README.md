---
number: 46
title: Permutations
difficulty: Medium
topic: Backtracking
pattern: Backtrack with used[]
link: https://leetcode.com/problems/permutations/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0047 Permutations II", "0078 Subsets", "0031 Next Permutation", "0077 Combinations"]
---

# 0046. Permutations

## ⚡ 30-Second Summary
**Pattern:** Backtracking with a `used[]` array
**Key insight:** Unlike combinations, order matters, so every position loops over *all* elements again instead of starting from an index. A `used[]` flag keeps each element to one appearance per permutation.
**Go-to:** Backtracking with used[], O(n · n!) time, O(n) extra space

## Problem
Given an array of distinct integers, return all of its orderings. Any order. [LeetCode](https://leetcode.com/problems/permutations/)

**Examples:**
```
Input:  nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
Why:    3 choices for the first slot, 2 for the second, 1 for the last: 6.

Input:  nums = [0,1]
Output: [[0,1],[1,0]]
Why:    Two elements, two orders.

Input:  nums = [1]
Output: [[1]]
Why:    One element has exactly one ordering.
```

**Constraints:**
- 1 ≤ n ≤ 6, values distinct. 6! = 720, so generating all is fine.

## Hints
<details><summary>Hint 1</summary>
How many choices does the first slot have? The second?
</details>
<details><summary>Hint 2</summary>
In combinations you loop from a start index. Why doesn't that work here?
</details>
<details><summary>Hint 3</summary>
Loop over every index at each depth, skip ones marked used, mark, recurse, unmark. Save when the path has n elements.
</details>

## Clarifying Questions
- Are the values distinct? (Yes. Duplicates are 0047.)
- Output order? (Any.)
- Return a list, or yield one at a time? (List.)

## Example Walkthrough
`[1,2,3]`: slot 1 = 1, slot 2 can be 2 or 3 → [1,2,3], [1,3,2]. Back up, slot 1 = 2 → [2,1,3], [2,3,1]. Slot 1 = 3 → [3,1,2], [3,2,1].

## Approaches

### 1. Backtracking with used[] ⭐ Go-to: O(n · n!) time, O(n) extra space
At each depth, try every unused element. The path and `used[]` are shared and undone on the way back.
**Why it's the go-to:** it's the general template; it extends directly to duplicates (0047) by adding the sorted skip.

### 2. In-Place Swapping: O(n · n!) time, O(n) recursion
For position `i`, swap each `j ≥ i` into slot `i`, recurse on `i + 1`, swap back. No `used[]` or path; the array prefix is the path. Output order differs from approach 1.

## Dry Run (Approach 1)
`nums = [1,2,3]`

| depth | path before | used before | picks | result |
|-------|-------------|-------------|-------|--------|
| 0 | [] | F F F | 1 | |
| 1 | [1] | T F F | 2 | |
| 2 | [1,2] | T T F | 3 | save **[1,2,3]** |
| 1 | [1] | T F F | 3 (unpicked 2) | |
| 2 | [1,3] | T F T | 2 | save **[1,3,2]** |
| 0 | [] | F F F | 2 (unpicked 1) | ... [2,1,3], [2,3,1] |
| 0 | [] | F F F | 3 | ... [3,1,2], [3,2,1] |

## Edge Case Check
- n = 1: one permutation. ✅
- Negative values / zero: no special handling, values are only copied. ✅

## ⚠️ Pitfalls
- **Looping from `start`** (combination habit) produces only the identity order.
- **Forgetting to unmark `used[i]`** after recursion loses later branches.
- **Saving a reference to the path** in Python/Go; copy it.
- **Swap version: forgetting to swap back** corrupts the array for siblings.

## 🎯 What the Interviewer Wants
- Why permutations loop over everything while combinations use a start index.
- n · n! complexity, with the n for copying each result.
- Optionally the swap trick for O(1) extra state.

## Follow-ups
- **Input has duplicates:** LC 0047 Permutations II (not added yet): sort, and skip `nums[i] == nums[i-1] && !used[i-1]`.
- **Next lexicographic permutation in place:** LC 0031 Next Permutation (not added yet)
- **k-th permutation directly:** LC 0060 Permutation Sequence (factorial number system) (not added yet)
- **Subsets instead:** [LC 0078 Subsets](../0078-subsets/)
