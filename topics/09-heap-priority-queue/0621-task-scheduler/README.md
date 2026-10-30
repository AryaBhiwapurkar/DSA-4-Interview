---
number: 621
title: Task Scheduler
difficulty: Medium
topic: Heap / Priority Queue
pattern: Greedy counting / max-heap
link: https://leetcode.com/problems/task-scheduler/
lists: [NeetCode 150]
followup_of: []
related: ["0358 Rearrange String k Distance Apart", "0767 Reorganize String", "1405 Longest Happy String"]
---

# 0621. Task Scheduler

## ⚡ 30-Second Summary
**Pattern:** Greedy: the most frequent task dictates the frame
**Key insight:** Let the most frequent task appear `maxCount` times. It forces `maxCount - 1` gaps of length `n` between its copies, giving `(maxCount - 1)·(n + 1)` slots plus one final slot for each task tied at `maxCount`. If there are more tasks than that frame holds, no idling is needed and the answer is just the number of tasks.
**Go-to:** Counting formula, O(T) time, O(1) space (26 letters)

## Problem
Tasks are letters A-Z, each taking one time unit. The same task must be at least `n` units apart; the CPU can idle. Return the minimum number of units to finish all tasks.

**Examples:**
```
Input:  tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Why:    A B idle A B idle A B.

Input:  tasks = ["A","C","A","B","D","B"], n = 1
Output: 6
Why:    A B A B C D: no idling needed.

Input:  tasks = ["A","A","A","B","B","B"], n = 3
Output: 10
Why:    A B _ _ A B _ _ A B.
```

**Constraints:**
- 1 ≤ T ≤ 10⁴ tasks; 0 ≤ n ≤ 100.

## Hints
<details><summary>Hint 1</summary>
Which task constrains the schedule the most?
</details>
<details><summary>Hint 2</summary>
Lay out the most frequent task with n gaps between copies. How many slots does that frame have?
</details>
<details><summary>Hint 3</summary>
answer = max(T, (maxCount - 1)·(n + 1) + numTasksWithMaxCount). Or simulate with a max-heap of counts and a cooldown queue.
</details>

## Clarifying Questions
- Order of output? (Only the length matters.)
- Can n be 0? (Yes: answer = T.)

## Example Walkthrough
`A×3, B×3, n = 2`: maxCount 3, tied count 2 → (3 - 1)·3 + 2 = 8; T = 6 → max = 8.

## Approaches

### 1. Max-Heap + Cooldown Queue Simulation: O(T log 26) time, O(26) space
Each time unit: run the most frequent available task (pop the heap, decrement, park it in a queue with its ready time); return tasks whose cooldown expired to the heap. Count units until both are empty.

### 2. Counting Formula ⭐ Go-to: O(T) time, O(1) space
**Why it's the go-to:** one pass to count, one line of math, and it's easy to justify with the frame picture. Mention the simulation if the interviewer wants the actual schedule.

## Dry Run (Approach 2)
`["A","A","A","A","A","A","B","C","D","E","F","G"], n = 2`

| quantity | value |
|----------|-------|
| T | 12 |
| maxCount (A) | 6 |
| tasks with maxCount | 1 |
| frame | (6 - 1)·3 + 1 = 16 |
| answer | max(12, 16) = **16** |

## Edge Case Check
- n = 0: frame ≤ T, answer T. ✅
- Many distinct tasks (no idling needed): T wins the max. ✅
- Several tasks tied at maxCount: each adds one slot at the end. ✅

## ⚠️ Pitfalls
- **Forgetting the max with T**: the frame can be smaller than the task count.
- **Counting only one task at maxCount**: ties each add to the last row.
- **Simulation off-by-one** on the ready time (time + n, not time + n + 1, depending on when you check).

## 🎯 What the Interviewer Wants
- The frame argument for the formula, or a correct heap simulation.
- Complexity in terms of T and the 26-letter alphabet.

## Follow-ups
- **Output an actual arrangement with k distance:** heap + queue: LC 0358 Rearrange String k Distance Apart (not added yet)
- **No two adjacent equal (n = 1), return the string:** LC 0767 Reorganize String (not added yet)
- **Tasks in fixed order:** a hashmap of next allowed time.
