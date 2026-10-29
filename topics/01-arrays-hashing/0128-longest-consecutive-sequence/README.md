---
number: 128
title: Longest Consecutive Sequence
difficulty: Medium
topic: Arrays & Hashing
pattern: Hash set, start-of-run
link: https://leetcode.com/problems/longest-consecutive-sequence/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0217 Contains Duplicate", "0298 Binary Tree Longest Consecutive Sequence", "0684 Redundant Connection"]
---

# 0128. Longest Consecutive Sequence

## ⚡ 30-Second Summary
**Pattern:** Hash set, count only from the start of each run
**Key insight:** x starts a run only if x-1 is NOT in the set. Count upward only from starts, so every number is visited at most twice overall.
**Go-to:** Hash set + start-of-run, O(n) time, O(n) space

## Problem
Given an unsorted integer array, return the length of the longest run of consecutive integers (values x, x+1, x+2, ...) that can be formed from its elements. Must run in O(n).

**Examples:**
```
Input:  nums = [100,4,200,1,3,2]
Output: 4
Why:    1, 2, 3, 4 are all present.

Input:  nums = [0,3,7,2,5,8,4,6,0,1]
Output: 9
Why:    0 through 8 are all present (the duplicate 0 doesn't matter).

Input:  nums = [1,0,1,2]
Output: 3
Why:    0, 1, 2; duplicates don't extend the run.
```

**Constraints:**
- 0 ≤ n ≤ 10⁵ (empty input → 0).
- -10⁹ ≤ nums[i] ≤ 10⁹, so no counting array.
- O(n) time required, which rules out sorting.

## Hints
<details><summary>Hint 1</summary>
Sorting makes runs easy to see, but it's O(n log n). What gives O(1) "is x present?" checks?
</details>
<details><summary>Hint 2</summary>
If you count upward from every number, you redo the same run many times. Which numbers should you count from?
</details>
<details><summary>Hint 3</summary>
Only count from x when x-1 is not in the set. Then walk x+1, x+2, ... while present.
</details>

## Clarifying Questions
- Can the array be empty? (Yes, return 0.)
- Duplicates? (Yes; they don't count twice.)
- Must elements be adjacent in the array? (No, any order.)
- Is O(n) strictly required? (Yes here.)

## Example Walkthrough
`nums = [100,4,200,1,3,2]`, set = {100, 4, 200, 1, 3, 2}
- 100: 99 absent, start. 101 absent. Length 1.
- 4: 3 present, not a start. Skip.
- 200: start, length 1.
- 1: 0 absent, start. 2, 3, 4 present, 5 absent. Length 4.
- 3, 2: not starts. Best = 4.

## Approaches

### 1. Sort + Scan: O(n log n) time, O(1) extra space
Sort, then walk: +1 gap extends the run, equal value is skipped, anything else resets. Doesn't meet the O(n) requirement but is a good first answer.

### 2. Hash Set, Start-of-Run ⭐ Go-to: O(n) time, O(n) space
Put everything in a set. For each value that has no predecessor, count up while the next value is present.
**Why it's the go-to:** it's the required O(n) and only a few lines. Each element is touched once as a start check and at most once inside a run.

## Dry Run (Approach 2)
`nums = [0,3,7,2,5,8,4,6,0,1]`, set = {0..8}

| x | x-1 in set? | action | run length | best |
|---|-------------|--------|------------|------|
| 0 | no | count 0..8 | 9 | 9 |
| 3 | yes | skip | - | 9 |
| 7 | yes | skip | - | 9 |
| ... | yes | skip | - | 9 |

(Iterate over the set, not the array, so the duplicate 0 is checked once.)

## Edge Case Check
- Empty array: loop never runs, 0. ✅
- All duplicates, `[5,5,5]`: set {5}, answer 1. ✅
- Negatives, `[-1,0,1]`: works the same, 3. ✅
- Extreme value 10⁹: x+1 doesn't overflow a 32-bit int (max ≈ 2.1·10⁹). ✅

## ⚠️ Pitfalls
- **Counting from every element** (no start check) is O(n²) on a long run.
- **Iterating the array instead of the set** re-checks duplicates; on `[1,1,1,...,2,3,...]` style inputs that's wasted work. Iterate the set.
- **Sort version with duplicates:** equal neighbours must neither break nor extend the run.
- **C++ `unordered_set` worst case** can degrade on adversarial hashes; mention it if asked, not a concern here.

## 🎯 What the Interviewer Wants
- Sorting first, then the O(n) set idea.
- The start-of-run trick and the amortized argument for why it's O(n).
- Duplicate and empty-input handling.

## Follow-ups
- **Return the sequence itself:** remember the start of the best run.
- **Union-Find alternative:** union x with x+1 when both are present; answer = largest component. Same O(n·α(n)).
- **Longest consecutive path in a binary tree:** LC 0298 Binary Tree Longest Consecutive Sequence (not added yet)
