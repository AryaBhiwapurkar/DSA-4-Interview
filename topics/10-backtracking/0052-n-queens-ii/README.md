---
number: 52
title: N-Queens II
difficulty: Hard
topic: Backtracking
pattern: Backtrack with col/diag sets (count)
link: https://leetcode.com/problems/n-queens-ii/
lists: [LC Top Interview 150]
followup_of: ["0051 N-Queens"]
related: ["0051 N-Queens"]
---

# 0052. N-Queens II

## ⚡ 30-Second Summary
**Pattern:** Row-by-row backtracking, counting instead of collecting
**Key insight:** Same search as 0051, but nothing needs to be built: return 1 at row n and sum over columns. Because no board is kept, the state shrinks to three bitmasks (columns, "\" and "/" diagonals), and shifting the diagonal masks by one per row moves the attacks down.
**Go-to:** Backtracking with col/diag sets, O(n!) time, O(n) space; bitmask version as the follow-up

## Problem
Return how many ways n queens can be placed on an n × n board with no two attacking each other. [LeetCode](https://leetcode.com/problems/n-queens-ii/)

**Examples:**
```
Input:  n = 4
Output: 2
Why:    The two mirror-image boards from 0051 are the only ones.

Input:  n = 1
Output: 1
Why:    One queen, one square.
```

**Constraints:**
- 1 ≤ n ≤ 9.

## Hints
<details><summary>Hint 1</summary>
You solved 0051. What can you drop now that only the count is needed?
</details>
<details><summary>Hint 2</summary>
The board itself. Which three facts decide whether a square is safe?
</details>
<details><summary>Hint 3</summary>
`count(r)`: if r == n return 1; sum `count(r+1)` over columns c where c, r-c, r+c are all free (mark before, unmark after).
</details>

## Clarifying Questions
- Return the count only? (Yes.)
- n range? (1..9, so plain backtracking is fast enough.)

## Example Walkthrough
n = 4: a queen in row 0 at column 0 or 3 leads to no full placement; at column 1 or 2 each gives exactly one. Total 2.

## Approaches

### 1. Backtracking with Column/Diagonal Sets ⭐ Go-to: O(n!) time, O(n) space
0051's search, returning counts.
**Why it's the go-to:** reuses the template you already explained; easy to get right.

### 2. Bitmask Backtracking: O(n!) time, O(n) space
`cols`, `d1`, `d2` are n-bit masks of attacked columns in the current row. Free squares = `~(cols | d1 | d2) & full`. Take the lowest free bit with `x & -x`; recurse with `cols | bit`, `(d1 | bit) << 1`, `(d2 | bit) >> 1`. Several times faster; a nice follow-up.

## Dry Run (Approach 1)
n = 4, solutions found under each row-0 column

| row 0 column | branch result | running total |
|--------------|---------------|---------------|
| 0 | (1,2) and (1,3) both dead-end by row 3 → 0 | 0 |
| 1 | (1,3) → (2,0) → (3,2) → 1 | 1 |
| 2 | mirror of column 1: (1,0) → (2,3) → (3,1) → 1 | 2 |
| 3 | mirror of column 0 → 0 | **2** |

## Edge Case Check
- n = 2, 3: 0. ✅
- n = 8: 92; n = 9: 352. ✅

## ⚠️ Pitfalls
- **Bitmask: not masking the free set with `full`**: `~(cols | d1 | d2)` has bits set above column n-1, so you'd place queens off the board (in Python `~` is negative and the loop never ends).
- **Diagonal array size** must be 2n - 1, with r - c offset by n - 1.
- **Masking `d1` after `<< 1`** keeps the numbers small; without it the answer is still right because the free set is masked, but the masks keep growing.

## 🎯 What the Interviewer Wants
- Quick reuse of 0051 without building boards.
- Bonus: the bitmask trick and why shifting models diagonals.

## Follow-ups
- **List the boards:** [LC 0051 N-Queens](../0051-n-queens/)
- **Exploit symmetry:** count row-0 columns in the left half, double, and handle the middle column for odd n.
