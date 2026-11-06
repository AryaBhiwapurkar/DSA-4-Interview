---
number: 502
title: IPO
difficulty: Hard
topic: Heap / Priority Queue
pattern: Sort by capital + max-heap
link: https://leetcode.com/problems/ipo/
lists: [LC Top Interview 150]
followup_of: []
related: ["0630 Course Schedule III", "0857 Minimum Cost to Hire K Workers", "1834 Single-Threaded CPU"]
---

# 0502. IPO

## ⚡ 30-Second Summary
**Pattern:** Sort by requirement, then a max-heap of everything currently affordable
**Key insight:** Capital only grows (profits are non-negative), so a project that's affordable now stays affordable. Sort projects by required capital; each round, push every newly affordable project's profit into a max-heap and take the best one.
**Go-to:** Sort + max-heap, O(n log n + k log n) time, O(n) space

## Problem
You start with capital w and may complete at most k distinct projects. Project i needs capital[i] to start and adds profits[i] to your capital when done (capital isn't spent). Return the maximum final capital. [LeetCode](https://leetcode.com/problems/ipo/)

**Examples:**
```
Input:  k = 2, w = 0, profits = [1,2,3], capital = [0,1,1]
Output: 4
Why:    Only project 0 is affordable: w = 1. Then 1 and 2 are affordable; take
        profit 3: w = 4.

Input:  k = 3, w = 0, profits = [1,2,3], capital = [0,1,2]
Output: 6
Why:    0 → w 1, then 1 → w 3, then 2 → w 6.
```

**Constraints:**
- 1 ≤ k ≤ 10⁵, n ≤ 10⁵; profits ≥ 0 (that's why greedy works).

## Hints
<details><summary>Hint 1</summary>
Among the projects you can afford right now, which one should you do?
</details>
<details><summary>Hint 2</summary>
The most profitable one: it never hurts, since capital only increases. How do you find it fast every round?
</details>
<details><summary>Hint 3</summary>
Sort by capital. Pointer i over the sorted list; each round push all projects with capital ≤ w into a max-heap of profits, then pop the top (stop if the heap is empty).
</details>

## Clarifying Questions
- Is capital consumed when starting a project? (No, it's only a threshold.)
- Can profits be negative? (No.)
- Stop early if nothing is affordable? (Yes.)

## Example Walkthrough
Example 1 sorted by capital: (0,1), (1,2), (1,3). Round 1: w=0 → push 1 → take 1, w=1. Round 2: push 2, 3 → take 3, w = 4.

## Approaches

### 1. Rescan Each Round: O(k · n) time, O(n) space
Each round, scan all unused projects for the best affordable profit.

### 2. Sort + Max-Heap ⭐ Go-to: O(n log n + k log n) time, O(n) space
**Why it's the go-to:** each project enters the heap once; greedy is provably optimal because capital never decreases.

## Dry Run (Approach 2)
`k = 3, w = 0`, sorted (capital, profit): (0,1), (1,2), (2,3)

| round | pushed (cap ≤ w) | heap | take | w |
|-------|------------------|------|------|---|
| 1 | (0,1) | 1 | 1 | 1 |
| 2 | (1,2) | 2 | 2 | 3 |
| 3 | (2,3) | 3 | 3 | **6** |

## Edge Case Check
- Nothing affordable at the start: the heap is empty, return w. ✅
- k larger than the number of projects: stops when the heap runs dry. ✅

## ⚠️ Pitfalls
- **Not stopping on an empty heap**: popping an empty heap crashes.
- **Sorting profits and capital separately**: keep them paired.
- **Python max-heap**: push negated profits.

## 🎯 What the Interviewer Wants
- Justify greedy: non-negative profits make "best affordable now" always safe.
- The sort + pointer + heap structure, with complexity.

## Follow-ups
- **Deadline scheduling with a heap:** LC 0630 Course Schedule III (not added yet)
- **Process jobs by arrival with a heap:** LC 1834 Single-Threaded CPU (not added yet)
- **Pick k items minimizing a ratio-based cost:** LC 0857 Minimum Cost to Hire K Workers (not added yet)
