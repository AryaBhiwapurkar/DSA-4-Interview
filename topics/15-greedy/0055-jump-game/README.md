---
number: 55
title: Jump Game
difficulty: Medium
topic: Greedy
pattern: Track farthest reach
link: https://leetcode.com/problems/jump-game/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0045 Jump Game II", "1306 Jump Game III", "1871 Jump Game VII"]
---

# 0055. Jump Game

## ⚡ 30-Second Summary
**Pattern:** Greedy, track the farthest reachable index
**Key insight:** The reachable indices always form a prefix [0, reach]. Sweep left to right, extending `reach = max(reach, i + nums[i])`. If you ever stand on an index beyond `reach`, you're stuck.
**Go-to:** Farthest reach, O(n) time, O(1) space

## Problem
Each value says how far you may jump forward from that index (any distance up to it). Starting at index 0, decide whether the last index is reachable. [LeetCode](https://leetcode.com/problems/jump-game/)

**Examples:**
```
Input:  nums = [2,3,1,1,4]
Output: true
Why:    Index 0 → 1 (jump 1), then index 1 can jump 3 straight to the end.

Input:  nums = [3,2,1,0,4]
Output: false
Why:    Every path lands on index 3, whose 0 is a dead end, and nothing jumps over it.
```

**Constraints:**
- 1 ≤ n ≤ 10⁴, 0 ≤ nums[i] ≤ 10⁵.
- O(n²) DP passes, but O(n) is expected.

## Hints
<details><summary>Hint 1</summary>
If you can reach index i, can you also reach every index before it?
</details>
<details><summary>Hint 2</summary>
So the reachable set is just a prefix. What single number describes it?
</details>
<details><summary>Hint 3</summary>
Keep reach = farthest index reachable. For each i: if i > reach return false; reach = max(reach, i + nums[i]). Return true after the loop (or as soon as reach ≥ n - 1).
</details>

## Clarifying Questions
- "Up to nums[i]", not exactly? (Up to.)
- Only forward jumps? (Yes.)
- n = 1? (Already at the end → true.)

## Example Walkthrough
`[1,0,1]`: at 0, reach = 1. At 1, reach stays 1 (jump 0). At 2: 2 > reach → false. The zero at index 1 walls off the rest.

## Approaches

### 1. DP from the Right: O(n²) time, O(n) space
good[i] = some j in (i, i + nums[i]] is good. Correct but quadratic.

### 2. Farthest Reach ⭐ Go-to: O(n) time, O(1) space
**Why it's the go-to:** one pass, one variable, and a clean argument (reachable = prefix).

### 3. Shrinking Goal: O(n) time, O(1) space
Walk backwards; whenever i can reach the current goal, move the goal to i. Answer: goal == 0. Equally good; some find it more intuitive.

## Dry Run (Approach 2)
`[3,2,1,0,4]`

| i | nums[i] | i > reach? | reach after |
|---|---------|------------|-------------|
| 0 | 3 | no (0 ≤ 0) | 3 |
| 1 | 2 | no | 3 |
| 2 | 1 | no | 3 |
| 3 | 0 | no | 3 |
| 4 | 4 | **yes (4 > 3)** | return false |

## Edge Case Check
- `[0]` → loop sees i = 0 ≤ reach → true. ✅
- `[2,0,0]` → reach 2 at once → true. ✅
- Zero in the middle that can be jumped over (`[2,0,1]`) → true. ✅

## ⚠️ Pitfalls
- **Treating 0 as an automatic failure:** you can jump over a zero.
- **Simulating "always jump max"** fails: [2,3,0,0,1] max-jumps to a 0, though 0 → 1 → 4 works.
- **Checking `i > reach` after updating** reach lets an unreachable index extend it.

## 🎯 What the Interviewer Wants
- The prefix argument behind the greedy.
- O(n) / O(1), and a quick mention of the DP it replaces.
- Readiness for Jump Game II (min jumps).

## Follow-ups
- **Minimum number of jumps:** [LC 0045 Jump Game II](../0045-jump-game-ii/)
- **Jump left or right by exactly nums[i]:** LC 1306 Jump Game III (not added yet). BFS/DFS.
- **Jumps within [minJump, maxJump] onto '0' cells:** LC 1871 Jump Game VII (not added yet). Sliding window over reachable cells.
