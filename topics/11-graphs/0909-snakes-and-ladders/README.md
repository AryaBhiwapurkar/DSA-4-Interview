---
number: 909
title: Snakes and Ladders
difficulty: Medium
topic: Graphs
pattern: BFS on board
link: https://leetcode.com/problems/snakes-and-ladders/
lists: [LC Top Interview 150]
followup_of: []
related: ["0433 Minimum Genetic Mutation", "0127 Word Ladder", "1306 Jump Game III"]
---

# 0909. Snakes and Ladders

## ⚡ 30-Second Summary
**Pattern:** BFS over squares (unweighted shortest path)
**Key insight:** Each square 1..n² is a node; a roll is an edge to any of the next 6 squares, redirected if that square starts a snake or ladder. Fewest rolls = BFS distance. The only fiddly part is mapping a square number to (row, col) on the zigzag board, so flatten the board once first.
**Go-to:** Flatten board + BFS, O(n²) time, O(n²) space

## Problem
An n × n board is numbered 1..n² starting bottom-left and snaking left-to-right, then right-to-left on the next row up, and so on. A cell holding a value other than -1 sends you to that square (snake or ladder) if you land on it by a roll; you follow at most one such jump per roll. Starting at 1, each move rolls 1-6. Return the fewest moves to reach n², or -1. [LeetCode](https://leetcode.com/problems/snakes-and-ladders/)

**Examples:**
```
Input:  board = [[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],
                 [-1,35,-1,-1,13,-1],[-1,-1,-1,-1,-1,-1],[-1,15,-1,-1,-1,-1]]
Output: 4
Why:    1 → 2 climbs to 15; 15 → 17 slides to 13; 13 → 14 climbs to 35; 35 → 36.

Input:  board = [[-1,-1],[-1,3]]
Output: 1
Why:    Square 2 is a ladder to 3, but rolling a 3 from square 1 reaches 4 = n² directly.
```

**Constraints:**
- 2 ≤ n ≤ 20; squares 1 and n² have no snake or ladder.
- At most 400 squares, so BFS is trivially fast.

## Hints
<details><summary>Hint 1</summary>
"Fewest moves" with every move costing the same. Which traversal?
</details>
<details><summary>Hint 2</summary>
What are the neighbours of square s? What happens when one of them has a snake or ladder?
</details>
<details><summary>Hint 3</summary>
Flatten the board into `jump[1..n²]` using the zigzag order (row from the bottom = (s-1)/n, reversed column on odd rows). BFS from 1; for each s try s+1..s+6 (≤ n²), replace by jump[t] if ≠ -1, enqueue unseen.
</details>

## Clarifying Questions
- Does landing at the end of a ladder trigger another ladder there? (No, one jump per roll.)
- Do snakes/ladders on squares you pass over (not land on) count? (No.)
- Can the target be unreachable? (Yes, return -1.)

## Example Walkthrough
Example 2: flatten → square 1: -1, 2: 3, 3: -1, 4: -1. From 1 the rolls reach 2 (→ 3), 3, 4. 4 = n² after one move.

## Approaches

### 1. BFS with On-the-Fly Coordinates: O(n²) time, O(n²) space
Same BFS, converting each candidate square to (row, col) as you go. Fine, but the conversion sits inside the hot loop and is easy to get wrong under pressure.

### 2. Flatten + BFS ⭐ Go-to: O(n²) time, O(n²) space
Build `jump[s]` once, then BFS on plain integers.
**Why it's the go-to:** separates the tricky index math from the search, so each part is easy to check.

## Dry Run (Approach 2)
Example 1 (jumps: 2 → 15, 14 → 35, 17 → 13)

| pop | dist | new squares reached (after jumps) |
|-----|------|-----------------------------------|
| 1 | 0 | 15 (via 2), 3, 4, 5, 6, 7 |
| 15 | 1 | 16, 13 (via 17), 18, 19, 20, 21 |
| 3 .. 7 | 1 | 8, 9, 10, 11, 12 |
| 16 | 2 | 22 |
| 13 | 2 | 35 (via 14) |
| 18 .. 21 | 2 | 23 .. 27 |
| 22 | 3 | 28 |
| 35 | 3 | 36 = n² → **4** |

## Edge Case Check
- Ladder straight to n²: answer can be 1. ✅
- Every reachable roll leads to a snake back to 1: BFS empties → -1. ✅
- n = 2: four squares, at most one move. ✅

## ⚠️ Pitfalls
- **Zigzag mapping**: rows count from the bottom, and every other row runs right-to-left.
- **Chaining jumps**: follow only one snake/ladder per roll.
- **Marking the pre-jump square** instead of the post-jump square as visited.
- **Board value is a 1-based square number**, not an index.

## 🎯 What the Interviewer Wants
- Model as shortest path in an unweighted graph → BFS.
- Correct, clearly separated index conversion.

## Follow-ups
- **BFS on an implicit string graph:** [LC 0433 Minimum Genetic Mutation](../0433-minimum-genetic-mutation/)
- **Reachability with jumps of fixed size:** LC 1306 Jump Game III (not added yet)
