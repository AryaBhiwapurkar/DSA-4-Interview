---
number: 45
title: Jump Game II
difficulty: Medium
topic: Greedy
pattern: BFS-style level greedy
link: https://leetcode.com/problems/jump-game-ii/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: ["0055 Jump Game"]
related: ["1024 Video Stitching", "1326 Minimum Number of Taps to Open to Water a Garden"]
---

# 0045. Jump Game II

## ⚡ 30-Second Summary
**Pattern:** Implicit BFS by levels, done greedily
**Key insight:** Indices reachable in k jumps form a contiguous window. The next window ends at the farthest `i + nums[i]` over the current window. Count how many windows you pass before covering the last index.
**Go-to:** Level greedy with `end` and `farthest`, O(n) time, O(1) space

## Problem
Same jump rules as LC 55, but the last index is guaranteed reachable. Return the fewest jumps needed to get there from index 0. [LeetCode](https://leetcode.com/problems/jump-game-ii/)

**Examples:**
```
Input:  nums = [2,3,1,1,4]
Output: 2
Why:    Jump to index 1, then its 3 reaches the end.

Input:  nums = [2,3,0,1,4]
Output: 2
Why:    Same route: index 0 → 1 → 4. The 0 at index 2 is never used.
```

**Constraints:**
- 1 ≤ n ≤ 10⁴, 0 ≤ nums[i] ≤ 1000.
- The end is always reachable.

## Hints
<details><summary>Hint 1</summary>
Think BFS: which indices are reachable in 0 jumps? In 1? Do these sets have a simple shape?
</details>
<details><summary>Hint 2</summary>
Each level is a contiguous range. While scanning the current range, what decides where the next range ends?
</details>
<details><summary>Hint 3</summary>
Loop i over 0..n-2, keeping farthest = max(farthest, i + nums[i]). When i hits end (the edge of the current level), jumps++ and end = farthest. Return jumps.
</details>

## Clarifying Questions
- Always reachable? (Yes, guaranteed.)
- n = 1? (0 jumps.)
- Need the path or just the count? (Count.)

## Example Walkthrough
`[2,3,1,1,4]`: level 0 = {0}. From it you reach up to index 2, so level 1 = {1, 2}. From those, index 1 reaches 4, so level 2 includes the end. Two jumps.

## Approaches

### 1. DP: O(n²) time, O(n) space
dp[j] = min(dp[i] + 1) over every i that can reach j.

### 2. BFS Levels ⭐ Go-to: O(n) time, O(1) space
Scan once; each time you finish a level, add a jump and move the boundary to the farthest reach.
**Why it's the go-to:** linear, constant space, and the "levels of BFS" framing makes correctness easy to argue.

## Dry Run (Approach 2)
`[2,3,1,1,4]` (loop stops before index 4).

| i | farthest | i == end? | jumps | end |
|---|----------|-----------|-------|-----|
| start | 0 | | 0 | 0 |
| 0 | 2 | yes | 1 | 2 |
| 1 | 4 | no | 1 | 2 |
| 2 | 4 | yes | **2** | 4 |
| 3 | 4 | no | 2 | 4 |

## Edge Case Check
- `[0]` → loop doesn't run → 0. ✅
- All ones `[1,1,1,1]` → 3. ✅
- One big first jump `[5,1,1,1,1]` → 1. ✅

## ⚠️ Pitfalls
- **Looping to the last index** adds an extra jump when end lands exactly on n-1.
- **Greedy "jump as far as possible"** is wrong: in `[2,3,1,1,4]` jumping 2 lands on a 1 and takes 3 jumps total.
- **Breaking early** is fine (`if end >= n-1: break`), but keep the check after the update.

## 🎯 What the Interviewer Wants
- The BFS-levels view, then the O(1)-space version.
- Clear handling of the last index.
- Mention the O(n²) DP as the baseline.

## Follow-ups
- **Just reachability:** [LC 0055 Jump Game](../0055-jump-game/)
- **Same greedy on intervals:** LC 1024 Video Stitching (not added yet), LC 1326 Minimum Number of Taps to Open to Water a Garden (not added yet)
- **Not always reachable:** return -1 if `farthest` doesn't grow past `end` at a level boundary.
