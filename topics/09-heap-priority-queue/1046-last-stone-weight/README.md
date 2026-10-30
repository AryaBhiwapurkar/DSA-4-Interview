---
number: 1046
title: Last Stone Weight
difficulty: Easy
topic: Heap / Priority Queue
pattern: Max-heap simulation
link: https://leetcode.com/problems/last-stone-weight/
lists: [NeetCode 150]
followup_of: []
related: ["1049 Last Stone Weight II", "0215 Kth Largest Element in an Array"]
---

# 1046. Last Stone Weight

## ⚡ 30-Second Summary
**Pattern:** Max-heap simulation
**Key insight:** Each round needs the two heaviest stones. A max-heap gives both in O(log n), and the leftover (if any) goes back in.
**Go-to:** Max-heap, O(n log n) time, O(n) space

## Problem
Each turn, smash the two heaviest stones x ≤ y: if equal, both are destroyed; otherwise a stone of weight y - x remains. Return the weight of the last stone, or 0 if none remain.

**Examples:**
```
Input:  stones = [2,7,4,1,8,1]
Output: 1
Why:    8,7 → 1; then 4,2 → 2; 2,1 → 1; 1,1 → 0; one stone of weight 1 remains.

Input:  stones = [1]
Output: 1
Why:    Nothing to smash.
```

**Constraints:**
- 1 ≤ n ≤ 30; weights 1..1000 (tiny, but the heap is the intended tool).

## Hints
<details><summary>Hint 1</summary>
Each round you need the two largest. What structure gives the max repeatedly?
</details>
<details><summary>Hint 2</summary>
What happens to the remainder?
</details>
<details><summary>Hint 3</summary>
Max-heap; pop y, pop x; if y > x push y - x. Return the top or 0.
</details>

## Clarifying Questions
- Return 0 when all stones are destroyed? (Yes.)

## Example Walkthrough
[2,7,4,1,8,1]: 8,7 → push 1; heap {4,2,1,1,1}. 4,2 → push 2; {2,1,1,1}. 2,1 → push 1; {1,1,1}. 1,1 → nothing; {1}. Answer 1.

## Approaches

### 1. Sort Every Round: O(n² log n) time, O(1) extra
Sort, take the last two, put back the difference, repeat.

### 2. Max-Heap ⭐ Go-to: O(n log n) time, O(n) space
**Why it's the go-to:** each round is O(log n); the canonical heap simulation.

## Dry Run (Approach 2)
`[2,2]`

| pop y | pop x | y - x | heap after |
|-------|-------|-------|------------|
| 2 | 2 | 0 (both destroyed) | {} |
| result | | | **0** |

## Edge Case Check
- One stone: returned as is. ✅
- All destroyed: 0. ✅

## ⚠️ Pitfalls
- **Python heapq is a min-heap**: push negatives.
- **Go container/heap**: `Less` must use `>` for a max-heap.
- **Pushing 0** when stones are equal: harmless but wasteful; skip it.

## 🎯 What the Interviewer Wants
- Max-heap usage in your language, including the Python negation trick.

## Follow-ups
- **Minimize the final weight with any order:** subset-sum DP: LC 1049 Last Stone Weight II (not added yet)
- **k-th largest with a heap:** [LC 0215 Kth Largest Element in an Array](../0215-kth-largest-element-in-an-array/)
