---
number: 77
title: Combinations
difficulty: Medium
topic: Backtracking
pattern: Backtrack choose k
link: https://leetcode.com/problems/combinations/
lists: [LC Top Interview 150]
followup_of: []
related: ["0078 Subsets", "0039 Combination Sum", "0216 Combination Sum III", "0046 Permutations"]
---

# 0077. Combinations

## ⚡ 30-Second Summary
**Pattern:** Backtracking with a start index, stop at size k
**Key insight:** Pick numbers in increasing order so each set is produced once. Prune: if fewer numbers remain than slots left to fill, stop, so the loop runs `i` only up to `n - (k - len(path)) + 1`.
**Go-to:** Start-index backtracking with the "enough left" prune, O(k · C(n, k)) time, O(k) space

## Problem
Return every way to choose k distinct numbers from 1..n, as sets (order inside doesn't matter). Any order. [LeetCode](https://leetcode.com/problems/combinations/)

**Examples:**
```
Input:  n = 4, k = 2
Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
Why:    C(4,2) = 6 pairs, each listed once in increasing order.

Input:  n = 1, k = 1
Output: [[1]]
Why:    The only number is the only choice.
```

**Constraints:**
- 1 ≤ k ≤ n ≤ 20. C(20,10) ≈ 1.8·10⁵, so pruning helps but output size dominates.

## Hints
<details><summary>Hint 1</summary>
[1,2] and [2,1] are the same answer. What ordering rule makes each set appear once?
</details>
<details><summary>Hint 2</summary>
Only pick numbers bigger than the last one picked. When does a branch become hopeless?
</details>
<details><summary>Hint 3</summary>
`dfs(start)`: if path has k elements, save. Loop i from start to `n - (k - len) + 1`, push, `dfs(i + 1)`, pop.
</details>

## Clarifying Questions
- Is k ≤ n guaranteed? (Yes.)
- Output order? (Any.)

## Example Walkthrough
`n = 4, k = 2`: start with 1 → pair it with 2, 3, 4. Start with 2 → 3, 4. Start with 3 → 4. Starting with 4 is pruned: no larger number remains for the second slot.

## Approaches

### 1. Include / Exclude: O(2ⁿ) time, O(n) space
For each number 1..n, either take it or skip it; save when k are taken. Visits many branches that can't reach size k.

### 2. Start-Index Loop with Pruning ⭐ Go-to: O(k · C(n, k)) time, O(k) space
Loop over candidates ≥ start, but stop early once there aren't enough numbers left to fill the remaining slots.
**Why it's the go-to:** every leaf it reaches is an answer, so it's output-optimal, and it's the same template as 0039/0078.

## Dry Run (Approach 2)
`n = 4, k = 2`

| path | start | loop range (i ≤ n - (k - len) + 1) | action |
|------|-------|-------------------------------------|--------|
| [] | 1 | 1..3 | i = 1 |
| [1] | 2 | 2..4 | save [1,2], [1,3], [1,4] |
| [] | 1 | 1..3 | i = 2 |
| [2] | 3 | 3..4 | save [2,3], [2,4] |
| [] | 1 | 1..3 | i = 3 |
| [3] | 4 | 4..4 | save [3,4] |
| [] | 1 | (4 is out of range) | done, 6 results |

## Edge Case Check
- k = n: one answer [1..n]; the prune leaves exactly one branch per level. ✅
- k = 1: n singletons. ✅

## ⚠️ Pitfalls
- **No prune:** still correct, but explores dead ends like [4] with k = 2.
- **Off-by-one in the bound:** with `need = k - len(path)`, the last valid start is `n - need + 1` (inclusive).
- **Copy the path when saving** in Python and Go.

## 🎯 What the Interviewer Wants
- The start index as the de-duplication device.
- The pruning bound, and that it makes the work proportional to output.

## Follow-ups
- **All sizes at once:** [LC 0078 Subsets](../0078-subsets/)
- **k numbers from 1-9 summing to n:** LC 0216 Combination Sum III (not added yet)
- **Lexicographic next combination iteratively:** Gosper's hack on bitmasks.
